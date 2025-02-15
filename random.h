/*
 * random.h
 *
 *  Created on: Feb 15, 2025
 */

#ifndef RANDOM_H_
#define RANDOM_H_

#include<stdint.h>

void init_random_seed(const uint64_t seed);
int next_int_between(int from, int to);
float next_float(void);
uint32_t next_int(void);

#endif /* RANDOM_H_ */
