/*
Student No.: 0611031
Student Name: HSIEH,CHIH-HENG
Email: oilover8728@gmail.com
SE tag: xnxcxtxuxoxsx
Statement: I am fully aware that this program is not
supposed to be posted to a public server, such as a
public GitHub repository or a public web page.
*/
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <error.h>
using namespace std;

int main()
{
    int SizeOfMatrix;
    cout << "Input the matrix dimension: ";
    cin >> SizeOfMatrix;
    cout << endl;

    uint32_t *MatrixA = new uint32_t[SizeOfMatrix * SizeOfMatrix];
    uint32_t *MatrixB = new uint32_t[SizeOfMatrix * SizeOfMatrix];

    //init Matrix A B
    for (int i = 0; i < SizeOfMatrix; i++)
    {
        for (int j = 0; j < SizeOfMatrix; j++)
        {
            MatrixA[i * SizeOfMatrix + j] = i * SizeOfMatrix + j;
            MatrixB[i * SizeOfMatrix + j] = i * SizeOfMatrix + j;
        }
    }
    //Real task start
    for (int n = 1; n <= 16; n++)
    {
        int shmidA;
        int shmidB;
        int shmidC;
        uint32_t *shmaddrA;
        uint32_t *shmaddrB;
        uint32_t *shmaddrC;
        struct shmid_ds buf;
        int flagA = 0;
        int flagB = 0;
        int flagC = 0;
        uint32_t checksum;

        struct timeval start, end;

        int NumberOfProcess = n;
        int WorkOfChild = SizeOfMatrix / NumberOfProcess;
        int WorkOfRemid = SizeOfMatrix % NumberOfProcess;
        int WorkOfStart[NumberOfProcess];
        int WorkOfEnd[NumberOfProcess];

        gettimeofday(&start, NULL);
        //calculate each child workload
        for (int j = 0; j < NumberOfProcess; j++)
        {
            if (j == 0)
            {
                WorkOfStart[j] = 0;
            }
            else
            {
                WorkOfStart[j] = WorkOfEnd[j - 1];
            }
            if (WorkOfRemid > 0)
            {
                WorkOfEnd[j] = WorkOfStart[j] + WorkOfChild + 1;
                WorkOfRemid--;
            }
            else
            {
                WorkOfEnd[j] = WorkOfStart[j] + WorkOfChild;
            }
        }
        pid_t pid[NumberOfProcess];
        int Ptag = -1; //note parent
        shmidA = shmget(IPC_PRIVATE, sizeof(uint32_t) * SizeOfMatrix * SizeOfMatrix, IPC_CREAT | 0600);
        shmidB = shmget(IPC_PRIVATE, sizeof(uint32_t) * SizeOfMatrix * SizeOfMatrix, IPC_CREAT | 0600);
        shmidC = shmget(IPC_PRIVATE, sizeof(uint32_t) * SizeOfMatrix * SizeOfMatrix, IPC_CREAT | 0600);

        /*--------------error detect---------------*/
        if (shmidA < 0 || shmidB < 0 || shmidC < 0)
        {
            perror("get shm  ipc_id error");
            return -1;
        }
        /*------------end error detect-------------*/

        shmaddrA = (uint32_t *)shmat(shmidA, NULL, 0);
        shmaddrB = (uint32_t *)shmat(shmidB, NULL, 0);

        /*--------------error detect---------------*/
        if ((int)*shmaddrA == -1 || (int)*shmaddrB == -1)
        {
            perror("shmat addr error");
            return -1;
        }
        /*------------end error detect-------------*/

        for (int i = 0; i < SizeOfMatrix; i++)
        {
            for (int j = 0; j < SizeOfMatrix; j++)
            {
                shmaddrA[i * SizeOfMatrix + j] = MatrixA[i * SizeOfMatrix + j];
                shmaddrB[i * SizeOfMatrix + j] = MatrixB[i * SizeOfMatrix + j];
            }
        }
        shmdt(shmaddrA);
        shmdt(shmaddrB);

        for (int Process_ID = 0; Process_ID < NumberOfProcess; Process_ID++)
        {
            pid[Process_ID] = fork();
            if (pid[Process_ID] == 0)
            { //child exit fork
                Ptag = Process_ID;
                break;
            }
        }
        if (pid[Ptag] == 0)
        {
            shmaddrA = (uint32_t *)shmat(shmidA, NULL, 0);
            shmaddrB = (uint32_t *)shmat(shmidB, NULL, 0);
            shmaddrC = (uint32_t *)shmat(shmidC, NULL, 0);

            /*--------------error detect---------------*/
            if ((int)*shmaddrA == -1 || (int)*shmaddrB == -1 || (int)*shmaddrC == -1)
            {
                perror("shmat addr error");
                return -1;
            }
            /*------------end error detect-------------*/

            //matrix calculate
            for (int i = WorkOfStart[Ptag]; i < WorkOfEnd[Ptag]; i++)
            {
                for (int j = 0; j < SizeOfMatrix; j++)
                {
                    for (int k = 0; k < SizeOfMatrix; k++)
                    {
                        shmaddrC[i * SizeOfMatrix + j] += shmaddrA[i * SizeOfMatrix + k] * shmaddrB[k * SizeOfMatrix + j];
                    }
                }
            }
            shmdt(shmaddrA);
            shmdt(shmaddrB);
            shmdt(shmaddrC);
            exit(0);
        }
        else if (Ptag == -1)
        { //parent deal with combine C and checksum
            for (int i = 1; i <= NumberOfProcess; i++)
            {
                wait(NULL);
            }
            flagA = shmctl(shmidA, IPC_STAT, &buf);
            flagB = shmctl(shmidB, IPC_STAT, &buf);
            flagC = shmctl(shmidC, IPC_STAT, &buf);

            /*--------------error detect---------------*/
            if (flagA == -1 || flagB == -1 || flagC == -1)
            {
                perror("shmctl shm error");
                return -1;
            }
            /*------------end error detect-------------*/

            shmaddrC = (uint32_t *)shmat(shmidC, NULL, 0);
            /*--------------error detect---------------*/
            if ((int)*shmaddrC == -1)
            {
                perror("shmat addr error");
                return -1;
            }
            /*------------end error detect-------------*/

            checksum = 0;
            for (int i = 0; i < SizeOfMatrix; i++)
            {
                for (int j = 0; j < SizeOfMatrix; j++)
                {
                    checksum += shmaddrC[i * SizeOfMatrix + j];
                }
            }

            shmdt(shmaddrC);
            shmctl(shmidA, IPC_RMID, NULL);
            shmctl(shmidB, IPC_RMID, NULL);
            shmctl(shmidC, IPC_RMID, NULL);
        } /*--------------error detect---------------*/
        else
        {

            perror("fork error");
            shmctl(shmidA, IPC_RMID, NULL);
            shmctl(shmidB, IPC_RMID, NULL);
            shmctl(shmidC, IPC_RMID, NULL);
        }
        /*------------end error detect-------------*/

        //calculate time and result
        gettimeofday(&end, 0);
        int sec = end.tv_sec - start.tv_sec;
        int usec = end.tv_usec - start.tv_usec;
        cout << "Multiplying matrices using " << NumberOfProcess;
        if (NumberOfProcess == 1)
        {
            cout << " process " << endl;
        }
        else
        {
            cout << " processes " << endl;
        }
        printf("Elapsed time: %f sec, ", sec + (usec / 1000000.0));
        cout << "Checksum: " << checksum << endl;
    }
    delete [] MatrixA;
    delete [] MatrixB;
    return 0;
}
