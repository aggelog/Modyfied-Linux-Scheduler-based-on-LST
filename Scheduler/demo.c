#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "lst_params.h"

long sys_set_lst_parameters(int pid, int remaining_computation_time, time_t deadline)
{
	syscall(341,pid,remaining_computation_time,deadline);                                       
}

int main(int argc, char **argv)
{
	int k,i,pid=1;
	int status;
	struct timeval tv;
	time_t current_time;
	
	if(argc != 2)
	{
		k = 2;
	}
	else
	{
		k = atoi(argv[1]);
	}

	printf("This is k = %d\n",k);
	printf("Im the original process with PID: %d and PPID: %d.\n",getpid(),getppid());
	for(i = 0; i < k; i++)
	{
		if(pid >= 1)
		{
			pid = fork();
			if(pid != 0)
			{
				printf("I'm the parent process with PID: %d and PPID: %d.\n",getpid(),getppid());
				printf("My child's PID is %d\n",pid);
				gettimeofday(&tv, NULL);
				current_time = tv.tv_sec;
				if((status = sys_set_lst_parameters(pid,(i+5),(current_time+100))) == 0)
				{
					fprintf(stdout,"set_lst_parameters successfully ended! \n");
				}
				else
				{
					fprintf(stderr,"set_lst_parameters failled!\n");
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				printf("I'm the child process with PID: %d and PPID: %d.\n",getpid(),getppid());
				//printf("=== i = %d\n",i);
				sleep(i);
				printf("=== i === %d\n",i);
			}
		}
	//	else
	//	{
//
	//		printf("I'm the child process with PID: %d and PPID: %d.\n",getpid(),getppid());
//
		//}
		//printf("PID %d terminates.\n",getpid());
	}	
	printf("PID %d terminates.\n",getpid());
	return 0;
}
