#include<bits/stdc++.h>
using namespace std;
//用pair來合併兩組資料　裡面放（是不是地雷, 位置）　vector來儲存所有pair資料　
#define clause pair<bool,pair<int,int>>
#define position pair<int,int>
//X代表 pair的第一項 Y代表 pair的第二項
#define X first
#define Y second

//棋盤的全域變數
int BOARD_HEIGHT_X;
int BOARD_WIDTH_Y;
int BOOMS;

struct Board{
    int width;
    int height;
    int booms;
    vector<position> locate;
};

struct KnowledgeBase{
    vector<vector<clause>> sentence;
};
KnowledgeBase KB;

struct KnowledgeBase0{
    vector<position> safe;
    vector<position> mined;
};
KnowledgeBase0 KB0;

vector<pair<int,int>> Init_Safe_Hint;

//生成一開始的棋盤
void generate_board(int level, char game_board[][30], char play_board[][30],char hint_board[][30]){
    if(level == 1){
        BOARD_HEIGHT_X = 9;
        BOARD_WIDTH_Y = 9;
        BOOMS = 10 ;
    }
    else if(level == 2){
        BOARD_HEIGHT_X = 16;
        BOARD_WIDTH_Y = 30;
        BOOMS = 25;
    }
    else if(level == 2){
        BOARD_HEIGHT_X = 16;
        BOARD_WIDTH_Y = 30;
        BOOMS = 25;
    }
    else{
        cout << "Error input ! Please input a number range in 1 to 3" << endl;
        return;
    }
    //生成棋盤

    //產生全空的板子
    for(int i=0;i<BOARD_HEIGHT_X;i++){
        for(int j=0; j<BOARD_WIDTH_Y;j++){
            game_board[i][j]='-';
            play_board[i][j]='-';
            hint_board[i][j]='-';
        }
    }
    srand(time(NULL));
    //隨機放入地雷
    for(int i=0;i<BOOMS;i++){
        int x = rand()% BOARD_HEIGHT_X;
        int y = rand()% BOARD_WIDTH_Y;
        while(game_board[x][y]!='-'){
            x = rand()% BOARD_HEIGHT_X;
            y = rand()% BOARD_WIDTH_Y;
        }
        game_board[x][y]='*';
        hint_board[x][y]='*';
    }
    /*//算出安全的地方周圍有幾個地雷
    for(int i=0;i<BOARD_HEIGHT_X;i++){
        for(int j=0;j<BOARD_WIDTH_Y;j++){
            int number_boom=0;
            if( i>0 && j>0 && game_board[i-1][j-1]=='*'){
                number_boom++;
            }
            if( i>0 && game_board[i-1][j]=='*'){
                number_boom++;
            }
            if( i>0 && j+1<BOARD_WIDTH_Y && game_board[i-1][j+1]=='*'){
                number_boom++;
            }
            if( j>0 && game_board[i][j-1]=='*'){
                number_boom++;
            }
            if( j+1<BOARD_WIDTH_Y && game_board[i][j+1]=='*'){
                number_boom++;
            }
            if( i+1<BOARD_HEIGHT_X && j>0 && game_board[i+1][j-1]=='*'){
                number_boom++;
            }
            if( i+1<BOARD_HEIGHT_X && game_board[i+1][j]=='*'){
                number_boom++;
            }
            if( i+1<BOARD_HEIGHT_X && j+1<BOARD_WIDTH_Y && game_board[i+1][j+1]=='*'){
                number_boom++;
            }
            if(game_board[i][j]!='*'){
                game_board[i][j]=number_boom+'0';
            }
        }
    */
    //隨機選定幾個安全點將位置存到pos裡，在將pos push進init_safe裡面
    int initial_hints=round(sqrt(BOARD_HEIGHT_X*BOARD_WIDTH_Y));
    for(int i=0;i<initial_hints;){
        int random = rand() % (BOARD_HEIGHT_X*BOARD_WIDTH_Y);
        int x = random / BOARD_HEIGHT_X;
        int y = random % BOARD_WIDTH_Y;
        if(game_board[x][y] != '*'){
            pair<int,int> pos = make_pair(x,y);
            Init_Safe_Hint.push_back(pos);
            i++;
        }
    }

}

