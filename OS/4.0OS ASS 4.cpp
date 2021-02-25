#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <time.h> 
using namespace std;

class replaceAlgo
{
	public:		
		void fifoAlgo(int n, int nf, int *arr)
		{ 
			printf("first in first out pages algorithem:\n");
			int frame[nf];	//memory partitions array 
			for(int i=0; i<nf; i++)
				frame[i]=-1;	//deafult initialization
			
			int pagefault=0;
			for(int i=0, j=0; i<n; i++)
			{
				int k=0;
				for(; k<nf; k++){
					if(frame[k]==arr[i])	//page is in array or not, if yes break
						break;
				}
				if(k>=nf){		//if index is greater than no of frames 
					frame[j]=arr[i];	//page added to frame
					j=(j+1)%nf;
					pagefault++;		//page fault
				}
				for(int a=0; a<nf; a++){
					if(frame[a]==-1)	//if frames is empty show " " otherwise page number
						cout<<" "<<",";
					else
						cout<<frame[a]<<",";
				}
				cout<<" : "<<pagefault<<endl;
			}
			cout<<"Total page faults in FIFO: "<<pagefault<<endl;
		}
		
	void lruAlgo(int n, int f, int *arr)
	{
		printf("Least recently used pages algorithem:\n");
		
		int frame[2][f];
		for(int i=0; i<f; i++){
			frame[0][i]=-1;
			frame[1][i]=f-i;
		}
		
		int pagefault=0;
		for(int i=0; i<n; i++){
			for(int j=0; j<f; j++)
				frame[1][j]++;
			int k=0;
			for(; k<f; k++){
				if(frame[0][k]==arr[i]){
					frame[1][k]=1;
					break;
				}
			}
			if(k>=f){
				int pos=distance(frame[1], max_element(frame[1], frame[1]+f));
				frame[0][pos]=arr[i];
				frame[1][pos]=1;
				pagefault++;
			}
			
			for(int a=0; a<f; a++){
				if(frame[0][a]==-1)
					cout<<" "<<",";
				else
					cout<<frame[0][a]<<",";
			}
			cout<<" : "<<pagefault<<endl;
		}
		cout<<"Total page faults in LRU: "<<pagefault<<endl;
	}
	int* genPageString(int n)		//Automatically generate n pages
	{
		int* arr=new int[n];
		for (int i = 0; i < n; i++)
			arr[i] = rand()%10;		//randomly assign pages to array of pages
		return arr;
	}
};

main(){
	
	//srand(time(0));
	replaceAlgo rep;
	int len, frame;
	
	lab1:		//label for recusion
	cout<<"Length of pages' string must atleast 5: ";
	cin>>len;
	if(len<5)
	{
		goto lab1;		//if less the 5 page items then go to lab1 for reenter
	}
	
	int* pageArray = rep.genPageString(len); //generate random array of the len pages
	
	for (int i = 0; i < len; i++)		//display the array of pages
		cout<<pageArray[i]<<","; 
		
	reenter:		//label for recusion
	cout<<"\nframes must be between 1 to 7: ";	
	cin>>frame;
	if(frame<0 || frame>7)		//frames checking if less than 0 or greater than 7
	{
		goto reenter;		//repeat label
	}
	
	rep.fifoAlgo(len, frame, pageArray);
	rep.lruAlgo(len, frame, pageArray);
	
	return 0;
}
