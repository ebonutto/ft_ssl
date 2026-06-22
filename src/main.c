#include "ssl.h"

#include "utils/colors.h"

#include <stdio.h>   // stderr, fprintf()
#include <string.h>  // strcmp()


/*
 * Macros
 */

#define INVALID_COMMAND_FORMAT \
RED \
"%s: Error: '%s' is an invalid command.\n" \
RST

#define HELP_FORMAT \
BOLD CYN "Usage:" RST " %s [command] [flags] [files]\n" \
BOLD CYN "\nMessage Digest commands:\n" RST \
"  md5\n" \
"  sha256\n" \
"  whirlpool\n" \
BOLD CYN "\nCipher commands:\n" RST \
"  base64\n" \
"  rc4\n" \
"\n"

static int do_cmd(int argc, char **argv)
{
	int i;

	i = 0;
	while (g_cmds[i].name) {
		if (strcmp(g_cmds[i].name, argv[1]) == 0)
			return (g_cmds[i].func(argc, argv));
		i++;
	}
	fprintf(stderr, INVALID_COMMAND_FORMAT, argv[0], argv[1]);
	fprintf(stderr, "\n");
	fprintf(stderr, HELP_FORMAT, argv[0]);
	return (2);
}

int main(int argc, char **argv)
{
	int ret;

	if (argc < 2) {
		return (1);
	}
	ret = do_cmd(argc, argv);
	return (ret);
}
