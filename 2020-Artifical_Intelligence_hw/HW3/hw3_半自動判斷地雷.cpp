#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <cstring>
using namespace std;

void generate_board(char *board, int height, int width){
    int SquareN=round(sqrt(height*width)+1);
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
    //檢查現在生成的board
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
    cout << "請輸入地雷模板要多大 : (H*W)";
    cin >> h >> w;
    cout << endl;
    //生成N*N的地雷棋盤
    char game_board[h][w];
    generate_board((char *)game_board,h,w);
    cout << endl;
    cout << "Game Board :"<< endl;
    //檢查是否有將生成的board傳回來
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
    //全空的play_board
    /*cout << "Play Board :"<< endl;
    //檢查play_board
    for(int i=0;i<N;i++){
        for(int j=0; j<N;j++){
            cout << play_board[i][j]<<" ";
        }
        cout << endl;
    }*/

    //自動產生幾個提示(round(sqrt(height))
    generate_hint((char *)game_board,(char *)play_board,h,w);

    //開始準備玩踩地雷 boom 總共有幾個地雷 mark_boom已標記的地雷
    int booms=10;

    cout << endl<<"遊戲開始 "<< endl <<endl;

    //先把上面的輸入N抓掉
    //cin.getline(sentence, 10);

    //讀取執行的指令
    int end=0;

    //把周圍地雷是0的都打開
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
            cout << endl << "error input 格式錯誤 ( 打開地雷 :o x y  標記地雷 :m x y )"<<endl<<endl;
        }*/
        //把0和周圍沒有地雷的地方都直接打開
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

        //把能開得先打開
        for(int i=0;i<h;i++){
            for(int j=0;j<w;j++){
                //判斷是不是數字
                if(play_board[i][j]!='0' && play_board[i][j]!='!' && play_board[i][j]!='-' && play_board[i][j]!='*'){
                    int number=play_board[i][j]-'0';
                    //一個一個檢查 假如有數字和周圍沒打開的格子數量一樣，則代表全部是炸彈
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
                //判斷是不是數字
                if(play_board[i][j]!='0' && play_board[i][j]!='!' && play_board[i][j]!='-'){
                    int number=play_board[i][j]-'0';
                    //假如數字=周圍已mark的炸彈數量，代表剩下的空格都是安全的
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
        //如果找到的炸彈和實際有的炸彈一樣多則結束 假如還沒結束 印出現在的板子
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
