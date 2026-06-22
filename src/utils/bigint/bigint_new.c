#include "bigint.h"

t_bigint *bigint_new(size_t capacity)
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
