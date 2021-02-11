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
	sem_t *s14=sem_open("s14",0);
	sem_t *s3=sem_open("s3",0666,0);       
       	sem_t *s4=sem_open("s4",0666,0);

      	pid_t p1;	
	key_t key=ftok("msg",65);

	int msgid;
	msgid=msgget(key,0666|IPC_CREAT);
	buff=new struct mymesg();                                                                                     
	
	sem_wait(s14);
	msgrcv(msgid,buff,512,0,0);
	p1=buff->type;
	cout<<"pid of p1 is : "<<p1<<endl;
	cout<<"my pid is : "<<getpid()<<endl;
	buff->type=getpid();
	msgsnd(msgid,buff,512,0);
	sem_post(s34);


	sem_wait(s3);               
	msgrcv(msgid,buff,512,getpid(),0);
	sleep(2);
	cout<<"mess->"<<buff->data<<endl;  
	char mess[]="this is message from p4 to p1";
	strcpy(buff->data,mess);
	buff->type=p1;    
	int n=strlen(buff->data);
	msgsnd(msgid,buff,n,0);
	sem_post(s4);

}
	

