#include <iostream>
#include <queue>
#include <math.h>
#include <algorithm>
using namespace std;

//節點的結構
struct node {
    int cur,x,y,step;
    node *pre;
};
void BFS(int s,int s1,int g,int g1,int step){
    //先做一NODE把起始點存入
    node *start=new node;
    start->x=s;
    start->y=s1;
    start->step=0;

    //TABLE用來檢查下一個準備要做的點有沒有走過，走過代表有人更早就走過了，沒必要再做一次
    vector<node> table;

    //用來存還剩下要做的NODE
    queue<node> memory;
    memory.push(*start);
    while(memory.front().x!=g || memory.front().y!=g1){
        int x1,y1;
        node *parent = new node;
        *parent=memory.front();
        table.push_back(memory.front());
        memory.pop();
        /*----------------------------方向1----------------------------*/
        node *next = new node;
        next->x=parent->x+1;
        next->y=parent->y+2;
        next->pre=parent;
        next->step=parent->step+1;

        int check=0;
        if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
            check=1;
        }
        if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
            check=1;
        }
        for(int i=0;i<table.size();i++){
            if(next->x==table[i].x && next->y==table[i].y){
                check=1;
                break;
            }
        }
        if(check==0){
            memory.push(*next);
        }
        /*----------------------------方向2----------------------------*/
        next->x=parent->x+1;
        next->y=parent->y-2;
        next->pre=parent;
        for(int i=0;i<table.size();i++){
            if(next->x==table[i].x && next->y==table[i].y){
                check=1;
                break;
            }
        }
        if(check==0){
            memory.push(*next);
        }
        check=0;
        if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
            check=1;
        }
        /*----------------------------方向3----------------------------*/
        next->x=parent->x+2;
        next->y=parent->y+1;
        next->pre=parent;
        for(int i=0;i<table.size();i++){
            if(next->x==table[i].x && next->y==table[i].y){
                check=1;
                break;
            }
        }
        if(check==0){
            memory.push(*next);
        }
        check=0;
        if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
            check=1;
        }
        /*---------------------------方向4-----------------------------*/
        next->x=parent->x+2;
        next->y=parent->y-1;
        next->pre=parent;
        for(int i=0;i<table.size();i++){
            if(next->x==table[i].x && next->y==table[i].y){
                check=1;
                break;
            }
        }
        if(check==0){
            memory.push(*next);
        }
        check=0;
        if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
            check=1;
        }
        /*--------------------------方向5------------------------------*/
        next->x=parent->x-1;
        next->y=parent->y+2;
        next->pre=parent;
        for(int i=0;i<table.size();i++){
            if(next->x==table[i].x && next->y==table[i].y){
                check=1;
                break;
            }
        }
        if(check==0){
            memory.push(*next);
        }
        check=0;
        if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
            check=1;
        }
        /*-------------------------方向6-------------------------------*/
        next->x=parent->x-1;
        next->y=parent->y-2;
        next->pre=parent;
        for(int i=0;i<table.size();i++){
            if(next->x==table[i].x && next->y==table[i].y){
                check=1;
                break;
            }
        }
        if(check==0){
            memory.push(*next);
        }
        check=0;
        if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
            check=1;
        }
        /*-------------------------方向7-------------------------------*/
        next->x=parent->x-2;
        next->y=parent->y+1;
        next->pre=parent;
        for(int i=0;i<table.size();i++){
            if(next->x==table[i].x && next->y==table[i].y){
                check=1;
                break;
            }
        }
        if(check==0){
            memory.push(*next);
        }
        check=0;
        if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
            check=1;
        }
        /*------------------------方向8--------------------------------*/
        next->x=parent->x-2;
        next->y=parent->y-1;
        next->pre=parent;
        check=0;
        if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
            check=1;
        }
        for(int i=0;i<table.size();i++){
            if(next->x==table[i].x && next->y==table[i].y){
                check=1;
                break;
            }
        }
        if(check==0){
            memory.push(*next);
        }

    }
    node result;
    result=memory.front();
    cout <<endl<<"Steps:"<< memory.front().step << endl;
    while(result.pre){
        cout << "( " <<  result.x << "," << result.y<<" )"<<endl;
        result=*result.pre;
    }
    cout << "( " <<  result.x << "," << result.y<<" )"<<endl;

}
int ans=0;
vector<node> path;
int DFS(int s,int s1,int g,int g1,int step){
    if(ans==1){
        return 0;
    }
    node *start=new node;
    start->x=s;
    start->y=s1;
    start->step=step;

    path.push_back(*start);

    node *next =new node;
    next->x=start->x+1;
    next->y=start->y+2;
    next->pre=start;
    next->step=step+1;

    //下面的if 判斷有沒有解和超出邊界，else if判斷是不是到了 else 進入下一層
    if(next->x >8 || next->x<0 || next->y >8 || next->y <0 || ans==1){
    }
    else if(next->x==g && next->y==g1){
        ans=1;
        cout << "Steps : "<<next->step <<endl;
    }
    else{
        int check=0;
        for(int i=0;i<path.size();i++){
            if(next->x==path[i].x && next->y==path[i].y){
                check=1;
                break;
            }
        }
            if(check==0){
                DFS(next->x,next->y,g,g1,next->step);
        }
    }


    next->x=start->x+1;
    next->y=start->y-2;
    next->pre=start;
    next->step=step+1;

    if(next->x >8 || next->x<0 || next->y >8 || next->y <0 || ans==1){
    }
    else if(next->x==g && next->y==g1){
        ans=1;
        cout << "Steps : "<<next->step <<endl;
    }
    else{
        int check=0;
        //cout << 2 <<endl;
        for(int i=0;i<path.size();i++){
            if(next->x==path[i].x && next->y==path[i].y){
                check=1;
                break;
            }
        }
            if(check==0){
                DFS(next->x,next->y,g,g1,next->step);
        }
    }

    next->x=start->x+2;
    next->y=start->y+1;
    next->pre=start;
    next->step=step+1;

    if(next->x >8 || next->x<0 || next->y >8 || next->y <0 || ans==1){
    }
    else if(next->x==g && next->y==g1){
        ans=1;
        cout << "Steps : "<<next->step <<endl;
    }
    else{
        int check=0;
        //cout << 3 <<endl;
        for(int i=0;i<path.size();i++){
            if(next->x==path[i].x && next->y==path[i].y){
                check=1;
                break;
            }
        }
            if(check==0){
                DFS(next->x,next->y,g,g1,next->step);
        }
    }

    next->x=start->x+2;
    next->y=start->y-1;
    next->pre=start;
    next->step=step+1;

    if(next->x >8 || next->x<0 || next->y >8 || next->y <0 || ans==1){
    }
    else if(next->x==g && next->y==g1){
        ans=1;
        cout << "Steps : "<<next->step <<endl;
    }
    else{
        int check=0;
        //cout << 4 <<endl;
        for(int i=0;i<path.size();i++){
            if(next->x==path[i].x && next->y==path[i].y){
                check=1;
                break;
            }
        }
            if(check==0){
                DFS(next->x,next->y,g,g1,next->step);
        }
    }

    next->x=start->x-1;
    next->y=start->y+2;
    next->pre=start;
    next->step=step+1;

    if(next->x >8 || next->x<0 || next->y >8 || next->y <0 || ans==1){
    }
    else if(next->x==g && next->y==g1){
        ans=1;
        cout << "Steps : "<<next->step <<endl;
    }
    else{
        int check=0;
        //cout << 5 <<endl;
        for(int i=0;i<path.size();i++){
            if(next->x==path[i].x && next->y==path[i].y){
                check=1;
                break;
            }
        }
            if(check==0){
                DFS(next->x,next->y,g,g1,next->step);
        }
    }

    next->x=start->x-1;
    next->y=start->y-2;
    next->pre=start;
    next->step=step+1;

    if(next->x >8 || next->x<0 || next->y >8 || next->y <0 || ans==1){
    }
    else if(next->x==g && next->y==g1){
        ans=1;
        cout << "Steps : "<<next->step <<endl;
    }
    else{
        int check=0;
        //cout << 6 <<endl;
        for(int i=0;i<path.size();i++){
            if(next->x==path[i].x && next->y==path[i].y){
                check=1;
                break;
            }
        }
            if(check==0){
                DFS(next->x,next->y,g,g1,next->step);
        }
    }

    next->x=start->x-2;
    next->y=start->y+1;
    next->pre=start;
    next->step=step+1;

    if(next->x >8 || next->x<0 || next->y >8 || next->y <0 || ans==1){
    }
    else if(next->x==g && next->y==g1){
        ans=1;
        cout << "Steps : "<<next->step <<endl;
    }
    else{
        int check=0;
        //cout << 7 <<endl;
        for(int i=0;i<path.size();i++){
            if(next->x==path[i].x && next->y==path[i].y){
                check=1;
                break;
            }
        }
            if(check==0){
                DFS(next->x,next->y,g,g1,next->step);
        }
    }

    next->x=start->x-2;
    next->y=start->y-2;
    next->pre=start;
    next->step=step+1;

    if(next->x >8 || next->x<0 || next->y >8 || next->y <0 || ans==1){
    }
    else if(next->x==g && next->y==g1){
        ans=1;
        cout << "Steps : "<<next->step <<endl;
    }
    else{
        int check=0;
        //cout << 8 <<endl;
        for(int i=0;i<path.size();i++){
            if(next->x==path[i].x && next->y==path[i].y){
                check=1;
                break;
            }
        }
            if(check==0){
                DFS(next->x,next->y,g,g1,next->step);
        }
    }
    return 0;
}

