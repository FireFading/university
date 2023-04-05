#include <stdio.h>
#include <math.h>
#define p 3,14159265

int main() {
	double x = 0, y = 0, check_y = 0;
	printf("input x: ");
	scanf_s("%e", &x);
	do { // проверка, чтобы знаменатель был не равен нулю
		printf("input y: ");
		scanf_s("%e", &y);
		check_y = 0.5 + sin(pow(y / 180, 2));
		if (check_y == 0) printf("math error, input another y!\n");
	} while (check_y == 0);
	x = 3 * pow((cos(x/180 - (p/6))), 2); // числитель
	y = 0.5 + sin(pow(y/180, 2)); // знаменатель
	x = x / y;
	printf("result: %f", x);
	return 0;
}