#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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
	printf("\n");
}

bool
jikan_prompt_confirm(void)
{
	char confirm[4];

	printf("[y/n] ");
	scanf("%s", confirm);

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
