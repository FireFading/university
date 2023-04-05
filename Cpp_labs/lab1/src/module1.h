#ifndef MODULE_H_
#define MODULE_H_

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

struct Microcontroller {
	int artikul = 1;
	string name = "Microcontroller";
	struct firma {
			char name_f[50] = "IBM";
			char town[50] = "Orel";
	} make;
	int rasrad = 64;
	float takt = 100;
	enum architecture {
		ARM = 1,
		X86,
	} arch = ARM;
	float cost = 100.99;
	bool cost_low = false;
};

Microcontroller* add_new(Microcontroller* base, int* number);


Microcontroller* del_item(Microcontroller* base, int* number);


void show_elements(Microcontroller* base, const int number);

void inf_firm(Microcontroller* base, const int number);


void count_arch_low(Microcontroller* base, const int number);


inline Microcontroller* save_file(Microcontroller* base, int* number) {
	string file_name;
	cout << "input path: ";
	cin >> file_name;
	ofstream fout(file_name, ios_base::binary | ios_base::trunc);
	fout.write((char*)(base), sizeof(Microcontroller) * (*number));
	fout.close();
	*number = 0;
	base = new Microcontroller [0];
	return base;
}


inline Microcontroller* read_file_el(Microcontroller* base, int* number) {
	string file_name;
	int m;
	cout << "input path: ";
	cin >> file_name;
	ifstream fin(file_name, ios_base::binary);
	fin.seekg(0, ios_base::end);
	m = fin.tellg();
	(*number) = m / sizeof(Microcontroller);
	base = new Microcontroller [*number];
	fin.seekg(0);
	fin.read((char*)base, (*number) * sizeof(Microcontroller));
	fin.close();
	return base;
}


#endif /* MODULE_H_ */
