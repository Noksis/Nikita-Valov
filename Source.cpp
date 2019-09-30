#include <stdio.h>
#include <math.h>
#include <assert.h>
#define mistake 1e-17
#pragma warning (disable: 4996)
int Max=3;

void input1(double cpeff[], int Max);

void solve1(double a, double b, double* x1);

int solve2(double a, double b, double c, double* x1, double* x2);


double tolerance(double r);
/*!
	\brief Main function
	\version 1.2.1
	\return 0 Programm is succesful working
*/

int main() {
	int intnroots = NAN;
	double x1 = NAN, x2 = NAN;
	double coeff[3] = { 0 };
	printf("Hello, I solve square equation, please enter odds\n");

	input1(coeff, Max);
	intnroots = solve2(coeff[0], coeff[1], coeff[2], &x1, &x2);

	x1 = tolerance(x1);
	x2 = tolerance(x2);

	switch (intnroots) {
	case -1:
		printf("Infinity number of roots");
		break;
	case 2:
		printf("x1 = %lf x2 = %lf ", x1, x2);
		break;
	case 1:
		printf("x1 = %lf", x1);
		break;
	case 0:
		printf("Sorry, you have not roots");
		break;
	}

}
/*!
	\brief Input function
	\details
	This is an input function. 
	You enter values; if the format is incorrect, it gives an error.
	When the value is accepted, it reports this and writes the number of successfully entered variables
	\param [in] coeff[] Empty array
	\param [in] Max Array size for coefficients
	\param [out] coeff[] Array of coefficients. Contains desired coefficients

*/

void input1(double coeff[], int Max) {
	int i = 0;
	for (int b = 0; i < Max; i++) {
		b = scanf("%lf", &coeff[i]);
		if (b == 0) {
			i--;
			printf("Wrong Input!\n");
			scanf("%*s");
		}
		else
			printf("Accept input %d/%d\n", i + 1, Max);
	}
}
/*!
	\brief Programm which solve  square equation
	\details
	You accept 3 value: there are coefficients our equation. If a = 0, b = 0,c = 0 we have infinity number
	of roots. If a = 0, b = 0 u have not roots. If a = 0 we have line equation and we use LineSolver(b,c).
	If c = 0, x1 = 0 and we need LineSolver(a,b). If a != 0 , b != 0 , c != 0 we should calculate discriminant
	and compare with 0: we will have 0 roots if discriminant < 0, we will have 1 roots if discr. = 0, we will
	have 2 roots if discr. > 0
	\param [in] a Is coefficients ax^2 + bx + c = 0
	\param [in] b is coefficients ax^2 + bx + c = 0
	\param [in] c is coefficients ax^2 + bx + c = 0
	\param [in] x1 adress first root
	\param [in] x2 adress second root
	\return 0 if we havenot roots
	\return 1 if we have one root
	\return 2 if we have two roots
	\return -1 if we have infinity number of root

*/
int solve2(double a, double b, double c, double* x1, double* x2) {
	double d = 0, sq = 0, t = mistake;
	a = tolerance(a); b = tolerance(b); c = tolerance(c);
	if (a == 0 && b == 0 && c == 0) {
		*x1 = 0;
		*x2 = 0;
		return -1;
	}
	else if (a == 0 && b == 0) {
		*x1 = 0;
		*x2 = 0;
		return 0;
	}
	else if (a == 0) {
		*x2 = 0;
		solve1(b, c, x1);
		return  1;
	}
	else if (c == 0) {
		*x2 = 0;
		solve1(a, b, x1);
		if (*x1 == *x2)
			return 1;
		return  2;
	}
	else if (a != 0 && b != 0 && c != 0) {
		d = b * b - 4 * a * c;
		d = tolerance(d);
		sq = sqrt(d);
		sq = tolerance(sq);
		if (fabs(d) < t) {
			*x1 = -b / 2 / a;
			return 1;
		}
		else if (tolerance(d) < 0)
			return -1;
		else {
			*x1 = (-b + sq) / 2 / a;
			*x2 = (-b - sq) / 2 / a;
		}
	}

	return 2;

}
/*!
	\brief Program which solve line equation
	\param [in] a is first coefficients in ax + b = 0
	\param [in] b is second coefficients in ax + b = 0
	\param [in] *x1  adress first root
*/
void solve1(double a, double b, double* x1) {
	*x1 = -b / a;
	if (b == 0)
		*x1 = 0;
}
/*!
	\brief Program which round value
	\param [in] r is value
	\param [out] r if r > mistake, we have r. Else we have 0
	\return 0 is r < mistake
	\return r is r > mistka
*/
double tolerance(double r) {
	double t = mistake;
	if (fabs(r) < t)
		r = 0;
	return r;
}
