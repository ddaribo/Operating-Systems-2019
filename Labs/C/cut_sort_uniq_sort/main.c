#include <fcntl.h> 
#include <stdlib.h> //write
#include <unistd.h> //read
#include <err.h> //err
#include <stdio.h> //printf
#include <sys/stat.h>	//open
#include <sys/types.h> //wait
#include <sys/wait.h> //wait


int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		err(1, "Error with args.");
	}

	const int R = 0;
	const int W = 1;

	int pd[2];

	if (pipe(pd) == -1) {
		err(1, "Could not create first pipe");
	}

	pid_t child1 = fork();

	if(child1 == -1)
	{
		err(2, "cannot fork");
	}
	
	if(child1 == 0)
	{
		close(pd[R]);
		dup2(pd[W],1);
		close(pd[W]);

		if( execlp("cut", "cut", argv[1], "-d:", "-f", "7", 0) == -1 )
		{
			err(3, "Could not exec.");
		}
	}


	int pd2[2];
	
	if (pipe(pd2) == -1) {
		err(3, "Could not create second pipe");
	}

	pid_t child2 = fork();
	
	if(child2 == 0)
	{
		dup2(pd2[R],0);
		dup2(pd2[W],1);
		close(pd2[R]);
		close(pd2[W]);
		
		if( execlp("sort", "sort", 0) == -1 )
		{
			err(4, "Could not exec.");
		}
	}

	
	int pd3[2];

	if (pipe(pd3) == -1) {
		err(4, "Could not create second pipe");
	}

	pid_t child3 = fork();

	if(child3 == 0)
	{
		close(pd3[W]);
		dup2(pd3[R],0);
		close(pd3[R]);

		if( execlp("uniq", "uniq", "-c", 0) == -1 )
		{
			err(5, "Could not exec.");
		}
	}


	wait(NULL);
	
	
	exit(0);
}