int IDS_ans=0;
vector<node> IDS_path;
int IDS(int s,int s1,int g,int g1,int step,int level){
    node *start=new node;
    start->x=s;
    start->y=s1;
    start->step=0;

    vector<node> table;

    queue<node> memory;
    memory.push(*start);
    while(memory.front().x!=g || memory.front().y!=g1){
        int x1,y1;
        node *parent = new node;
        *parent=memory.front();
        table.push_back(memory.front());
        memory.pop();
        node *next = new node;
        next->x=parent->x+1;
        next->y=parent->y+2;
        next->pre=parent;
        next->step=parent->step+1;

        int check=0;
        if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
            check=1;
        }
        if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
            check=1;
        }
        for(int i=0;i<table.size();i++){
            if(next->x==table[i].x && next->y==table[i].y){
                check=1;
                break;
            }
        }
        if(check==0){
            memory.push(*next);
        }
        next->x=parent->x+1;
        next->y=parent->y-2;
        next->pre=parent;
        for(int i=0;i<table.size();i++){
            if(next->x==table[i].x && next->y==table[i].y){
                check=1;
                break;
            }
        }
        if(check==0){
            memory.push(*next);
        }
        check=0;
        if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
            check=1;
        }
        next->x=parent->x+2;
        next->y=parent->y+1;
        next->pre=parent;
        for(int i=0;i<table.size();i++){
            if(next->x==table[i].x && next->y==table[i].y){
                check=1;
                break;
            }
        }
        if(check==0){
            memory.push(*next);
        }
        check=0;
        if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
            check=1;
        }
        next->x=parent->x+2;
        next->y=parent->y-1;
        next->pre=parent;
        for(int i=0;i<table.size();i++){
            if(next->x==table[i].x && next->y==table[i].y){
                check=1;
                break;
            }
        }
        if(check==0){
            memory.push(*next);
        }
        check=0;
        if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
            check=1;
        }
        next->x=parent->x-1;
        next->y=parent->y+2;
        next->pre=parent;
        for(int i=0;i<table.size();i++){
            if(next->x==table[i].x && next->y==table[i].y){
                check=1;
                break;
            }
        }
        if(check==0){
            memory.push(*next);
        }
        check=0;
        if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
            check=1;
        }
        next->x=parent->x-1;
        next->y=parent->y-2;
        next->pre=parent;
        for(int i=0;i<table.size();i++){
            if(next->x==table[i].x && next->y==table[i].y){
                check=1;
                break;
            }
        }
        if(check==0){
            memory.push(*next);
        }
        check=0;
        if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
            check=1;
        }
        next->x=parent->x-2;
        next->y=parent->y+1;
        next->pre=parent;
        for(int i=0;i<table.size();i++){
            if(next->x==table[i].x && next->y==table[i].y){
                check=1;
                break;
            }
        }
        if(check==0){
            memory.push(*next);
        }
        check=0;
        if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
            check=1;
        }
        next->x=parent->x-2;
        next->y=parent->y-1;
        next->pre=parent;
        check=0;
        if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
            check=1;
        }
        for(int i=0;i<table.size();i++){
            if(next->x==table[i].x && next->y==table[i].y){
                check=1;
                break;
            }
        }
        if(check==0){
            memory.push(*next);
        }

    }
    node result;
    result=memory.front();
    cout <<endl<<"Steps:"<< memory.front().step << endl;
    while(result.pre){
        cout << "( " <<  result.x << "," << result.y<<" )"<<endl;
        result=*result.pre;
    }
    cout << "( " <<  result.x << "," << result.y<<" )"<<endl;

}

