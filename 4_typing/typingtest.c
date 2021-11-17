#include <stdio.h>
#include <termios.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int main (void){
	int fd;
	int nread, cnt=0, errcnt=0;
	char ch, text[] = "The magic thing is that you can change it.";
	struct termios init_attr, new_attr;
	time_t start_time, end_time;
	//speed_t speed;
	
	fd = open(ttyname(fileno(stdin)), O_RDWR);
	tcgetattr(fd, &init_attr);	
	new_attr = init_attr;
	new_attr.c_lflag &= ~ICANON;
	new_attr.c_lflag &= ~ECHO;
	new_attr.c_cc[VMIN] = 1;
	new_attr.c_cc[VTIME] = 0;
	if(tcsetattr(fd, TCSANOW, &new_attr) != 0){
		fprintf(stderr, "터미널 속성을 설정할 수 없음.\n");
	}
	printf("다음 문장을 그대로 입력하세요.\n%s\n", text);
	start_time = time(NULL);
	while ((nread=read(fd, &ch, 1)) > 0 && ch != '\n') {
		if (ch == text[cnt++])
			write(fd, &ch, 1);
		else {
			write(fd, "*", 1);
			errcnt++;
		}
	}
	end_time = time(NULL);
	double diff_timer = difftime(end_time, start_time);
	int text_len = strlen(text);
	printf("\n타이핑 오류의 횟수는 %d\n", errcnt);
	printf("분당 타자수는 %lf\n", text_len/diff_timer*60);
	//speed = cfgetispeed(&new_attr);
	//printf("%d", speed);
	tcsetattr(fd, TCSANOW, &init_attr);
	close(fd);
}