//得到確定安全的座標的hint
void Hint_Board(int level, char game_board[][30],char hint_board[][30]){
    if(level == 1){
        BOARD_HEIGHT_X = 9;
        BOARD_WIDTH_Y = 9;
        BOOMS = 10 ;
    }
    else if(level == 2){
        BOARD_HEIGHT_X = 16;
        BOARD_WIDTH_Y = 30;
        BOOMS = 25;
    }
    else if(level == 2){
        BOARD_HEIGHT_X = 16;
        BOARD_WIDTH_Y = 30;
        BOOMS = 25;
    }
    //算出安全的地方周圍有幾個地雷
    for(int i=0;i<BOARD_HEIGHT_X;i++){
        for(int j=0;j<BOARD_WIDTH_Y;j++){
            int number_boom=0;
            if( i>0 && j>0 && game_board[i-1][j-1]=='*'){
                number_boom++;
            }
            if( i>0 && game_board[i-1][j]=='*'){
                number_boom++;
            }
            if( i>0 && j+1<BOARD_WIDTH_Y && game_board[i-1][j+1]=='*'){
                number_boom++;
            }
            if( j>0 && game_board[i][j-1]=='*'){
                number_boom++;
            }
            if( j+1<BOARD_WIDTH_Y && game_board[i][j+1]=='*'){
                number_boom++;
            }
            if( i+1<BOARD_HEIGHT_X && j>0 && game_board[i+1][j-1]=='*'){
                number_boom++;
            }
            if( i+1<BOARD_HEIGHT_X && game_board[i+1][j]=='*'){
                number_boom++;
            }
            if( i+1<BOARD_HEIGHT_X && j+1<BOARD_WIDTH_Y && game_board[i+1][j+1]=='*'){
                number_boom++;
            }
            if(hint_board[i][j]!='*'){
                hint_board[i][j]=number_boom+'0';
            }
        }
    }
}

