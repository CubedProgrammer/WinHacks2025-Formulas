/*
 * equation.h
 *
 *  Created on: Feb 15, 2025
 */

#ifndef EQUATION_H_
#define EQUATION_H_

void linear(const float a, const float b, float *const x);
void quadratic(const float a, const float b, const float c, float *const x);
void linear2(float const matrix[], float const vector[], float *const x, float *const y);
float linear3(float const matrix[], float const vector[], float *const x, float *const y, float *const z);
float det3(float const matrix[]);

#endif /* EQUATION_H_ */
