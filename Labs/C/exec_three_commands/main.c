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
	if (argc < 4)
	{
		err(1, "Error! The program requires three arguments - three commands to be executed!");
		exit(1);
	}

	for(int i = 1; i < 4; i++)
	{
		pid_t childpid=fork();
		int status_code;

		if(childpid < 0)
		{
			err(2, "Error!");
			exit(2);	
		}
		else if( childpid == 0 )
		{
			if (execlp(argv[i], argv[i],  0) == -1 )
			{ 
				err(2, "Error executing %s!", argv[i]);
			}
		}

	wait(&status_code);

		if ( WIFEXITED(status_code) )
		{
			printf("The executed process pid was: %d\n", childpid);
			int exit_status=WEXITSTATUS(status_code);
			printf("The executed process status was: %d\n", exit_status);
		}
	}
	
	exit(0);
}
