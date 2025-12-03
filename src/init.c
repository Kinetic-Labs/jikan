#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static void
jikan_init_tracking(void)
{
	struct stat st = {0};
	const char path[] = "./.jikan/";

	if (stat(path, &st) == -1) {
#if defined(_WIN32) || defined(__MINGW32__)
		mkdir(path);
#else
		mkdir(path, 0700);
#endif
	}

	jikan_log(INFO, "successfully initialized Jikan!");
}