//印出棋盤的座標位置
void PrintBoard(char game_board[][30]){
    cout << endl;
    cout << "     ";
    for(int i = 0; i < BOARD_WIDTH_Y; i++){
        cout << i << " ";
        if(i < 10) cout << " ";
    }
    cout << endl<<endl ;
    for(int i = 0; i < BOARD_HEIGHT_X; i++){
        if(i < 10) cout << " ";
        cout << i << "   ";
        for(int j = 0; j < BOARD_WIDTH_Y; j++){
            cout << game_board[i][j] << " ";
            cout << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool subsumption(vector<clause> temp){
    // cout << endl << "subsumption " <<endl;
    bool condition=false;
    vector<vector<clause>> newKB = KB.sentence;
    bool erase = false;
    //檢查兩個句子有多少相同
    for(int i = 0; i < KB.sentence.size(); i++){
        int number_ident = 0;
        for(int j = 0; j < KB.sentence[i].size(); j++){
            for(int k = 0; k < temp.size(); k++){
                if(temp[k].second.X == KB.sentence[i][j].second.X && temp[k].second.Y == KB.sentence[i][j].second.Y){
                    if(temp[k].first == KB.sentence[i][j].first){
                        number_ident++;
                    }
                }
            }
        }
        if(KB.sentence[i].size() == temp.size()){
            if(number_ident == temp.size()){
                //相同的sentence
                if(erase) KB.sentence = newKB;
                return true;
            }
        }
        if(condition){
            cout << "condition";
        }
        if(number_ident == temp.size()){
            cout << "\nerase " << i << endl;
            for(int j = 0; j < KB.sentence[i].size(); j++){
                if(KB.sentence[i][j].first == false) cout << " !";
                else cout << "  ";
                cout  << "(" << KB.sentence[i][j].second.X << "," << KB.sentence[i][j].second.Y << ") ";
                if(j < KB.sentence[i].size()) cout << "V";
            }
            //新的比較嚴格，刪掉舊的，將新的加入KB
            auto k = find(begin(newKB), end(newKB), KB.sentence[i]);
            newKB.erase(k);
            erase = true;
            cout << newKB.size() << endl;
        }
        if(number_ident == KB.sentence[i].size()){//如果現在的比較嚴格，刪掉新的
            if(erase) KB.sentence = newKB;
            return true;
        }
    }
    if(condition){
        cout << "condition";
    }
    if(erase) KB.sentence = newKB;
    return false;
}

//當有相同位置存在不同的bool值，可以做resolution來減少條件判斷
void resolution_KB0(vector<clause> &temp){
    bool earse=false;
    // cout << endl << "resolution" <<endl;
    for(int i = 0; i < KB0.safe.size(); i++){
        for(int j = 0; j < temp.size(); j++){
            if(KB0.safe[i].X == temp[j].second.X && KB0.safe[i].Y == temp[j].second.Y){
                if(temp[j].first == true){
                    //不同號則刪掉
                    auto k = find(begin(temp), end(temp), temp[j]);
                    temp.erase(k);
                }
                else{
                    //同號就清掉就好
                    temp.clear();
                }
            }
        }
    }
    for(int i = 0; i < KB0.mined.size(); i++){
        for(int j = 0; j < temp.size(); j++){
            if(KB0.mined[i].X == temp[j].second.X && KB0.mined[i].Y == temp[j].second.Y){//same position
                if(temp[j].first == false){//opposite sign
                    auto k = find(begin(temp), end(temp), temp[j]);
                    temp.erase(k);
                }
                else{
                    temp.clear();
                }

            }
        }
    }
}

//有提示進來的時候，需要生成新的clause，
/*
About generating clauses from the hints:
Each hint provides the following information: There are n mines in a list of m unmarked cells.
(n == m): Insert the m single-literal positive clauses to the KB, one for each unmarked cell.
(n == 0): Insert the m single-literal negative clauses to the KB, one for each unmarked cell.
(m>n>0): General cases (need to generate CNF clauses and add them to the KB):
    C(m, m-n+1) clauses, each having m-n+1 positive literals
    C(m, n+1) clauses, each having n+1 negative literals.
    For example, for m=5 and n=2, let the cells be x1, x2, …, x5:
    There are C(5,4) all-positive-literal clauses:
        (x1 V x2 V x3 V x4), (x1 V x2 V x3 V x5), …,  (x2 V x3 V x4 V x5)
    There are C(5,3) all-negative-literal clauses:
        (!x1 V !x2 V !x3), (!x1 V ! x2 V !x4), (!x1 V !x2 V !x5), …, (!x3 V !x4 V !x5)
*/

void generate_Clauses(int x, int y, int hint, char play_board[][30], char hint_board[][30]){
    bool earse=false;
    int mines = hint;
    int unmarked = 0;
    vector<position> list_unmarked;
    for(int i = x-1; i <= x+1; i++){
        for(int j = y-1; j <= y+1; j++){
            if((i >= 0) && (i < BOARD_HEIGHT_X) && (j >= 0) && (j < BOARD_WIDTH_Y)){
                if(play_board[i][j] == '-'){
                    unmarked++;
                    position pos = make_pair(i,j);
                    list_unmarked.push_back(pos);
                }
                else if(play_board[i][j] == '*'){
                    mines--;
                }
            }
        }
    }

    if(mines == unmarked){
        // Insert the m single-literal positive clauses to the KB, one for each unmarked cell.
        for(int i = x-1; i <= x+1; i++){
            for(int j = y-1; j <= y+1; j++){
                if((i >= 0) && (i < BOARD_HEIGHT_X) && (j >= 0) && (j < BOARD_WIDTH_Y)){
                    if(play_board[i][j] == '-'){
                        position pos = make_pair(i, j);
                        clause temp = make_pair(true, pos);
                        vector<clause> temp_clauses;
                        temp_clauses.push_back(temp);
                        resolution_KB0(temp_clauses);
                        if(subsumption(temp_clauses) == false && temp_clauses.size())
                            KB.sentence.push_back(temp_clauses);
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
                if((i >= 0) && (i < BOARD_HEIGHT_X) && (j >= 0) && (j < BOARD_WIDTH_Y)){
                    if(play_board[i][j] == '-'){
                        position pos = make_pair(i, j);
                        clause temp = make_pair(false, pos);
                        vector<clause> temp_clauses;
                        temp_clauses.push_back(temp);
                        resolution_KB0(temp_clauses);
                        if(subsumption(temp_clauses) == false && temp_clauses.size())
                            KB.sentence.push_back(temp_clauses);
                    }
                }
            }
        }
        return;
    }
    if(unmarked > mines){
        // C(m, m-n+1) clauses, each having m-n+1 positive literals
        vector<clause> temp_clauses;
        vector<int> combination(unmarked, 0);
        for(int i = 0; i < (unmarked-mines+1); i++){
            combination[i] = 1;
        }

        for(int i = 0; i < combination.size(); i++){
            if(combination[i] == 1){
                position pos = list_unmarked[i];
                clause temp = make_pair(true, pos);
                temp_clauses.push_back(temp);
            }
        }
        resolution_KB0(temp_clauses);
        if(subsumption(temp_clauses) == false && temp_clauses.size()){
                KB.sentence.push_back(temp_clauses);
        }
        for(int i = 0; i < unmarked - 1; i++){
            temp_clauses.clear();
            if(combination[i] == 1 && combination[i+1] == 0){
                swap(combination[i], combination[i+1]);
                sort(combination.begin(), combination.begin()+i);
                for(int i = 0; i < combination.size(); i++){
                    if(combination[i] == 1){
                        position pos = list_unmarked[i];
                        clause temp = make_pair(true, pos);
                        temp_clauses.push_back(temp);
                    }
                }
                resolution_KB0(temp_clauses);
                if(subsumption(temp_clauses) == false && temp_clauses.size()){
                        KB.sentence.push_back(temp_clauses);
                }
                i=-1;
                if(earse){
                    KB.sentence.push_back(temp_clauses);
                }
            }
        }
        temp_clauses.clear();

        // C(m, n+1) clauses, each having n+1 negative literals
        for(int i = 0; i < unmarked; i++){
            if(i < (mines+1))
                combination[i] = 1;
            else
                combination[i] = 0;
        }

        for(int i = 0; i < combination.size(); i++){
            if(combination[i] == 1){
                position pos = list_unmarked[i];
                clause temp = make_pair(false, pos);
                temp_clauses.push_back(temp);
            }
        }
        if(earse){
            KB.sentence.push_back(temp_clauses);
        }
        resolution_KB0(temp_clauses);
        if(subsumption(temp_clauses) == false && temp_clauses.size()){
                KB.sentence.push_back(temp_clauses);
        }

        for(int i = 0; i < unmarked - 1; i++){
            temp_clauses.clear();
            if(combination[i] == 1 && combination[i+1] == 0){
                swap(combination[i], combination[i+1]);
                sort(combination.begin(), combination.begin()+i);
                for(int i = 0; i < combination.size(); i++){
                    if(combination[i] == 1){
                        position pos = list_unmarked[i];
                        clause temp = make_pair(false, pos);
                        temp_clauses.push_back(temp);
                    }
                }
                resolution_KB0(temp_clauses);
                if(subsumption(temp_clauses) == false && temp_clauses.size()){
                        KB.sentence.push_back(temp_clauses);
                }
                i=-1;
                if(earse){
                    KB.sentence.push_back(temp_clauses);
                }
            }
        }
    }
}

//控制遊戲開始與結束
void GameStart(char game_board[][30], char play_board[][30],char hint_board[][30]){
    //將Init_Safe_Hint裡面所有位置(確定是沒有地雷)生成最一開始的clause
    bool game_end=false;
    //check hint_board
    cout << "Hint Board:"<<endl;
    cout << endl;
    cout << "     ";
    for(int i = 0; i < BOARD_WIDTH_Y; i++){
        cout << i << " ";
        if(i < 10) cout << " ";
    }
    cout << endl<<endl ;
    for(int i = 0; i < BOARD_HEIGHT_X; i++){
        if(i < 10) cout << " ";
        cout << i << "   ";
        for(int j = 0; j < BOARD_WIDTH_Y; j++){
            cout << hint_board[i][j] << " ";
            cout << " ";
        }
        cout << endl;
    }
    cout << endl;
    while(Init_Safe_Hint.size()){
        position pos = Init_Safe_Hint.back();
        Init_Safe_Hint.pop_back();
        clause temp = make_pair(false, pos);
        //生成一個vector裡面存一連串的clause的類型資料裡面存的是sentence，push_back() - 新增元素至 vector 的尾端，必要時會進行記憶體配置。
        vector<clause> temp_clauses;
        temp_clauses.push_back(temp);
        KB.sentence.push_back(temp_clauses);
    }
    //當KB面還有sentence (則需要繼續檢查有沒有可以做的)
    int identical=0;
    int size=0;
    int endn=0;
    while(KB.sentence.size()&& endn==0){
        if(KB.sentence.size()==size){
            identical++;
        }
        if(identical == 100){
            endn=1;
        }
        //每次都先印出現在棋盤和有的條件
        cout << "================================================================================================================\n";
        cout << endl;
        cout << "Game Board:"<<endl;
        PrintBoard(game_board);
        cout << "Play Board:"<<endl;
        PrintBoard(play_board);
        cout << endl;
        cout << "KB0:" << endl;
        cout << "Now mined position:" << endl;
        for(int i=0; i<KB0.mined.size();i++){
            cout << "(" << KB0.mined[i].X << "," << KB0.mined[i].Y << ") , ";
        }
        cout << endl;
        cout << "Now safe  position:" << endl;
        for(int i=0; i<KB0.safe.size();i++){
            cout << "(" << KB0.safe[i].X << "," << KB0.safe[i].Y << ") , ";
        }
        cout << endl<<endl;
        //檢查KB  KB[i]但代表第幾個clause [i][j]代表裡面存的位置和bool值
        cout << "KB.sentence.size:  " << KB.sentence.size() << endl<<endl;
        cout << "KB:"<<endl;
        for(int i=0;i < KB.sentence.size();i++){
            for(int j=0;j<KB.sentence[i].size(); j++){
                if(KB.sentence[i][j].first == false) cout << " !";
                else cout << "  ";
                cout << "(" << KB.sentence[i][j].second.X << "," << KB.sentence[i][j].second.Y << ") ";
                if(j < KB.sentence[i].size()) cout << "V";
            }
            cout << endl;
        }
        cout << endl;
        //如果有一個clause只有一個元素，代表可以確定她是地雷或是沒有(一次只做一個)
        //則消除這個clause 並更新play_board的值和放入KB0相應的地方
        bool single = false;
        for(int i = 0; i < KB.sentence.size(); i++){
            if(KB.sentence[i].size() == 1){
                single = true;
                bool sign = KB.sentence[i][0].first;
                position pos = KB.sentence[i][0].second;

                auto e = find(begin(KB.sentence), end(KB.sentence), KB.sentence[i]);
                KB.sentence.erase(e);

                if(sign){
                    KB0.mined.push_back(pos);
                    //標記是個地雷
                    //cout << hint_board[pos.X][pos.Y] << endl; //檢查是不是真的是地雷
                    play_board[pos.X][pos.Y] = '*';
                }
                else{
                    KB0.safe.push_back(pos);
                    //得到的提示加到play_board
                    //cout << hint_board[pos.X][pos.Y]<< endl; // 查看值
                    play_board[pos.X][pos.Y] = hint_board[pos.X][pos.Y];
                }
                //產生一個clause vector 存取這個點的clause值
                clause temp = make_pair(sign, pos);
                //產生一個可以存clause　的 vector
                vector<clause> temp_clauses;
                temp_clauses.push_back(temp);

                //檢查這個_clause會不會產生 subsumption (存在2 clause 一個是另外一個的子集合
                //會刪除較不嚴格的那個
                if(subsumption(temp_clauses)){//Check for duplication or subsumption first. Keep only the more strict clause.
                }

                bool street;
                for(int i = 0; i < KB.sentence.size(); i++){
                    for(int j = 0; j < KB.sentence[i].size(); j++){
                        if(pos.X == KB.sentence[i][j].second.X && pos.Y == KB.sentence[i][j].second.Y && sign != KB.sentence[i][j].first){
                                street = true;
                        }
                    }
                }

                //檢查這個新產生的clause會不會resolution，如果有將結果加進KB裡
                for(int i = 0; i < KB.sentence.size(); i++){
                    for(int j = 0; j < KB.sentence[i].size(); j++){

                        if(pos.X == KB.sentence[i][j].second.X && pos.Y == KB.sentence[i][j].second.Y && sign != KB.sentence[i][j].first){

                            cout << endl << endl;
                            for(int m = 0; m < KB.sentence[i].size(); m++){
                                if(KB.sentence[i][m].first == false) cout << " !";
                                else cout << "  ";
                                cout  << "(" << KB.sentence[i][m].second.X << "," << KB.sentence[i][m].second.Y << ") ";
                                if(m < KB.sentence[i].size()) cout << "V";
                            }
                            //刪除resolution 的那個條件
                            auto k = find(begin(KB.sentence[i]), end(KB.sentence[i]), KB.sentence[i][j]);
                            KB.sentence[i].erase(k);

                            vector<clause> temp_clauses = KB.sentence[i];
                            auto l = find(begin(KB.sentence), end(KB.sentence), KB.sentence[i]);
                            KB.sentence.erase(l);
                            resolution_KB0(temp_clauses);

                            for(int m = 0; m < temp_clauses.size(); m++){
                                if(temp_clauses[m].first == false) cout << " !";
                                else cout << "  ";
                                cout  << "(" << temp_clauses[m].second.X << "," << temp_clauses[m].second.Y << ") ";
                                if(m < temp_clauses.size()) cout << "v";
                            }

                            if(subsumption(temp_clauses) == false && temp_clauses.size()){
                                KB.sentence.push_back(temp_clauses);
                                cout << "sub false\n";
                            }
                        }
                    }
                }
                //如果不是地雷
                if(!sign){
                    int hint = hint_board[pos.X][pos.Y]-'0';
                    //產生根據其hint周圍地雷數相對旁邊８個格子的clauses
                    generate_Clauses(pos.X, pos.Y, hint, play_board, hint_board);
                }

                for(int i = 0; i < KB.sentence.size(); i++){
                    for(int j = 0; j < KB.sentence[i].size(); j++){
                        if(pos.X == KB.sentence[i][j].second.X && pos.Y == KB.sentence[i][j].second.Y && sign != KB.sentence[i][j].first){
                                street = true;
                        }
                    }
                }
                break;
            }
        }
        if(single) continue;
        //如果不是單一條件
        else{
            for(int k = 0; k < KB.sentence.size(); k++){
                if(KB.sentence[k].size() > 2) continue;

                bool sign0 = KB.sentence[k][0].first;
                position pos0 = KB.sentence[k][0].second;
                bool sign1 = KB.sentence[k][1].first;
                position pos1 = KB.sentence[k][1].second;

                for(int i = 0; i < KB.sentence.size(); i++){
                    int pairs = 0;
                    if(i == k) continue;
                    for(int j = 0; j < KB.sentence[i].size(); j++){
                        if(pos0.X == KB.sentence[i][j].second.X && pos0.Y == KB.sentence[i][j].second.Y && sign0 != KB.sentence[i][j].first)
                            pairs++;
                        if(pos1.X == KB.sentence[i][j].second.X && pos1.Y == KB.sentence[i][j].second.Y && sign1 != KB.sentence[i][j].first)
                            pairs++;
                    }

                    if(pairs == 1){
                        vector<clause> temp_clauses;
                        //檢查這個新產生的clause會不會resolution，如果有將結果加進KB裡
                        for(int j = 0; j < KB.sentence[i].size(); j++){
                            if(pos0.X == KB.sentence[i][j].second.X && pos0.Y == KB.sentence[i][j].second.Y && sign0 != KB.sentence[i][j].first){
                                auto m = find(begin(KB.sentence[i]), end(KB.sentence[i]), KB.sentence[i][j]);
                                KB.sentence[i].erase(m);
                                clause temp = make_pair(sign1, pos1);
                                KB.sentence[i].push_back(temp);
                                temp_clauses = KB.sentence[i];
                                auto l = find(begin(KB.sentence), end(KB.sentence), KB.sentence[i]);
                                KB.sentence.erase(l);

                                resolution_KB0(temp_clauses);
                                if(subsumption(temp_clauses) == false && temp_clauses.size())
                                        KB.sentence.push_back(temp_clauses);
                            }
                            //檢查這個新產生的clause會不會resolution，如果有將結果加進KB裡
                            else if(pos1.X == KB.sentence[i][j].second.X && pos1.Y == KB.sentence[i][j].second.Y && sign1 != KB.sentence[i][j].first){
                                auto m = find(begin(KB.sentence[i]), end(KB.sentence[i]), KB.sentence[i][j]);
                                KB.sentence[i].erase(m);
                                clause temp = make_pair(sign0, pos0);
                                KB.sentence[i].push_back(temp);
                                temp_clauses = KB.sentence[i];
                                auto l = find(begin(KB.sentence), end(KB.sentence), KB.sentence[i]);
                                KB.sentence.erase(l);

                                resolution_KB0(temp_clauses);
                                if(subsumption(temp_clauses) == false && temp_clauses.size())
                                    KB.sentence.push_back(temp_clauses);
                            }
                        }
                    }
                }
            }
        }
        size=KB.sentence.size();
    }
    cout <<"================================================================================================================\n";
    cout << "Game Board:\n";
    PrintBoard(game_board);
    cout << "Play Board\n";
    PrintBoard(play_board);
    cout << "END!\n";
}


int main(){
    int level;
    while(1){
        //初始化
        Init_Safe_Hint.clear();
        KB0.safe.clear();
        KB0.mined.clear();
        cout<<endl;
        cout<<"                                         Choose the level"<<endl;
        cout<<"================================================================================================================\n";
        cout<< "                                (1 for Easy    9 * 9  with 10 booms)" <<endl;
        cout<< "                                (2 for Medium 16 * 16 with 25 booms)" <<endl;
        cout<< "                                (3 for Hard   16 * 30 with 99 booms)" <<endl;
        cout<<"================================================================================================================\n";
        cout<< "Input Level : ";
        cin >> level;
        char game_board[30][30];
        char play_board[30][30];
        char hint_board[30][30];
        generate_board(level,game_board,play_board,hint_board);
        Hint_Board(level,game_board,hint_board);
        //PrintBoard(game_board);
        //PrintBoard(play_board);
        GameStart(game_board,play_board,hint_board);
        //Start(game_board,play_board);
    }
    return 0;
}
