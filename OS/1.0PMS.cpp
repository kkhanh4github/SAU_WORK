#include <iostream>
//#include<windows.h>
#include<stdio.h>
using namespace std;
#define MAX 50
// Kamran Khan 09
// I don't like to copy the other's code actually, what ever is this but, it only belongs to me mam.
// Sorry, but
bool cpuIdeal = true;

class thread
{
	protected:
		int tid;			//thread id
	public:
		void settid(int i)	//set thread id 
		{
			tid = i;
		}
		
		int gettid()		//set thread id and to specified process
		{
			return tid;
		}
		
		void showThreadInfo()
		{
			cout<<"Thread Id: "<<tid<<endl;
		}
};

class process 
{
	protected:
		static int pid;	//process id
		int prt;		//process required time
		int NOT;		//number of threads
	public:
		void set()
		{
			pid++;
			cout<<"Set the required time for process"<<pid<<": ";
			cin>>prt;
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
		
		void includeThreads(thread temp[], int numOfThreads)
		{
			NOT = numOfThreads;
			for(int i =0; i< NOT; i++)
			{
				t[i] = temp[i];
			}
		}
		
		thread getThread()
		{
			for(int i=0; i<NOT; i++)
			{
				return t[i];
			}
		}
		
		int getpid()		//access process id.
		{
			return pid;
		}	
		
		thread t[];
};
int process::pid = 0;

class states
{
	public:
	static int tindex;		//terminated threads indexer
	
	static int rear;
	static int front;
	
	process readyQueue[MAX];	  //data structure for processes.
	process terminatedQueue[MAX]; //terminated process store in.
	
		void ready(process p) //ready phase, the created process add to data structure.
		{
		    process pro = p;
		    if (rear == MAX)		//compare with last index
		    	printf("Queue Overflow \n");
		    else
		    {
		        if (front == - 1)
		        /*If queue is initially empty */
		        front = 0;
		        rear = rear + 1;
		        readyQueue[rear] = pro;
		        cout<<"readyQueue: p"<<readyQueue[rear].getpid()<<" is in ready"<<endl;
		    }
		} /* End of insert() */
	
		void showTerminated()
		{
			cout<<"Terminated process are:\n";
			for(int i=0; i<=tindex; i++)
			{
				cout<<"p"<<terminatedQueue[i].getpid()<<", ";
			}
		}
		
		void running()	//running phase
		{
		if(cpuIdeal)
		{
			cpuIdeal = false;
				
			if (front == - 1 || front > rear)
		    {
		    printf("Queue Underflow \n");
		        return ;
		    }
		    else
		    {
		        cout<<"\np"<<readyQueue[front].getpid()<<" is delete from readyQueue\n";
	        
				cout<<"\n p"<<readyQueue[front].getpid()<<" is running.."<<endl;
				
					
				//Sleep(1000);		//indecates every process is running for 1000 ms.
				tindex++;
			        
				readyQueue[front].updateRT(1000);				
				
				int protime = 0;
				protime = readyQueue[front].getReqTime();
				
				
				if(protime <= 0 )
				{
					terminatedQueue[tindex] = readyQueue[front];
					cout<<"\nthe process "<<terminatedQueue[tindex].getpid()<<" is termenated.."<<endl;
					tindex++;
				}
				else{
					ready(readyQueue[front]);
					cout<<"\nthe process "<<readyQueue[front].getpid()<<" is pass back in ready.."<<endl;
				}
								
				//extract the next process from ready data structure for next execution.
				front = front + 1;		
		   }
		}
	}
	
	void showReady()
	{
	    int i;
	    if (front == - 1)
	    {
	        printf("Queue is empty \n");
	    }
	    else
	    {
	        printf("Queue is : \n");
	        for (i = front; i <= rear; i++)
	        {
	            cout<<" ,p"<<readyQueue[i].getpid();
		        printf("\n");
	        }
	    }
	} /* End of display() */
};
int states::tindex = 0;	      //terminated process indexer
int states::rear = - 1;       //every time extends but in the begining it is empty
int states::front = - 1;      //no element in the begin to pop up from the front


int main()
{
	int inx = 0;
	int indexer = 0;
	states s[MAX];
	
	process p[MAX];
	
	char repeat;
	int option;
	int nt;
	do{
		printf("\n\tGo To:");
		printf("\n >Create Process Press 1.");
		printf("\n >Show Ready Processes Press 2.");
		printf("\n >Show Running Process Press 3.");
		printf("\n >Show Terminated Processes Press 4.\n >");
		scanf("%d",&option);
		
		if(option==1)
		{
				cout<<"process created.\n";
				p[indexer].set();		//set the id and require time.
				printf("how many threads do you want to create in p%d",p[indexer].getpid());
				cin>>nt;
				
				thread t[nt];				// number of thread objects.
					for(int i=0; i<nt; i++)
					{
						t[i].settid(i);
					}
				p[indexer].includeThreads(t, nt);
				s[inx].ready(p[indexer]);
				indexer++;
		}
		else if(option==2)
		{
			s[inx].showReady();
		}
		
		else if(option==4)
		{
			s[inx].showTerminated();
		}
		else if(option==3)
		{
		      s[inx].running();
		}
		else{
			cout<<" invalid value!";
		}
		
		inx++;
		
		char c;
		printf("\n G for Go & S for Stop(G/S): ");
		scanf(" %c",&repeat);
	}while((repeat=='G' || repeat=='g') & (repeat != 'S' || repeat != 's'));
	
    return 0;
}


