#include <fcntl.h> 
#include <stdlib.h> //write
#include <unistd.h> //read
#include <err.h> //err
#include <sys/types.h> //open
#include <sys/stat.h>	//open


int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		err(1, "Error! There should be at least one argument for the program!");
		exit(1);
	}

	int argCount=1;
	int bytesRead;
	char* buff[4096];

	while(argCount < argc)
	{
		int fd;
		
		if( (fd = open(argv[argCount], O_RDONLY)) == -1 )
		{
			err(2,"Error! File %s failed to open for reading!", argv[argCount]);
			continue;
		}
		
		while ( (bytesRead = read(fd, buff, sizeof(buff))) > 0 )
		{
			write(1, buff, bytesRead);
		}
		
		close(fd);		
		
		argCount++;
	}

	exit(0);
}
