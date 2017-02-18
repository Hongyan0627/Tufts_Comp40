#include <stdlib.h>
#include <stdio.h>
#include "cputiming.h"


int
main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	int i;
	double sum;
	CPUTime_T timer;
	double time_used; 
	const int outerlooptimes = 8;
	int outerct;
	int innerlimit = 1;

	timer = CPUTime_New();


	for (outerct = 0; outerct < outerlooptimes; outerct++) {
		sum = 0.0;
		CPUTime_Start(timer);
		for (i = 0; i< innerlimit; i++) {
			sum += i;
		}
		time_used = CPUTime_Stop(timer);
		printf ("Sum %.0f was computed in %.0f nanoseconds\n", sum, time_used);
		innerlimit *= 10;
	}

	CPUTime_Free(&timer);

	return EXIT_SUCCESS;
}

 
