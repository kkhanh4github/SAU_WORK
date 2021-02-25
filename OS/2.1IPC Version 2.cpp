#include<iostream>
#include<cstring>
#include<stdlib.h>
#include<queue>

//gcc program.cpp -o program.exe
//program.exe

using namespace std;

class Application
{
	private:
		int appid;

		queue<string> receivedQ;	//this is the queue for msges that, received from other.
		queue<string> sentQ;		//this is the queue for msges that, sent to other.
	
	public:
		
		void setId(int id)			//when ever create the object the id must be passed to!
		{
			appid = id;
		}
		
		int getAppid()			//get the id of the app
		{
			return appid;
		}
		
		void sendMessage(string msge)		//the queue for sent messages for keeping track.
		{
			sentQ.push(msge);
		}
		
		void receiveMessage(string msge)			//the queue will represent all the received msges.
		{
			receivedQ.push(msge);
		}
				
		void sentMessages()		//the queue for sent messages for keeping track.
		{
			while(!sentQ.empty())
			{
				cout<< sentQ.front()<<"\n"<<endl;
				sentQ.pop();
			}
		}
		
		void receivedMessages()			//the queue will represent all the received msges.
		{
			if(!receivedQ.empty())
			{
				cout<<"\n\napp"<<appid<<": \n";
				while(!receivedQ.empty())
				{
					cout<<receivedQ.front() <<", ";
					receivedQ.pop();
				}	
			}
			else{
				cout<<"\n\napp"<<appid<<": is empty.\n"<<endl;
			}
		}
		
		bool anyMessage()
		{
		    if(receivedQ.empty())
		    {
		        return 0;
		    }
		    else{
		        return 1;   
		    }
		}
};

class mailBox		//is the place where two apps can communicate with each others.
{
	private:
		int mid;		//mail box id int type
		string msg;		//the message passing through one of the processes.
		//queue<string> msgQ;
		Application *sender, *receiver, *currentApp;
	public:
	
	    void setMid(int id)
		{
			mid = id;
		}
		
		int getMid()
		{
			return mid;
		}
		
		void send(Application *s, string message)
		{
		   // sender = s;
    	//	sender->sendMessage(message);
    		s->sendMessage(message);
    		cout<<"message sent\n";
		}
				
		void receive(Application *r, string message)
		{
		    //*receiver = r;cout<<"chk"
    		//.receiveMessage(message);
    		r->receiveMessage(message);
    		cout<<"message received!\n";
		}
		
		void showSent(Application *app)
		{
		    //*currentApp = app;
		    app->sentMessages();
		}
		
		void showReceived(Application *app)
		{
		    //*currentApp = app;
		    app->receivedMessages();
		}
		
		void hasMessage(Application *app)
		{
		    //*currentApp = app;
		    bool b;
		    b = app->anyMessage();
		    if(b){
		        cout<<"app"<<app->getAppid()<<" is not empty!";
		    }
		    else{
		        cout<<"app"<<app->getAppid()<<" is empty!";
		    }
		    
		}
		
		void dispMid()
		{
			cout<<" p"<<mid<<endl;
		}

};



main()
{
        char repeat;        // repeating condition local variable.
        string msg;         // what message is passing to.
        
        // no: n apps. Optionth app's received and sent messages
        int no, Option; 
        int chooseApp, source, destination; // chooseAppth app. source app. destination app. 
        mailBox mb;                     // mailBox instance.
        mb.setMid(1);
        
        appLabel:
        printf("How many apps you want to create: ");
        scanf("%d",&no);
		Application app[no];
		if(no>10){                          // no of app must not be more than 10.
		    printf("not more than 10!\n");
            goto appLabel;                  // jum for reentering the no of apps.
        }
        for(int i=0; i<no; i++){
        	app[i].setId(i);
     	}
    do{
        
        printf("Press 0 Send Message!\n");
        printf("Press 1 to see the received messages!\n");
        printf("Press 2 to see the sent messages!\n");
        printf("Press 3 to see the all apps received messages:!\n");
        printf("Press 4 to see that app has received messages or not!\n");
        printf("Press 5 for exit!\n"); 
        scanf("%d",&Option);
        
        if(Option==0)       //to send the Message from one Application to another one.
        {   
            sourceLabel:
            printf("Send Message, but keep remember!\nthat there is only {app0} to {app%d} apps\nFrom which app: ",no-1); 
            scanf("%d",&source);
                if(source>no-1 || source<0)    // the source must be in the created Apps bound.
                {
                    printf("choose the right one!\n");
                    goto sourceLabel;       // Just jum a step back to insert the correct value.
                }
            destLabel:
            printf("To which app: ");
            scanf("%d",&destination);
                if((destination>no-1 || destination <0) || destination == source)  // the destination must be in the created Apps bound and not be the source itself.
                {
                    printf("choose the right one!\n");
                    goto destLabel;                     // Just jum a step back to insert the correct value.
                }
            printf("Write the message:\n");
            cin>>msg;

            mb.send(&app[source], msg);    		//to send message from source to destination.
            mb.receive(&app[destination], msg);    //to send message from source to destination.
            
        }
        else if(Option==1)
		{
		    chooseReceiver:
		    printf("which app's you want to see received messages: ");
		    cin>>chooseApp;
		    if(chooseApp>no-1 || chooseApp<0)    // the source must be in the created Apps bound.
            {
                printf("choose the right one!\n");
                goto chooseReceiver;                 // Just jum a step back to insert the correct value.
            }
            else{
                mb.showReceived(&app[chooseApp]);        //show the passing app received messages.
            }
        	
		}
		else if(Option==2)
		{
		    chooseSender:
		    printf("which app's you want to see sent messages: ");
		    cin>>chooseApp;
		    if(chooseApp>no-1 || chooseApp<0)    // the source must be in the created Apps bound.
            {
                printf("choose the right one!\n");
                goto chooseSender;                 // Just jum a step back to insert the correct value.
            }
            else{
                mb.showSent(&app[chooseApp]);    // show the passing app sent messages.
            }
		}
		
		else if(Option==3)
		{
		    printf("\nlist of all apps messages:\n");
		    for(int i=0; i<no; i++)
		    {
		    	mb.showReceived(&app[i]);
			}
		}
		
		else if(Option==4)
		{
		    goHere:
		    printf("there is only {app0} to {app%d} apps: ",no-1); 
            
		    printf("\nwhich app's you want to check that it has received messages: ");
		    cin>>chooseApp;
		    if(chooseApp>no-1 || chooseApp<0)    // the app must be in the created Apps bound.
            {
                printf("choose the right one!\n");
                goto goHere;                 // Just jump a step back to insert the correct value.
            }
            else{
                mb.hasMessage(&app[chooseApp]);    // show the passing app has messages or not.
            }
		}
		else if(Option==5)      // for exit Option if you terminate the program!
		{
		    exit(0);            // built in function.
		}
    	else{
    	    printf("Wrong input!");
    	}
    	
    	printf("\nDo you want to continue?");
    	printf("\nPress Y/N: ");
    	
    	scanf(" %c",&repeat);
    }while(repeat == 'y' || repeat=='Y');
}


