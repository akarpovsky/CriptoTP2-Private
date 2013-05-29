#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <string.h>

#include "cmdline.h"


char *path_cat (const char *str1, char *str2);

int
main(int argc, char **argv)
{

	struct gengetopt_args_info *args_info = malloc(sizeof(struct gengetopt_args_info));

	if(cmdline_parser(argc, argv, args_info) != 0) {
		return EXIT_FAILURE;
	}

}
