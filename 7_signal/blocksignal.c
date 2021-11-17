/* blocksignal.c */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int sigprocmask(int how, const sigset_t *set, sigset_t *oset);

int main()
{	
	sigset_t set1, set2;
	
	/*fill set1 */
	sigfillset (&set1); 
	/*set up set 2 with just SIGINT*/
	sigemptyset (&set2);
	sigaddset (&set2, SIGINT);	
	printf("Critical region start. \n");
	
	sigprocmask(SIG_BLOCK, &set1, NULL); /*block*/
	sleep(5);
	printf("Less critical region start. \n");
	
	sigprocmask(SIG_UNBLOCK, &set2, NULL); /* unblock SIGINT */
	sleep(5);
	printf("Non critical region start. \n");
	
	sigprocmask(SIG_UNBLOCK, &set1, NULL); /*unblock all*/
	sleep(5);
}
