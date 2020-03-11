#include <fcntl.h> 
#include <stdlib.h> //write
#include <unistd.h> //read
#include <err.h> //err
#include <sys/types.h> //open
#include <sys/stat.h>	//open
#include <stdio.h> //printf
#include <string.h> //strcmp
#include <stdint.h> //uint16_t


int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		err(1, "Error! There should be exactly 2 arguments for the program!");
		exit(1);
	}

	if( strcmp(argv[1],"--min") != 0 && strcmp(argv[1],"--max") != 0 && strcmp(argv[1],"--print") != 0 )
	{
		err(2, "Error! The given arguments are not among --min, --max or --print!");
		exit(2);
	}
	
	int fd;
	
	if( (fd = open(argv[2], O_RDONLY)) == -1 )
	{
		err(2,"Error! File %s failed to open for reading!", argv[2]);
		exit(2);
	}

	//FILE *f = fopen(argv[2], "r");
	
	ssize_t read_size;

	uint16_t min = UINT16_MAX;
	uint16_t max = 0;
	
	uint32_t myNum;


	if( strcmp(argv[1],"--min") == 0)
	{
		while ( (read_size = read(fd, &myNum, sizeof(myNum))) > 0 )
		{
			//printf("%d\n",myNum.n);
			if(myNum < min)
			{
				min=myNum;
			}
		}
		printf("%d\n",min);
		
	}
	else if( strcmp(argv[1],"--max") == 0)
	{
		while ( (read_size = read(fd, &myNum, sizeof(myNum))) > 0 )
		{
			//printf("%d\n",myNum.n);
			if(myNum > max)
			{
				max=myNum;
			}
		}
		printf("%d\n",max);
	}
	else if ( strcmp(argv[1],"--print") == 0)
	{
		while ( (read_size = read(fd, &myNum, sizeof(myNum))) > 0 )
		{
			printf("%d ",myNum);
		}
	}
	

	/*if( strcmp(argv[1],"--min") == 0)
	{
		while ( (read_size = fread(&myNum, sizeof(myNum),1,f)) > 0 )
		{
			//printf("%d\n",myNum.n);
			if(myNum < min)
			{
				min=myNum;
			}
		}
		printf("%d\n",min);
		
	}
	else if( strcmp(argv[1],"--max") == 0)
	{
		while ( (read_size = fread(&myNum, sizeof(myNum),1,f)) > 0 )
		{
			//printf("%d\n",myNum.n);
			if(myNum > max)
			{
				max=myNum;
			}
		}
		printf("%d\n",max);
	}
	else if( strcmp(argv[1],"--print") == 0)
	{
		while ( (read_size = fread(&myNum, sizeof(myNum),1,f)) > 0 )
		{
			printf("%d\n",myNum);
		}
	}

	//fclose(f);*/
	close(fd);
	exit(0);

}