int A(int s,int s1,int g,int g1,int step){
    node *start=new node;
    start->x=s;
    start->y=s1;
    start->step=0;

    vector<node> table;

    queue<node> memory;
    memory.push(*start);
    while(memory.front().x!=g || memory.front().y!=g1){
        node *parent = new node;
        *parent=memory.front();
        table.push_back(memory.front());
        memory.pop();

        int x1[8],y1[8];
        float heuristic_number[8];
        x1[0]=memory.front().x+1;
        x1[1]=memory.front().x+1;
        x1[2]=memory.front().x+2;
        x1[3]=memory.front().x+2;
        x1[4]=memory.front().x-1;
        x1[5]=memory.front().x-1;
        x1[6]=memory.front().x-2;
        x1[7]=memory.front().x-2;
        y1[0]=memory.front().y+2;
        y1[1]=memory.front().y-2;
        y1[2]=memory.front().y+1;
        y1[3]=memory.front().y-1;
        y1[4]=memory.front().y+2;
        y1[5]=memory.front().y-2;
        y1[6]=memory.front().y+1;
        y1[7]=memory.front().y-1;
        for(int i=0;i<8;i++){
            heuristic_number[i]=(abs(g-x1[i])+abs(g1-y1[i]))/3;
        }
        sort(heuristic_number,heuristic_number+8);
        node *next = new node;
        for(int i=0;i<8;i++){
            if((abs(g-x1[0])+abs(g1-y1[0]))/3==heuristic_number[i]){
                next->x=parent->x+1;
                next->y=parent->y+2;
                next->pre=parent;
                next->step=parent->step+1;

                int check=0;
                if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
                    check=1;
                }
                for(int i=0;i<table.size();i++){
                    if(next->x==table[i].x && next->y==table[i].y){
                        check=1;
                        break;
                    }
                }
                if(check==0){
                    memory.push(*next);
                }
            }
            else if((abs(g-x1[1])+abs(g1-y1[1]))/3==heuristic_number[i]){
                next->x=parent->x+1;
                next->y=parent->y-2;
                next->pre=parent;
                next->step=parent->step+1;

                int check=0;
                if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
                    check=1;
                }
                for(int i=0;i<table.size();i++){
                    if(next->x==table[i].x && next->y==table[i].y){
                        check=1;
                        break;
                    }
                }
                if(check==0){
                    memory.push(*next);
                }
            }
            else if((abs(g-x1[2])+abs(g1-y1[2]))/3==heuristic_number[i]){
                next->x=parent->x+2;
                next->y=parent->y+1;
                next->pre=parent;
                next->step=parent->step+1;

                int check=0;
                if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
                    check=1;
                }
                for(int i=0;i<table.size();i++){
                    if(next->x==table[i].x && next->y==table[i].y){
                        check=1;
                        break;
                    }
                }
                if(check==0){
                    memory.push(*next);
                }
            }
            else if((abs(g-x1[3])+abs(g1-y1[3]))/3==heuristic_number[i]){
                next->x=parent->x+2;
                next->y=parent->y-1;
                next->pre=parent;
                next->step=parent->step+1;

                int check=0;
                if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
                    check=1;
                }
                for(int i=0;i<table.size();i++){
                    if(next->x==table[i].x && next->y==table[i].y){
                        check=1;
                        break;
                    }
                }
                if(check==0){
                    memory.push(*next);
                }
            }
            else if((abs(g-x1[4])+abs(g1-y1[4]))/3==heuristic_number[i]){
                next->x=parent->x-1;
                next->y=parent->y+2;
                next->pre=parent;
                next->step=parent->step+1;

                int check=0;
                if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
                    check=1;
                }
                for(int i=0;i<table.size();i++){
                    if(next->x==table[i].x && next->y==table[i].y){
                        check=1;
                        break;
                    }
                }
                if(check==0){
                    memory.push(*next);
                }
            }
            else if((abs(g-x1[5])+abs(g1-y1[5]))/3==heuristic_number[i]){
                next->x=parent->x-1;
                next->y=parent->y-2;
                next->pre=parent;
                next->step=parent->step+1;

                int check=0;
                if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
                    check=1;
                }
                for(int i=0;i<table.size();i++){
                    if(next->x==table[i].x && next->y==table[i].y){
                        check=1;
                        break;
                    }
                }
                if(check==0){
                    memory.push(*next);
                }
            }
            else if((abs(g-x1[6])+abs(g1-y1[6]))/3==heuristic_number[i]){
                next->x=parent->x-2;
                next->y=parent->y+1;
                next->pre=parent;
                next->step=parent->step+1;

                int check=0;
                if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
                    check=1;
                }
                for(int i=0;i<table.size();i++){
                    if(next->x==table[i].x && next->y==table[i].y){
                        check=1;
                        break;
                    }
                }
                if(check==0){
                    memory.push(*next);
                }
            }
            else if((abs(g-x1[7])+abs(g1-y1[7]))/3==heuristic_number[i]){
                next->x=parent->x-2;
                next->y=parent->y-1;
                next->pre=parent;
                next->step=parent->step+1;

                int check=0;
                if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
                    check=1;
                }
                for(int i=0;i<table.size();i++){
                    if(next->x==table[i].x && next->y==table[i].y){
                        check=1;
                        break;
                    }
                }
                if(check==0){
                    memory.push(*next);
                }
            }
        }
    }
    node result;
    result=memory.front();
    cout <<endl<<"Steps:"<< memory.front().step << endl;
    while(result.pre){
        cout << "( " <<  result.x << "," << result.y<<" )"<<endl;
        result=*result.pre;
    }
    cout << "( " <<  result.x << "," << result.y<<" )"<<endl;
}

