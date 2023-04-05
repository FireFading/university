#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

struct Firm_proisvod // фирма - производитель
{
	int code; // код
	char name[20]; // имя
	char town[20]; // город
	char adress[20]; // адрес
	char phone[13]; // телефон
};

typedef struct product
{
	int articul; // артикул
	char name[20]; // имя
	struct Firm_proisvod firm_proisvod[1]; // имя - производитель
	int rasrad; // разряд
	int takt; // тактовая частота
	char architecture[10]; // архитектура
	int cost; // цена
} microcontroller;

int main() {
	microcontroller* all; // указатель на массив структур
	int number = 0; // количество заполненных полей
	all = (microcontroller*)malloc(number*sizeof(microcontroller));
	enum menu { add_new, find_ARM, find_cost, all_microcontrollers, number_16_Microchip, number_Mega, exit } M;
	int a = 0; // артикул
	int counter = 0;

	do {
		printf("MENU:\n");
		printf("0 - add_new\n1 - find_ARM\n2 - find_cost_800_1000\n3 - all_microcontrollers\n4 - number_16_Microchip\n5 - number_Mega\n6 - exit\n");
		scanf_s("%d", &M);
		switch (M)
		{
		case add_new:
		{
			printf("new microcontroller\n");
			printf("artikul: ");
			scanf_s("%d", &a);
			int new_art = 0;
			do { // проверка на наличие артикула
				for (int i = 0; i < number; i++) {
					if ((all + i)->articul == a) {
						printf("there is microcontroller with such artukul, input new: ");
						scanf_s("%d", &a);
						new_art = 1;
						break;
					}
					else new_art = 0;
				}
			} while (new_art == 1);

			all = (microcontroller*)realloc(all, (number + 1) * sizeof(microcontroller));
			(all + number)->articul = a;
			printf("data of microcontroller with this artikul:\n");
			printf("name: ");
			scanf_s("%s", (all + number)->name, _countof((all + number)->name));
			printf("code: ");
			scanf_s("%d", &(all + number)->firm_proisvod[0].code);
			printf("firma: ");
			scanf_s("%s", (all + number)->firm_proisvod[0].name, _countof((all + number)->firm_proisvod[0].name));
			printf("town: ");
			scanf_s("%s", (all + number)->firm_proisvod[0].town, _countof((all + number)->firm_proisvod[0].town));
			printf("adress: ");
			scanf_s("%s", (all + number)->firm_proisvod[0].adress, _countof((all + number)->firm_proisvod[0].adress));
			printf("phone: ");
			scanf_s("%s", (all + number)->firm_proisvod[0].phone, _countof((all + number)->firm_proisvod[0].phone));
			printf("rasrad: ");
			scanf_s("%d", &(all + number)->rasrad);
			printf("chastota: ");
			scanf_s("%d", &(all + number)->takt);
			printf("architecture: ");
			scanf_s("%s", (all + number)->architecture, _countof((all + number)->architecture));
			printf("cost: ");
			scanf_s("%d", &(all + number)->cost);
			number++;
			getch();
			break;
		}
		case find_ARM:
		{
			for (int i = 0; i < number; i++) {
				if (strcmp((all + i)->architecture, "ARM") == 0) printf("artikul: %d\nname: %s\nfirma: %s\nrasrad: %d\nchastota: %d\n", (all + i)->articul, (all + i)->name, (all + i)->firm_proisvod[1].name, (all + i)->rasrad, (all + i)->takt);
			}
			getch();
			break;
		}
		case find_cost:
		{
			for (int i = 0; i < number; i++) {
				if (((all + i)->cost >= 800) && ((all + i)->cost <= 1000)) printf("name: %s\nrasrad: %d\nchastota: %d\narchitecture: %s\ncost: %d\n", (all + i)->name, (all + i)->rasrad, (all + i)->takt, (all + i)->architecture, (all + i)->cost);
			}
			getch();
			break;
		}
		case all_microcontrollers:
		{
			printf("artikul    name       code       firma      town       adress     phone      rasrad      chastota   architecture cost      \n");
			for (int i = 0; i < number; i++) {
				printf("%10d %10s %10d %10s %10s %10s %10s %10d %10d %10s %10d\n", (all + i)->articul, (all + i)->name, (all + i)->firm_proisvod[0].code, (all + i)->firm_proisvod[0].name, (all + i)->firm_proisvod[0].town, (all + i)->firm_proisvod[0].adress, (all + i)->firm_proisvod[0].phone, (all + i)->rasrad, (all + i)->takt, (all + i)->architecture, (all + i)->cost);
			}
			getch();
			break;
		}
		case number_16_Microchip:
		{
			counter = 0;
			for (int i = 0; i < number; i++) {
				if (((all + i)->rasrad == 16) && (strcmp((all + i)->firm_proisvod[0].name, "Microchip") == 0)) counter++;
			}
			printf("count 16-rasrad microcontrollers by Microchip: %d\n", counter);
			getch();
			break;
		}
		case number_Mega:
		{
			counter = 0;
			for (int i = 0; i < number; i++) {
				if (strncmp((all + i)->name, "Mega", 4) == 0) counter++;
			}
			printf("count microcontrollers with Mega-: %d\n", counter);
			getch();
			break;
		}
		case exit:
		{
			free(all);
			break;
		}
		default:
		{
			break;
		}
		};
	} while (M != 6);

}