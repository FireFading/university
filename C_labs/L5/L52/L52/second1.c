#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int main() {
	// ������� ���������
	unsigned int* matrix;
	int n = 0, m = 0;
	unsigned int min_el = 100000;
	printf("input size: ");
	scanf_s("%d %d", &n, &m);
	matrix = (unsigned int*)malloc(n * m * sizeof(unsigned int));
	for (int i = 0; i < n; i++) { // �� �������
		for (int j = 0; j < m; j++) { // �� ��������
			printf("matrix[%d][%d] = ", i, j);
			scanf_s("%d", (matrix + i * m + j));
		}
	}
	int k = 0; // ���������� ��������� � ������
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < k; j++) {
			if (*(matrix + i * m + j) < min_el) min_el = *(matrix + i * m + j);
		}
		if (k < m) k++;
	}
	free(matrix);
	printf("min element: %d\n", min_el);

	// ������� ���������
	int** points;
	min_el = 100000;
	printf("input size: ");
	scanf_s("%d %d", &n, &m);
	points = (int**)malloc(n * sizeof(int*)); // ��� ��������� �� ������ �������

	for (int i = 0; i < n; i++) {
		*(points + i) = (unsigned int*)malloc(m * sizeof(unsigned int)); // ��� �������� �����
		for (int j = 0; j < m; j++) {
			printf("a[%d][%d] = ", i, j);
			scanf_s("%d", (*(points + i) + j));
		}
	}
	k = 0; // ���������� ��������� � ������
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < k; j++) {
			if (*(*(points + i) + j) < min_el)  min_el = *(*(points + i) + j);
		}
		if (k < m) k++;
	}
	free(points);
	printf("min element: %d", min_el);
	return 0;
}