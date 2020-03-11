#include <fcntl.h> 
#include <stdlib.h> //write
#include <unistd.h> //read
#include <err.h> //err
#include <sys/types.h> //open
#include <sys/stat.h>	//open
 #include <string.h> //open

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		err(1, "Error! There should be /etc/passwd and a file to copy it in as an argument");
		exit(1);
	}

	int bytesRead;
	char buff[1];

	
	int fd1;
	int fd2;

	if( (fd1 = open(argv[1], O_RDONLY)) == -1 )
	{
		err(2,"Error! File %s failed to open for reading!", argv[1]);
	}


	if( (fd2 = open(argv[2], O_WRONLY | O_CREAT, S_IRWXU)) == -1 )
	{
		err(3,"Error! File %s failed to open for reading!", argv[2]);
	}
		
	while ( (bytesRead = read(fd1, &buff, sizeof(buff))) > 0 )
	{
		if(buff[0]==':')
		{ 
			buff[0]='?';
		}
		//if(strcmp((const char*)buff,":")==0) { buff[0]='?'; }
		write(fd2, &buff, bytesRead);
	}
		
	close(fd1);		
	close(fd2);

	exit(0);
}
