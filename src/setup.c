#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void
save_config(const char *username, const char *email)
{
	char *config_dir;
	jikan_get_config_dir(&config_dir);

	char *config_filename = CONFIG_FILENAME;

	char config[CONFIG_LEN];
	sprintf(config, "%s,%s", username, email);
	if (jikan_save_config(config_dir, config_filename, config) != -1)
		jikan_log(0, "Config saved successfully!");
}

void
jikan_setup_user(void)
{
	jikan_print_user_config();
	char name[128], email[512];

	printf("What is your name? ");
	fgets(name, sizeof name, stdin);
	jikan_delete_newline(name);

	printf("What is your email? ");
	scanf("%s", email);
	jikan_delete_newline(email);

	printf("You are %s <%s>, is that correct? ", name, email);
	if (jikan_prompt_confirm()) {
		save_config(name, email);
		printf("Thank you!\nYou can change this at any time by "
		       "re-running `jikan setup`\n");
	} else {
		printf("Changes not saved! Rerun with `jikan setup` if you "
		       "wish to reenter your information\n");
	}
}
