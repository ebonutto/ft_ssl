#include "hash.h"

#include "lib/colors.h"

#include <stdio.h> // stderr, fprintf(), printf()
#include <stdlib.h> // free(), malloc()
#include <string.h> // NULL, memset(), strcmp()

static const t_hash_algo *get_hash_algo(const char *name)
{
	int i = 0;

	while (g_hash_algos[i].name) {
		if (strcmp(g_hash_algos[i].name, name) == 0)
			return (&g_hash_algos[i]);
		i++;
	}
	return (NULL); // This should not happen
}

int hash_main(int argc, char **argv)
{
	int        ret;
	t_hash_ctx ctx;

	memset(&ctx, 0, sizeof(ctx));
	ctx.algo = get_hash_algo(argv[1]); // Does not have to be secured
	ret = parse_inputs(&ctx, argc, argv);
	if (ret)
		goto cleanup;
	if (ctx.flags & (1 << FLAG_H)) { // Add is flag active
		printf(HASH_HELP_FORMAT, argv[0], argv[1]);
		goto cleanup;
	}
	ctx.algo_ctx = malloc(ctx.algo->ctx_size);
	if (!ctx.algo_ctx) {
		perror("malloc() failed");
		goto cleanup;
	}
	ret = process_inputs(&ctx);
	free(ctx.algo_ctx);
cleanup:
	list_clear(&ctx.inputs, free);
	return (ret);
}
