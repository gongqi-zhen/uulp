#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int ac, char *av[])
{

	int fd1, fd2, fd3;
	char buf[5];
	char wtest[13] = "testing 1 2 3";


	if ( ( fd1 = open ("./TEST", O_RDONLY)) == -1 ){
		perror( "fd1" );
		exit ( 1 );
	}
	
	if ( ( fd2 = open ("./TEST", O_WRONLY)) == -1 ){
		perror( "fd2" );
		exit ( 1 );
	}
	
	if ( ( fd3 = open ("./TEST", O_RDONLY)) == -1 ){
		perror( "fd3" );
		exit ( 1 );
	}

	if ( read ( fd1, buf, sizeof(buf) ) != -1 ) {
		write ( 1 , buf, sizeof(buf) );
	}

	write ( fd2, wtest, sizeof(wtest) );

	if ( read ( fd3, buf, sizeof(buf) ) != -1 ) {
		write ( 1 , buf, sizeof(buf) );
	}

	return 0;

}
