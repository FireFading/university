#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

int main() {
	float *mas;
	float cur;
	float e;
	int* pos;
	int n = 0; // количество элементов в массиве
	int m = 0; // номер позиции в массиве
	int flag;
	mas = (float *)malloc(n * sizeof(float)); // выделение памяти
	enum Menu { add_element, delete_first, all_elements, clear_mas, find_pos_element, sort, exit } M;
	do {
		printf("MENU\n0 - add element\n1 - delete first element\n2 - show all elements\n3 - clear massiv\n4 - find position of element\n5 - sort massiv\n6 - exit\n");
		scanf_s("%d", &M);
		switch (M) {
		case add_element:
			flag = 0; // если введена неверная позиция
			do {
				printf("position of element: ");
				scanf_s("%d", &m);
				if (m > n) printf("wrong position, you should give position before this\n");
				else flag = 1;
			} while (flag == 0);
			if (m >= n) {
				n++;
				mas = (float*)realloc(mas, n * sizeof(float)); // увеличение массива
			}
			printf("mas[%d] = ", m);
			scanf_s("%f", (mas + m));
			getch();
			break;
		case delete_first:
			if (n != 0) {
				n--;
				for (int i = 0; i < n; i++) {
					*(mas + i) = *(mas + i + 1);
				}
				mas = (float*)realloc(mas, n * sizeof(float));
			}
			else printf("empty massiv");
			getch();
			break;
		case all_elements:
			printf("ELEMENTS:");
			for (int i = 0; i < n; i++) {
				printf("%f ", *(mas + i));
			}
			printf("\n");
			getch();
			break;
		case clear_mas:
			mas = (float*)calloc(n, sizeof(float));
			getch();
			break;
		case find_pos_element:
			printf("element: ");
			scanf_s("%f", &e);
			for (int i = 0; i < n; i++) {
				if (*(mas + i) == e) printf("position: %d\n", i);
			}
			getch();
			break;
		case sort:
			for (int i = 0; i < n - 1; i++) { // пузырьковая сортировка
				for (int j = 0; j < n - i - 1; j++) { // сравниваем два соседних элемента
					if (mas[j] > mas[j + 1]) { // если они идут в неправильном порядке, то меняем их местами
						cur = *(mas + j);
						*(mas + j) = *(mas + j + 1);
						*(mas + j + 1) = cur;
					}
				}
			}
			for (int i = 0; i < n; i++) printf("%f ", *(mas + i)); // вывод элементов массива
			printf("\n");
			getchar();
			break;
		case exit:
			free(mas);
			break;
		default:
			break;
		};
	} while (M != 6);
	return 0;
}