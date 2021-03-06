// SESSION    : 2016-17
// LAB        : PROGRAMMING TOOLS - II
// ASSIGNMENT : #6
	
// PROBLEM    : #3

// CODE : -

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

int status;
void sig_handler(int sig)
{
	printf("This is the CUSTOM signal handler\n");
	if ( WIFEXITED(status) )
	{
		printf("\tChild's Termination was NORMAL.\n");
		printf("\tThe exit status returned by the child is :: %d\n",WEXITSTATUS(status));
	}
	else
		printf("\tChild's Termination was ABNORMAL\n");

}

int main()
{
	signal(SIGCHLD,sig_handler);
	
	pid_t pid = fork();
	if( pid != 0 )		//PARENT SHALL EXECUTE IN THIS BLOCK
	{
		wait( &status );
		printf("This is PARENT'S process\n\n");
	}
	else
	{
		//CHILD SHALL EXECUTE IN THIS BLOCK
		printf("This is CHILD'S process\n");
		
		char option;
		printf("\nHow do you wish to terminate the child?\n\t1. Normally\n\t2. Abnormally\nYour Response ::");
		if((option = getchar()) == '1')
		{
			printf("\nWhat (8 bit) value should the child return to the parent? :: ");
			int op;
			scanf("%d",&op);
			printf("\n");
			exit(op);
		}
		else
			abort();	//abnormal termination
	}
}
