#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <cstring>
using namespace std;

void generate_board(char *board, int height, int width){
    int SquareN=round(sqrt(height*width)+1);
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

void generate_hint(char *board, char*play_board,int height, int width){
    int hints;
    hints=round((sqrt(height*width)));
    cout << endl<<"hint :"<< hints << endl;
    for(int i=0;i<hints;i++){
        int x = rand()%height;
        int y = rand()%height;
        //cout << x << y <<endl;
        while(*(board+x*width+y)=='*'){
            x = rand()%height;
            y = rand()%height;
        }
        *(play_board+x*width+y)=*(board+x*width+y);
    }
    //�ˬd�{�b�ͦ���board
    cout << "Play Board :"<< endl;
    for(int i=0;i<height;i++){
        for(int j=0; j<width;j++){
            cout << *(play_board+i*width+j)<<" ";
        }
        cout << endl;
    }

}

int main(){
    srand( time(NULL) );
    int h,w;
    cout << "�п�J�a�p�ҪO�n�h�j : (H*W)";
    cin >> h >> w;
    cout << endl;
    //�ͦ�N*N���a�p�ѽL
    char game_board[h][w];
    generate_board((char *)game_board,h,w);
    cout << endl;
    cout << "Game Board :"<< endl;
    //�ˬd�O�_���N�ͦ���board�Ǧ^��
    for(int i=0;i<h;i++){
        for(int j=0; j<w;j++){
            cout << game_board[i][j]<<" ";
        }
        cout << endl;
    }

    char play_board[h][w];
    for(int i=0;i<h;i++){
        for(int j=0; j<w;j++){
            play_board[i][j]='-';
        }
    }
    cout << endl;
    //���Ū�play_board
    /*cout << "Play Board :"<< endl;
    //�ˬdplay_board
    for(int i=0;i<N;i++){
        for(int j=0; j<N;j++){
            cout << play_board[i][j]<<" ";
        }
        cout << endl;
    }*/

    //�۰ʲ��ʹX�Ӵ���(round(sqrt(height))
    generate_hint((char *)game_board,(char *)play_board,h,w);

    //�}�l�ǳƪ���a�p boom �`�@���X�Ӧa�p mark_boom�w�аO���a�p
    int booms=10;

    cout << endl<<"�C���}�l "<< endl <<endl;

    //����W������JN�챼
    //cin.getline(sentence, 10);

    //Ū�����檺���O
    int end=0;

    //��P��a�p�O0�������}
    int loop=0;
    while(end==0){
        /*cin.getline(sentence, 10);
        if(sentence[0]=='o' && sentence[1]==' '){
            cout << "open" <<endl;
            cout << sentence[2] <<" "<< sentence[4] <<endl;
            if(game_board[sentence[2]-'0'][sentence[4]-'0']=='*'){
                cout << "Boom! End Game" << endl << endl;
                end=1;
            }
            else{
                play_board[sentence[2]-'0'][sentence[4]-'0'] = game_board[sentence[2]-'0'][sentence[4]-'0'];
            }
        }
        else if(sentence[0]=='m' && sentence[1]==' '){
            cout << "mark" <<endl;
            cout << sentence[2] <<" "<< sentence[4] <<endl;
            if(game_board[sentence[2]-'0'][sentence[4]-'0']=='*'){
                play_board[sentence[2]-'0'][sentence[4]-'0']='!';
                mark_boom++;
            }
            else{
                play_board[sentence[2]-'0'][sentence[4]-'0']='!';
            }
        }
        else{
            cout << endl << "error input �榡���~ ( ���}�a�p :o x y  �аO�a�p :m x y )"<<endl<<endl;
        }*/
        //��0�M�P��S���a�p���a�賣�������}
        for(int i=0;i<h;i++){
            for(int j=0;j<w;j++){
                if(game_board[i][j]=='0'){
                    play_board[i][j]='0';
                    if(i>0 && j>0){
                        play_board[i-1][j-1]=game_board[i-1][j-1];
                    }
                    if(i>0){
                        play_board[i-1][j]=game_board[i-1][j];
                    }
                    if(i>0 && j+1<w){
                        play_board[i-1][j+1]=game_board[i-1][j+1];
                    }
                    if(j>0){
                        play_board[i][j-1]=game_board[i][j-1];
                    }
                    if(j+1<w){
                        play_board[i][j+1]=game_board[i][j+1];
                    }
                    if(i+1<h && j>0){
                        play_board[i+1][j-1]=game_board[i+1][j-1];
                    }
                    if(i+1<h){
                        play_board[i+1][j]=game_board[i+1][j];
                    }
                    if(i+1<h && j+1<w){
                        play_board[i+1][j+1]=game_board[i+1][j+1];
                    }
                }
            }
        }

        //���}�o�����}
        for(int i=0;i<h;i++){
            for(int j=0;j<w;j++){
                //�P�_�O���O�Ʀr
                if(play_board[i][j]!='0' && play_board[i][j]!='!' && play_board[i][j]!='-' && play_board[i][j]!='*'){
                    int number=play_board[i][j]-'0';
                    //�@�Ӥ@���ˬd ���p���Ʀr�M�P��S���}����l�ƶq�@�ˡA�h�N������O���u
                    int space_number=0;
                    if(i>0 && j>0 ){
                        if(play_board[i-1][j-1]=='-'||play_board[i-1][j-1]=='*'){
                            space_number++;
                        }
                    }
                    if(i>0){
                        if(play_board[i-1][j]=='-'||play_board[i-1][j]=='*'){
                            space_number++;
                        }
                    }
                    if( i>0 && j+1<w){
                        if(play_board[i-1][j+1]=='-'||play_board[i-1][j+1]=='*'){
                            space_number++;
                        }
                    }
                    if( j>0 ){
                        if(play_board[i][j-1]=='-'||play_board[i][j-1]=='*'){
                            space_number++;
                        }
                    }
                    if(j+1<w){
                        if(play_board[i][j+1]=='-'||play_board[i][j+1]=='*'){
                            space_number++;
                        }
                    }
                    if( i+1<h && j>0){
                        if(play_board[i+1][j-1]=='-'||play_board[i+1][j-1]=='*'){
                            space_number++;
                        }
                    }
                    if( i+1<h){
                        if(play_board[i+1][j]=='-'||play_board[i+1][j]=='*'){
                            space_number++;
                        }
                    }
                    if( i+1<h && j+1<w){
                        if(play_board[i+1][j+1]=='-'||play_board[i+1][j+1]=='*'){
                            space_number++;
                        }
                    }
                    if(space_number==play_board[i][j]-'0'){
                        play_board[i-1][j-1]=game_board[i-1][j-1];
                        play_board[i-1][j]=game_board[i-1][j];
                        play_board[i-1][j+1]=game_board[i-1][j+1];
                        play_board[i][j-1]=game_board[i][j-1];
                        play_board[i][j+1]=game_board[i][j+1];
                        play_board[i+1][j-1]=game_board[i+1][j-1];
                        play_board[i+1][j]=game_board[i+1][j];
                        play_board[i+1][j+1]=game_board[i+1][j+1];
                    }
                    //cout << "position " << " x : "<<i<<" y : " << j << "Boom : " << space_number <<endl;
                }
            }
        }
        for(int i=0;i<h;i++){
            for(int j=0;j<w;j++){
                //�P�_�O���O�Ʀr
                if(play_board[i][j]!='0' && play_board[i][j]!='!' && play_board[i][j]!='-'){
                    int number=play_board[i][j]-'0';
                    //���p�Ʀr=�P��wmark�����u�ƶq�A�N��ѤU���Ů泣�O�w����
                    int boom_number=0;
                    if( i>0 && j>0 && play_board[i-1][j-1]=='*'){
                        boom_number++;
                    }
                    if( i>0 && play_board[i-1][j]=='*'){
                        boom_number++;
                    }
                    if( i>0 && j+1<w && play_board[i-1][j+1]=='*'){
                        boom_number++;
                    }
                    if( j>0 && play_board[i][j-1]=='*'){
                        boom_number++;
                    }
                    if( j+1<w && play_board[i][j+1]=='*'){
                        boom_number++;
                    }
                    if( i+1<h && j>0 && play_board[i+1][j-1]=='*'){
                        boom_number++;
                    }
                    if( i+1<h && play_board[i+1][j]=='*'){
                        boom_number++;
                    }
                    if( i+1<h && j+1<w && play_board[i+1][j+1]=='*'){
                        boom_number++;
                    }
                    if(boom_number==play_board[i][j]-'0'){
                        play_board[i-1][j-1]=game_board[i-1][j-1];
                        play_board[i-1][j]=game_board[i-1][j];
                        play_board[i-1][j+1]=game_board[i-1][j+1];
                        play_board[i][j-1]=game_board[i][j-1];
                        play_board[i][j+1]=game_board[i][j+1];
                        play_board[i+1][j-1]=game_board[i+1][j-1];
                        play_board[i+1][j]=game_board[i+1][j];
                        play_board[i+1][j+1]=game_board[i+1][j+1];
                    }
                }
            }
        }
        //�p�G��쪺���u�M��ڦ������u�@�˦h�h���� ���p�٨S���� �L�X�{�b���O�l
        int found_boom=0;
        for(int i=0;i<h;i++){
            for(int j=0;j<w;j++){
                if(play_board[i][j]=='*'){
                    found_boom++;
                }
            }
        }
        loop++;
        if(loop>100){
            cout << endl << "Loop" <<endl;
            end=1;
        }
        if(found_boom==booms){
            end=1;
        }
        if(end==1){
            for(int i=0;i<h;i++){
                for(int j=0;j<w;j++){
                    cout << play_board[i][j]<<" ";
                }
                cout <<endl;
            }
        }
    }
    cout << endl <<"GAME OVER"<<endl<<endl;
    return 0;
}
