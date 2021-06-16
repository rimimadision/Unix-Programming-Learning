#include "stdio.h"
#include "utmp.h"
#include "fcntl.h"
#include "unistd.h"

#define MYWHOSHOWHOST /* include remote machine in output */

void showinfo(struct utmp* rec);

int main()
{
	struct utmp rec;
	int utmpfd = -1;
	int reclen = sizeof(struct utmp);
 
	if((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1)
	{	
		perror(UTMP_FILE);
	}
		
	while(read(utmpfd, &rec, reclen) == reclen)
	{
		showinfo(&rec);
	}

	close(utmpfd);

	return 0;	
}

void showinfo(struct utmp* rec)
{
	printf("%-8.8s ", rec->ut_name);
	printf("%-8.8s ", rec->ut_line);
	printf("%10d ", rec->ut_time);
	#ifdef MYWHOSHOWHOST
	printf("(%s)", rec->ut_host);
	#endif
	printf("\n");
}
