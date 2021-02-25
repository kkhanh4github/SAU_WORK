#include <windows.h>   
#include <stdio.h>   
//#include <queue>   
#include <time.h>    
#include <math.h> 

void P(int*);
void V(int*);
DWORD WINAPI Producer(LPVOID lpPara); //Producer threads   
DWORD WINAPI Consumer(LPVOID lpPara); //consumer threads 

int mutex = 1;      //Semaphore Mutex,to ensure mutual excute   
int full = 0; 		//Semaphore Full,to indicate the buffer HAS product or not
int empty;    	//Semaphore Empty,to indicate total number of products in buffer   

//queue<int> sharedBuffer;  //act as buffer,to save products   
int shared[5];
int sleep, buffer_size;	//sleepTime: time for main function to sleep before termination    
int randNum, counter=0;  					//to save the value of product   

int pi=101, ci=202; 	//The id of Producer and Consumer threads
//int NoP, NoC;		//number of Producer and Consumer threads

main()   
{   

	printf(">>>Bounded Buffer Producer Consumer Problem<<<\n>>Initialization<<\nEnter the buffer_size:\n"); 
	scanf("%d",&buffer_size);
	empty = buffer_size;
	
	printf("empty: %d\n",empty);  
	
	printf("How long to sleep before terminating?\n");  
	scanf("%d",&sleep);
	
	//printf("The number of Producer threads?\n");        
	//scanf("%d",&NoP); 
	
	//printf("The number of Consumer threads?\n");        
	//scanf("%d",&NoC);   
	/*
	Mutex=CreateMutex(NULL,FALSE,NULL);      //Create Semaphores   
	Full=CreateSemaphore(NULL,0,bufferSize,NULL);   
	Empty=CreateSemaphore(NULL,bufferSize,bufferSize,NULL);   
	*/
	
	HANDLE p, c;	//Create threads: producer and consumer 
	//HANDLE p[NoP-1], c[NoC-1];	//Create threads: producer and consumer 
	
	//for(int ci=0;ci<=NoC-1;ci++)
	//{   
	    //c[ci]=CreateThread(NULL,0,Consumer,NULL,ci,NULL);    
	    c=CreateThread(NULL,0,Consumer,NULL,ci,NULL);    
	        printf("\tCONSUMER:%d created \n\n",ci+1);    
	//}   
	   	   
	//for(int pi=0; pi<NoP; pi++)   
	//{   
	    //p[pi]=CreateThread(NULL,0,Producer,NULL,pi,NULL);    
	    p = CreateThread(NULL,0,Producer,NULL,pi,NULL);    
	    	printf("\t>>PRODUCER:%d created \n",pi+1);    
	//}   
	

	Sleep(sleep);   //sleep~
}  
      
DWORD WINAPI Producer(LPVOID lpPara) //Producer threads   
{   
		while(true)
		{
			printf("producer called");
			while(full==buffer_size)
			; //do nothing the buffer is full.
			P(&empty);
			P(&mutex);
				Sleep(500);
					//sharedBuffer.push(randNum);
					shared[counter] = (rand()%6)+5;
					printf("Produced %d\n", shared[counter]);
					counter++;
			V(&mutex);
			V(&full);
		}
}      

DWORD WINAPI Consumer(LPVOID lpPara)//consumer threads   
{
			while(true)
			{
				printf("consumer called");
				while(empty==buffer_size)
				; // do nothing the buffer is empty
				P(&full);
				P(&mutex);
					printf("consumed %d from array\n", shared[counter--]);
					Sleep(500);
					//printf("Consumed item: %d",sharedBuffer.front());
					//sharedBuffer.pop();
				V(&mutex);
				V(&empty);
			}
}

void P(int *S)
{
	while(*S<=0);
		*S--;
}

void V(int *S)
{
	if(*S<full)
	{
		*S++;
	}
}
