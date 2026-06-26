#include "lib/bigint.h"

#include <stdio.h> // putchar()

void bigint_print(const t_bigint *n)
{
	if (!n)
		return ;
	if (n->sign)
		putchar('-');
	printf("0x%x", n->limbs[n->length - 1]);
	for (size_t i = n->length - 1; i-- > 0;)
		printf("%08x", n->limbs[i]);
	putchar('\n');
}
