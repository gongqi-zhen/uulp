#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{

	int fd;
	char buf[10] = "hello";

	if (( fd = open ("./HOGE", O_RDWR) ) == -1 ){
			perror ("HOGE");
			exit(1);
	}

	if (  lseek ( fd , 20000, SEEK_END ) == -1 ) {
			perror( " lseek ");
			exit(1);
	}

	if ( write ( fd, buf, sizeof(buf) ) == -1 ){
			perror(" write ");
			exit(1);
	}
	return 0;

}

