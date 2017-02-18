

#include "program_loader.h"
#include "UM.h"
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	size_t size = 1;
	struct stat statistics;
	FILE *input;

	if (argc != 2)
		return 1;
	else {
		/* only run programs with number of bytes divisible by 4 */
		if (stat(argv[1], &statistics) == 0)
			size = statistics.st_size;
			if (size % 4 == 0)
			 	input = fopen(argv[1], "r");
				Seg_T program = initial_load_program(input, 
					(uint32_t)(size / 4));
				fclose(input);
				return run_um(program);
		return 1;
	}
}