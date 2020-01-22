/** ls qsort sample
 **   purpose  list contents of directory or directories
 **   action   if no args, use .  else list files in args
 **/
#include	<stdio.h>
#include	<sys/types.h>
#include	<dirent.h>
#include <string.h>
#include <stdlib.h>

void do_ls(char []);

int compare_string(const void *a, const void *b);

int main(int ac, char *av[])
{
	if ( ac == 1 )
		do_ls( "." );
	else
		while ( --ac ){
			printf("%s:\n", *++av );
			do_ls( *av );
		}
}

void do_ls( char dirname[] )
/*
 *	list files in directory called dirname
 */
{
	DIR		*dir_ptr;		/* the directory */
	struct dirent	*direntp;		/* each entry	 */
	char *buf[BUFSIZ];
	int i = 0;
	int j = 0;

	if ( ( dir_ptr = opendir( dirname ) ) == NULL )
		fprintf(stderr,"ls1: cannot open %s\n", dirname);
	else
	{
		while ( ( direntp = readdir( dir_ptr ) ) != NULL ){
			if(direntp->d_name[0] == '.')
				continue;
			buf[i] = direntp->d_name;
			i++;
//			printf("%s\n", direntp->d_name );
		}
		closedir(dir_ptr);
	}
	printf("=== BEFORE SORT ===\n");
	for( j = 0; j < i; j++)
		printf("%s\n",buf[j]);

	printf("=== AFTER SORT ===\n");
	qsort(buf, i, sizeof(*buf), compare_string);
	for( j = 0; j < i; j++)
		printf("%s\n",buf[j]);

}

 int compare_string(const void *a, const void *b)
 {
   return strcmp(*(const char **)a, *(const char **)b);
 }
