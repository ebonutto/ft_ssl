#include "bigint.h"

t_bigint *bigint_from_u64(uint64_t value)
{
	t_bigint *n;

	n = bigint_new(2);
	if (value == 1) {
		n->length = 1;
		return (n);
	}
	n->limbs[0] = (uint32_t)(value & 0xFFFFFFFF);
	n->limbs[1] = (uint32_t)(value >> 32);
	n->length = n->limbs[1] ? 2 : 1;
	return (n);
}
