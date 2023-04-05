#include <iostream>
#include <cstdlib>
#include "module.h"
using namespace std;

string Microcontroller:: shop = "bagira";

int main() {
	int n = 0; // количество объектов
	int input_command;
	Microcontroller* base = (Microcontroller*)operator new(sizeof(Microcontroller) * n);
	enum menu {
			add=1,
			del,
			show,
			find_firm,
			find_arch,
			change,
			exit,
		};
		menu command;
	do {
		cout << "MENU" << endl;
		cout << "1 - add new item" << endl;
		cout << "2 - del item" << endl;
		cout << "3 - show all elements" << endl;
		cout << "4 - find such firm" << endl;
		cout << "5 - find low cost with such architecture" << endl;
		cout << "6 - change shop" << endl;
		cout << "7 - exit" << endl;
		cin >> input_command;
		command = static_cast<menu>(input_command); // преобразование числа в перечисляемый тип
		switch(command) {
		case add:
			base = add_new(base, &n);
			break;
		case del:
			base = del_item(base, &n);
			break;
		case show:
			show_elements(base, n);
			break;
		case find_firm:
			inf_firm(base, n);
			break;
		case find_arch:
			count_arch_low(base, n);
			break;
		case change:
			new_shop();
			break;
		case exit:
			delete [] base;
			break;
		default:
			cout << "wrong digit!" << endl;
			break;
		}
	} while (command != 7);
	return 0;
}
