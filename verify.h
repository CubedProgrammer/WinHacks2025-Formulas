/*
 * verify.h
 *
 *  Created on: Feb 15, 2025
 */

#ifndef VERIFY_H_
#define VERIFY_H_

struct Question
{
	char prompt[91];
	float ans[9];
	unsigned cnt;
};

enum QuestionType
{
	LINEAR = 97,
	QUADRATIC_EASY,
	QUADRATIC_HARD,
	LINEAR_TWO,
	LINEAR_THREE
};

int init_question(struct Question *const this, const enum QuestionType t);
void print_system_of_equation(char *const str, const float matrix[], const unsigned cnt);
void print_polynomial_equation(char *str, const float *const first, const float *const last);
char *print_number(char *str, const int number, char variable, const int printzero, const int prefix);
int verify(const struct Question *const q, float given[]);
int close_enough(float x, float y);
float absdiff(float x, float y);

#endif /* VERIFY_H_ */
