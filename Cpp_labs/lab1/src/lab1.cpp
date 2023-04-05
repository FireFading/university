#include "module1.h"

using namespace std;

int main() {
	int n = 0;
	int input_command;
	Microcontroller* base = new Microcontroller[n];
	enum menu {
		add=1,
		del,
		show,
		find_firm,
		find_arch,
		save_in_file,
		read_file,
		exit,
	};
	menu command;
	do {
		cout << "MENU" << endl;
		cout << "1 - add new item" << endl;
		cout << "2 - del item" << endl;
		cout << "3 - show all elements" << endl;
		cout << "4 - find such firm" << endl;
		cout << "5 - find such architecture" << endl;
		cout << "6 - save table in file" << endl;
		cout << "7 - read from file" << endl;
		cout << "8 - exit" << endl;
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
		case save_in_file:
			base = save_file(base, &n);
			break;
		case read_file:
			base = read_file_el(base, &n);
			break;
		case exit:
			delete [] base;
			break;
		default:
			cout << "wrong digit!" << endl;
			break;
		}
	} while (command != 8);

	return 0;
}
