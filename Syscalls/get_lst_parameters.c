#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <linux/syscalls.h>
#include <linux/lst_params.h>

asmlinkage long sys_get_lst_parameters(int pid, struct lst_params *lst_arguments)
{
	struct task_struct *task;
	int found = 0;
	int remaining_computation_time = 0.0;
	unsigned int utime = 0, stime = 0;
	int total_time = 0;

	printk("get_list_parameters: Giannis Aggelogiannis 2556 \n");

	if((lst_arguments == NULL) || (pid < -1))
	{
		return((long)22);	/* error value for EINVAL */
	}

	if(pid == -1)
	{
		if(access_ok(VERIFY_WRITE,lst_arguments,sizeof(struct lst_params)) == 0)
		{
			printk("lst_arguments is not accessible!\n");
			return((long)22);
		}

		utime = cputime_to_usecs(current->utime);
		stime = cputime_to_usecs(current->stime);
		total_time = utime + stime;
		remaining_computation_time = current->remaining_computation_time - total_time;
		current->remaining_computation_time = remaining_computation_time;

		if(copy_to_user(&lst_arguments->remaining_computation_time,&remaining_computation_time,sizeof(int)) != 0)
		{
			printk("can not copy to lst_arguments->remaining_computation_time\n");
			return((long)22);
		}
		if(copy_to_user(&lst_arguments->deadline,&current->deadline,sizeof(time_t)) != 0)
		{
			printk("can not copy to lst_arguments->deadline\n");
			return((long)22);
		}
		found = 1;
		return((long)0);	/* returns 0 uppon success */
	}
	else
	{
		for_each_process(task)
		{
			printk("%s [%d]\n",task->comm,task->pid);
			if(pid == task->pid)
			{
				if(access_ok(VERIFY_WRITE,lst_arguments,sizeof(struct lst_params)) == 0)
                		{
                        		printk("lst_arguments is not accessible!\n");
                        		return((long)22);
                		}
				utime = cputime_to_usecs(task->utime);
				stime = cputime_to_usecs(task->stime);
        		        total_time = utime + stime;
		                remaining_computation_time = task->remaining_computation_time - total_time;
				task->remaining_computation_time = remaining_computation_time;

                		if(copy_to_user(&lst_arguments->remaining_computation_time,&remaining_computation_time,sizeof(int)) != 0)
                		{
                		        printk("can not copy to lst_arguments->remaining_computation_time\n");
                		        return((long)22);
                		}
                		if(copy_to_user(&lst_arguments->deadline,&task->deadline,sizeof(time_t)) != 0)
                		{
                		        printk("can not copy to lst_arguments->deadline\n");
                		        return((long)22);
                		}
				found = 1;
				return ((long)0); /* returns 0 uppon success */
			}
		}
	}

	if(found == 0)
	{
		return((long)22);	/* error value for EINVAL */
	}

        return((long)0); 		/* returns 0 uppon success */
}
