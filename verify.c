/*
 * verify.c
 *
 *  Created on: Feb 15, 2025
 */
#include<stdio.h>
#include<stdlib.h>
#include"equation.h"
#include"random.h"
#include"verify.h"
#define MIN_QUESTION_VALUE -12
#define MAX_QUESTION_VALUE 13

int comp_float(const void *x, const void *y)
{
	const float u = *(float*)x;
	const float v = *(float*)y;
	return u > v ? 1 : u < v ? -1 : 0;
}

int init_question(struct Question *const this, const enum QuestionType t)
{
	float a, b, c;
	float mat[12];
	int mina = MIN_QUESTION_VALUE, maxa = MAX_QUESTION_VALUE;
	switch(t)
	{
		case LINEAR:
			a = (float)next_int_between(MIN_QUESTION_VALUE, MAX_QUESTION_VALUE);
			b = (float)next_int_between(MIN_QUESTION_VALUE, MAX_QUESTION_VALUE);
			linear(a, b, this->ans);
			mat[0] = a, mat[1] = b;
			this->cnt = 1;
			print_polynomial_equation(this->prompt, mat, mat + this->cnt + 1);
			break;
		case QUADRATIC_EASY:
			mina = 1, maxa = 2;
		case QUADRATIC_HARD:
			a = (float)next_int_between(mina, maxa);
			b = (float)next_int_between(MIN_QUESTION_VALUE, MAX_QUESTION_VALUE);
			c = (float)next_int_between(MIN_QUESTION_VALUE, MAX_QUESTION_VALUE);
			quadratic(a, b, c, this->ans);
			mat[0] = a, mat[1] = b, mat[2] = c;
			this->cnt = 2;
			print_polynomial_equation(this->prompt, mat, mat + this->cnt + 1);
			break;
		case LINEAR_TWO:
			for(float*it = mat; it != mat + 6; ++it)
				*it = (float)next_int_between(MIN_QUESTION_VALUE, MAX_QUESTION_VALUE);
			linear2(mat, mat + 9, this->ans, this->ans + 1);
			this->cnt = 2;
			print_system_of_equation(this->prompt, mat, this->cnt);
			break;
		case LINEAR_THREE:
			for(float*it = mat; it != mat + 12; ++it)
				*it = (float)next_int_between(MIN_QUESTION_VALUE, MAX_QUESTION_VALUE);
			linear3(mat, mat + 9, this->ans, this->ans + 1, this->ans + 2);
			this->cnt = 3;
			print_system_of_equation(this->prompt, mat, this->cnt);
			break;
		default:
			return 1;
	}
	qsort(this->ans, this->cnt, sizeof(float), comp_float);
	return 0;
}

void print_system_of_equation(char *str, const float matrix[], const unsigned cnt)
{
	const char vars[] = "xyz";
	char fmt[] = "+%dx";
	int started = 0;
	for(int i = 0; i < cnt; ++i)
	{
		int val = matrix[i];
		int col = i % (cnt + 1);
		fmt[3] = vars[col];
		if(col == cnt)
		{
			str += sprintf(str, "=%d\n", val);
			started = 0;
		}
		else if(val == 0)
			continue;
		switch(val)
		{
			case -1:
				*str = '-';
				++str;
			case 1:
				*str = vars[col];
				++str;
				break;
			default:
				str += sprintf(str, fmt + (!started || val < 0), val);
				break;
		}
		started = 1;
	}
}

void print_polynomial_equation(char *str, const float *const first, const float *const last)
{
	int started = 0;
	for(const float *it = first; it != last; ++it)
	{
		str = print_number(str, *it, 'x' * (it != last - 1), 0, started);
		if(last - it > 2)
			str += sprintf(str, "^%d", last - it - 1);
		started = 1;
	}
	*str++ = '=';
	print_number(str, 0, 0, 1, 0);
}

char *print_number(char *str, const int number, char variable, const int printzero, const int prefix)
{
	if(number > 0 && prefix)
	{
		*str = '+';
		++str;
	}
	switch(number)
	{
		case 0:
			if(printzero)
				*str++ = '0';
			break;
		case -1:
			*str = '-';
			++str;
		case 1:
			if(!variable)
				variable = '1';
			*str = variable;
			++str;
			break;
		default:
			str += sprintf(str, "%d", number);
			if(variable)
			{
				*str = variable;
				++str;
			}
			break;
	}
	*str = '\0';
	return str;
}

int verify(const struct Question *const q, float given[])
{
	int correct = 1;
	qsort(given, q->cnt, sizeof(float), comp_float);
	for(const float *it = q->ans; it != q->ans + q->cnt; ++given, ++it)
		correct &= close_enough(*it, *given);
	return correct;
}

int close_enough(float x, float y)
{
	return absdiff(x, y) < 0.000001f;
}

float absdiff(float x, float y)
{
	return x > y ? x - y : y - x;
}
