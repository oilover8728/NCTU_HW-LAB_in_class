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
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <string>
using namespace std;

int string_num = 0;	//count the command number

char **stringtoken(char *input){

	/*---instruction point to a address stroe 32 char address         ---*/
	/*---so a instruction can be deal with less than 32 words         ---*/
	/*---input is that getline catch ,means a line of instruction     ---*/
	/*---every instruction[i] will store a word address means the word---*/

	char **instruction = new char *[32];
	char *pch = strtok(input," ");		//strtok register
	int size=0;							//number of word

	/*---spilt---*/
	while(pch != NULL){
		instruction[size] = pch;
		size++;
		pch = strtok(NULL, " ");
	}

	string_num=size-1;
	/*---execvp have to end with NULL---*/
	instruction[size] = NULL;
	/*---return had splited words---*/
	return instruction;
}

int main()
{
	while(1){
		pid_t pid;			//process ID
		char **instruction; //register for command
		//check "&"
		string check_sync;
		bool Non_wait = false;
		string_num=0;
		//input
		cout << ">";
		char buffer[64];	//register for input
		cin.getline(buffer,64);
		/*---    strtok    ---*/
		instruction = stringtoken(buffer);
		check_sync = instruction[string_num];
		if(check_sync == "&"){

			Non_wait=true;
		}
		/*---     fork     ---*/
		pid=fork();
		if(pid < 0){			/* error detection */

			fprintf(stderr,"Fork Failed");
			exit(-1);
		}
		else if(pid == 0){		/* child process */
			/*---if not wait, call another child to do task---*/
			/*---and child exit that parent call continue  ---*/
			/*---then use child of child process execution ---*/
			/*---when it end will be caught by init        ---*/
			if(Non_wait){

				pid_t pid_2;				//process ID_2
				pid_2=fork();
				if(pid_2 < 0){
					exit(-1);
				}
				else if(pid_2 == 0){		/* grandson process */

					instruction[string_num] = NULL;
					execvp(instruction[0],instruction);
				}
				else{						/* chile process */

					exit(0);
				}
			}
			else{

				execvp(instruction[0],instruction);
			}
		}
		else{					/* parent process */

			wait(NULL);
		}
	}
	return 0;
}
