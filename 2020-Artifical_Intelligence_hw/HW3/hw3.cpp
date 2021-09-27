#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

void generate_board(char *board, int height, int width){
    int SquareN=height+1;
    //���ͥ��Ū��O�l
    for(int i=0;i<height;i++){
        for(int j=0; j<width;j++){
            *(board+i*width+j)='-';
        }
    }
    //�H���K�[�a�p
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
    //�ˬd�{�b�ͦ���board
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
    cout << "�п�J�a�p�ҪO�n�h�j : ";
    cin >> N;
    cout << endl;
    //�ͦ�N*N���a�p�ѽL
    char game_board[N][N];
    generate_board((char *)game_board,N,N);
    cout << endl;
    cout << "Game Board :"<< endl;
    //�ˬd�O�_���N�ͦ���board�Ǧ^��
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
    //�ˬdplay_board
    for(int i=0;i<N;i++){
        for(int j=0; j<N;j++){
            cout << play_board[i][j]<<" ";
        }
        cout << endl;
    }

    //�۰ʲ��ʹX�Ӵ���(round(sqrt(height))
    generate_hint((char *)game_board,N,N);
    return 0;
}
