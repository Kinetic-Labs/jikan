#include "00_config.c"
#include "01_util.c"
#include "02_user_config.c"
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
	} else if (strcmp("help", command) == 0) {
		goto help;
	} else {
		goto usage;
	}

init:
	jikan_init_tracking();
	return 0;
setup:
	jikan_setup_user();
	return 0;
help:
	jikan_log(INFO, "usage: %s <setup,help> [...args]", NAME);
	return 0;
usage:
	jikan_log(ERROR, "usage: %s <command> [...args]", NAME);
	jikan_log(INFO, "run with 'help' command for more information");
	return 1;
}
