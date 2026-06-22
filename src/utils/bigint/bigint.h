#ifndef BIGINT_H
#define BIGINT_H

typedef struct s_bigint {
	uint32_t *limbs;
	size_t    length;
	size_t    capacity;
	int       sign;
} s_bigint;

