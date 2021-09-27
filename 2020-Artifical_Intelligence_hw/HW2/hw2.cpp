#include <iostream>
#include <queue>
#include <math.h>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;



//還剩下的問題
//1.沒有完全符合每個constraint
//  可能有一個constraint = 1 但最後附近沒有地雷
//
//
//
//
//
//
struct node {
    int r_domain[36];    //每個格子剩下的domain 如果有一格不是原來的0.1 則表示已assign
    bool map[36];               //36格中已assign的值
    int boom_board[36];
    int b_degree[36];
    int choose_board[36];
    int num_boom;
    int now_boom;
    int deep;
    int already_back;
    int num_constraint;
    bool zero_pop;
};
struct board{
    int domain[36];
    int board[36];
    int degree[36];
};

void boomalogorithm(node *start){
    //進到函式
    cout << endl << "boom!" << endl;

    ////印出開始節點r_domain
    cout << "domain:";
    for(int i=0;i<36;i++){
        if(i%6==0){
            cout <<endl;
        }
        cout << start->r_domain[i]<<" ";
    }
    cout << endl;

    //印出開始節點以assign值
    cout << "assign:";
    for(int i=0;i<36;i++){
        if(i%6==0){
            cout <<endl;
        }
        cout << start->map[i]<<" ";
    }
    cout << endl;

    //印出board
    cout << "board:";
    for(int i=0;i<36;i++){
        if(i%6==0){
            cout <<endl;
        }
        cout << start->boom_board[i]<<" ";
    }
    cout << endl;

    //印出degree
    cout << "b_degree:";
    for(int i=0;i<36;i++){
        if(i%6==0){
            cout <<endl;
        }
        cout << start->b_degree[i]<<" ";
    }
    cout << endl;

    //建立stack
    stack<node> s;
    cout <<endl<< "stack top: "<<endl;
    s.push(*start);
    char result[36];
    int end_condition=0;
    int back_check=0;

    while(end_condition==0){
        if(back_check==1){
            s.top().already_back+=1;
            back_check=0;
        }
        int  pop_already=0;
        cout << "now board-----------------------------"<<endl;
        cout << "deep : "<<s.top().deep<<endl;
        for(int i=0;i<36;i++){
            if(i%6==0){
                cout <<endl;
            }
            if(s.top().choose_board[i]==100){
                cout <<"* ";
            }
            else if(s.top().choose_board[i]==99){
                cout <<"_ ";
            }
            else if(s.top().choose_board[i]==98){
                cout <<"/ ";
            }
            else{
                cout << s.top().choose_board[i]<<" ";
            }
        }
        cout << endl;
        //correct 檢查是否所有限制都剛好符合
        int correct=0;
            //check local constraint
        for(int i=0; i<36 ; i++){
            int check=0;
            int find_constraint=0;
            //cout << s.top().boom_board[i] << endl;
            if(s.top().boom_board[i]!=-1){
                find_constraint=1;
                if(i%6!=0 && i-6>0){
                    if(s.top().boom_board[i-7]==-1 && s.top().r_domain[i-7]!=2)
                    check+=s.top().r_domain[i-7];
                }
                if(i-6>0){
                    if(s.top().boom_board[i-6]==-1 && s.top().r_domain[i-6]!=2)
                    check+=s.top().r_domain[i-6];
                }
                if(i%6!=5 && i-6>0){
                    if(s.top().boom_board[i-5]==-1 && s.top().r_domain[i-5]!=2)
                    check+=s.top().r_domain[i-5];
                }
                if(i%6!=0){
                    if(s.top().boom_board[i-1]==-1 && s.top().r_domain[i-1]!=2)
                    check+=s.top().r_domain[i-1];
                }
                if(i%6!=5){
                    if(s.top().boom_board[i+1]==-1 && s.top().r_domain[i+1]!=2)
                    check+=s.top().r_domain[i+1];
                }
                if(i%6!=0 && i<30){
                    if(s.top().boom_board[i+5]==-1 && s.top().r_domain[i+5]!=2)
                    check+=s.top().r_domain[i+5];
                }
                if(i<30){
                    if(s.top().boom_board[i+6]==-1 && s.top().r_domain[i+6]!=2)
                    check+=s.top().r_domain[i+6];
                }
                if(i%6!=5 && i<30){
                    if(s.top().boom_board[i+7]==-1 && s.top().r_domain[i+7]!=2)
                    check+=s.top().r_domain[i+7];
                }
            }
            if(check==s.top().boom_board[i]&&find_constraint==1){
                    correct++;
            }
            if(check>s.top().boom_board[i] && find_constraint==1&&pop_already==0){
                pop_already=1;
                if(s.top().zero_pop==false){
                    s.pop();
                    s.top().already_back+=1;
                    s.top().zero_pop=true;
                }
                cout << "pop more boom than constraint"<<endl;
                break;
            }
        }
        //check global constraint
        int global=0;
        for(int i=0;i<36;i++){
            if(s.top().map[i]==true){
                global++;
            }
        }
        if(global==36){
            if(correct==s.top().num_constraint){
                end_condition=1;
                cout << "pop less boom than a constraint" <<endl;
                break;
            }
            else{
                if(pop_already==0){
                    pop_already=1;
                    cout << "pop less boom than a constraint" <<endl;
                    s.pop();
                }
            }
        }
        if(s.top().now_boom==s.top().num_boom){
            if(correct==s.top().num_constraint){
                cout << "boom enough _" << correct << endl;
                end_condition=1;
                break;
            }
            else{
                pop_already=1;
                cout << "pop boom"<<endl;
                s.pop();
            }
        }
        //找出Degree heuristic 中包含最多constraint的
        int max_constraint=0;
        int locate=0;
        for(int i=0;i<36;i++){
            if(max_constraint<s.top().b_degree[i]){
                max_constraint=s.top().b_degree[i];
                locate=i;
            }
        }
        //cout << max_constraint <<" " << locate <<endl;

        node *next = new node;
        //先放選出的位置不是炸彈的　（　先放會後做　）
        cout << "before push board:";
        for(int i=0;i<36;i++){
            if(i%6==0){
                cout <<endl;
            }
            if(s.top().choose_board[i]==100){
                cout <<"* ";
            }
            else if(s.top().choose_board[i]==99){
                cout <<"_ ";
            }
            else if(s.top().choose_board[i]==98){
                cout <<"/ ";
            }
            else{
                cout << s.top().choose_board[i]<<" ";
            }
        }
        cout << endl;
        cout << endl;
        cout <<endl<< "degree : ";
        int zero=0;
        for(int i=0;i<36;i++){
            if(s.top().b_degree[i]==0){
                zero++;
            }
            if(i%6==0){
                cout <<endl;
            }
            cout << s.top().b_degree[i] << " ";
        }
        cout << endl;
        if(zero==36){
            cout << "------------------------------------------------------------------------------------------------"<<endl;
            cout << "deep : " << s.top().deep;
            cout << "------------------------------------------------------------------------------------------------"<<endl;
            while(s.top().deep!=s.top().already_back+1){
                s.pop();
            }
            s.pop();
            pop_already=1;
            back_check=1;
            cout << "pop zero" <<endl;
        }

        if(pop_already==0){
        next->num_boom=s.top().num_boom;
        next->now_boom=s.top().now_boom;
        next->num_constraint=s.top().num_constraint;
        next->already_back=s.top().already_back;
        next->deep=s.top().deep+=1;
        for(int i=0;i<36;i++){
            next->b_degree[i]=s.top().b_degree[i];
            next->r_domain[i]=s.top().r_domain[i];
            next->boom_board[i]=s.top().boom_board[i];
            next->choose_board[i]=s.top().choose_board[i];
            if(s.top().r_domain[i]==9){
                next->map[i]=true;
            }
            else{
                next->map[i]=false;
            }
        }
        next->b_degree[locate]=0;
        next->r_domain[locate]=0;
        next->map[locate]=true;
        next->choose_board[locate]=98;
        s.push(*next);
        cout << "next board1";
        cout << endl <<"deep : "<< next->deep << endl;
        for(int i=0;i<36;i++){
            if(i%6==0){
                cout <<endl;
            }
            if(s.top().choose_board[i]==100){
                cout <<"* ";
            }
            else if(s.top().choose_board[i]==99){
                cout <<"_ ";
            }
            else if(s.top().choose_board[i]==98){
                cout <<"/ ";
            }
            else{
                cout << s.top().choose_board[i]<<" ";
            }
        }
        cout << endl;
        //再放選出的位置為炸彈　（　會在stack的上層　）
        next->num_boom=s.top().num_boom;
        next->now_boom=s.top().now_boom+1;
        next->num_constraint=s.top().num_constraint;
        next->deep=s.top().deep;
        next->already_back=s.top().already_back;
        for(int i=0;i<36;i++){
            next->b_degree[i]=s.top().b_degree[i];
            next->r_domain[i]=s.top().r_domain[i];
            next->boom_board[i]=s.top().boom_board[i];
            next->choose_board[i]=s.top().choose_board[i];
            if(s.top().r_domain[i]==9){
                next->map[i]=true;
            }
            else{
                next->map[i]=false;
            }
        }
        next->b_degree[locate]=0;
        next->r_domain[locate]=1;
        next->map[locate]=true;
        next->choose_board[locate]=100;

        s.push(*next);
        cout << "next board2";
        cout << endl <<"deep : "<<next->deep << endl;
        for(int i=0;i<36;i++){
            if(i%6==0){
                cout <<endl;
            }
            if(s.top().choose_board[i]==100){
                cout <<"* ";
            }
            else if(s.top().choose_board[i]==99){
                cout <<"_ ";
            }
            else if(s.top().choose_board[i]==98){
                cout <<"/ ";
            }
            else{
                cout << s.top().choose_board[i]<<" ";
            }
        }
        cout << endl;
        }
    }

    //while 結束
    for(int i=0;i<36;i++){
        if(i%6==0){
            cout <<endl;
        }
        if(s.top().choose_board[i]==100){
            cout <<"* ";
        }
        else if(s.top().choose_board[i]==99){
            cout <<"_ ";
        }
        else if(s.top().choose_board[i]==98){
            cout <<"/ ";
        }
        else{
            cout << s.top().choose_board[i]<<" ";
        }
    }
    cout << endl;
}

