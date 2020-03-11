#include <fcntl.h> 
#include <stdlib.h> //write
#include <unistd.h> //read
#include <err.h> //err
#include <sys/types.h> //open
#include <sys/stat.h>	//open
#include <stdio.h> //printf
#include <sys/types.h> //wait
#include <sys/wait.h> //wait

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		err(1, "Error! The program requires one argument - a command to be executed!");
		exit(1);
	}
	
	int status;

	pid_t childpid=fork();

	if(childpid < 0)
	{
		err(2, "Error!");
		exit(2);	
	}
	else if( childpid==0 )
	{
		if (execlp("sort","sort","-d","-t"," ","-k","3",argv[1], 0) == -1 )
		{ 
			errx(2, "Error executing %s!", argv[1]);
		}
	}

	wait(&status);
	
	if(WEXITSTATUS(status) == 0)
		printf("The command was successfuly executed!\n");
	else
		errx(2, "Error executing !");
	
	exit(0);
}
