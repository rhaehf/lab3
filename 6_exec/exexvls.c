/* exexvls.c */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() 
{
	char * const argv[] = {"ls", "-l", (char *) 0};
	printf("Executing execv.\n");
	
	execv("/bin/ls", argv);
	/* 만약 execv 이 복귀하면 호출은 실패. */
	perror("execv failed to run ls");
	exit(1);
}
