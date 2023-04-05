#include <stdio.h>
#include <math.h>

int main() {
	char x = 'f';
	int a = 0, b = 0;
	do {
		printf("MENU:\nR - area_triangle_90\nT - area_trapezoid\nS - area_square\nE - exit\n");
		scanf_s("%c", &x);
		if (x == 'R') {
			printf("input sides:\n");
			scanf_s("%d", &a);
			scanf_s("%d", &b);
			if ((a != 0) && (b != 0)) printf("result: %d\n", (a * b / 2));
			else {
				printf("ERROR\n");
			}
		}
		if (x == 'T') {
			printf("input trapezoid bases:\n");
			scanf_s("%d", &a);
			scanf_s("%d", &b);
			if ((a != 0) && (b != 0)) printf("result: %f\n", ((a * b) * 0.5));
			else {
				printf("ERROR\n");
			}
		}
		if (x == 'S') {
			printf("input side:\n");
			scanf_s("%d", &a);
			if (a != 0) printf("result: %d\n", (a * a));
			else {
				printf("ERROR\n");
			}
		}
	} while (x != 'E');
	return 0;
}