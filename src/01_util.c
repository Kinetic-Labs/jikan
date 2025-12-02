#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

enum LogLevel { INFO = 0, WARN, ERROR };

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch-default"
static void
jikan_log(enum LogLevel level, const char *format, ...)
{
	va_list args;
	va_start(args, format);

	switch (level) {
	case INFO:
		if (printf("info:  ") < 0)
			perror("printf");
		break;
	case WARN:
		if (printf("warn:  ") < 0)
			perror("printf");
		break;
	case ERROR:
		if (printf("error: ") < 0)
			perror("printf");
		break;
	}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-nonliteral"
	vprintf(format, args);
#pragma clang diagnostic pop
	va_end(args);

	if (printf("\n") < 0)
		perror("printf");
}
#pragma clang diagnostic pop

static bool
jikan_prompt_confirm(void)
{
	char confirm[4];

	if (printf("[y/n] ") < 0)
		perror("printf");
	if (scanf("%3s", confirm) != 1)
		perror("scanf error - reading y/n");

	return strncmp("y", confirm, 1) == 0;
}

static void
jikan_delete_newline(char *string)
{
	const int len = (int)strlen(string);
	if (len > 0 && string[len - 1] == '\n')
		string[len - 1] = '\0';
}

static int
jikan_get_home(char **home)
{
	*home = getenv("HOME");
	if (*home == NULL) {
		jikan_log(ERROR, "HOME environment variable not set!");
		return 1;
	}
	return 0;
}
