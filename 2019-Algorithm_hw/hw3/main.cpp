#include<iostream>
#include<stdio.h>
#include<cstdlib>
#include<fstream>
#include<cstring>
#include<cctype>
#include<iomanip>

using namespace std;

FILE *pFile;
FILE *pOFile;

int matrix[500][500]={0};

// recursive function for dynamic program
int resource_alloc(int cut_h,int cut_t,int remain){
    if(cut_h==cut_t){
        return matrix[remain-1][cut_h];
    }
    int max = 0;
    int i = cut_h;
        for(int j=1;remain-j>=cut_t-cut_h;j++){
            int q=resource_alloc(cut_h, cut_h, j)+resource_alloc(cut_h+1, cut_t, remain-j);
            if(q>max){
                max=q;
            }
        }
    return max;
}

int main(){

//  I/O File
//  buffer the txt.line
    char buffer[1024]={0};
    pFile = fopen("input.txt", "r" );
    pOFile = fopen ("output.txt","w");

    int line = 1;
    int j=0;
    int k=0;

    while(!feof(pFile)){

        int invest;
        memset(buffer,0,sizeof(buffer));
        fgets(buffer, sizeof(buffer),pFile);

        char *pch;

//  if input is matrix then split the string into numbers
        if(strlen(buffer)>2){
            j=0;
            while(buffer[0]!='\n'){
                    char *pch;
                    pch = strtok(buffer," ");
                    k=0;
                    while(pch!=NULL){
                        if(*pch!='x'){
                            matrix[j][k]=atoi(pch);
                        }
                        k++;
                        pch = strtok(NULL," ");
                    }
                    memset(buffer,0,sizeof(buffer));
                    fgets(buffer, sizeof(buffer),pFile);
                    j++;
            }
//  Show the matrix
//            for(int r=0;r<j;r++){
//                for(int c=0;c<k;c++){
//                    cout << matrix[r][c]<<" ";
//                }
//                cout << endl;
//            }
        }

//  if input is "only one" number , mean we have to count the answer
        if(strlen(buffer)==2){
            invest=atoi(buffer);
//  output on the screen for checking convenience
            cout << "invest : " << line <<" index : "<< buffer << endl;
            int profit=resource_alloc(0,k-1,invest);
            cout << "Max_profit : "<< profit << endl;
            cout << "------------------------------------------"<<endl;

            fprintf(pOFile,"%d\n",profit);
            line++;
        }
    }
    return 0;
}

