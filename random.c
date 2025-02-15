/*
 * random.c
 *
 *  Created on: Feb 15, 2025
 */

#include"random.h"

static uint64_t GLOBAL_SEED;

void init_random_seed(const uint64_t seed)
{
	GLOBAL_SEED = 25214903917 ^ seed;
}

int next_int_between(int from, int to)
{
	return(int)(next_int() % (to - from)) + from;
}

float next_float(void)
{
	union dummy
	{
		int32_t i;
		float f;
	} dummy;
	dummy.i = 0x3f800000 | (next_int() & 0x7fffff);
	return dummy.f;
}

uint32_t next_int(void)
{
	GLOBAL_SEED *= 25214903917;
	GLOBAL_SEED += 11;
	GLOBAL_SEED &= (1ul << 48) - 1;
	return(uint32_t)(GLOBAL_SEED & ((1ul << 32) - 1));
}
