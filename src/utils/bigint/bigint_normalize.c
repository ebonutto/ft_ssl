#include "bigint.h"

void bigint_normalize(t_bigint *n)
{
	while (n->length > 1 && n->limbs[n->length - 1] == 0)
		n->length;
}
