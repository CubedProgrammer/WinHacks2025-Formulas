/*
 * equation.c
 *
 *  Created on: Feb 15, 2025
 */
#include<math.h>
#include<string.h>
#include"equation.h"

void linear(const float a, const float b, float *const x)
{
	*x = -b / a;
}

void quadratic(const float a, const float b, const float c, float *const x)
{
	const float u = -b/(2*a);
	const float v = sqrtf(b*b-4*a*c);
	x[0] = u + v / (2 * a);
	x[1] = u - v / (2 * a);
}

void linear2(float const matrix[], float const vector[], float *const x, float *const y)
{
	const float denom = matrix[0] * matrix[3] - matrix[1] * matrix[2];
	*x = (vector[0] * matrix[3] - matrix[1] * vector[1]) / denom;
	*y = (matrix[0] * vector[1] - vector[0] * matrix[2]) / denom;
}

float linear3(float const matrix[], float const vector[], float *const x, float *const y, float *const z)
{
	float new[9];
	const float denom = det3(matrix);
	memcpy(new, matrix, sizeof(new));
	for(int i = 0; i < 3; ++i)
		new[i * 3] = vector[i];
	*x = det3(new) / denom;
	for(int i = 0; i < 3; ++i)
		new[i * 3] = matrix[i * 3];
	for(int i = 0; i < 3; ++i)
		new[i * 3 + 1] = vector[i];
	*y = det3(new) / denom;
	for(int i = 0; i < 3; ++i)
		new[i * 3 + 1] = matrix[i * 3 + 1];
	for(int i = 0; i < 3; ++i)
		new[i * 3 + 2] = vector[i];
	*z = det3(new) / denom;
}

float det3(float const matrix[])
{
	const float dn = matrix[0] * matrix[4] * matrix[8]
			+ matrix[1] * matrix[5] * matrix[6]
			+ matrix[2] * matrix[3] * matrix[7];
	const float up = matrix[0] * matrix[5] * matrix[7]
			+ matrix[1] * matrix[3] * matrix[8]
			+ matrix[2] * matrix[4] * matrix[6];
	return dn - up;
}
