#include<bits/stdc++.h>
#include<unistd.h>                                                                                                  
#include<semaphore.h>
#include<fcntl.h>    
#include<sys/msg.h>

using namespace std;                                                                                                    
struct mymesg
{
	long type;
	char data[512];
} *buff;
int main()
{
	sem_t *s34=sem_open("s34",0);
	sem_t *s23=sem_open("s23",0);
	sem_t *s2=sem_open("s2",0666,0);
	       
       	sem_t *s3=sem_open("s3",0666,0);
		  
	pid_t p4;
	key_t key=ftok("msg",65);

	int msgid;
	msgid=msgget(key,0666|IPC_CREAT);
	buff=new struct mymesg();

	sem_wait(s34);
	msgrcv(msgid,buff,512,0,0);
	p4=buff->type;
	cout<<"pid of p4 is : "<<p4<<endl;
	cout<<"my pid is : "<<getpid()<<endl;
	buff->type=getpid();
	msgsnd(msgid,buff,512,0);
	sem_post(s23);

	sem_wait(s2);  
	msgrcv(msgid,buff,512,getpid(),0);
	 sleep(2);
	cout<<"mess->"<<buff->data<<endl;
        char mess[]="this is message from p3 to p4";
	                        strcpy(buff->data,mess); 
	buff->type=p4;  
	int n=strlen(buff->data);	
	msgsnd(msgid,buff,n,0);
	sem_post(s3);

}
