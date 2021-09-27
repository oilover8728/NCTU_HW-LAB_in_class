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

#include <queue>
#include <string.h>

using namespace std;

pthread_t p[8];
sem_t  mutex;
int SizeOfArray;
int array[1000000];

int array_input[1000000];   //array store the result of sort array_input store txt index
int task[8];                //the range each thread have to sort
bool work_done[15];         //check if bottom sort already
bool already_push[7];       //check if alread push into work_table

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
    queue <int> *work_table = (queue <int> *) pointer;
    while(!work_done[0]){
        sem_wait(&mutex);
        if(work_table->empty()){
            sem_post(&mutex);
            continue;
        }
        int number=work_table->front();
        work_table->pop();
        sem_post(&mutex);
        if(number<7){
            multithread_merge_sort(number);
        }
        else if(number==7){
            multi_bubble_sort(0,task[number-7]);
        }
        else{
            multi_bubble_sort(task[number-8],task[number-7]);
        }
        sem_wait(&mutex);
        work_done[number]=true;
        sem_post(&mutex);
    }
    pthread_exit(0);
}



int main(){
    struct timeval start, end;
    int pthread_pool=1;
    //read input
    FILE *fPtr = fopen("input.txt", "rb");
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
            //array[i]=atoi(buffer);
            array_input[i]=atoi(buffer);
        }
        else{
            break;
        }
    }
    fclose(fPtr);

    //task calculate    task[i] means the end of bubble have to work to
    for(int i=0;i<8;i++){
        task[i]=(i+1)*SizeOfArray/8;
    }

    for(pthread_pool=1;pthread_pool<=8;pthread_pool++){
        //init
        for(int i=0;i<SizeOfArray;i++){
            array[i]=array_input[i];
        }

        queue <int> work_table;
        while (!work_table.empty()){
            work_table.pop(); //check the queue is clear
        }

        gettimeofday(&start, 0);    //time start

        for(int i=0;i<15;i++){
            work_done[i]=false;
        }

        for(int i=0;i<7;i++){
            already_push[i]=false;
        }

        for(int i=7;i<15;i++){
            work_table.push(i);
        }

        sem_init(&mutex,0,1);       //reset semaphore

        for(int i=0;i<pthread_pool;i++){            //creat pthread(s)
            pthread_create(&p[i],NULL,&create,&work_table);
        }

        while(!work_done[0]){       //schedule
            for(int i=0;i<7;i++){
                if(already_push[i]==true){
                    continue;
                }
                else if(work_done[2*i+1]==true && work_done[2*i+2]==true){
                    sem_wait(&mutex);
                    work_table.push(i);
                    already_push[i]=true;
                    sem_post(&mutex);
                }
            }
        }

        //time calculate
        gettimeofday(&end, 0);
        int sec = end.tv_sec - start.tv_sec;
        int usec = end.tv_usec - start.tv_usec;
        printf("Sorting time of %d-thread pool: %f sec, \n",pthread_pool, sec + (usec / 1000000.0));

        //file output
        FILE *out;
        string output_filename="output_";
        string output_filename_number=to_string(pthread_pool);
        output_filename+=output_filename_number;
        output_filename+=".txt";
        char filename[1024];
        strcpy(filename,output_filename.c_str());
        out = fopen(filename, "w" );
        if( out != NULL ){
            for(int i=0;i<SizeOfArray;i++){
                fprintf( out, "%d ", array[i] );
            }
        }
    }
    sem_destroy(&mutex);
    return 0;
}
