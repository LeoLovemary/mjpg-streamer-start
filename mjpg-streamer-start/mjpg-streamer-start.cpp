#include <iostream>
#include "errno.h"
#include "unistd.h"
#include "sys/wait.h"
#include "stdlib.h"
#include "sys/types.h"
#include "stdio.h"
#include "string.h"


/*
 *使用的时候需要将生成的可执行文件移动到和mjpg可执行目录.
 **/



using namespace std;

#define  ERR_EXIT(msg) \
	do \
	{ \
		perror(msg); \
		exit(EXIT_FAILURE); \
	} while (0)\

int main(int argc, char *argv[])
{
	
	int pid;

	while (1) {
		pid = fork();

		if (pid < 0)
			ERR_EXIT("fork");

		if (pid == 0) {
			//child
			execl("mjpg_streamer", "-o", "output_http.so -w ./www", "-i", "input_uvc.so", NULL);
			exit(-1);
		}
		else {
			cout << "child pid = " << pid << endl;
			
			pid = wait(NULL);
			sleep(1);
			cout << "child exit restarting ... " << endl;
			continue;
		}



	}

	

	return 0;
}