#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h>
#define len 20

void hare(int fd1,int fd2){
     int j;
     int i=0;
     while(i<len){
     	sleep(1);
     	read(fd1,&j,sizeof(int));
     	if(i-j==5){
     		printf("Hmm its time to take a nap");
     		sleep(2);
     	}
     	i = i+2;
     	write(fd2,&i,sizeof(int));	
     }
	 
}

void turtle(int fd1,int fd2){
	int i = 0;
	while(i++<len)
		{
			sleep(1);
			write(fd1,&i,sizeof(int));
			write(fd2,&i,sizeof(int));
		}
}


void report(int fd1,int fd2){
	int tur,har;
	read(fd1,&tur,sizeof(int));
	read(fd2,&har,sizeof(int));
	while(tur!=len || har!=len){
		read(fd1,&tur,sizeof(int));
		read(fd2,&har,sizeof(int));
		printf("turtle = %d\n", tur);
		printf("hare = %d\n", har);
	}
	printf("Race is finished");
	if(har==len)printf("Hare won the race");
	if(tur==len)printf("Turtle won the race");
	exit(0);
}

int main(){
	    int hareAndTur[2];
	    int hareAndRep[2];
	    int turAndRep[2];

	    if(pipe(hareAndTur)==-1){
	    	printf("not able to create pipe1");
	    }

	    if(pipe(hareAndRep)==-1){
	    	printf("not able to create pipe2");
	    }

	    if(pipe(turAndRep)==-1){
	    	printf("not able to create pipe3");
	    }

	    int n1 = fork();

    	int n2 = fork(); 
	    
	    if (n1 > 0 && n2 > 0) {
	    turtle(hareAndTur[1],turAndRep[1]);  
	    } 
	    else if (n1 == 0 && n2 > 0) 
	    { 
		hare(hareAndTur[0],hareAndRep[1]);
	    } 
	    else if(n1>0 && n2 ==0){
	    report(turAndRep[0],hareAndRep[0]);	
	    }
}
