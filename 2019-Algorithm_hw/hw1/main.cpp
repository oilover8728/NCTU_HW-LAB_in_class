#include <iostream>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iomanip>
using namespace std;

int main(){
    FILE *pFile;
    FILE *pOFile;
    char buffer[1024]={0};
    long long int matrix[500][500];
    int n=0;
    int count=0;
    int num=0;
    long long int array[500];

    pFile = fopen( "input.txt", "r" );
    pOFile = fopen ("output.txt","w");
    memset(buffer,0,sizeof(buffer));
    fgets(buffer, sizeof(buffer),pFile);
    n=buffer[0]-48;                             //read how many tests
    while(!feof(pFile)&&num!=n){
        memset(matrix, 0, sizeof(matrix));
        memset(buffer,0,sizeof(buffer));        //read insert or delete
        fgets(buffer, sizeof(buffer),pFile);
        count = buffer[0]-48;
        if(count==1){
            memset(buffer,0,sizeof(buffer));
            fgets(buffer, sizeof(buffer),pFile);
            int size=0;
            char *pch;
            pch = strtok(buffer," ");
            while(pch!=NULL){
                array[size]=atoll(pch);
                size++;
                pch = strtok(NULL," ");
                    }
            memset(buffer,0,sizeof(buffer));
            fgets(buffer, sizeof(buffer),pFile);

            int j=0;
            int k=0;
            while(buffer[0]!='\n'){
                    char *pch;
                    pch = strtok(buffer," ");
                    k=0;
                    while(pch!=NULL){
                        if(*pch!='x'){
                            matrix[j][k]=atoll(pch);
                        }
                        else{
                            matrix[j][k]= 2147483648ul;
                        }
                        k++;
                        pch = strtok(NULL," ");
                    }
                    memset(buffer,0,sizeof(buffer));
                    fgets(buffer, sizeof(buffer),pFile);
                    j++;
            }
           int ok;
           long long int temp;
           int c1;
           int c2;

           fprintf(pOFile,"Insert");
           for(int i=0;i<size;i++){
                matrix[j-1][k-1]=array[i];
                ok=0;
                c1=j-1;
                c2=k-1;
                fprintf(pOFile," %lld",array[i]);
                while((matrix[c1][c2]<matrix[c1-1][c2]||matrix[c1][c2]<matrix[c1][c2-1])&&ok==0){
                    if(c1==0){
                        for(int i=c2;i!=0;i--){
                            if(matrix[c1][i]<matrix[c1][i-1]){
                                temp = matrix[c1][i-1];
                                matrix[c1][i-1]=matrix[c1][i];
                                matrix[c1][i]=temp;
                            }
                            else{
                                break;
                            }
                            ok++;
                            break;
                        }
                    }
                    else if(c2==0){
                        for(int i=c1;i!=0;i--){
                            if(matrix[i][c2]<matrix[i-1][c2]){
                                temp = matrix[i-1][c2];
                                matrix[i-1][c2]=matrix[i][c2];
                                matrix[i][c2]=temp;
                            }
                            else{
                                break;
                            }
                        }
                        ok++;
                        break;

                    }
                    if(matrix[c1][c2]<matrix[c1-1][c2]&&matrix[c1][c2]<matrix[c1][c2-1]){
                        if(matrix[c1-1][c2]>=matrix[c1][c2-1]){
                                goto q1;
                        }
                        else {
                                goto q2;
                        }
                    }

                    else if(matrix[c1][c2]<matrix[c1-1][c2]){
q1:
                        temp=matrix[c1-1][c2];
                        matrix[c1-1][c2]=matrix[c1][c2];
                        matrix[c1][c2]=temp;
                        c1--;
                    }
                    else if(matrix[c1][c2]<matrix[c1][c2-1]){
q2:
                       temp=matrix[c1][c2-1];
                       matrix[c1][c2-1]=matrix[c1][c2];
                       matrix[c1][c2]=temp;
                       c2--;
                    }

                }
           }
           fprintf(pOFile,"\n");
           for(int i=0;i<j;i++){
                for(int l=0;l<k;l++){
                    if(matrix[i][l]!=2147483648ul){
                        fprintf(pOFile,"%lld ",matrix[i][l]);
                        //cout << matrix[i][l]<<" ";
                    }
                    else{
                        fprintf(pOFile,"x ");
                        //cout << "x ";
                    }
                }
                fprintf(pOFile,"\n");
            }
            fprintf(pOFile,"\n");
        }
        else if(count==2){
           memset(buffer,0,sizeof(buffer));
            fgets(buffer, sizeof(buffer),pFile);

            int j=0;
            int k=0;

            while(buffer[0]!='\n'){

                    char *pch;

                    pch = strtok(buffer," ");
                    k=0;
                    while(pch!=NULL){

                        if(*pch!='x'){
                            matrix[j][k]=atoll(pch);
                        }
                        else{
                            matrix[j][k]= 2147483648ul;
                        }
                        k++;
                        pch = strtok(NULL," ");
                    }
                    memset(buffer,0,sizeof(buffer));
                    fgets(buffer, sizeof(buffer),pFile);
                    j++;
            }
            fprintf(pOFile,"Extract-min %lld\n",matrix[0][0]);
            //cout << "Extract-min "<<matrix[0][0]<<endl;
            matrix[0][0]=2147483648ul;
            int c1=0;
            int c2=0;
            long long int temp;
            int ok=0;
            while((matrix[c1][c2]>matrix[c1+1][c2]||matrix[c1][c2]>matrix[c1][c2+1])&&ok==0){
                    if(c1==j-1){
                        for(int i=c2;i!=k-2;i++){
                            if(matrix[c1][i]>matrix[c1][i+1]){
                                temp=matrix[c1][i+1];
                                matrix[c1][i+1]=matrix[c1][i];
                                matrix[c1][i]=temp;
                            }
                            else{
                                break;
                            }
                        }
                        ok++;
                        break;
                    }
                    else if(c2==k-1){
                        for(int i=c1;i!=j-2;i++){
                            if(matrix[i][c2]>matrix[i+1][c2]){
                                temp=matrix[i+1][c2];
                                matrix[i+1][c2]=matrix[i][c2];
                                matrix[i][c2]=temp;
                            }
                            else{
                                break;
                            }
                        }
                        ok++;
                        break;
                    }
                    if(matrix[c1][c2]>matrix[c1+1][c2]&&matrix[c1][c2]>matrix[c1][c2+1]){
                        if(matrix[c1+1][c2]>=matrix[c1][c2+1]){
                                goto q4;
                        }
                            else {
                                goto q3;
                            }
                    }
q3:
                    if(matrix[c1][c2]>matrix[c1+1][c2]){

                        temp=matrix[c1+1][c2];
                        matrix[c1+1][c2]=matrix[c1][c2];
                        matrix[c1][c2]=temp;
                        c1++;
                    }
                    else if(matrix[c1][c2]>matrix[c1][c2+1]){
q4:
                       temp=matrix[c1][c2+1];
                       matrix[c1][c2+1]=matrix[c1][c2];
                       matrix[c1][c2]=temp;
                       c2++;
                    }
                }
            for(int i=0;i<j;i++){
                for(int l=0;l<k;l++){
                    if(matrix[i][l]!=2147483648ul){
                        fprintf(pOFile,"%lld ",matrix[i][l]);
                        //cout << matrix[i][l]<<" ";
                    }
                    else{
                        fprintf(pOFile,"x ");
                        //cout << "x ";
                    }
                }
                fprintf(pOFile,"\n");
            }
            fprintf(pOFile,"\n");
        }
        num++;
    }
    //array a[2]=-1;
    //long long int b=atoll(a);
    //cout << b<2147483648ul<<endl;
    fclose(pFile);
    fclose(pOFile);
    return 0;
}
