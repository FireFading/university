#include "module.h"

	// конструктор без параметров
//Microcontroller:: Microcontroller():
//		artikul(1), name("Microcontroller"), make{"IBM", "Orel"}, rasrad(64), takt(50), arch(ARM), cost(100.44), cost_low(false)
//	{}

	// конструктор с параметрами
Microcontroller:: Microcontroller(int n_artikul, string n_name, string fn_name, string n_town, int n_rasrad, float n_takt, architecture n_arch, float n_cost, bool n_cost_low): // конструктор по умолчанию
		artikul(n_artikul), name(n_name), make{fn_name, n_town}, rasrad(n_rasrad), takt(n_arch), arch(n_arch), cost(n_cost), cost_low(n_cost_low)
	{}

Microcontroller:: ~Microcontroller() {}; // деструктор


void Microcontroller:: set_data(int n_artikul, string n_name, string fn_name, string n_town, int n_rasrad, float n_takt, architecture n_arch, float n_cost, bool n_cost_low)
	{
		artikul = n_artikul;
		name = n_name;
		make.name_f = fn_name;
		make.town = n_town;
		rasrad = n_rasrad;
		takt = n_takt;
		arch = n_arch;
		cost = n_cost;
		cost_low = n_cost_low;
	}

int Microcontroller:: getArtikul() { return artikul; }
string Microcontroller:: getName() { return name; };
string Microcontroller:: getFirmName() { return make.name_f; }
string Microcontroller:: getFirmTown() { return Microcontroller::make.town; }
int Microcontroller:: getRasrad(){ return Microcontroller::rasrad; }
float Microcontroller:: getTakt() { return Microcontroller::takt; }
int Microcontroller:: getArchitecture() { return arch; }
float Microcontroller:: getCost() { return cost; }
bool Microcontroller:: getCostLow() { return cost_low; }


void Microcontroller:: show_element() { // вывод свойств объекта
		string arch_name; // для названия архитектуры
		int n; // для дальнейшего вывода названия архитектуры
		string* architecture = new string[2]; // для вывода названия архитектуры
		architecture[0] = "ARM";
		architecture[1] = "X86";
		n = arch;
		arch_name = architecture[n-1];
		cout.setf(ios::fixed);
		cout << setw(8) << left << artikul;
		cout << setw(16) << left << name;
		cout << setw(10) << left << make.name_f;
		cout << setw(10) << left << make.town;
		cout << setw(10) << left << rasrad;
		cout << setw(10) << left << setprecision(3) << takt;
		cout << setw(16) << left << arch_name;
		cout << setw(10) << left << setprecision(3) << cost;
		cout << setw(10) << left << boolalpha << cost_low << endl;

}


Microcontroller* add_new(Microcontroller* base, int* number) {
	Microcontroller* temp_base = (Microcontroller*)operator new(sizeof(Microcontroller) * (*number + 1));
	bool flag;
	int flag_err = 0;
	if (*number != 0) {
		for (int i = 0; i < *number; i++) {
			temp_base[i] = base[i]; // копирование существующих записей во временный объект
		}
	}
	cout << "INPUT DATA:" << endl;
	cout << "Do you want to use default information? 1 - yes, 0 - no" << endl;
	cin >> flag;
	if (flag == 1) {
		temp_base[*number] = Microcontroller(); // создание объекта с информацией по умолчанию
	}
	else {
		int n_artikul, n_rasrad, input_architecture;
		string n_name, fn_name, n_town;
		architecture n_arch = ARM;
		float n_takt, n_cost;
		bool n_cost_low;

		cout << "artikul: ";
		do {
			flag_err = 0; // флаг ошибки - такой артикул уже есть
			cin >> n_artikul;
			for (int i = 0; i < *number; i++) {
				if (temp_base[i].getArtikul() == n_artikul) {
					cout << "this artikul is already in table!" << endl;
					flag_err = 1;
					break;
				}
			}
		} while (flag_err != 0);

		cout << "name: ";
		cin >> n_name;
		cout << "firma: ";
		cin >> fn_name;
		cout << "town of firma: ";
		cin >> n_town;
		cout << "rasrad: ";
		cin >> n_rasrad;
		cout << "takt: ";
		cin >> n_takt;
		cout << "architecture: ";
		cout << "1 - ARM, 2 - x86" << endl;
		cin >> input_architecture;
			if (input_architecture == 1 || input_architecture == 2) {
				n_arch = static_cast<architecture>(input_architecture);
			}
			else {
				cout << "wrong value! will use default value!" << endl;
			}
		cout << "cost: ";
		cin >> n_cost;
		cout << "cost_low: ";
		cin >> n_cost_low;
		Microcontroller new_s = Microcontroller(n_artikul, n_name, fn_name, n_town, n_rasrad, n_takt, n_arch, n_cost, n_cost_low); // конструктор с параметрами
		temp_base[*number] =  new_s;
	}
	(*number)++;
	return temp_base;
}


