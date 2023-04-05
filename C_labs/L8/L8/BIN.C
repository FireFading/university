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

void ADD_new(microcontroller** all, int number) {
	int a = 0; // артикул
	printf("new microcontroller\n");
	printf("artikul: ");
	scanf_s("%d", &a);
	int new_art = 0;
	do { // проверка на наличие артикула
		for (int i = 0; i < number; i++) {
			if ((*all + i)->articul == a) {
				printf("there is microcontroller with such artukul, input new: ");
				scanf_s("%d", &a);
				new_art = 1;
				break;
			}
			else new_art = 0;
		}
	} while (new_art == 1);

	*all = (microcontroller*)realloc(*all, (number + 1) * sizeof(microcontroller));
	(*all + number)->articul = a;
	printf("data of microcontroller with this artikul:\n");
	printf("name: ");
	scanf_s("%s", (*all + number)->name, _countof((*all + number)->name));
	printf("code: ");
	scanf_s("%d", &(*all + number)->firm_proisvod[0].code);
	printf("firma: ");
	scanf_s("%s", (*all + number)->firm_proisvod[0].name, _countof((*all + number)->firm_proisvod[0].name));
	printf("town: ");
	scanf_s("%s", (*all + number)->firm_proisvod[0].town, _countof((*all + number)->firm_proisvod[0].town));
	printf("adress: ");
	scanf_s("%s", (*all + number)->firm_proisvod[0].adress, _countof((*all + number)->firm_proisvod[0].adress));
	printf("phone: ");
	scanf_s("%s", (*all + number)->firm_proisvod[0].phone, _countof((*all + number)->firm_proisvod[0].phone));
	printf("rasrad: ");
	scanf_s("%d", &(*all + number)->rasrad);
	printf("chastota: ");
	scanf_s("%d", &(*all + number)->takt);
	printf("architecture: ");
	scanf_s("%s", (*all + number)->architecture, _countof((*all + number)->architecture));
	printf("cost: ");
	scanf_s("%d", &(*all + number)->cost);
}

microcontroller* delete_pos(microcontroller* all, int* number) {
	int a = 0; // артикул--
	printf("input artikul: ");
	scanf_s("%d", &a);
	for (int i = 0; i < *number; i++) {
		if ((all + i)->articul == a) {
			*number = *number - 1;
			for (int j = i; j < *number; j++) {
				(all + j)->articul = (all + j + 1)->articul;
				for (int h = 0; h < 20; h++) (all + j)->name[h] = (all + j + 1)->name[h];
				(all + j)->firm_proisvod[0].code = (all + j + 1)->firm_proisvod[0].code;
				for (int h = 0; h < 20; h++) (all + j)->firm_proisvod[0].name[h] = (all + j + 1)->firm_proisvod[0].name[h];
				for (int h = 0; h < 20; h++) (all + j)->firm_proisvod[0].town[h] = (all + j + 1)->firm_proisvod[0].town[h];
				for (int h = 0; h < 20; h++) (all + j)->firm_proisvod[0].adress[h] = (all + j + 1)->firm_proisvod[0].adress[h];
				for (int h = 0; h < 13; h++) (all + j)->firm_proisvod[0].phone[h] = (all + j + 1)->firm_proisvod[0].phone[h];
				(all + j)->rasrad = (all + j + 1)->rasrad;
				(all + j)->takt = (all + j + 1)->takt;
				for (int h = 0; h < 10; h++) (all + j)->architecture[h] = (all + j + 1)->architecture[h];
				(all + j)->cost = (all + j + 1)->cost;
			}
			all = (microcontroller*)realloc(all, *number * sizeof(microcontroller));
		}
	}
	return all;
}

void show_elements(int i, microcontroller** pos_all) {
	if (i > 0) {
		show_elements(--i, pos_all);
		printf("%10d %10s %10d %10s %10s %10s %10s %10d %10d %10s %10d\n", (*pos_all + i)->articul, (*pos_all + i)->name, (*pos_all + i)->firm_proisvod[0].code, (*pos_all + i)->firm_proisvod[0].name, (*pos_all + i)->firm_proisvod[0].town, (*pos_all + i)->firm_proisvod[0].adress, (*pos_all + i)->firm_proisvod[0].phone, (*pos_all + i)->rasrad, (*pos_all + i)->takt, (*pos_all + i)->architecture, (*pos_all + i)->cost);
	}
	else printf("artikul    name       code       firma      town       adress     phone      rasrad      chastota   architecture cost      \n");
}


