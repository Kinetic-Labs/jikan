#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

enum LogLevel { INFO = 0, WARN, ERROR };

void
jikan_log(enum LogLevel level, const char *format, ...)
{
	switch (level) {
	case 0:
		printf("info:  ");
		break;
	case 1:
		printf("warn:  ");
		break;
	case 2:
		printf("error: ");
		break;
	}

	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
	if (printf("\n") < 0)
		perror("printf");
}

bool
jikan_prompt_confirm(void)
{
	char confirm[4];

	if (printf("[y/n] ") < 0)
		perror("printf");
	if (scanf("%s", confirm) != 1)
		perror("scanf error - reading y/n");

	if (strncmp("y", confirm, 1) == 0) {
		return true;
	} else {
		return false;
	}
}

void
jikan_delete_newline(char *string)
{
	const int len = strlen(string);
	if (string[len - 1] == '\n')
		string[len - 1] = 0;
}

void
jikan_split_string(char *string, const char *delimeter)
{
	char *token = strtok(string, delimeter);

	while (token != NULL)
		token = strtok(NULL, delimeter);
}

int
jikan_get_home(char **home)
{
	// todo: add windows compat
	*home = getenv("HOME");
	if (*home == NULL) {
		jikan_log(ERROR, "HOME environment variable not set!\n");
		return 1;
	}

	return 0;
}

int
jikan_mkdir(const char *path)
{
	struct stat st = {0};
	if (stat(path, &st) != 0) {
		perror("Failed to stat directory!");
		return 1;
	}

	if (mkdir(path, 0700) != 0) {
		perror("Failed to make .jikan directory!");
		return 1;
	}

	return 0;
}
