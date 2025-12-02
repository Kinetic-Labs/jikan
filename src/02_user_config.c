#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define CONFIG_LEN 1024
#define CONFIG_FILENAME "config.conf"
#ifndef NAME
#define NAME "jikan"
#endif

typedef struct {
	char **kv;
	size_t len;
} jikan_config;

static int
jikan_save_config(const char *directory, const char *filename, const char *data)
{
	struct stat st = {0};
	char path[512];
	FILE *file_p;
	size_t data_len;

	if (stat(directory, &st) == -1)
		mkdir(directory, 0700);

	snprintf(path, sizeof path, "%s/%s", directory, filename);
	file_p = fopen(path, "w");
	if (!file_p)
		return -1;

	data_len = strlen(data);
	if (fwrite(data, 1, data_len, file_p) != data_len || fclose(file_p))
		return -1;

	return 0;
}

static int
jikan_parse_config(const char *path, jikan_config *out)
{
	char line[1024];
	FILE *file_p = fopen(path, "r");
	if (!file_p)
		return -1;

	out->kv = NULL;
	out->len = 0;

	while (fgets(line, sizeof line, file_p)) {
		char *tok = strtok(line, ",");
		while (tok) {
			out->kv =
			    realloc(out->kv, (out->len + 1) * sizeof *out->kv);
			out->kv[out->len++] = strdup(tok);
			tok = strtok(NULL, ",");
		}
	}
	fclose(file_p);
	return 0;
}

static void
jikan_config_free(jikan_config *c)
{
	for (size_t i = 0; i < c->len; ++i)
		free(c->kv[i]);
	free(c->kv);
	c->kv = NULL;
	c->len = 0;
}

static void
jikan_get_config_dir(char **path)
{
	char *home;
	size_t len;

	if (jikan_get_home(&home) != 0)
		return;

	len = strlen(home) + strlen(NAME) + 3;
	*path = malloc(len);
	snprintf(*path, len, "%s/.%s", home, NAME);
}

static void
jikan_get_config_path(char **path)
{
	char *dir;
	jikan_get_config_dir(&dir);
	if (asprintf(path, "%s/config.conf", dir) == -1)
		*path = NULL;
	free(dir);
}

static void
jikan_print_user_config(void)
{
	char *config_path = NULL;
	jikan_config conf = {.kv = NULL, .len = 0};

	jikan_get_config_path(&config_path);
	if (jikan_parse_config(config_path, &conf) == 0 && conf.len >= 2)
		if (printf("Current User: %s <%s>\n", conf.kv[0], conf.kv[1]) <
		    0)
			perror("printf");

	jikan_config_free(&conf);
	free(config_path);
}
