//#include "lib/bigint.h"

//#include <stddef.h> // size_t
//#include <stdint.h> // uintX_t
//#include <string.h> // memset()

//int bigint_grow(t_bigint *n, size_t new_capacity)
//{
//	uint32_t *tmp;

//	tmp = realloc(n->limbs, new_capacity * sizeof(uint32_t));
//	if (!tmp)
//		return (-1);
//	memset(tmp + n->capacity, 0,
//	       (new_capacity - n->capacity) * sizeof(uint32_t));
//	n->limbs = tmp;
//	return (0);
//}