int main(){
    int width;
    int height;
    int booms;
    int board[36];

    cin >> width >> height >> booms;
    for(int i=0;i<width * height;i++){
        cin >>  board[i];
    }

    for(int i=0;i<width * height;i++){
         if(i%6==0){
            cout <<endl;
        }
        cout << board[i]<<" ";
    }
    cout << endl;

    //全域限制
    //區域限制
    int degree[36];
    int domain[36];

    //初始化
    for(int i=0;i<width * height;i++){
        degree[i]=0;
        domain[i]=0;
    }

    //算出degree 和 初始化domain
    for(int i=0;i<width*height;i++){
        if(board[i]!=-1){
            domain[i]=9;
            if(i%6!=0 && i-6>0){
                if(board[i-7]==-1)
                degree[i-7]+=1;
            }
            if(i-6>0){
                if(board[i-6]==-1)
                degree[i-6]+=1;
            }
            if(i%6!=5 && i-6>0){
                if(board[i-5]==-1)
                degree[i-5]+=1;
            }
            if(i%6!=0){
                if(board[i-1]==-1)
                degree[i-1]+=1;
            }
            if(i%6!=5){
                if(board[i+1]==-1)
                degree[i+1]+=1;
            }
            if(i%6!=0 && i<30){
                if(board[i+5]==-1)
                degree[i+5]+=1;
            }
            if(i<30){
                if(board[i+6]==-1)
                degree[i+6]+=1;
            }
            if(i%6!=5 && i<30){
                if(board[i+7]==-1)
                degree[i+7]+=1;
            }
        }
        else{
            domain[i]=2;
        }
    }
    //
    //印出degree
    for(int i=0;i<width*height;i++){
        if(i%6==0){
            cout <<endl;
        }
        cout << degree[i]<<" ";
    }
    cout << endl;

    /*
    //印出domain
    for(int i=0;i<width*height;i++){
        if(i%6==0){
            cout <<endl;
        }
        cout << domain[i]<<" ";
    }
    cout << endl;
*/
    int count=0;
    //初始化開始節點
    node *start=new node;
    start->num_boom=booms;
    start->now_boom=0;
    start->deep=0;
    start->zero_pop=false;
    start->already_back=0;
    for(int i=0;i<36;i++){
        start->b_degree[i]=degree[i];
        start->r_domain[i]=domain[i];
        start->boom_board[i]=board[i];
        if(board[i]==-1){
            start->choose_board[i]=99;
        }
        else{
            start->choose_board[i]=board[i];
        }
        if(domain[i]==9){
                count++;
            start->map[i]=true;
        }
        else{
            start->map[i]=false;
        }
    }
    start->num_constraint=count;

 /*
    //印出開始節點r_domain
    for(int i=0;i<36;i++){
        if(i%6==0){
            cout <<endl;
        }
        cout << start->r_domain[i]<<" ";
    }
    cout << endl;

    //印出開始節點以assign值
    for(int i=0;i<36;i++){
        if(i%6==0){
            cout <<endl;
        }
        cout << start->map[i]<<" ";
    }
    cout << endl;
*/
    boomalogorithm(start);
    return 0;
}


