#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

int main() {

	struct Firm_proisvod // фирма - производитель
	{
		int code; // код
		char name[20]; // имя
		char town[20]; // город
		char adress[20]; // адрес
		char phone[13]; // телефон
	};

	struct microcontroller
	{
		int articul; // артикул
		char name[20]; // имя
		struct Firm_proisvod firm_proisvod; // имя - производитель
		int rasrad; // разряд
		int takt; // тактовая частота
		char architecture[10]; // архитектура
		int cost; // цена
	};

	setlocale(LC_ALL, "Russian");

	struct microcontroller all[10] = { 0, "0", 0, "0", "0", "0", "0", 0, 0, "0", 0, 0, "0", 0, "0", "0", "0", "0", 0, 0, "0", 0, 0, "0", 0, "0", "0", "0", "0", 0, 0, "0", 0, 0, "0", 0, "0", "0", "0", "0", 0, 0, "0", 0, 0, "0", 0, "0", "0", "0", "0", 0, 0, "0", 0, 0, "0", 0, "0", "0", "0", "0", 0, 0, "0", 0, 0, "0", 0, "0", "0", "0", "0", 0, 0, "0", 0, 0, "0", 0, "0", "0", "0", "0", 0, 0, "0", 0, 0, "0", 0, "0", "0", "0", "0", 0, 0, "0", 0, 0, "0", 0, "0", "0", "0", "0", 0, 0, "0", 0 };
	enum menu {add_new, find_ARM, find_cost, all_microcontrollers, number_16_Microchip, number_Mega, exit} M;
	int a = 0; // артикул
	int number = 0; // количество заполненных полей
	int counter = 0;

	do {
		printf("%s", "MENU:\n");
		printf("%s", "0 - add_new\n1 - find_ARM\n2 - find_cost_800_1000\n3 - all_microcontrollers\n4 - number_16_Microchip\n5 - number_Mega\n6 - exit\n");
		scanf_s("%d", &M);
		switch (M)
		{
		case add_new:
		{
			printf("%s", "new microcontroller\n");
			printf("%s", "artikul: ");
			scanf_s("%d", &a);
			int new_art = 0;
			do { // проверка на наличие артикула
				for (int i = 0; i < number; i++) {
					if (all[i].articul == a) {
						printf("%s", "there is microcontroller with such artukul, input new: ");
						scanf_s("%d", &a);
						new_art = 1;
						break;
					}
					else new_art = 0;
					printf("ok");
				}
			} while (new_art == 1);
			
			all[number].articul = a;
			printf("%s", "data of microcontroller with this artikul:\n");
			printf("%s", "name: ");
			scanf_s("%s", all[number].name, _countof(all[number].name));
			printf("%s", "code: ");
			scanf_s("%d", &all[number].firm_proisvod.code);
			printf("%s", "firma: ");
			scanf_s("%s", all[number].firm_proisvod.name, _countof(all[number].firm_proisvod.name));
			printf("%s", "town: ");
			scanf_s("%s", all[number].firm_proisvod.town, _countof(all[number].firm_proisvod.town));
			printf("%s", "adress: ");
			scanf_s("%s", all[number].firm_proisvod.adress, _countof(all[number].firm_proisvod.adress));
			printf("%s", "phone: ");
			scanf_s("%s", all[number].firm_proisvod.phone, _countof(all[number].firm_proisvod.phone));
			printf("%s", "rasrad: ");
			scanf_s("%d", &all[number].rasrad);
			printf("%s", "chastota: ");
			scanf_s("%d", &all[number].takt);
			printf("%s", "architecture: ");
			scanf_s("%s", all[number].architecture, _countof(all[number].architecture));
			printf("%s", "cost: ");
			scanf_s("%d", &all[number].cost);
			number++;
			getch();
			break;
		}
		case find_ARM:
		{
			for (int i = 0; i < 10; i++) {
				if (strcmp(all[i].architecture, "ARM") == 0) printf("artikul: %d\nname: %s\nfirma: %s\nrasrad: %d\nchastota: %d\n", all[i].articul, all[i].name, all[i].firm_proisvod.name, all[i].rasrad, all[i].takt);
			}
			getch();
			break;
		}
		case find_cost:
		{
			for (int i = 0; i < 10; i++) {
				if ((all[i].cost >= 800) && (all[i].cost <= 1000)) printf("name: %s\nrasrad: %d\nchastota: %d\narchitecture: %s\ncost: %d\n", all[i].name, all[i].rasrad, all[i].takt, all[i].architecture, all[i].cost);
			}
			getch();
			break;
		}
		case all_microcontrollers:
		{
			printf("%s", "artikul    name       code       firma      town       adress     phone      rasrad      chastota   architecture cost      \n");
			for (int i = 0; i < 10; i++) {
				printf("%10d %10s %10d %10s %10s %10s %10s %10d %10d %10s %10d\n", all[i].articul, all[i].name, all[i].firm_proisvod.code, all[i].firm_proisvod.name, all[i].firm_proisvod.town, all[i].firm_proisvod.adress, all[i].firm_proisvod.phone, all[i].rasrad, all[i].takt, all[i].architecture, all[i].cost);
			}
			getch();
			break;
		}
		case number_16_Microchip:
		{
			counter = 0;
			for (int i = 0; i < 10; i++) {
				if ((all[i].rasrad == 16) && (strcmp(all[i].firm_proisvod.name,"Microchip") == 0)) counter++;
			}
			printf("count 16-rasrad microcontrollers by Microchip: %d\n", counter);
			getch();
			break;
		}
		case number_Mega:
		{
			counter = 0;
			for (int i = 0; i < 10; i++) {
				if (strncmp(all[i].name, "Mega", 4) == 0) counter++;
			}
			printf("count microcontrollers with Mega-: %d\n", counter);
			getch();
			break;
		}
		case exit:
		{
			break;
		}
		default:
		{
			break;
		}
		};
	} while (M != 6);
	
}