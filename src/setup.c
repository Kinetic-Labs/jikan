#include <stdio.h>
#include <string.h>

void
jikan_setup_user(void)
{
	char name[128];
	char email[512];

	printf("What is your name? ");
	fgets(name, 128, stdin);
	jikan_delete_newline(name);

	printf("What is your email? ");
	scanf("%s", email);
	jikan_delete_newline(email);

	printf("You are %s <%s>, is that correct? ", name, email);

	if (jikan_prompt_confirm()) {
		printf("Thank you!\n");
		printf("You can change this at any time by re-running `jikan "
		       "setup`\n");
	} else {
		printf("Changes not saved! Rerun with `jikan setup` if you "
		       "wish to reenter "
		       "your information\n");
	}
}
