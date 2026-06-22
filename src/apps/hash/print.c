#include "hash.h"

#include <stddef.h> // size_t
#include <stdio.h> // printf()

static void print_hex(uint8_t *digest, size_t size)
{
	size_t i = 0;

	while (i < size) {
		printf("%02x", digest[i]);
		i++;
	}
}

void print_digest(uint8_t *digest, t_hash_ctx *ctx, t_hash_input *input)
{
	if (ctx->flags & (1 << FLAG_Q)) {
		print_hex(digest, ctx->algo->digest_size);
		printf("\n");
		return ;
	}
	if (ctx->flags & (1 << FLAG_R)) {
		print_hex(digest, ctx->algo->digest_size);
		if (input->type == INPUT_STRING)
			printf(" \"%s\"", input->data);
		else // INPUT_FILE or INPUT_STDIN
			printf(" %s", input->data);
		printf("\n");
		return ;
	}
	if (input->type == INPUT_STRING)
		printf("%s(\"%s\") = ", ctx->algo->name, input->data);
	else  // INPUT_FILE || INPUT_STDIN
		printf("%s(%s) = ", ctx->algo->name, input->data);

	print_hex(digest, ctx->algo->digest_size);
	printf("\n");
}
