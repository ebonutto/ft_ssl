#include "bigint.h"

#include <stddef.h> // NULL

t_bigint *bigint_grow(t_bigint *n, size_t new_capacity)
{
	
}

// a >= b
t_bigint *bigint_add_abs(const t_bigint *a, const t_bigint *b)
{
	t_bigint *res;
	uint64_t sum;
	size_t i;

	res = bigint_new(a->len);
	if (!res)
		return (NULL);
	sum = 0;
	i = 0;
	for (; i < b->length; i++) {
		sum = (uint64_t)a->limbs[i] + b->limbs[i] + carry;
		res->limbs[i] = (uint32_t)(sum & 0xFFFFFFFF);
		carry = sum >> 32;
	}
	for (; i < a->length; i++) {
		sum = (uint64_t)a->limbs[i] + carry;
		res->limbs[i] = (uint32_t)(sum & 0xFFFFFFFF);
		carry = sum >> 32;
	}
	if (carry) {
		if (bigint_grow(res, max + 1) < 0) {
			bigint_free(res);
			return (NULL);
		}
	}
}

t_bigint *bigint_add(const t_bigint *a, const t_bigint *b)
{
	t_bigint *res;

	if (a->sign == b->sign) {
		const t_bigint *big = (a->len >= b->len) ? a : b;
		const t_bigint *small = (a->len >= b->len) ? b : a;
		res = add_abs(big, small);
		if (res)
			res->sign = a->sign;
	}
}
