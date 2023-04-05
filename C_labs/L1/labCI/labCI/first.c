#include <stdio.h>

int main() {
	int a, b, m = 0, n = 0;
	printf("input m: ");
	scanf_s("%d", &m);
	printf("input n: ");
	scanf_s("%d", &n);
	a = m; // сохранение начальных значений
	b = n;
	for (int i = 1; i <= 6; i = i + 1) {
		m = a;
		n = b;
		if (i == 1) {
			printf("m + --n = %d\n", (m + --n));
		}
		if (i == 2) {
			printf("-n - --m = %d\n", (-n - --m));
		}
		if (i == 3) {
			printf("5 * n-- > m++ = %d\n", (5 * n-- > m++));
		}
		if (i == 4) {
			printf("++m << n-- = %d\n", (++m << n--));
		}
		if (i == 5) {
			printf("(m && n) || (m & n) || m) = %d\n", ((m && n) || (m & n) || m));
		}
		if (i == 6) {
			printf("m++ mod ~n = %d\n", (m++ % ~n));
		}
	}
	return 0;
}