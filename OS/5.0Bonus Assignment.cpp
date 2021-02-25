#include <iostream>
#include <thread>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;


class tasks
{
	private:
		const int lengthOfBuffer;
		vector<string> cloud;		//cloud for perminent storage of collected data
		vector<string> buffer;		//buffer for temprary storage of collected data
		int empty, full, mutex;		//properties of buffer
		bool sens, send;			//wakeup sensor /  call sensder  
	public:	
	
		void waite(int *S)		// Decrease the whatever real values come to 
		{		
			while(*S<=0);
			*S=*S-1;
		}
	
		void signal(int *S)  	// increase the whatever real values come to 
		{
			*S=*S+1;
		}
		
		void initialize(int len)
		{
			lengthOfBuffer = len;
			empty= len;
			full=0;
			mutex=1;
			sens=false;		//set for 
			send=0;
		}
		
		
	void sender()
	{		
		while(true)		// Critical solution problem because buffer is shared beween both sensor and sender
		{
			waite(&full);	//decrement the value of full because of poping the element and store on cloud
			waite(&mutex);	// set mutex for critical problem
			
			cout<<"Sending data to cloud -> \n";
			
			while(!buffer.empty())	//pop the data from buffer and put into the cloud
			{
				send=1;
				cloud.push_back(buffer.front());	//push to cloud
				buffer.erase(buffer.begin());		//pop from buffer
				if(sens==true)						//sens true mean buffer is empty and call the sensor
					break;
			}
			for(int i=0; i<cloud.size(); i++)
				cout<<" ----- "<<cloud[i];	cout<<endl;
				
			signal(&mutex);			//increase the calue by 1
			signal(&empty);
			
			for(int i=0; i<30; i++)
			{
				system("sleep 1");
				if(send==-1)	//if send == -1 then call sensor
					break;
			}
		}
	}
	
		void sensor()
		{
			while(true)		//sensor producing data
			{
				string input;	// what ever string wanna put
				cout<<"sensor --: ";
				cin>>input;
				if(input!=""){
					if(buffer.size()==lengthOfBuffer-1){
						cout<<"LESS MEMORY!!\n";
						send=-1;
					}
					else{
						sens=true;		//
						waite(&empty);
						waite(&mutex);
							buffer.push_back(input);
						signal(&mutex);
						signal(&full);
						sens=false;			// it means to wake up the sender to send data to cloud form buffer
					}
				}
				system("sleep 1");
				send=1;
			}
			
		}
}
int main(){
	int buff;
	cout<<"enter the buffer size: "; cin>>buff;
	initialize(buff);
	tasks t;
	
	cout<<"\nIoT Sensors:\n OS To schedule tasks and assign priority and memory manangement: \n\n";
	thread t1(t.sensor);
	thread t2(t.sender);
	while(1);	
}
