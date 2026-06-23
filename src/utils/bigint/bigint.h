#ifndef BIGINT_H
#define BIGINT_H

typedef struct s_bigint {
	uint32_t *limbs;
	size_t    length;
	size_t    capacity;
	int       sign;
} t_bigint;

t_bigint *bigint_new(size_t capacity);
void bigint_free(s_bigint *n);
t_bigint *bigint_from_u64(uint64_t value);
void bigint_normalize(t_bigint *n);
