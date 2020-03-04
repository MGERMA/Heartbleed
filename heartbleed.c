// https://github.com/MGERMA/Heartbleed.git

// C program to illustrate 
// heartbleeding

#include <stdio.h> 
#include <unistd.h> 
#define MSGSIZE 15 
char* msg1 = "Shared Message";  
char* msg2 = "Secret Message"; 

int main() 
{ 
	char inbuf[MSGSIZE]; 
	int p1[2], pid, nbytes; 
	int lengthSend = 0;
	int p2[2], nbytes2; 
	int reqsize = 0;

	if (pipe(p1) < 0) 
		exit(1); 
	if (pipe(p2) < 0) 
		exit(1);
	/* continued */
	if ((pid = fork()) > 0) {
			while ((nbytes2 = read(p2[0], &lengthSend, sizeof(&lengthSend))) > 0) {
				printf("Sending %d chars of message 1\n", lengthSend); 
				write(p1[1], msg1, lengthSend); 
				close(p1[1]);
				exit(0);
			}
		printf("Finished sending\n"); 
		wait(NULL); 
	}

	else { 
			printf("How many characters do you want ?\n");
			scanf ("%d", &reqsize);
			printf("Requesting %d chars of message 1\n", reqsize); 
			write(p2[1], &reqsize, sizeof(&reqsize)); 
			close(p2[1]);
			while ((nbytes = read(p1[0], inbuf, MSGSIZE)) > 0)
				printf("%s \n", inbuf); 
			
		if (nbytes != 0) 
			exit(2); 
		printf("Finished reading\n"); 
	} 
	return 0; 
} 

