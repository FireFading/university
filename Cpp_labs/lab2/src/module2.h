#ifndef MODULE_H_
#define MODULE_H_

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

struct firma {
			string name_f;
			string town;
};

enum architecture {
		ARM = 1,
		X86,
};

class Microcontroller {

private:
	int artikul;
	string name;
	firma make{};
	int rasrad;
	float takt;
	architecture arch;
	float cost;
	bool cost_low;

	static string shop;

public:
	// конструктор без параметров
//	Microcontroller();

	// конструктор с параметрами
	Microcontroller(int n_artikul = 1, string n_name = "Microcontroller", string fn_name = "IBM", string n_town = "Orel", int n_rasrad = 64, float n_takt = 100.33, architecture n_arch = ARM, float n_cost = 100.99, bool n_cost_low = false);

	~Microcontroller(); // деструктор

	static void set_shop(string new_shop) { shop = new_shop; }

	static string get_shop() { return shop; }

	void set_data(int n_artikul, string n_name, string fn_name, string n_town, int n_rasrad, float n_takt, architecture n_arch, float n_cost, bool n_cost_low);

	int getArtikul();
	string getName();
	string getFirmName();
	string getFirmTown();
	int getRasrad();
	float getTakt();
	int getArchitecture();
	float getCost();
	bool getCostLow();


	void show_element();

};


Microcontroller* add_new(Microcontroller* base, int* number);

Microcontroller* del(Microcontroller* base, int* number, int art);

Microcontroller* del(Microcontroller* base, int* number, string n);

Microcontroller* del(Microcontroller* base, int* number, int art, string n);

Microcontroller* del_item(Microcontroller* base, int* number);

void show_elements(Microcontroller* base, const int number);

void inf_firm(Microcontroller* base, const int number);

void count_arch_low(Microcontroller* base, const int number);

void new_shop();

#endif /* MODULE_H_ */
