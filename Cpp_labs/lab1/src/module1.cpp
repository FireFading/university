#include "module1.h"

using namespace std;


Microcontroller* add_new(Microcontroller* base, int* number) {
	Microcontroller* temp_base = new Microcontroller[*number+1];
	int input_architecture, input_artikul, flag_err, is_low;
	string input_name;
	int flag; // для решения нужно ли добавлять данные по конкретному пункту или нет
	if (*number != 0) {
		for (int i = 0; i < *number; i++) {
			temp_base[i] = base[i]; // копирование существующих записей во временный объект
		}
	}
	cout << "INPUT DATA:" << endl;
	cout << "Do you want input any data or use insltall data? 1 - input own, 0 - use default" << endl;
	cin >> flag;
	if (flag == 1) {

		cout << "artikul: ";
		do {
			flag_err = 0; // флаг ошибки - такой артикул уже есть
			cin >> input_artikul;
			for (int i = 0; i < *number; i++) {
				if (temp_base[i].artikul == input_artikul) {
					cout << "this artikul is already in table!" << endl;
					flag_err = 1;
					break;
				}
			}
			if (flag_err == 0) {
				temp_base[*number].artikul = input_artikul;
			}
		} while (flag_err != 0);

		cout << "name: ";
		do {
			flag_err = 0;
			cin >> input_name;
			for (int i = 0; i < *number; i++) {
				if (temp_base[i].name == input_name) {
					cout << "this name is already in table!" << endl;
					flag_err = 1;
					break;
				}
			}
			if (flag_err == 0) {
				temp_base[*number].name = input_name;
			}
		} while (flag_err != 0);

		cout << "firma? ";
		cin >> flag;
		if (flag == 1) {
			cin >> temp_base[*number].make.name_f;
		}
		cout << "town of firma? ";
		cin >> flag;
		if (flag == 1) {
			cin >> temp_base[*number].make.town;
		}
		cout << "rasrad? ";
		cin >> flag;
		if (flag == 1) {
			cin >> temp_base[*number].rasrad;
		}
		cout << "takt? ";
		cin >> flag;
		if (flag == 1) {
			cin >> temp_base[*number].takt;
		}
		cout << "architecture? " << endl;
		cin >> flag;
		if (flag == 1) {
			do {
				flag_err = 0; // флаг ошибки - выбрана несуществующая архитектура
				cout << "1 - ARM, 2 - x86" << endl;
				cin >> input_architecture;
				if (input_architecture == 1 || input_architecture == 2) {
					flag_err = 0;
					temp_base[*number].arch = static_cast<Microcontroller :: architecture>(input_architecture);
				}
				else {
					flag_err = 1;
					cout << "wrong value! will use default value!" << endl;
				}
			} while (flag_err != 0);
		}
		cout << "cost? ";
		cin >> flag;
		if (flag == 1) {
			cin >> temp_base[*number].cost;
		}
		cout << "cost_low? ";
		cin >> flag;
		if (flag == 1) {
			do {
				flag_err = 0;
				cin >> is_low;
				if (is_low == 1 || is_low == 0) {
					flag_err = 0;
					temp_base[*number].cost_low = is_low;
				}
				else {
					flag_err = 1;
					cout << "wrong value!" << endl;
				}
			} while (flag_err != 0);
		}
	}
	(*number)++;
	return temp_base;
}


Microcontroller* del(Microcontroller* base, int* number, int art) {
	Microcontroller* temp_base = new Microcontroller[*number-1];
	int k = 0;
	for (int i = 0; i < *number; i++) {
		if (base[i].artikul != art) {
			temp_base[k] = base[i];
			k++;
		}
	}
	*number = k;
	return temp_base;
}


Microcontroller* del(Microcontroller* base, int* number, string n) {
	Microcontroller* temp_base = new Microcontroller[*number-1];
	int k = 0;
	for (int i = 0; i < *number; i++) {
		if (base[i].name != n) {
			temp_base[k] = base[i];
			k++;
		}
	}
	*number = k;
	return temp_base;
}


