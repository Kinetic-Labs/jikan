#include "00_config.c"
#include "0_util.c"
#include "init.c"
#include "setup.c"
#include <stdio.h>
#include <string.h>

int
main(const int argc, char **argv)
{
	if (argc < 2)
		goto usage;

	const char *command = argv[1];
	if (strcmp("init", command) == 0) {
		goto init;
	} else if (strcmp("setup", command) == 0) {
		goto setup;
	} else {
		goto usage;
	}

init:
	jikan_init_tracking();
	return 0;
setup:
	jikan_setup_user();
	return 0;

usage:
	jikan_log(ERROR, "usage: %s <command> [...args]", NAME);
	return 1;
}
