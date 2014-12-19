#ifndef _LINUX_LST_PARAMS_H
#define _LINUX_LST_PARAMS_H

#include <time.h>

struct lst_params {
	int remaining_computation_time;
	time_t deadline;
};

#endif
