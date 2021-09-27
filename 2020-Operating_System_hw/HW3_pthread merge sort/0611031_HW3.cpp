/*
Student No.: 0611031
Student Name: HSIEH,CHIH-HENG
Email: oilover8728@gmail.com
SE tag: xnxcxtxuxoxsx
Statement: I am fully aware that this program is not
supposed to be posted to a public server, such as a
public GitHub repository or a public web page.
*/
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <sys/time.h>
using namespace std;

pthread_t p[15];
sem_t  call[15];
sem_t  recall[15];
int SizeOfArray;
int array[1000000];
int array_single[1000000];
int task[8];

void bubble_sort(int *array_single,int start,int end){
    int temp=0;
    for(int i=start;i<end;i++){
        for(int j=i+1;j<end;j++){
            if(array_single[i]>array_single[j]){
                temp=array_single[i];
                array_single[i]=array_single[j];
                array_single[j]=temp;
            }
        }
    }
    return;
}

void merge_sort(int *array_single, int start, int end,int level){
    int SizeOfArray = end-start;
    int mid = (start+end)/2;
    if(level==0){
        bubble_sort(array_single,start,end);
        return;
    }
    else{
        merge_sort(array_single,start,mid,level-1);
        merge_sort(array_single,mid,end,level-1);
        vector<int> left (array_single+start,array_single+mid);
        vector<int> right (array_single+mid,array_single+end);
        int leftindex=0;
        int rightindex=0;
        for(int i=start;i<end;i++){
            if(leftindex+start>=mid){
                array_single[i]=right[rightindex];
                rightindex++;
            }
            else if(rightindex+mid>=end){
                array_single[i]=left[leftindex];
                leftindex++;
            }
            else if(left[leftindex]>right[rightindex]){
                array_single[i]=right[rightindex];
                rightindex++;
            }
            else{
                array_single[i]=left[leftindex];
                leftindex++;
            }
        }
        return;
    }
}

void multi_bubble_sort(int task_start, int task_end){
    int temp;
    for(int i=task_start;i<task_end;i++){
        for(int j=i+1;j<task_end;j++){
            if(array[j]<array[i]){
                temp=array[i];
                array[i]=array[j];
                array[j]=temp;
            }
        }
    }
}

void multi_merge(int *array, int start,int mid, int end){
    vector<int> left (array+start,array+mid);
    vector<int> right (array+mid,array+end);
    int leftindex=0;
    int rightindex=0;
    for(int i=start;i<end;i++){
        if(leftindex+start>=mid){
            array[i]=right[rightindex];
            rightindex++;
        }
        else if(rightindex+mid>=end){
            array[i]=left[leftindex];
            leftindex++;
        }
        else if(left[leftindex]>right[rightindex]){
            array[i]=right[rightindex];
            rightindex++;
        }
        else{
            array[i]=left[leftindex];
            leftindex++;
        }
    }
    return;
}

void multithread_merge_sort(int tasknumber){
    if(tasknumber==0){
        multi_merge(array,0,task[3],task[7]);
    }
    else if(tasknumber==1){
        multi_merge(array,0,task[1],task[3]);
    }
    else if(tasknumber==2){
        multi_merge(array,task[3],task[5],task[7]);
    }
    else if(tasknumber==3){
        multi_merge(array,0,task[0],task[1]);
    }
    else if(tasknumber==4){
        multi_merge(array,task[1],task[2],task[3]);
    }
    else if(tasknumber==5){
        multi_merge(array,task[3],task[4],task[5]);
    }
    else if(tasknumber==6){
        multi_merge(array,task[5],task[6],task[7]);
    }
    return;
}

void *create(void* pointer){
    int number = *(int*)pointer;
    sem_wait(&call[number]);
    if(number<7){
        sem_post(&call[number*2+1]);
        sem_post(&call[number*2+2]);
        sem_wait(&recall[number*2+1]);
        sem_wait(&recall[number*2+2]);
        multithread_merge_sort(number);
        sem_post(&recall[number]);
    }
    else if(number==7){
        multi_bubble_sort(0,task[number-7]);
        sem_post(&recall[number]);
    }
    else{
        multi_bubble_sort(task[number-8],task[number-7]);
        sem_post(&recall[number]);
    }
    pthread_exit(0);
}

int main(){
    struct timeval start, end;
    char filename[1024];
    cin >> filename;
    //read input
    FILE *fPtr = fopen(filename, "rb");
    if (!fPtr)
    {
        printf("檔案開啟失敗...(需輸入副檔名)\n");
    }
    char buffer[1024];
    fscanf(fPtr, "%s", buffer);
    SizeOfArray = atoi(buffer);
    for(int i=0;i<SizeOfArray;i++){
        if(!feof(fPtr)){
            fscanf(fPtr, "%s",buffer);
            array[i]=atoi(buffer);
            array_single[i]=atoi(buffer);
        }
        else{
            break;
        }
    }
    fclose(fPtr);

    gettimeofday(&start, 0);
    //task calculate    task[i] means the end of bubble have to work to
    for(int i=0;i<8;i++){
        task[i]=(i+1)*SizeOfArray/8;
    }

    //initial the semaphore
    for(int i=0;i<15;i++){
        sem_init(&call[i],0,0);
        sem_init(&recall[i],0,0);
    }
    //creat 15 threads
    int number[15];
    for(int i=0;i<15;i++){
        //note the number of semaphore in number[i]
        number[i]=i;
        pthread_create(&p[i],NULL,&create,number+i);
    }

    //thread work
    sem_post(&call[0]);
    sem_wait(&recall[0]);

    //decontruction
    for(int i=0;i<15;i++){
        sem_destroy(&call[i]);
        sem_destroy(&recall[i]);
    }

    //time calculate
    gettimeofday(&end, 0);
    int sec = end.tv_sec - start.tv_sec;
    int usec = end.tv_usec - start.tv_usec;
    cout << endl << "MTsorting:"<<endl;
    printf("Elapsed time: %f sec, ", sec + (usec / 1000000.0));

    //file output
    FILE *out;
    out = fopen( "output1.txt", "w" );
    if( out != NULL ){
        for(int i=0;i<SizeOfArray;i++){
            fprintf( out, "%d ", array[i] );
        }
    }
    //-------------------------------------------------------------------
    //single thread
    gettimeofday(&start, 0);
    merge_sort(array_single,0,SizeOfArray,3);
    gettimeofday(&end, 0);

    //calculate time
    sec = end.tv_sec - start.tv_sec;
    usec = end.tv_usec - start.tv_usec;
    cout << endl << "STsorting:"<<endl;
    printf("Elapsed time: %f sec, ", sec + (usec / 1000000.0));

    //file output
    FILE *out2;
    out2 = fopen( "output2.txt", "w" );
    if( out2 != NULL ){
        for(int i=0;i<SizeOfArray;i++){
            fprintf( out2, "%d ", array_single[i] );
        }
    }
    cout << endl;
    return 0;
}
