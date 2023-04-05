#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

int main() {
	struct microcontroller
	{
		int articul; // артикул
		char name[20]; // название
		char firm_proisvod[20]; // фирма - производитель
		int rasrad; // разрядность
		int takt; // тактовая частота
		char architecture[10]; // архитектура
		int cost; // цена
	};
	struct sell
	{
		int tabel; // табельный номер
		char name[30]; // ФИО
		char adress[30]; // адрес
		int money; // оклад
	};
	union Uni
	{
		struct microcontroller prod[1];
		struct sell buy[1];
	};
	enum menu { add_new, all, all_microcontrollers, count_sellars, find_20000, exit } M;
	union Uni u[21];
	int a;
	int n = 0; // количество заполненных полей товар
	int m = 20; // количество заполненных полей продавец - запись в объединение ведется с конца, чтобы избежать перекрывания данных
	do {
		printf("MENU:\n0 - add_new\n1 - all\n2 - all_microcontrollers\n3 - count_sellars\n4 - find_20000\n5 - exit\n");
		scanf_s("%d", &M);
		switch (M) {
		case add_new:
			a = 0;
			if (n != m + 1) {
				printf("1 - ввести информацию о микроконтроллера, 2 - ввести продавца\n");
				scanf_s("%d", &a);
				switch (a) {
				case 1:
					printf("введите артикул: ");
					scanf_s("%d", &u[n].prod[0].articul);
					printf("введите название: ");
					scanf_s("%s", u[n].prod[0].name, _countof(u[n].prod[0].name));
					printf("введите фирму: ");
					scanf_s("%s", u[n].prod[0].firm_proisvod, _countof(u[n].prod[0].firm_proisvod));
					printf("введите разрядность: ");
					scanf_s("%d", &u[n].prod[0].rasrad);
					printf("введите тактовую частоту: ");
					scanf_s("%d", &u[n].prod[0].takt);
					printf("введите архитектуру: ");
					scanf_s("%s", u[n].prod[0].architecture, _countof(u[n].prod[0].architecture));
					printf("введите цену: ");
					scanf_s("%d", &u[n].prod[0].cost);
					n++;
					getch();
					break;
				case 2:
					printf("введите табельный номер: ");
					scanf_s("%d", &u[m].buy[0].tabel);
					printf("введите ФИО: ");
					scanf_s("%s", u[m].buy[0].name, _countof(u[m].buy[0].name));
					printf("введите адрес: ");
					scanf_s("%s", u[m].buy[0].adress, _countof(u[m].buy[0].adress));
					printf("введите оклад: ");
					scanf_s("%d", &u[m].buy[0].money);
					m--;
					getch();
					break;
				default:
					break;
				}
			}
			else printf("база данных уже заполнена!\n");
			break;
		case all:
			printf("microcontrollers\n");
			printf("name        firma       rasrad      takt        architecture cost\n");
			for (int i = 0; i < n; i++) printf("%10s %10s %10d %10d %10s %10d\n", u[i].prod[0].name, u[i].prod[0].firm_proisvod, u[i].prod[0].rasrad, u[i].prod[0].takt, u[i].prod[0].architecture, u[i].prod[0].cost);
			printf("\nsellars\n");
			printf("tabel       name        adress      money\n");
			for (int i = 20; i > m; i--) printf("%10d %10s %10s %10d\n", u[i].buy[0].tabel, u[i].buy[0].name, u[i].buy[0].adress, u[i].buy[0].money);
			getch();
			break;
		case all_microcontrollers:
			printf("name        firma       rasrad      takt        architecture cost\n");
			for (int i = 0; i < n; i++) printf("%10s %10s %10d %10d %10s %10d\n", u[i].prod[0].name, u[i].prod[0].firm_proisvod, u[i].prod[0].rasrad, u[i].prod[0].takt, u[i].prod[0].architecture, u[i].prod[0].cost);
			getch();
			break;
		case count_sellars:
			printf("количество продавцов: %d\n", (20 - m));
			getch();
			break;
		case find_20000:
			printf("продавцы с окладом менее 20000\n");
			for (int i = 20; i > m; i--) 
				if (u[i].buy[0].money < 20000) {
					printf("табельный номер: %d\n", u[i].buy[0].tabel);
					printf("имя: %s\n", u[i].buy[0].name);
					printf("адресс: %s\n", u[i].buy[0].adress);
					printf("оклад: %d\n", u[i].buy[0].money);
				}
			getch();
			break;
		case exit:
			break;
		default:
			break;
		}
	} while (M != 5);
	return 0;
}