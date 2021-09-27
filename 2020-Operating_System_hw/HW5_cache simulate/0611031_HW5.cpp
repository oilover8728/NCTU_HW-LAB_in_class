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
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <sys/time.h>

#include <queue>
#include <string.h>
#include <math.h>

using namespace std;

int array[10000000];


struct Page
{
    int stored_frame;       //store which frame number
    int into_frame_time;    //when the frame into the page
    int reference_count;    //how many times the frame be refered;
};
typedef struct Page page_declare;



void initial(Page *page,int frame_number){
    for(int i=0;i<frame_number;i++){
        page[i].stored_frame=-1;
        page[i].into_frame_time=-1;
        page[i].reference_count=0;
    }
}

void initial2(Page *page2,int frame_number){
    for(int i=0;i<frame_number;i++){
        page2[i].stored_frame=-1;
        page2[i].into_frame_time=-1;
        page2[i].reference_count=0;
    }
}

int find_least_ref(Page *page,int frame_number){
    int i;
    int temp = page[0].reference_count;
    int min=0;
    for(i=1;i<frame_number;i++){
        if(temp > page[i].reference_count){
            temp=page[i].reference_count;
            min = i;
        }
    }
    return min;
}

int find_first_come(Page *page2,int frame_number){
    int i=0;
    int come_time=page2[0].into_frame_time;
    int first=i;
    for(i=1;i<frame_number;i++){
        if(come_time > page2[i].into_frame_time){
            come_time = page2[i].into_frame_time;
            first=i;
        }
    }
    return first;
}

int main(int argc, char *argv[ ]){
    struct timeval start, end;
    //read input
    FILE *fPtr = fopen(argv[1], "rb");
    if (!fPtr)
    {
        printf("error input\n");
    }
    char buffer[1024];


    int i=0;
    while(!feof(fPtr)){
        fscanf(fPtr, "%s",buffer);
        array[i]=atoi(buffer);
        i++;
    }
    int size_of_data = i-1;
    fclose(fPtr);
    
    //LFU Algorithm
    cout << "LFU policy:"<<endl;
    printf("Frmae\tHit\t\tMiss\t\tPage fault ratio\n");
    gettimeofday(&start, 0);
    for(int size_of_page=64;size_of_page<=512;size_of_page*=2){
        //the table information
        int frame_number=size_of_page;
        int Hit=0;
        int Miss=0;
        double page_fault_ratio;
        //page declare
        int number=-1;
        page_declare page[frame_number];

        initial(page,frame_number);
        //into data
        int dtt=0;
        for(int data_in=0;data_in<size_of_data;data_in++){
            number=array[data_in];
            //Hit
            int flag=0;
            for(int search_count=0;search_count<size_of_page;search_count++){
                if(page[search_count].stored_frame==number){
                    flag=1;
                    Hit++;
                    page[search_count].reference_count++;
                    break;
                }
            }
            //Miss
            if(flag==0){
                Miss++;
                //find a space to put in
                int full=1;
                for(int search_count=0;search_count<size_of_page;search_count++){
                    if(page[search_count].stored_frame==-1){
                        full=0;
                        page[search_count].stored_frame=number;
                        page[search_count].into_frame_time=data_in;
                        page[search_count].reference_count=0;
                    }
                }
                //cache is full
                if(full==1){
                    int number_to_kill = find_least_ref(page,frame_number);
                    page[number_to_kill].stored_frame=number;
                    page[number_to_kill].into_frame_time=data_in;
                    page[number_to_kill].reference_count=0;
                }
            }
            dtt=data_in;
        }
        page_fault_ratio =((double)Miss/(double)size_of_data);
        printf("%d\t%d\t\t%d\t\t%.10f\n",frame_number,Hit,Miss,page_fault_ratio);
    }
    

    gettimeofday(&end, 0);
    int sec = end.tv_sec - start.tv_sec;
    int usec = end.tv_usec - start.tv_usec;
    printf("Total elapsed time %.4f sec\n", sec + (usec / 1000000.0));


    //LRU Algorithm
    cout << endl << "LRU policy:"<<endl;
    printf("Frmae\tHit\t\tMiss\t\tPage fault ratio\n");
    gettimeofday(&start, 0);
    for(int size_of_page=64;size_of_page<=512;size_of_page*=2){
        //the table information
        int frame_number=size_of_page;
        int Hit=0;
        int Miss=0;
        double page_fault_ratio;
        //page declare
        int number=-1;
        page_declare page2[frame_number];

        initial2(page2,frame_number);
        //into data
        for(int data_in=0;data_in<size_of_data;data_in++){
            number=array[data_in];
            //Hit
            int flag=0;
            for(int search_count=0;search_count<size_of_page;search_count++){
                if(page2[search_count].stored_frame==number){
                    //cout << "Hit" <<endl;
                    flag=1;
                    Hit++;
                    page2[search_count].reference_count++;
                    page2[search_count].into_frame_time=data_in;
                    break;
                }
            }
            //Miss
            if(flag==0){
                Miss++;
                //find a space to put in
                int full=1;
                for(int search_count=0;search_count<size_of_page;search_count++){
                    if(page2[search_count].stored_frame==-1){
                        full=0;
                        //cout << "Miss 1 :" << endl;
                        page2[search_count].stored_frame=number;
                        page2[search_count].into_frame_time=data_in;
                        page2[search_count].reference_count=0;
                    }
                }
                //cache is full
                if(full==1){
                    //cout << "Miss 2 :" << endl;
                    //for(int k=0;k<64;k++){
                    //    cout << page2[k].into_frame_time << " ";
                    //}
                    //cout << endl;
                    int number_to_kill = find_first_come(page2,frame_number);
                    page2[number_to_kill].stored_frame=number;
                    page2[number_to_kill].into_frame_time=data_in;
                    page2[number_to_kill].reference_count=0;
                }
            }
        }
        page_fault_ratio =((double)Miss/(double)size_of_data);
        printf("%d\t%d\t\t%d\t\t%.10f\n",frame_number,Hit,Miss,page_fault_ratio);
    }


    gettimeofday(&end, 0);
    sec = end.tv_sec - start.tv_sec;
    usec = end.tv_usec - start.tv_usec;
    printf("Total elapsed time %.4f sec\n", sec + (usec / 1000000.0));
    return 0;
}
