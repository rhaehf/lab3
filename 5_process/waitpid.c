/* waitpid를 사용하여 자식의 퇴장 상태를 어떻게 알아내는지 보여준다 */
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
int main()
{
	pid_t pid;
	int status, exit_status;
	if ((pid = fork()) < 0)
		fatal (“fork failed”);
	if (pid == 0) /* 자식 */
	{
		sleep (4); /* 수행을 4초 동안 중단 */
		exit (5);
	}
/* 부모 코드 : 자식이 퇴장했는지 확인한다. 
퇴장하지 않았으면, 1초 동안 잠든 후 다시 검사한다. */
	while (waitpid (pid, &status, WNOHANG) == 0) {
		printf (“still waiting… \n”);
		sleep (1);
}
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS (status);
		printf (“Exit status from %d was %d\n”, pid, exit_status);
	}
	exit (0);
}

/* zombie 프로세스 실행 확인 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(void)
{
	pid_t pid;

	if ((pid = fork()) < 0) {
		perror("folk");
	exit(1);
	}
	else if (pid == 0) /* child */
	exit(0);
/* parent */
	sleep(4);
	system("ps -o pid,ppid,state,tty,command");
	exit(0);
}
