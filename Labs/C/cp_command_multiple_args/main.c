#include <fcntl.h> 
#include <stdlib.h> //write
#include <unistd.h> //read
#include <err.h> //err
#include <sys/types.h> //open
#include <sys/stat.h>	//open


int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		err(1, "Error! There should be at least two file-arguments for the program!");
		exit(1);
	}

	int argCount=1;
	int bytesRead;
	char* buff[4096];

	while(argCount < argc)
	{
		int fd1;
		int fd2;

		if( (fd1 = open(argv[argCount], O_RDONLY)) == -1 )
		{
			err(2,"Error! File %s failed to open for reading!", argv[argCount]);
			argCount++;
			continue;
		}

		argCount++;

		if( (fd2 = open(argv[argCount], O_WRONLY | O_CREAT, S_IRWXU)) == -1 )
		{
			err(3,"Error! File %s failed to open for reading!", argv[argCount]);
			argCount++;
			continue;
		}
		
		while ( (bytesRead = read(fd1, buff, sizeof(buff))) > 0 )
		{
			write(fd2, buff, bytesRead);
		}
		
		close(fd1);		
		close(fd2);

		argCount++;
	}

	exit(0);
}