int solution=0;
int IDA(int s,int s1,int g,int g1,int step,int level){
    node *start=new node;
    start->x=s;
    start->y=s1;
    start->step=0;
    cout << "level : "<<level <<endl;
    vector<node> table;
    cout << "times"<<endl;
    queue<node> memory;
    memory.push(*start);
    while(memory.front().x!=g || memory.front().y!=g1){
        node *parent = new node;
        *parent=memory.front();
        table.push_back(memory.front());
        memory.pop();
        cout << "run" <<endl;
        int increase=0;
        int x1[8],y1[8];
        double heuristic_number[8];
        x1[0]=memory.front().x+1;
        x1[1]=memory.front().x+1;
        x1[2]=memory.front().x+2;
        x1[3]=memory.front().x+2;
        x1[4]=memory.front().x-1;
        x1[5]=memory.front().x-1;
        x1[6]=memory.front().x-2;
        x1[7]=memory.front().x-2;
        y1[0]=memory.front().y+2;
        y1[1]=memory.front().y-2;
        y1[2]=memory.front().y+1;
        y1[3]=memory.front().y-1;
        y1[4]=memory.front().y+2;
        y1[5]=memory.front().y-2;
        y1[6]=memory.front().y+1;
        y1[7]=memory.front().y-1;
        for(int i=0;i<8;i++){
            heuristic_number[i]=(abs(g-x1[i])+abs(g1-y1[i]))/3.0;
        }
        sort(heuristic_number,heuristic_number+8);
        node *next = new node;
        for(int i=0;i<8;i++){
            if((abs(g-x1[0])+abs(g1-y1[0]))/3.0==heuristic_number[i]){
                next->x=parent->x+1;
                next->y=parent->y+2;
                next->pre=parent;
                next->step=parent->step+1;

                int check=0;
                if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
                    check=1;
                }
                for(int i=0;i<table.size();i++){
                    if(next->x==table[i].x && next->y==table[i].y){
                        check=1;
                        break;
                    }
                }
                if(check==0&&next->step<=level){
                    memory.push(*next);
                    increase++;
                    cout << "add1"<<endl;
                }
            }
            else if((abs(g-x1[1])+abs(g1-y1[1]))/3.0==heuristic_number[i]){
                next->x=parent->x+1;
                next->y=parent->y-2;
                next->pre=parent;
                next->step=parent->step+1;

                int check=0;
                if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
                    check=1;
                }
                for(int i=0;i<table.size();i++){
                    if(next->x==table[i].x && next->y==table[i].y){
                        check=1;
                        break;
                    }
                }
                if(check==0&&next->step<=level){
                    memory.push(*next);
                    increase++;
                    cout << "add2"<<endl;
                }
            }
            else if((abs(g-x1[2])+abs(g1-y1[2]))/3.0==heuristic_number[i]){
                next->x=parent->x+2;
                next->y=parent->y+1;
                next->pre=parent;
                next->step=parent->step+1;

                int check=0;
                if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
                    check=1;
                }
                for(int i=0;i<table.size();i++){
                    if(next->x==table[i].x && next->y==table[i].y){
                        check=1;
                        break;
                    }
                }
                if(check==0&&next->step<=level){
                    increase++;
                    cout << "add3"<<endl;
                    memory.push(*next);
                }
            }
            else if((abs(g-x1[3])+abs(g1-y1[3]))/3.0==heuristic_number[i]){
                next->x=parent->x+2;
                next->y=parent->y-1;
                next->pre=parent;
                next->step=parent->step+1;

                int check=0;
                if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
                    check=1;
                }
                for(int i=0;i<table.size();i++){
                    if(next->x==table[i].x && next->y==table[i].y){
                        check=1;
                        break;
                    }
                }
                if(check==0&&next->step<=level){
                    increase++;
                    cout << "add4"<<endl;
                    memory.push(*next);
                }
            }
            else if((abs(g-x1[4])+abs(g1-y1[4]))/3.0==heuristic_number[i]){
                next->x=parent->x-1;
                next->y=parent->y+2;
                next->pre=parent;
                next->step=parent->step+1;

                int check=0;
                if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
                    check=1;
                }
                for(int i=0;i<table.size();i++){
                    if(next->x==table[i].x && next->y==table[i].y){
                        check=1;
                        break;
                    }
                }
                if(check==0&&next->step<=level){
                    increase++;
                    cout << "add5"<<endl;
                    memory.push(*next);
                }
            }
            else if((abs(g-x1[5])+abs(g1-y1[5]))/3.0==heuristic_number[i]){
                next->x=parent->x-1;
                next->y=parent->y-2;
                next->pre=parent;
                next->step=parent->step+1;

                int check=0;
                if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
                    check=1;
                }
                for(int i=0;i<table.size();i++){
                    if(next->x==table[i].x && next->y==table[i].y){
                        check=1;
                        break;
                    }
                }
                if(check==0&&next->step<=level){
                    increase++;
                    cout << "add6"<<endl;
                    memory.push(*next);
                }
            }
            else if((abs(g-x1[6])+abs(g1-y1[6]))/3.0==heuristic_number[i]){
                next->x=parent->x-2;
                next->y=parent->y+1;
                next->pre=parent;
                next->step=parent->step+1;

                int check=0;
                if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
                    check=1;
                }
                for(int i=0;i<table.size();i++){
                    if(next->x==table[i].x && next->y==table[i].y){
                        check=1;
                        break;
                    }
                }
                if(check==0&&next->step<=level){
                    increase++;
                    cout << "add7"<<endl;
                    memory.push(*next);
                }
            }
            else if((abs(g-x1[7])+abs(g1-y1[7]))/3.0==heuristic_number[i]){
                next->x=parent->x-2;
                next->y=parent->y-1;
                next->pre=parent;
                next->step=parent->step+1;

                int check=0;
                if(next->x >8 || next->x<0 || next->y >8 || next->y <0){
                    check=1;
                }
                for(int i=0;i<table.size();i++){
                    if(next->x==table[i].x && next->y==table[i].y){
                        check=1;
                        break;
                    }
                }
                if(check==0&&next->step<=level){
                    cout << "add8"<<endl;
                    increase++;
                    memory.push(*next);
                }
            }


        }
        cout <<memory.front().x << memory.front().y<<endl;
        if(memory.front().x==s&&memory.front().y==s1){
            cout<<"break"<<endl;
            break;
        }
    }
    if(memory.front().x==g && memory.front().y==g1){
        node result;
        result=memory.front();
        cout <<endl<<"Steps:"<< memory.front().step << endl;
        while(result.pre){
            cout << "( " <<  result.x << "," << result.y<<" )"<<endl;
            result=*result.pre;
        }
        solution=1;
        cout << "( " <<  result.x << "," << result.y<<" )"<<endl;
    }
    else{
        return 0;
    }
}
int main(){
    int type;
    cout << "Enter algorithm (1.BFS 2.DFS 3.IDS 4.A* 5.IDA*) : ";
    cin >> type;
    int start[2],goal[2];
    cout << "Enter start point (form :_ _) : ";
    cin >> start[0] >> start[1];
    cout << "Enter goal point (form :_ _) : ";
    cin >> goal[0] >> goal[1];
    //cout <<start[0] << start[1] << goal[0] << goal[1];
    int i=0;
    switch(type){
        case 1:
            BFS(start[0],start[1],goal[0],goal[1],0);
            break;
        case 2:
            DFS(start[0],start[1],goal[0],goal[1],0);
            break;
        case 3:
            IDS(start[0],start[1],goal[0],goal[1],0,0);
            break;
        case 4:
            A(start[0],start[1],goal[0],goal[1],0);
            break;
        case 5:
            IDA(start[0],start[1],goal[0],goal[1],0,0);
            while(solution==0){
                i++;
                IDA(start[0],start[1],goal[0],goal[1],0,i);
            }
            break;
        default:
            break;
    }
    return 0;
}

