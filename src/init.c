#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void
jikan_init_tracking(void)
{
	struct stat st = {0};
	const char path[10] = "./.jikan/";

	if (stat(path, &st) == -1)
		mkdir(path, 0700);

	jikan_log(INFO, "sucessfully initialized Jikan!");
}
