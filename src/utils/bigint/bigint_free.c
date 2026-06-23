#include "bigint.h"

void bigint_free(t_bigint *n)
{
	if (!n)
		return ;
	free(n->limbs);
	free(n);
}
