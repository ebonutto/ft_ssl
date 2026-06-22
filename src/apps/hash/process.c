#include "hash.h"

#include <fcntl.h> // O_RDONLY, open()
#include <unistd.h> // ssize_t, read(), close()

#include <stddef.h> // size_t
#include <stdint.h> // uintX_t
#include <stdio.h> // BUFSIZ, STDIN_FILENO, perror()
#include <stdlib.h> // free(), malloc()
#include <string.h> // strlen()


static int process_stdin(t_hash_ctx *ctx, uint8_t *digest)
{
	ssize_t r;
	t_input input;
	uint8_t buffer[BUFSIZ];

	if (ctx->algo->init(ctx->algo_ctx))
		return (1);
	while ((r = read(STDIN_FILENO, buffer, BUFSIZ)) > 0) {
		if (ctx->algo->update(ctx->algo_ctx, buffer, r))
			return (0);
	}
	if (r < 0) {
		perror("read() failed");
		return (1);
	}
	if (ctx->algo->final(digest, ctx->algo_ctx))
		return (1);
	input.type = INPUT_STDIN;
	input.data = "stdin";
	print_digest(digest, ctx, &input);
	return (0);
}


static int process_file(t_hash_ctx *ctx, const char *filename)
{
	int     fd;
	int     ret;
	ssize_t r;
	uint8_t buffer[BUFSIZ];

	fd = open(filename, O_RDONLY);
	if (fd < 0) {
		perror(filename);
		return (0);
	}
	while ((r = read(fd, buffer, BUFSIZ)) > 0) {
		if (!ctx->algo->update(ctx->algo_ctx, buffer, r)) {
			ret = 0;
			goto cleanup;
		}
	}
	if (r < 0) {
		perror("read() failed");
		ret = 0;
		goto cleanup;
	}
	ret = 1;
cleanup:
	close(fd);
	return (ret);
}


static int process_string(t_hash_ctx *ctx, const char *str)
{
	size_t len;

	len = strlen(str);
	if (!ctx->algo->update(ctx->algo_ctx, (const uint8_t *)str, len))
		return (1);
	return (0);
}


static int process_input_dispatch(t_hash_ctx *ctx, t_input *input)
{
	switch (input->type) {
		case INPUT_STRING:
			return (process_string(ctx, input->data));
		default: // INPUT_FILE
			return (process_file(ctx, input->data));
	}
}


int process_inputs(t_hash_ctx *ctx)
{
	int          ret;
	t_input *input;
	t_list       *node;
	uint8_t      *digest;

	digest = malloc(ctx->algo->digest_size);
	if (!digest) {
		perror("malloc() failed");
		return (1);
	}
	node = ctx->inputs;
	if (!node || ctx->flags & (1 << FLAG_P)) {
		if (process_stdin(ctx, digest)) {
			ret = 1;
			goto cleanup;
		}
	}
	while (node) {
		input = (t_input *)node->content;
		if (ctx->algo->init(ctx->algo_ctx) ||
		    process_input_dispatch(ctx, input) ||
		    ctx->algo->final(digest, ctx->algo_ctx)) {
			ret = 1;
			goto cleanup;
		}
		print_digest(digest, ctx, input);
		node = node->next;
	}
	ret = 0;
cleanup:
	free(digest);
	return (ret);
}
