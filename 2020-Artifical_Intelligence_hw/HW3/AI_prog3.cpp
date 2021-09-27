#include<bits/stdc++.h>
#include <cmath>
using namespace std;
#define MAXSIDE 30
#define pbp pair<bool,pair<int,int> >
#define pii pair<int,int>
#define X first
#define Y second

int BOARD_SIZE_X;
int BOARD_SIZE_Y;
int MINES;

vector <pair<int,int> > init_safe;
//KB的資料型態 -- 單一條件句 裡面存有BOOL值以及對應的位置
//和所有的條件句
struct _KB{
    vector<pbp> single_literal;
    vector<vector<pbp> > literal;
};
_KB KB;

//KB0儲存這格是有沒有地雷
struct _KB0{
    vector<pii> safe;
    vector<pii> mined;
};
_KB0 KB0;

//判斷是不是在有效範圍
bool isValid(int x, int y){
    return (x >= 0) && (x < BOARD_SIZE_X) &&
		(y >= 0) && (y < BOARD_SIZE_Y);
}

//判斷是不是地雷 地雷的true 安全=false
bool isMine(int x, int y, char board[][MAXSIDE]){
    if(board[x][y] == '*')
        return true;
    else
        return false;

}

//印出現在的棋盤
void printBoard(char board[][MAXSIDE]){
    cout << endl;
    cout << "     ";
    for(int i = 0; i < BOARD_SIZE_Y; i++){
        cout << i << " ";
        if(i < 10) cout << " ";
    }
    cout << endl;
    cout << endl;
    for(int i = 0; i < BOARD_SIZE_X; i++){
        if(i < 10) cout << " ";
        cout << i << "   ";
        for(int j = 0; j < BOARD_SIZE_Y; j++){
            cout << board[i][j] << " ";
            cout << " ";
        }
        cout << endl;
    }
}


void resolution_KB0(vector<pbp> &clause){
    for(int i = 0; i < KB0.safe.size(); i++){
        for(int j = 0; j < clause.size(); j++){
            if(KB0.safe[i].X == clause[j].second.X && KB0.safe[i].Y == clause[j].second.Y){//same position
                if(clause[j].first == true){//opposite sign clause說他有地雷 但已經知道沒有了 則刪除
                    auto k = find(begin(clause), end(clause), clause[j]);
                    clause.erase(k);
                }
                else{//same sign vector = 0
                    clause.clear();
                }
            }
        }
    }
    for(int i = 0; i < KB0.mined.size(); i++){
        for(int j = 0; j < clause.size(); j++){
            if(KB0.mined[i].X == clause[j].second.X && KB0.mined[i].Y == clause[j].second.Y){//same position
                if(clause[j].first == false){//opposite sign
                    auto k = find(begin(clause), end(clause), clause[j]);
                    clause.erase(k);
                }
                else{
                    clause.clear();
                }

            }
        }
    }
}

bool subsumption(vector<pbp> &clause){//0 insert, 1 skip
     for(int i = 0; i < KB.single_literal.size(); i++){
        for(int j = 0; j < clause.size(); j++){
            if(clause[j].second.X == KB.single_literal[i].second.X && clause[j].second.Y == KB.single_literal[i].second.Y){
                if(clause[j].first == KB.single_literal[i].first){//if existing clause is stricter or identical
                    return true;
                }
            }
        }
    }

    for(int i = 0; i < KB.literal.size(); i++){
        int cnt = 0;

        for(int j = 0; j < KB.literal[i].size(); j++){
            for(int k = 0; k < clause.size(); k++){
                if(clause[k].second.X == KB.literal[i][j].second.X && clause[k].second.Y == KB.literal[i][j].second.Y){
                    if(clause[k].first == KB.literal[i][j].first)
                        cnt++;
                }
            }
        }
        if(KB.literal[i].size() == clause.size()){
            if(cnt == clause.size()){//identical clause
                return true;
            }
        }
        if(cnt == clause.size()){//if new sentence is stricter
            auto k = find(begin(KB.literal), end(KB.literal), KB.literal[i]);
            KB.literal.erase(k);//delete existing
        }
        if(cnt == KB.literal[i].size()){//if existing clause is stricter
            return true;
        }
    }
    return false;//if no existing stricter than new sentence
}

bool compare(int a, int b){
    if(a>b) return true;
    else return false;
}