Microcontroller* del(Microcontroller* base, int* number, int art, string n) {
	Microcontroller* temp_base = new Microcontroller[*number-1];
	int k = 0;
	for (int i = 0; i < *number; i++) {
		if ((base[i].name != n) || (base[i].artikul != art)) {
			temp_base[k] = base[i];
			k++;
		}
	}
	*number = k;
	return temp_base;
}


Microcontroller* del_item(Microcontroller* base, int* number) {
	int t = *number;
	Microcontroller* temp_base = new Microcontroller[*number-1];
	int art;
	string n;
	enum choose {
		artikul=1,
		name,
		both
	};
	choose command;
	int input_command;
	cout << "DELETE " << endl;
	cout << "1 - by artikul" << endl;
	cout << "2 - by name" << endl;
	cout << "3 - by name and artikul" << endl;
	cin >> input_command;
	command = static_cast<choose>(input_command);
	switch(command) {
	case artikul: // удаление по артикулу
		cout << "input artikul: ";
		cin >> art;
		temp_base = del(base, number, art);
		if (*number == t) {
			return base;
		}
		break;
	case name: // удаление по имени
		cout << "input name: ";
		cin >> n;
		temp_base = del(base, number, n);
		if (*number == t) {
			return base;
		}
		break;
	case both:
		cout << "input artikul: ";
		cin >> art;
		cout << "input name: ";
		cin >> n;
		temp_base = del(base, number, art, n);
		if (*number == t) {
			return base;
		}
		break;
	}
	return temp_base;
}


void show_elements(Microcontroller* base, const int number) {
	cout << "MICROCONTROLLERS:" << endl;
	string arch_name; // для названия архитектуры
	int n; // для дальнейшего вывода названия архитектуры
	string* architecture = new string[2]; // для вывода названия архитектуры
	architecture[0] = "ARM";
	architecture[1] = "X86";
	cout.setf(ios::fixed); // установка формата вывода
	cout << setw(8) << left << "artikul"; // шапка таблицы
	cout << setw(16) << left << "name";
	cout << setw(10) << left << "firma";
	cout << setw(10) << left << "town";
	cout << setw(10) << left << "rasrad";
	cout << setw(10) << left << "takt";
	cout << setw(16) << left << "architecture";
	cout << setw(10) << left << "cost";
	cout << setw(10) << left << "low" << endl;
	for (int i = 0; i < number; i++) { // вывод таблицы
		n = base[i].arch;
		arch_name = architecture[n-1];
		cout.setf(ios::fixed);
		cout << setw(8) << left << base[i].artikul;
		cout << setw(16) << left << base[i].name;
		cout << setw(10) << left << base[i].make.name_f;
		cout << setw(10) << left << base[i].make.town;
		cout << setw(10) << left << base[i].rasrad;
		cout << setw(10) << left << setprecision(3) << base[i].takt;
		cout << setw(16) << left << arch_name;
		cout << setw(10) << left << setprecision(3) << base[i].cost;
		cout << setw(10) << left << boolalpha << base[i].cost_low << endl;
	}
}


void inf_firm(Microcontroller* base, const int number) {
	string firma;
	cout << "input firma: ";
	cin >> firma;
	for (int i = 0; i < number; i++) {
		if (base[i].make.name_f == firma) {
			cout << "artikul: "<< base[i].artikul <<endl;
			cout << "name: " << base[i].name << endl;
			cout << "firm's name: " << base[i].make.name_f << endl;
			cout << "firm's town " << base[i].make.town << endl;
			cout << "rasrad: " << base[i].rasrad << endl;
			cout << "takt: " << base[i].takt << endl;
			cout << "architecture: " << base[i].arch << endl;
			cout << "cost: " << base[i].cost << endl;
			cout << "low: " << base[i].cost_low << endl;
		}
	}
}


void count_arch_low(Microcontroller* base, const int number) {
	int input_architecture;
	int count_all = 0;
	cout << "input architecture:" << endl;
	cout << "1 - ARM" << endl << "2 - x86";
	cin >> input_architecture;
	for (int i = 0; i < number; i++) {
		if ((base[i].arch == input_architecture) && (base[i].cost_low == true)) {
			count_all++;
		}
	}
	cout << "number low cost microcontrollers with such architecture: " << count_all << endl;
}


