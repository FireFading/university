#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

int main() {
	struct microcontroller
	{
		int articul; // �������
		char name[20]; // ��������
		char firm_proisvod[20]; // ����� - �������������
		int rasrad; // �����������
		int takt; // �������� �������
		char architecture[10]; // �����������
		int cost; // ����
	};
	struct sell
	{
		int tabel; // ��������� �����
		char name[30]; // ���
		char adress[30]; // �����
		int money; // �����
	};
	union Uni
	{
		struct microcontroller prod[1];
		struct sell buy[1];
	};
	enum menu { add_new, all, all_microcontrollers, count_sellars, find_20000, exit } M;
	union Uni u[21];
	int a;
	int n = 0; // ���������� ����������� ����� �����
	int m = 20; // ���������� ����������� ����� �������� - ������ � ����������� ������� � �����, ����� �������� ������������ ������
	do {
		printf("MENU:\n0 - add_new\n1 - all\n2 - all_microcontrollers\n3 - count_sellars\n4 - find_20000\n5 - exit\n");
		scanf_s("%d", &M);
		switch (M) {
		case add_new:
			a = 0;
			if (n != m + 1) {
				printf("1 - ������ ���������� � ����������������, 2 - ������ ��������\n");
				scanf_s("%d", &a);
				switch (a) {
				case 1:
					printf("������� �������: ");
					scanf_s("%d", &u[n].prod[0].articul);
					printf("������� ��������: ");
					scanf_s("%s", u[n].prod[0].name, _countof(u[n].prod[0].name));
					printf("������� �����: ");
					scanf_s("%s", u[n].prod[0].firm_proisvod, _countof(u[n].prod[0].firm_proisvod));
					printf("������� �����������: ");
					scanf_s("%d", &u[n].prod[0].rasrad);
					printf("������� �������� �������: ");
					scanf_s("%d", &u[n].prod[0].takt);
					printf("������� �����������: ");
					scanf_s("%s", u[n].prod[0].architecture, _countof(u[n].prod[0].architecture));
					printf("������� ����: ");
					scanf_s("%d", &u[n].prod[0].cost);
					n++;
					getch();
					break;
				case 2:
					printf("������� ��������� �����: ");
					scanf_s("%d", &u[m].buy[0].tabel);
					printf("������� ���: ");
					scanf_s("%s", u[m].buy[0].name, _countof(u[m].buy[0].name));
					printf("������� �����: ");
					scanf_s("%s", u[m].buy[0].adress, _countof(u[m].buy[0].adress));
					printf("������� �����: ");
					scanf_s("%d", &u[m].buy[0].money);
					m--;
					getch();
					break;
				default:
					break;
				}
			}
			else printf("���� ������ ��� ���������!\n");
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
			printf("���������� ���������: %d\n", (20 - m));
			getch();
			break;
		case find_20000:
			printf("�������� � ������� ����� 20000\n");
			for (int i = 20; i > m; i--) 
				if (u[i].buy[0].money < 20000) {
					printf("��������� �����: %d\n", u[i].buy[0].tabel);
					printf("���: %s\n", u[i].buy[0].name);
					printf("������: %s\n", u[i].buy[0].adress);
					printf("�����: %d\n", u[i].buy[0].money);
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