void generatingClauses(int x, int y, int hint, char playerBoard[][MAXSIDE]){
    int mines = hint;
    int unmarked = 0;
    vector<pii> list_unmarked;
    for(int i = x-1; i <= x+1; i++){
        for(int j = y-1; j <= y+1; j++){
            if(isValid(i, j)){
                if(playerBoard[i][j] == '-'){
                    unmarked++;
                    pii pos = make_pair(i,j);
                    list_unmarked.push_back(pos);
                }
                else if(playerBoard[i][j] == '*'){
                    mines--;
                }
            }
        }
    }

    if(mines == unmarked){
        // Insert the m single-literal positive clauses to the KB, one for each unmarked cell.
        for(int i = x-1; i <= x+1; i++){
            for(int j = y-1; j <= y+1; j++){
                if(isValid(i, j)){
                    if(playerBoard[i][j] == '-'){
                        pii pos = make_pair(i, j);
                        pbp clause = make_pair(true, pos);
                        vector<pbp> clauses;
                        clauses.push_back(clause);
                        resolution_KB0(clauses);
                        if(subsumption(clauses) == false && clauses.size())
                            KB.single_literal.push_back(clause);
                    }
                }
            }
        }
        return;
    }
    if(mines == 0){
        // Insert the m single-literal negative clauses to the KB, one for each unmarked cell.
        for(int i = x-1; i <= x+1; i++){
            for(int j = y-1; j <= y+1; j++){
                if(isValid(i, j)){
                    if(playerBoard[i][j] == '-'){
                        pii pos = make_pair(i, j);
                        pbp clause = make_pair(false, pos);
                        vector<pbp> clauses;
                        clauses.push_back(clause);
                        resolution_KB0(clauses);
                        if(subsumption(clauses) == false && clauses.size())
                            KB.single_literal.push_back(clause);
                    }
                }
            }
        }
        return;
    }
    if(unmarked > mines){
        // C(m, m-n+1) clauses, each having m-n+1 positive literals
        vector<pbp> clauses;
        vector<int> combination(unmarked, 0);
        for(int i = 0; i < (unmarked-mines+1); i++){
            combination[i] = 1;
        }

        for(int i = 0; i < combination.size(); i++){
            if(combination[i] == 1){
                pii pos = list_unmarked[i];
                pbp clause = make_pair(true, pos);
                clauses.push_back(clause);
            }
        }
        resolution_KB0(clauses);
        if(subsumption(clauses) == false && clauses.size()){
            if(clauses.size() == 1)
                KB.single_literal.push_back(clauses[0]);
            else
                KB.literal.push_back(clauses);
        }

        for(int i = 0; i < unmarked - 1; i++){
            clauses.clear();
            if(combination[i] == 1 && combination[i+1] == 0){
                swap(combination[i], combination[i+1]);
                sort(combination.begin(), combination.begin()+i, compare);
                for(int i = 0; i < combination.size(); i++){
                    if(combination[i] == 1){
                        pii pos = list_unmarked[i];
                        pbp clause = make_pair(true, pos);
                        clauses.push_back(clause);
                    }
                }
                resolution_KB0(clauses);
                if(subsumption(clauses) == false && clauses.size()){
                    if(clauses.size() == 1)
                        KB.single_literal.push_back(clauses[0]);
                    else
                        KB.literal.push_back(clauses);
                }
                i=-1;
            }
        }
        clauses.clear();

        // C(m, n+1) clauses, each having n+1 negative literals
        for(int i = 0; i < unmarked; i++){
            if(i < (mines+1))
                combination[i] = 1;
            else
                combination[i] = 0;
        }

        for(int i = 0; i < combination.size(); i++){
            if(combination[i] == 1){
                pii pos = list_unmarked[i];
                pbp clause = make_pair(false, pos);
                clauses.push_back(clause);
            }
        }
        resolution_KB0(clauses);
        if(subsumption(clauses) == false && clauses.size()){
            if(clauses.size() == 1)
                KB.single_literal.push_back(clauses[0]);
            else
                KB.literal.push_back(clauses);
        }

        for(int i = 0; i < unmarked - 1; i++){
            clauses.clear();
            if(combination[i] == 1 && combination[i+1] == 0){
                swap(combination[i], combination[i+1]);
                sort(combination.begin(), combination.begin()+i, compare);
                for(int i = 0; i < combination.size(); i++){
                    if(combination[i] == 1){
                        pii pos = list_unmarked[i];
                        pbp clause = make_pair(false, pos);
                        clauses.push_back(clause);
                    }
                }
                resolution_KB0(clauses);
                if(subsumption(clauses) == false && clauses.size()){
                    if(clauses.size() == 1)
                        KB.single_literal.push_back(clauses[0]);
                    else
                        KB.literal.push_back(clauses);
                }
                i=-1;
            }
        }
    }
/*
// global constraint
    if(KB0.mined.size() == (MINES-2)){
        mines = MINES - KB0.mined.size();
        unmarked = 0;
        for(int i = 0; i < BOARD_SIZE_X; i++){
            for(int j = 0; j < BOARD_SIZE_Y; j++){
                if(playerBoard[i][j] == '-')
                        unmarked++;
            }
        }
        if(mines == unmarked){
        // Insert the m single-literal positive clauses to the KB, one for each unmarked cell.

        }
        if(mines == 0){
            // Insert the m single-literal negative clauses to the KB, one for each unmarked cell.

        }
        if(unmarked > mines){
            // C(m, m-n+1) clauses, each having m-n+1 positive literals
            // C(m, n+1) clauses, each having n+1 negative literals
        }
    }
*/
}

