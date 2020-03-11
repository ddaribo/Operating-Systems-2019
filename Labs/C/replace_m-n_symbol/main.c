#include <fcntl.h> 
#include <stdlib.h> //write
#include <unistd.h> //read
#include <err.h> //err
#include <sys/types.h> //open
#include <sys/stat.h>	//open

int main(int argc, char* argv[])
{
	if (argc < 5)
	{
		err(1, "Error! There should be four arguments for the program!");
		exit(1);
	}

	int fd;
	char buff;
	
	if( (fd = open(argv[1], O_RDWR)) == -1 )
	{
		err(2,"Error! File %s failed to open for reading!", argv[1]);
		exit(2);
	}
	
	ssize_t read_size;

	int chars_to_read = (argv[3] - argv[2]);
	int start_offset = atoi(argv[2]);
	
	lseek(fd, start_offset, SEEK_SET);

	while(chars_to_read >= 0 )
	{
		if ( (read_size = read(fd, &buff, 1)) > 0 )
		{
			lseek(fd, -1, SEEK_CUR);
			if (write(fd, argv[4], 1) != read_size) {
				close(fd);
				err(3, "Error writing!");
				exit(3);
			}
		}
		chars_to_read-=1;
	}

	/*ili prosto 
	while(start_offset <= arv[3])
	{
		lseek(fd, start_offset - 1, SEEK_CUR);

		if ( (read_size = read(fd, &buff, 1)) > 0 )
		{
			if (write(fd, argv[4], 1) != read_size) {
				close(fd);
				err(3, "Error writing!");
				exit(3);
			}
		}

		start_offset++;
	}*/

	lseek(fd, 0, SEEK_SET);

	close(fd);
	exit(0);

}
