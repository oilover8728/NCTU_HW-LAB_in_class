#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

void generate_board(char *board, int height, int width){
    int SquareN=height+1;
    //產生全空的板子
    for(int i=0;i<height;i++){
        for(int j=0; j<width;j++){
            *(board+i*width+j)='-';
        }
    }
    //隨機添加地雷
    for(int i=0;i<SquareN;i++){
        int x = rand()%height;
        int y = rand()%height;
        //cout << x << y <<endl;
        while(*(board+x*width+y)!='-'){
            x = rand()%height;
            y = rand()%height;
        }
        *(board+x*width+y)='*';
    }
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            int number_boom=0;
            if( i>0 && j>0 && *(board+(i-1)*width+j-1)=='*'){
                number_boom++;
                //*(board+(i-1)*width+j-1)
                //board[i-1][j-1]
            }
            if( i>0 && *(board+(i-1)*width+j)=='*'){
                number_boom++;
                //*(board+(i-1)*width+j)
                //board[i-1][j]
            }
            if( i>0 && j+1<width && *(board+(i-1)*width+j+1)=='*'){
                number_boom++;
                //*(board+(i-1)*width+j+1)
                //board[i-1][j+1]
            }
            if( j>0 && *(board+i*width+j-1)=='*'){
                number_boom++;
                //*(board+i*width+j-1)
                //board[i][j-1]
            }
            if( j+1<width && *(board+i*width+j+1)=='*'){
                number_boom++;
                //*(board+i*width+j+1)
                //board[i][j+1]
            }
            if( i+1<height && j>0 && *(board+(i+1)*width+j-1)=='*'){
                number_boom++;
                //*(board+(i+1)*width+j-1)
                //board[i+1][j-1]
            }
            if( i+1<height && *(board+(i+1)*width+j)=='*'){
                number_boom++;
                //*(board+(i+1)*width+j)
                //board[i+1][j]
            }
            if( i+1<height && j+1<width && *(board+(i+1)*width+j+1)=='*'){
                number_boom++;
                //*(board+(i+1)*width+j+1)
                //board[i+1][j+1]
            }
            if(*(board+i*width+j)!='*'){
                *(board+i*width+j)=number_boom+'0';
            }
        }
    }
    //檢查現在生成的board
    /*for(int i=0;i<height;i++){
        for(int j=0; j<width;j++){
            cout << *(board+i*width+j)<<" ";
        }
        cout << endl;
    }*/

}

void generate_hint(char *board, int height, int width){
    int hints;
    hints=round((sqrt(height*width)));
    cout << hints << endl;
    for(int i=0;i<hints;i++){
        int x = rand()%height;
        int y = rand()%height;
        //cout << x << y <<endl;
        while(*(board+x*width+y)!='-'){
            x = rand()%height;
            y = rand()%height;
        }
        *(board+x*width+y)='*';
    }

}

int main(){
    srand( time(NULL) );
    int N;
    cout << "請輸入地雷模板要多大 : ";
    cin >> N;
    cout << endl;
    //生成N*N的地雷棋盤
    char game_board[N][N];
    generate_board((char *)game_board,N,N);
    cout << endl;
    cout << "Game Board :"<< endl;
    //檢查是否有將生成的board傳回來
    for(int i=0;i<N;i++){
        for(int j=0; j<N;j++){
            cout << game_board[i][j]<<" ";
        }
        cout << endl;
    }

    char play_board[N][N];
    for(int i=0;i<N;i++){
        for(int j=0; j<N;j++){
            play_board[i][j]='-';
        }
    }
    cout << endl;
    cout << "Play Board :"<< endl;
    //檢查play_board
    for(int i=0;i<N;i++){
        for(int j=0; j<N;j++){
            cout << play_board[i][j]<<" ";
        }
        cout << endl;
    }

    //自動產生幾個提示(round(sqrt(height))
    generate_hint((char *)game_board,N,N);
    return 0;
}
