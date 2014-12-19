#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <linux/syscalls.h>

asmlinkage long sys_set_lst_parameters(int pid, int remaining_computation_time, time_t deadline)
{
	struct task_struct *task;
	int found = 0;

	printk("set_list_parameters: Giannis Aggelogiannis 2556 \n");

	if(remaining_computation_time > deadline)
	{
		return ((long)22); /* error value for EINVAL */
	}

	if(pid == -1)
	{
		current->remaining_computation_time = 1000000 * remaining_computation_time;
		current->deadline = deadline;
		found = 1;
		return((long)0);
	}
	else
	{
		for_each_process(task)
		{
			printk("%s [%d]\n",task->comm,task->pid);
			if(pid == task->pid)
			{
				found = 1;
				task->remaining_computation_time = 1000000 * remaining_computation_time;
				task->deadline = deadline;
				return((long)0);
			}
		}
	}

	if((pid < -1) || (found == 0))
	{
		return ((long)22); /* error value for EINVAL*/
	}

	return((long)0);
}
