#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define CONFIG_LEN 128
#define CONFIG_FILENAME "config.conf"

typedef struct {
	char **kv;
	size_t len;
} jikan_config;

int
jikan_save_config(const char *directory, const char *filename, const char *data)
{
	struct stat st = {0};
	if (stat(directory, &st) == -1)
		mkdir(directory, 0700);

	char path[512];
	sprintf(path, "%s/%s", directory, filename);

	FILE *file_p = fopen(path, "w");
	if (!file_p)
		return -1;

	size_t data_len = strlen(data);
	if (fwrite(data, 1, data_len, file_p) != data_len || fclose(file_p))
		return -1;

	return 0;
}

int
jikan_parse_config(const char *path, jikan_config *out)
{
	FILE *file_p = fopen(path, "r");
	if (!file_p) {
		return -1;
	}

	out->kv = NULL;
	out->len = 0;
	char line[1024];

	while (fgets(line, sizeof line, file_p) != NULL) {
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

void
jikan_config_free(jikan_config *c)
{
	for (size_t i = 0; i < c->len; ++i)
		free(c->kv[i]);
	free(c->kv);
	c->kv = NULL;
	c->len = 0;
}

void
jikan_get_config_dir(char **path)
{
	char *home;
	jikan_get_home(&home);
	*path = malloc(strlen(home) + strlen(NAME) + 3);
	snprintf(*path, strlen(home) + strlen(NAME) + 3, "%s/.%s", home, NAME);
}

void
jikan_get_config_path(char **path)
{
	char *dir;
	jikan_get_config_dir(&dir);
	if (asprintf(path, "%s/config.conf", dir) == -1)
		*path = NULL;
	free(dir);
}

void
jikan_print_user_config(void)
{
	char *config_path = NULL;
	jikan_get_config_path(&config_path);
	jikan_config conf = {.kv = NULL, .len = 0};

	if (jikan_parse_config(config_path, &conf) == 0 && conf.len)
		printf("Current User: %s <%s>\n", conf.kv[0], conf.kv[1]);

	free(config_path);
}