int getHint(int x, int y, char realBoard[][MAXSIDE]){
    int cnt = 0;
    for(int i = x-1; i <= x+1; i++){
        for(int j = y-1; j <= y+1; j++){
            if(isValid(i, j)){
                if(isMine(i, j, realBoard)){
                    cnt++;
                }
            }
        }
    }
    return cnt;
}

void playMinesweeper(char realBoard[][MAXSIDE], char playerBoard[][MAXSIDE]){
    while(init_safe.size()){
        pii pos = init_safe.back();
        init_safe.pop_back();
        pbp clause = make_pair(false, pos);
        KB.single_literal.push_back(clause);
    }
    while(KB.single_literal.size() || KB.literal.size()){
        cout << "================================================================================================================\n";
        cout << "KB.single_literal: " << KB.single_literal.size() << endl;
        cout << "KB.literal:        " << KB.literal.size() << endl;
        cout << endl;
        cout << "realBoard:\n";
        printBoard(realBoard);
        cout << "playerBoard\n";
        printBoard(playerBoard);

        cout << "KB:\n";
        for(int i = 0; i < KB.single_literal.size(); i++){
            if(KB.single_literal[i].first == false) cout << " !";
            else cout << "  ";
            cout << "(" << KB.single_literal[i].second.X << "," << KB.single_literal[i].second.Y << ") ";
            cout << endl;
        }
        for(int i = 0; i < KB.literal.size(); i++){
            for(int j = 0; j < KB.literal[i].size(); j++){
                if(KB.literal[i][j].first == false) cout << " !";
                else cout << "  ";
                cout  << "(" << KB.literal[i][j].second.X << "," << KB.literal[i][j].second.Y << ") ";
                if(j != KB.literal[i].size()-1) cout << "v";
            }
            cout << endl;
        }
        cout << endl;

        cout << "KB0:\n";
        cout << "mined\n";
        for(int i = 0; i < KB0.mined.size(); i++){
            cout << "(" << KB0.mined[i].X << "," << KB0.mined[i].Y << ") , ";
        }
        cout << "\nsafe\n";
        for(int i = 0; i < KB0.safe.size(); i++){
            cout << "(" << KB0.safe[i].X << "," << KB0.safe[i].Y << ") , ";
        }
        cout << endl;

        if(KB.single_literal.size()){//If there is a single-lateral clause in the KB (if there are several, just pick one):
            bool sign = KB.single_literal.back().first;
            pii pos = KB.single_literal.back().second;
            vector<pbp> clauses;
            clauses.push_back(KB.single_literal.back());
            KB.single_literal.pop_back();

            if(sign){//if is mined
                playerBoard[pos.X][pos.Y] = '*';//Mark that cell mined.
                KB0.mined.push_back(pos);//Move that clause to KB0.
            }
            else{
                int h = getHint(pos.X, pos.Y, realBoard);
                playerBoard[pos.X][pos.Y] = h + '0';
                KB0.safe.push_back(pos);
            }

            if(subsumption(clauses) == true){//Check for duplication or subsumption first. Keep only the more strict clause.
            }
            for(int i = 0; i < KB.literal.size(); i++){//matching
                int cnt = 0;
                for(int j = 0; j < KB.literal[i].size(); j++){
                    if(pos.X == KB.literal[i][j].second.X && pos.Y == KB.literal[i][j].second.Y && sign != KB.literal[i][j].first)
                        cnt++;
                }
                if(cnt == 1){//If new clauses are generated due to resolution, insert them into the KB.
                    for(int j = 0; j < KB.literal[i].size(); j++){
                        if(pos.X == KB.literal[i][j].second.X && pos.Y == KB.literal[i][j].second.Y && sign != KB.literal[i][j].first){
                            auto k = find(begin(KB.literal[i]), end(KB.literal[i]), KB.literal[i][j]);
                            KB.literal[i].erase(k);
                            if(KB.literal[i].size() == 1){
                                pbp clause = KB.literal[i][0];
                                auto l = find(begin(KB.literal), end(KB.literal), KB.literal[i]);
                                KB.literal.erase(l);
                                vector<pbp> clauses;
                                clauses.push_back(clause);
                                resolution_KB0(clauses);
                                if(subsumption(clauses) == false && clauses.size()){
                                    KB.single_literal.push_back(clause);
                                }
                            }
                        }
                    }
                }
            }

            if(!sign){//If this cell is safe:
                int hint = getHint(pos.X, pos.Y, realBoard);//Query the game control module for the hint at that cell.
                generatingClauses(pos.X, pos.Y, hint, playerBoard);//Insert the clauses regarding its unmarked neighbors into the KB.
            }
        }
        else{//Otherwise:
            //Apply pairwise "matching" of the clauses in the KB.
            for(int k = 0; k < KB.literal.size(); k++){
                if(KB.literal[k].size() > 2) //only match clause pairs where one clause has only at most two literals.
                    continue;
                bool sign0 = KB.literal[k][0].first;
                pii pos0 = KB.literal[k][0].second;
                bool sign1 = KB.literal[k][1].first;
                pii pos1 = KB.literal[k][1].second;
                for(int i = 0; i < KB.literal.size(); i++){
                    int cnt = 0;
                    if(i == k) continue;
                    for(int j = 0; j < KB.literal[i].size(); j++){
                        if(pos0.X == KB.literal[i][j].second.X && pos0.Y == KB.literal[i][j].second.Y && sign0 != KB.literal[i][j].first)
                            cnt++;
                        if(pos1.X == KB.literal[i][j].second.X && pos1.Y == KB.literal[i][j].second.Y && sign1 != KB.literal[i][j].first)
                            cnt++;
                    }
                    if(cnt == 1){
                        cout << "at most two literal:\n";//DEBUG
                        if(sign0) cout << " ";
                        else cout << "!";
                        cout << " (" << pos0.X << "," << pos0.Y << ") v ";
                        if(sign1) cout << " ";
                        else cout << "!";
                        cout <<"(" << pos1.X << "," << pos1.Y << ")\n";
                        for(int j = 0; j < KB.literal[i].size(); j++){
                            if(KB.literal[i][j].first == false) cout << " !";
                            else cout << "  ";
                            cout  << "(" << KB.literal[i][j].second.X << "," << KB.literal[i][j].second.Y << ") ";
                            if(j != KB.literal[i].size()-1) cout << "v";
                        }
                        cout << endl;
                        //If new clauses are generated by resolution, insert them into the KB.
                        vector<pbp> clauses;
                        for(int j = 0; j < KB.literal[i].size(); j++){
                            if(pos0.X == KB.literal[i][j].second.X && pos0.Y == KB.literal[i][j].second.Y && sign0 != KB.literal[i][j].first){
                                auto k = find(begin(KB.literal[i]), end(KB.literal[i]), KB.literal[i][j]);
                                KB.literal[i].erase(k);
                                pbp clause = make_pair(sign1, pos1);
                                KB.literal[i].push_back(clause);
                                clauses = KB.literal[i];
                                auto l = find(begin(KB.literal), end(KB.literal), KB.literal[i]);
                                KB.literal.erase(l);

                                cout << "Resolution:";//DEBUG
                                for(int m = 0; m < clauses.size(); m++){
                                    if(clauses[m].first == false) cout << " !";
                                    else cout << "  ";
                                    cout  << "(" << clauses[m].second.X << "," << clauses[m].second.Y << ") ";
                                    if(m != clauses.size()-1) cout << "v";
                                }
                                cout << endl;
                                resolution_KB0(clauses);
                                if(subsumption(clauses) == false && clauses.size()){
                                    if(clauses.size() == 1)
                                        KB.single_literal.push_back(clauses[0]);
                                    else
                                        KB.literal.push_back(clauses);
                                }
                            }

                            else if(pos1.X == KB.literal[i][j].second.X && pos1.Y == KB.literal[i][j].second.Y && sign1 != KB.literal[i][j].first){
                                auto k = find(begin(KB.literal[i]), end(KB.literal[i]), KB.literal[i][j]);
                                KB.literal[i].erase(k);
                                pbp clause = make_pair(sign0, pos0);
                                KB.literal[i].push_back(clause);
                                clauses = KB.literal[i];
                                auto l = find(begin(KB.literal), end(KB.literal), KB.literal[i]);
                                KB.literal.erase(l);

                                cout << "Resolution:";//DEBUG
                                for(int m = 0; m < clauses.size(); m++){
                                    if(clauses[m].first == false) cout << " !";
                                    else cout << "  ";
                                    cout  << "(" << clauses[m].second.X << "," << clauses[m].second.Y << ") ";
                                    if(m != clauses.size()-1) cout << "v";
                                }
                                cout << endl;
                                resolution_KB0(clauses);
                                if(subsumption(clauses) == false && clauses.size()){
                                    if(clauses.size() == 1)
                                        KB.single_literal.push_back(clauses[0]);
                                    else
                                        KB.literal.push_back(clauses);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout <<"================================================================================================================\n";
    cout << "realBoard:\n";
    printBoard(realBoard);
    cout << "playerBoard\n";
    printBoard(playerBoard);
    cout << "Success!\n";
}

void game_generate(int level, char realBoard[][MAXSIDE], char playerBoard[][MAXSIDE]){
    if(level == 1){
        BOARD_SIZE_X = 9;
        BOARD_SIZE_Y = 9;
        MINES = 10;
    }
    else if(level == 2){
        BOARD_SIZE_X = 16;
        BOARD_SIZE_Y = 16;
        MINES = 25;
    }
    else if(level == 3){
        BOARD_SIZE_X = 16;
        BOARD_SIZE_Y = 30;
        MINES = 99;
    }
    else{
        cout << "Please enter 1 or 2 or 3\n";
        return;
    }

    srand(time(NULL));
    for(int i = 0; i < BOARD_SIZE_X; i++){
        for(int j = 0; j < BOARD_SIZE_Y; j++){
            realBoard[i][j] = playerBoard[i][j] = '-';
        }
    }

    int initialSafe = round(sqrt(BOARD_SIZE_X*BOARD_SIZE_Y));
    for(int i = 0; i < MINES;){
        int random = rand() % (BOARD_SIZE_X*BOARD_SIZE_Y);
        int x = random / BOARD_SIZE_X;
        int y = random % BOARD_SIZE_Y;

        if(realBoard[x][y] == '-'){
            realBoard[x][y] = '*';
            i++;
        }
    }
    for(int i = 0; i < initialSafe;){
        int random = rand() % (BOARD_SIZE_X*BOARD_SIZE_Y);
        int x = random / BOARD_SIZE_X;
        int y = random % BOARD_SIZE_Y;

        if(realBoard[x][y] == '-'){
            pair<int,int> pos = make_pair(x, y);
            init_safe.push_back(pos);
            i++;
        }
    }

    printBoard(realBoard);
    //printBoard(playerBoard);
}

int main(){
    int level;
    while(1){
        cout << "\nChoose difficulty level\n";
        cout << "Press 1 for Easy   ( 9 *  9 board with 10 mines)\n";
        cout << "Press 2 for Medium (16 * 16 board with 25 mines)\n";
        cout << "Press 3 for Hard   (30 * 16 board with 99 mines)\n";
        cin >> level;
        char realBoard[MAXSIDE][MAXSIDE];
        char playerBoard[MAXSIDE][MAXSIDE];
        game_generate(level, realBoard, playerBoard);
        playMinesweeper(realBoard, playerBoard);
    }
    return 0;
}
