/*
 * verify.c
 *
 *  Created on: Feb 15, 2025
 */
#include<stdio.h>
#include"equation.h"
#include"random.h"
#include"verify.h"
#define MIN_QUESTION_VALUE -12
#define MAX_QUESTION_VALUE 13

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
			sprintf(this->prompt, "%dx+%d=0", (int)a, (int)b);
			this->cnt = 1;
			break;
		case QUADRATIC_EASY:
			mina = 1, maxa = 2;
		case QUADRATIC_HARD:
			a = (float)next_int_between(mina, maxa);
			b = (float)next_int_between(MIN_QUESTION_VALUE, MAX_QUESTION_VALUE);
			c = (float)next_int_between(MIN_QUESTION_VALUE, MAX_QUESTION_VALUE);
			quadratic(a, b, c, this->ans);
			sprintf(this->prompt, "%dx^2+%dx+%d=0", (int)a, (int)b, (int)c);
			this->cnt = 2;
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
	return 0;
}

void print_system_of_equation(char *str, const float matrix[], int cnt)
{
	const char vars[] = "xyz";
	char fmt[] = "+%dx";
	for(int i = 0; i < cnt; ++i)
	{
		int col = i % (cnt + 1);
		fmt[3] = vars[col];
		if(col == 0)
			str += sprintf(str, "%dx", (int)matrix[i]);
		else if(col == cnt)
			str += sprintf(str, "=%d\n", (int)matrix[i]);
		else
			str += sprintf(str, fmt, (int)matrix[i]);
	}
}

int verify(const struct Question *const q, const float given[])
{
	int correct = 1;
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
