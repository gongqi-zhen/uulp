#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>

#define PAGELEN 24
#define LINELEN 512

void do_more(FILE *);
int see_more(FILE *);
void tty_mode(int );
void set_term_noecho(void);
void set_nodelay_mode(void);

int main(int ac, char *av[])
{
	FILE *fp;

	tty_mode (0);
  set_term_noecho();
  set_nodelay_mode();
	if ( ac == 1 )
		do_more (stdin);
	else
		while ( --ac ) {
			if ( ( fp = fopen ( *++av, "r" )) != NULL ) {
				do_more (fp);
				fclose (fp);
			} else
				exit(1);
		}
	tty_mode (1);
	return 0;
}

void do_more ( FILE *fp )
{
	char line[LINELEN];
	int reply;
	int num_of_lines = 0;
	FILE *tty_ptr;

	tty_ptr = fopen ("/dev/tty", "r");
	if ( tty_ptr == NULL ){
		perror("fopen tty"); exit(1);
	}
	
	while ( ( fgets ( line, LINELEN, fp )) != NULL ) {
		if ( num_of_lines == PAGELEN ) {
			reply = see_more(tty_ptr);
			if ( reply == 0 )
				break;
			num_of_lines -= reply;
		}
		if ( fputs ( line, stdout ) == EOF )
			exit(0);
		num_of_lines++;
	}
	
}

int see_more ( FILE *cmd )
{
	int c;
	
	printf("see more?");
	while ( ( c = fgetc (cmd)) != EOF ) {
		if ( c == 'q' )
			return 0;
		if ( c == ' ' )
			return PAGELEN;
		if ( c == '\n' )
			return 1;
	}

	return 1;

}

void tty_mode(int how)
{
	static struct termios attribute;
	static int save = 0;

	if ( how == 0 ) {
		tcgetattr ( 0, &attribute );
		save = 1;
	} else if ( save == 1 ) {
		tcsetattr ( 0, TCSANOW, &attribute );
	}
}

void set_term_noecho(void)
{
	struct termios attribute;

	tcgetattr ( 0, &attribute );
	attribute.c_lflag &= ~ECHO;
	attribute.c_lflag &= ~ICANON;
	attribute.c_cc[VMIN] = 1;
	tcsetattr ( 0 , TCSANOW, &attribute );

}

void set_nodelay_mode(void)
{
	int termflags;

	termflags = fcntl(0, F_GETFL); /* read curr. settings▸-*/
	termflags |= O_NDELAY; /* flip on nodelay bit▸-*/
	fcntl(0, F_SETFL, termflags); /* and install 'em▸-*/
}

