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
	sem_t *s12=sem_open("s12",0);
	sem_t *s23=sem_open("s23",0);
	sem_t *s1=sem_open("s1",0666,0);
			       
       	sem_t *s2=sem_open("s2",0666,0);
	pid_t p3;
	key_t key=ftok("msg",65);

	int msgid;
	msgid=msgget(key,0666|IPC_CREAT);
	buff=new struct mymesg();

	sem_wait(s23);
	msgrcv(msgid,buff,512,0,0);
	p3=buff->type;
	cout<<"pid of p3 is : "<<p3<<endl;
	cout<<"my pid is : "<<getpid()<<endl;
	buff->type=getpid();
	msgsnd(msgid,buff,512,0);
	sem_post(s12);
	
	sem_wait(s1);
	msgrcv(msgid,buff,512,getpid(),0);
	sleep(2);
	cout<<"mess->"<<buff->data<<endl;
	char mess[]="this is message from p2 to p3";
	                strcpy(buff->data,mess);
	buff->type=p3;
	int n=strlen(buff->data);
	msgsnd(msgid,buff,n,0);
	sem_post(s2);


}
