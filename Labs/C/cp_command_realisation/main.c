#include <unistd.h> //read
#include <sys/types.h> //read
#include <stdio.h> //read
#include <stdlib.h> //read
#include <sys/stat.h> //open
#include <fcntl.h> //open
#include <err.h> //open

int main(int argc, char *argv[])
{
        if (argc != 3)
        {
                err(2,"Error! Not enough arguments!");
                exit(1);
        }

        int fd1;
        int fd2;

        if ( (fd1=open(argv[1], O_RDONLY)) == -1)
        {
                //Chisloto 2 ne e che izveshda na stderr a e kod na greshkata!
                err(2,"Error! Failed to open %s for reading", argv[1]);
                exit(2);
        }

        //cp - ako vtoriyat file ne sushtestuva, komandata go suzdava

        if ( (fd2=open(argv[2], O_WRONLY | O_CREAT, S_IRWXU)) == -1 )
        {
                err(3, "Error! Failed to open %s for reading", argv[2]);
                exit(3);
        }

        char* buff[4096];
        int bytesRead;

        while( (bytesRead = read(fd1, buff, sizeof(buff))) > 0 )
        {
                write(fd2, buff, bytesRead);
        }

        close(fd1);
        close(fd2);

        exit(0);
}

