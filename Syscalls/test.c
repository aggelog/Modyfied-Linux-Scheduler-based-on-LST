#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include "lst_params.h"

long sys_set_lst_parameters(int pid, int remaining_computation_time, time_t deadline)
{
	syscall(341,pid,remaining_computation_time,deadline);
}

long sys_get_lst_parameters(int pid, struct lst_params *lst_arguments)
{
	syscall(342,pid,lst_arguments);
}

int main()
{
	int status;
	struct lst_params *ptr;
	int i;

	if((status = sys_set_lst_parameters(-1,100,200)) == 0)
	{
		fprintf(stdout,"set_lst_parameters successfully ended!\n");
	}
	else
	{
		fprintf(stderr,"set_lst_parameters failed! status :%d\n",status);
		exit(EXIT_FAILURE);
	}
	
	ptr = malloc(sizeof(struct lst_params));
	
	if( (status = sys_get_lst_parameters(-1,ptr)) == 0)
	{
		fprintf(stdout,"get_lst_parameters successfully ended!\n");
		fprintf(stdout,"remaining_computation_time = %d\n",ptr->remaining_computation_time);
		fprintf(stdout,"deadline = %d\n",ptr->deadline);
	}
	else
	{
		fprintf(stderr,"get_lst_parameters failed! status :%d\n",status);
	}
	
	for(i = 0; i < 1000000; i++)
	{
		i*=1;
	}
	
	if( (status = sys_get_lst_parameters(-1,ptr)) == 0)
	{
		fprintf(stdout,"get_lst_parameters successfully ended!\n");
		fprintf(stdout,"remaining_computation_time = %d\n",ptr->remaining_computation_time);
		fprintf(stdout,"deadline = %d\n",ptr->deadline);
	}
	else
	{
		fprintf(stderr,"get_lst_parameters failed! status :%d\n",status);
		exit(EXIT_FAILURE);
	}
	
	sleep(5);
	
	if( (status = sys_get_lst_parameters(-1,ptr)) == 0)
	{
		fprintf(stdout,"get_lst_parameters successfully ended!\n");
		fprintf(stdout,"remaining_computation_time = %d\n",ptr->remaining_computation_time);
		fprintf(stdout,"deadline = %d\n",ptr->deadline);
	}
	else
	{
		fprintf(stderr,"get_lst_parameters failed! status :%d\n",status);
		exit(EXIT_FAILURE);
	}
	
	return 0;
}
