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
	sem_t *s12=sem_open("s12",O_CREAT,0666,0);
	sem_t *s14=sem_open("s14",O_CREAT,0666,0);
	sem_t *s23=sem_open("s23",O_CREAT,0666,0);
	sem_t *s34=sem_open("s34",O_CREAT,0666,0);
	sem_t *s1=sem_open("s1",O_CREAT,0666,0);
	
	sem_t *s2=sem_open("s2",O_CREAT,0666,0);

	sem_t *s3=sem_open("s3",O_CREAT,0666,0);

	sem_t *s4=sem_open("s4",O_CREAT,0666,0);
		key_t key=ftok("msg",65);
	        int msgid;
		pid_t p2;       
	       	msgid=msgget(key,0666|IPC_CREAT);
		buff=new struct mymesg();

		buff->type=getpid();
		cout<<"my pid is : "<<getpid()<<endl;
		msgsnd(msgid,buff,512,0);
		sem_post(s14);
		sem_wait(s12);
		msgrcv(msgid,buff,512,0,0);
		p2=buff->type;
		cout<<"pid of p2 is : "<<p2<<endl;

		char mess[]="this is message from p1 to p2";
		
		strcpy(buff->data,mess);
		buff->type=p2;
		int n=strlen(buff->data);
		msgsnd(msgid,buff,n,0);
		sem_post(s1);
		sem_wait(s4);
		msgrcv(msgid,buff,512,getpid(),0);
		sleep(2);
		cout<<"mess->"<<buff->data<<endl;

		msgctl(msgid,IPC_RMID,NULL);
}