void Find_arch(int i, char* arch, microcontroller** pos_all) {
	if (i > 0) {
		Find_arch(--i, arch, pos_all);
		if (strcmp((*pos_all + i)->architecture, arch) == 0) {
			printf("MICROCONTROLLER: \n");
			printf("artikul: %d\nname: %s\ncode of firma: %d\nfirma: %s\ntown: %s\nadress: %s\nphone: %s\nrasrad: %d\ntakt: %d\narchitecture: %s\ncost: %d\n", (*pos_all + i)->articul, (*pos_all + i)->name, (*pos_all + i)->firm_proisvod[0].code, (*pos_all + i)->firm_proisvod[0].name, (*pos_all + i)->firm_proisvod[0].town, (*pos_all + i)->firm_proisvod[0].adress, (*pos_all + i)->firm_proisvod[0].phone, (*pos_all + i)->rasrad, (*pos_all + i)->takt, (*pos_all + i)->architecture, (*pos_all + i)->cost);
		}
	}
	else printf("MICROCONTROLLERS:\n");
}


int Count_microcont(int i, int counter, microcontroller* all, char* user_firma) {
	if (i > 0) {
		counter = Count_microcont(--i, counter, all, user_firma);
		if (((all + i)->rasrad == 16) && (strcmp((all + i)->firm_proisvod[0].name, user_firma)) == 0) counter++;
	}
	return counter;
}

int main() {
	microcontroller* all; // указатель на массив структур
	int number = 0; // количество заполненных полей
	char arch[10], firma[10]; // для ввода архитектуры и фирмы

	FILE* f = NULL;

	all = (microcontroller*)malloc(number * sizeof(microcontroller)); // выделение памяти
	microcontroller** pos_all = &all; // для коректной записи данных в функции

	enum menu { add_new, del_on_pos, all_microcontrollers, find_architecture, count_16_firma, write_file, read_file, exit } M;
	int counter = 0;
	int number_file = 0; //количество записей в файле

	do {
		printf("MENU:\n");
		printf("0 - add_new\n1 - del_on_pos\n2 - all_microcontrollers\n3 - find_architecrure\n4 - count_16_firma\n5 - add_to_file\n6 - read_from_file\n7 - exit\n");
		scanf_s("%d", &M);
		switch (M) {
		case add_new:
		{
			ADD_new(pos_all, number);
			number++;
			getch();
			break;
		}
		case del_on_pos:
		{
			all = delete_pos(all, &number);
			getch();
			break;
		}
		case all_microcontrollers:
		{
			show_elements(number, pos_all);
			getch();
			break;
		}
		case find_architecture:
		{
			printf("input architecture: ");
			scanf_s("%s", arch, _countof(arch));
			Find_arch(number, &arch, pos_all);
			getch();
			break;
		}
		case count_16_firma:
		{
			counter = 0;
			printf("input firma: ");
			scanf_s("%s", firma, _countof(firma));
			counter = Count_microcont(number, counter, all, &firma);
			printf("count microcontrollers with 16 rasrad and such firma: %d\n", counter);
			getch();
			break;
		}
		case write_file:
		{
			fopen_s(&f, "file.bin", "wb");
			fwrite(all, sizeof(microcontroller), number, f);
			number_file = number;
			number = 0;
			all = (microcontroller*)realloc(all, number * sizeof(microcontroller));
			fclose(f);
			getch();
			break;
		}
		case read_file:
		{
			if (number_file > 0) {
				fopen_s(&f, "file.bin", "rb");
				all = (microcontroller*)realloc(all, (number + number_file) * sizeof(microcontroller));
				fread((all + number), sizeof(microcontroller), number_file, f);
				number = number + number_file;
				getch();
				fclose(f);
			}
			else printf("file empty\n");
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
	} while (M != 7);
	return 0;
}