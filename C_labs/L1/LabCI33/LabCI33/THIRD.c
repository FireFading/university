#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Rus");
	char x[2];
	int a = 0; int b = 0;
	int i = 1;
	for (int k = 0; k != 4; k = k) {
		printf("%s", "R - площадь пр€моугольного треугольника\nT - площадь трапеции\nS - площадь квадрата\nE - выход из программы\n");
		scanf_s("%s", x, _countof(x));
		if (strcmp(x, "R") == 0) i = 1;
		if (strcmp(x, "T") == 0) i = 2;
		if (strcmp(x, "S") == 0) i = 3;
		if (strcmp(x, "E") == 0) i = 4;
		switch (i)
		{
		case 1:
		{
			printf("%s", "¬ведите размеры катетов: ");
			scanf_s("%d %d", &a, &b);
			if ((a != 0) && (b != 0)) printf("%d\n", (a * b / 2));
			else printf("ERROR\n");
			break;
		}
		case 2:
		{
			printf("%s", "¬ведите размеры оснований трапеции: ");
			scanf_s("%d %d", &a, &b);
			if ((a != 0) && (b != 0)) printf("%d\n", ((a * b) / 2));
			else printf("ERROR\n");
			break;
		}
		case 3:
		{
			printf("%s", "¬ведите длину стороны квадрата: ");
			scanf_s("%d", &a);
			if (a != 0) printf("%d\n", (a * a));
			else printf("ERROR\n");
			break;
		}
		case 4:
		{
			k = 4;
			break;
		}
		default:
		{
			printf("ERROR\n");
			break;
		}
		};
	}
	return 0;
}