Microcontroller* del(Microcontroller* base, int* number, int art) {
	Microcontroller* temp_base = (Microcontroller*)operator new(sizeof(Microcontroller) * (*number-1));
	int k = 0;
	for (int i = 0; i < *number; i++) {
		if (base[i].getArtikul() != art) {
			temp_base[k] = base[i];
			k++;
		}
	}
	*number = k;
	return temp_base;
}


Microcontroller* del(Microcontroller* base, int* number, string n) {
	Microcontroller* temp_base = (Microcontroller*)operator new(sizeof(Microcontroller) * (*number-1));
	int k = 0;
	for (int i = 0; i < *number; i++) {
		if (base[i].getName() != n) {
			temp_base[k] = base[i];
			k++;
		}
	}
	*number = k;
	return temp_base;
}


Microcontroller* del(Microcontroller* base, int* number, int art, string n) {
	Microcontroller* temp_base = (Microcontroller*)operator new(sizeof(Microcontroller) * (*number-1));
	int k = 0;
	for (int i = 0; i < *number; i++) {
		if ((base[i].getName() != n) || (base[i].getArtikul() != art)) {
			temp_base[k] = base[i];
			k++;
		}
	}
	*number = k;
	return temp_base;
}



Microcontroller* del_item(Microcontroller* base, int* number) {
	int t = (*number);
	string n;
	int art;
	Microcontroller* temp_base = (Microcontroller*)operator new(sizeof(Microcontroller) * (*number-1));
	enum choose {
		artikul=1,
		name,
		both
	} command;
	int input_command;
	cout << "DELETE " << endl;
	cout << "1 - by artikul" << endl;
	cout << "2 - by name" << endl;
	cout << "3 - by artikul and name" << endl;
	cin >> input_command;
	command = static_cast<choose>(input_command);
	switch(command) {
	case artikul: // удаление по артикулу
		cout << "input artikul: ";
		cin >> art;
		temp_base = del(base, number, art);
		break;
	case name: // удаление по имени
		cout << "input name: ";
		cin >> n;
		temp_base = del(base, number, n);
		break;
	case both:
		cout << "input artikul: ";
		cin >> art;
		cout << "input name: ";
		cin >> n;
		temp_base = del(base, number, art, n);
		break;
	}
	if (t == (*number)) {
		return base;
	}
	return temp_base;
}


void show_elements(Microcontroller* base, const int number) {
	cout << "current shop: " << Microcontroller::get_shop() << endl;
	cout << "MICROCONTROLLERS:" << endl;
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
		base[i].show_element();
	}
}


void inf_firm(Microcontroller* base, const int number) { // вывод информации об элементах нужной фирмы
	string firma;
	cout << "input firma: ";
	cin >> firma;
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
	for (int i = 0; i < number; i++) {
		if (base[i].getFirmName() == firma) {
			base[i].show_element();
		}
	}
}


void count_arch_low(Microcontroller* base, const int number) {
	int input_architecture;
	int count_all = 0;
	cout << "input architecture:" << endl;
	cout << "1 - ARM" << endl << "2 - x86" << endl;
	cin >> input_architecture;
	for (int i = 0; i < number; i++) {
		if ((base[i].getArchitecture() == input_architecture) || (base[i].getCostLow() == true)) {
			count_all++;
		}
	}
	cout << "number low cost microcontrollers with such architecture: " << count_all << endl;
}


void new_shop() {
	string new_shop;
	cout << "input new name of shop: ";
	cin >> new_shop;
	Microcontroller::set_shop(new_shop);
}

