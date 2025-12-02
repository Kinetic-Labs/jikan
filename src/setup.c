#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void
save_config(const char *username, const char *email)
{
	char *config_dir;
	char *config_filename = CONFIG_FILENAME;
	char config[CONFIG_LEN];

	jikan_get_config_dir(&config_dir);
	snprintf(config, sizeof config, "%s,%s", username, email);
	if (jikan_save_config(config_dir, config_filename, config) != -1)
		jikan_log(INFO, "Config saved successfully!");
}

static void
jikan_setup_user(void)
{
	char name[128], email[512];

	jikan_print_user_config();

	if (printf("What is your name? ") < 0)
		perror("printf");
	if (fgets(name, sizeof name, stdin) == NULL)
		perror("fgets");
	jikan_delete_newline(name);

	if (printf("What is your email? ") < 0)
		perror("printf");
	if (scanf("%511s", email) != 1)
		perror("scanf");
	jikan_delete_newline(email);

	if (printf("You are %s <%s>, is that correct? ", name, email) < 0)
		perror("printf");

	if (jikan_prompt_confirm()) {
		save_config(name, email);
		if (printf("Thank you!\nYou can change this at any time by "
			   "re-running `jikan setup`\n") < 0)
			perror("printf");
	} else {
		if (printf("Changes not saved! Rerun with `jikan setup` if you "
			   "wish to re-enter your information\n") < 0)
			perror("printf");
	}
}
