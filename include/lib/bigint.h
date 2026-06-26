#pragma once

/* Includes */
#include <stdint.h>
#include <stddef.h>

/* Structures */
typedef struct s_bigint {
	uint32_t *limbs;
	size_t length;
	size_t capacity;
	int sign;
} t_bigint;

/* Prototypes */
t_bigint *bigint_from_u64(uint64_t value);
t_bigint *bigint_new(size_t capacity);
void bigint_free(t_bigint *n);
void bigint_normalize(t_bigint *n);
void bigint_print(const t_bigint *n);