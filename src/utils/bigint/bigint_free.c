#include "bigint.h"

void bigint_free(s_bigint *)
{
	t_bigint *n;

	n = malloc(sizeof(t_bigint));
	if (!n)
		return (NULL);
	n->digits = calloc(capacity, sizeof(uint32_t));
	if (!n->digits) {
		free(n);
		return (NULL);
	}
	n->length = 0;
	n->capacity = capacity;
	n->sign = 0;
	return (n);
}
