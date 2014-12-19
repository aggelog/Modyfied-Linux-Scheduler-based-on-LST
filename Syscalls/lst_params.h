#ifndef _LINUX_LST_PARAMS_H
#define _LINUX_LST_PARAMS_H

#include <linux/types.h>

struct lst_params {			/* info and times about the process */
        int remaining_computation_time; /* time limit for this process */
	time_t deadline;		/* process's deadline */
};

#endif

