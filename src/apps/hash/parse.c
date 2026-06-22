#include "hash.h"

#include "lib/colors.h"
#include "lib/list.h"

#include <stdio.h> // stderr, fprintf(), perror()
#include <stdlib.h> // NULL, free(), malloc()
#include <string.h> // strcmp()

static int parse_input(t_hash_ctx *ctx, t_input_type type, char *data)
{
	t_input *input;
	t_list  *new;

	input = malloc(sizeof(t_input));
	if (!input) {
		perror("malloc failed");
		return (1);
	}
	input->type = type;
	input->data = data;
	new = list_new(input);
	if (!new) {
		perror("list_new() failed");
		free(input);
		return (1);
	}
	list_push_back(&ctx->inputs, new);
	return (0);
}


static void print_error(const char *format, char **argv, int i)
{
	fprintf(stderr, format, argv[0], argv[1], argv[i]);
	fprintf(stderr, "\n");
	fprintf(stderr, HASH_HELP_FORMAT, argv[0], argv[1]);
}


static int parse_flag(t_hash_ctx *ctx, int *i, int argc, char **argv)
{
	if (strcmp("-h", argv[*i]) == 0 ||
	    strcmp("--help", argv[*i]) == 0)
		ctx->flags |= 1 << FLAG_H;
	else if ((strcmp("-p", argv[*i]) == 0) ||
	           (strcmp("--append", argv[*i]) == 0))
		ctx->flags |= 1 << FLAG_P;
	else if ((strcmp("-q", argv[*i]) == 0) ||
	           (strcmp("--quiet", argv[*i]) == 0))
		ctx->flags |= 1 << FLAG_Q;
	else if ((strcmp("-r", argv[*i]) == 0) ||
	           (strcmp("--reverse", argv[*i]) == 0)) {
		ctx->flags |= 1 << FLAG_R;
	} else if ((strcmp("-s", argv[*i]) == 0) ||
	           (strcmp("--string", argv[*i]) == 0)) {
		if (*i + 1 >= argc) {
			print_error(HASH_EXPECTING_ARGUMENT_AFTER_FLAG_FORMAT,
			            argv, *i);
			return (2);
		}
		*i += 1;
		if (parse_input(ctx, INPUT_STRING, argv[*i]))
			return (1);
	} else {
		print_error(HASH_INVALID_OPTION_FORMAT, argv, *i);
		return (2);
	}
	return (0);
}


int parse_inputs(t_hash_ctx *ctx, int argc, char **argv)
{
	int i = 2;
	int ret;

	while (i < argc) {
		if (argv[i][0] == '-')
			ret = parse_flag(ctx, &i, argc, argv);
		else
			ret = parse_input(ctx, INPUT_FILE, argv[i]);
		if (ret)
			return (ret);
		i++;
	}
	return (0);
}
