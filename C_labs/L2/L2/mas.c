#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <stdlib.h>


int main() 
{
	char opt[ 4 ]; // для выбора пунктов меню
	int b = 0; // для выбора случаев
	int *mas, a;; // указатели на массивы
	int n, m, i, j, x, max = 0, k = 0, flag = 1;
	do {
		printf("%s", "Z1 - add elements\nZ2 - find max in matrix\nZ3 - count words with begining vowel\nZ4 - redaction text\nEXIT - exit\n");
		scanf_s("%s", opt, _countof(opt));
		b = 0;
		if (strcmp(opt, "Z1") == 0) b = 1;
		if (strcmp(opt, "Z2") == 0) b = 2;
		if (strcmp(opt, "Z3") == 0) b = 3;
		if (strcmp(opt, "Z4") == 0) b = 4;
		switch (b)
		{
		case 1:
		{
			printf("input size of massiv: : ");
			scanf_s("%d", &n); // размер массива
			mas = (int*)malloc(n * sizeof(int)); // выделение пам€ти
			for (i = 0; i < n; i++) // ввод элементов массива
			{
				scanf_s("%d", &mas[i]);
			}
			for (i = 0; i < n - 1; i++) { // пузырьковая сортировка
				for (j = 0; j < n - i - 1; j++) { // сравниваем два соседних элемента
					if (mas[j] > mas[j + 1]) { // если они идут в неправильном пор€дке, то мен€ем их местами
						int tmp = mas[j];
						mas[j] = mas[j + 1];
						mas[j + 1] = tmp;
					}
				}
			}
			for (i = 0; i < n; i++) printf("%d ", mas[i]); // вывод элементов массива
			printf("\n");
			getchar();
			break;
		};
		case 2:
		{
			printf("input size of matrix: ");
			scanf_s("%d %d", &n, &m);
			if (n % 2 == 0)	k = n / 2;
			else k = n / 2 + 1;
			mas = (int*)malloc(k * sizeof(int));
			a = (int*)malloc(n * m * sizeof(int));
			printf("INPUT ELEMENTS:\n");
			for (i = 0; i < n; i++)  // цикл по строкам
			{
				for (j = 0; j < m; j++)  // цикл по столбцам
				{
					scanf_s("%d", (a + i * m + j));
				}
			}
			for (i = 0; i < n; i++)  // цикл по строкам
			{
				for (j = 0; j < m; j++)  // цикл по столбцам
				{
					if ((i + 1) % 2 != 0) { // проверка нечетности
						x = *(a + i * m + j);
						if (x > max) {
							max = x;
							mas[i / 2] = x;
						}
					}
					else break;
				}
				max = 0;
			}
			for (i = 0; i < k; i = i++) printf("%d ", mas[i]);
			printf("\n");
			getchar();
			break;
		};
		case 3:
		{
			printf("INPUT TEXT:\n");
			char mas[12] = {'A', 'E', 'I', 'O', 'U', 'Y', 'a', 'e', 'i', 'o', 'u', 'y'}, text[100];
			char ch;
			k = 0;
			ch = getchar();
			while ((ch = getchar()) != '\n') {
				if (ch == ' ' || ch == '.' || ch == ',') flag = 1;
				if (flag == 1) {
					for (j = 0; j < 12; j++) {
						if (ch == mas[j]) {
							flag = 0;
							k = k + 1;
							break;
						}
					}
				}
			}
			printf("%d\n", k);
			getchar();
			break;
		}
		case 4:
		{
			char mas[100];
			char ch;
			int fl = 0;
			flag = 0;
			printf("%s", "¬ведите текст\n");
			ch = getchar();
			i = 0;
			while ((ch = getchar()) != '\n') {
				mas[i] = ch;
				i++;
			}
			int n = i;
			i = 0;
			for (i = 0; i <= n; i++) {
				if ((mas[i] == ' ') || (mas[i] == ',')) {
					if (mas[i] == ' ') {
						if (mas[i + 1] != ',') {
							if (flag == 0) printf("%c", mas[i]);
							flag = flag + 1;
							fl = 0;
						}
					}
					if (mas[i] == ',') {
						if (fl == 0) printf("%c", mas[i]);
						fl = fl + 1;
						flag = 0;
					}
				}
				else {
					flag = 0;
					fl = 0;
					printf("%c", mas[i]);
				}
			}
			printf("\n");
			getchar();
			break;
		}
		default:
		{
			break;
		};
		};
	} while (b != 0);
	return 0;
}