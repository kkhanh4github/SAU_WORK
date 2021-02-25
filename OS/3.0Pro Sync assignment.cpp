#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include<queue>
#define MAX  10
using namespace std; 
// Kamran Khan 09
// I don't like to copy the other's code actually, what ever is this but, 
// it only belongs to me.
// Sorry
bool cpuIdeal = true;

class process 
{
	protected:
		static int pid;	//process id
		int prt;		//process required time
		string pname;
	public:
		void set(string name)
		{
			pid++;
			pname = name;
			prt = 5000;
			setPret(prt);
		}
		
		void setPret(int i)	//set process require time if greater than 0.
		{
			if(i > 1000)
				prt = i;
			else{
				prt = 1000;
			}
		}
							
		int updateRT(int time)	//update process require time after running for some while.
		{
			if(prt < time)
			{
				return prt = 0;
			}
			else
			{
				return prt -= time;
			}
		}
		
		int getReqTime()
		{
			return prt;
		}
		
		int getpid()		//access process id.
		{
			return pid;
		}
		
		string getpname()		//access process id.
		{
			return pname;
		}
};
int process::pid = 0;

class sync
{
	public:	
		int buffer_size;
		int counter, rand;
		
		static int empty;
		static int mutex ;
		static int full;
		
		void P(int S);
		void V(int S);
		process *cp, *bp;
		queue<process> terminatedQueue;	  //data structure for processes.
		//queue<process>* blockQueue;	  //data structure for processes.
		queue<int> sharedBuffer; //terminated process store in.
		
		void setBuffer(int size = 5) //the size of the shared buffer, by default 5.
		{
		    buffer_size = size;
		    empty = size;
		}
				
		void currentProcess() //ready phase, the created process add to data structure.
		{
		        cout<<"Current process in critical section is: "<< cp->getpname();
		}
				
		void blockProcess() //ready phase, the created process add to data structure.
		{
		        cout<<"Current process in critical section is: "<< bp->getpname();
		}
		
		void Producer(process p)	//producer proces object.
		{
			*cp = p;
			while(true)
			{ 
				if(full==buffer_size)
				{
					*bp = p;	
				} //do nothing the buffer is full.
				else{
					P(empty);
					P(mutex);
					//Critical section
							sharedBuffer.push(counter+10);
							cout<<"Produce an item: "<<sharedBuffer.back();
							counter++;
					V(mutex);
					V(full);
				}
			}
		}
		
		void Consumer(process c) 	//consumer process object.
		{
			*cp = c;
			while(true)
			{
				if(empty==buffer_size)
				{
					*bp =c;
				} // do nothing the buffer is empty
				else{
					P(full);
					P(mutex);
						cout<<"Consumed item: %"<<sharedBuffer.front()<<endl;
						sharedBuffer.pop();
					V(mutex);
					V(empty);
				}
			}
		}
		
	
};
int sync::full = 0;
int sync::mutex = 1;
int sync::empty = 0;

void sync::P(int S)
{
	if(S<=0)
	{
		return;
	}
	else{
		S--;
	}
}

void sync::V(int S)
{
		S++;
}

int main()
{
	sync s;
	process producer, consumer;
	char repeat, pno;
	int option, nt, buffer;
	char choose;
	
	printf("\n >>Process consumer and producer are created.\n");
	producer.set("producer");
	consumer.set("consumer");
	
	printf("Inialize The Buffer Size: \n");
	s.setBuffer(scanf("%d",&buffer));		//set the buffer size
	
	do{
		printf("\n MENU:");
		printf("\n >>Press 1 To select a process to enter critical section.");
		printf("\n >>Press 2 Show Running Process in critical section.");
		printf("\n >>Press 3 Show blocked Processes .\n >>");
		scanf("%d",&option);
	
		if(option==1)
		{
				comeback1:
				cout<<"\n Which process you want to enter critical section:\n";
				printf("\n >>P for Producer Processss and C for Consumer process:");
				scanf(" %c",&choose);
				if(choose=='p' || choose=='P'){
					s.Producer(producer);
				}
				else if(choose=='C' || choose=='c'){
					s.Consumer(consumer);
				}
				else{
					printf("invalid option.\n ");
				}
				goto comeback1;
		}
		else if(option==2)
		{
		    s.currentProcess();
		}
		else if(option==3)
		{
			s.blockProcess();
		}
		else{
			cout<<" invalid value!";
		}
				
		printf("\nReturn to Menu? Y/N: ");
		scanf(" %c",&repeat);
	}while((repeat=='Y' || repeat=='y') && (repeat != 'N' || repeat != 'n'));
	
    return 0;
}




/*	
	void showTerminated()
		{
			if(!terminatedQueue.empty())
			{
				cout<<"Terminated process are:\n";
				for(int i=0; !terminatedQueue.empty(); i++)
				{
					cout<<"p"<<terminatedQueue.front().getpid()<<", ";
					terminatedQueue.pop();
				}
			}
			else{
				cout<<"No process is terminated!\n";
			}
		}
		
	void running()	//running phase
		{
		if(cpuIdeal)
		{
			cpuIdeal = false;
				
			if (counter <= 0 )
		    {
		    printf("Queue Underflow \n");
		        return ;
		    }
		    else
		    {	        
				cout<<"\np"<<blockQueue[0].getpid()<<" is running.."<<endl;
								
			//	Sleep(1000);		//indecates every process is running for 1000 ms. 
				blockQueue[0].updateRT(1000);				
				
				if(	blockQueue[0].getReqTime()  <= 0 )
				{
					terminatedQueue.push( blockQueue[0]);
					blockQueue[0];
					cout<<"\nthe process "<<terminatedQueue.back().getpid()<<" is termenated.."<<endl;
				}
				else
				{
					blockQueue[0];//(blockQueue.front());
					cout<<"\nthe process "<<blockQueue[0].getpid()<<" is pass back in ready.."<<endl;
					blockQueue[0];
				}
				//extract the next process from ready data structure for next execution.
		   }
		}
		
	}
	*/
	/*
	void showReady()
	{
	    int i;
	    if (counter>-1)
	    {
	        printf("Queue is empty \n");
	    }
	    else
	    {
	        printf("Queue is : \n");
	            cout<<" ,p"<<blockQueue[counter].getpid();
	            blockQueue[0];
		        printf("\n");
	    }
	}
	End of display() 
	*/
