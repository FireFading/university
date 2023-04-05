#include <iostream>
#include <string>
#include "module.h"

using namespace std;

int main() {
	string command;
	do {
		cout << "MENU" << endl;
		cout << "ONE - count words that starts with capital" << endl;
		cout << "TWO - redaction text with only consonant" << endl;
		cout << "THREE - redaction text with defis" << endl;
		cout << "exit" << endl;
		cin >> command;
		if (command == "ONE") {
			cout_big_word();
		}
		else {
			if (command == "TWO") {
				redaction();
			}
			else {
				if (command == "THREE") {
					redaction_text();
				}
				else {
					if (command == "exit") {
						break;
					}
					else {
						cout << "wrong COMMAND!" << endl;
					}
				}
			}
		}
	} while (command != "exit");

	return 0;
}
