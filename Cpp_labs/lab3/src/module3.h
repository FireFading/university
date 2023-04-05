#include <iostream>
#include <string>
#include <cctype>   // для функции islower

using namespace std;


#ifndef MODULE_H_
#define MODULE_H_

void cout_big_word() {
	int n = 0; // количество слов в тексте, начинающиеся с заглавной буквы
	int flag = 1;
	string s;
	cout << "input your text:" << endl;
	cin.clear();
	getline(cin, s);
	getline(cin, s);
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == ' ') {
			flag = 1; // начало слова
		}
		else {
			if (flag == 1) { // перед этим символом был пробел
				if (islower(s[i]) == false) { // символ заглавный
					n++;
				}
			}
			flag = 0;
		}
	}
	cout << n << " words that starts with capital" << endl;
}


void redaction() { // удаление гласных из строки
	string text;
	cout << "YOUR TEXT:" << endl;
	cin.clear();
	getline(cin, text);
	getline(cin, text);
	string consonant = "aeiouyAEIOUY";
	int n = text.size(); // количество символов в тексте

	for (int i = 0; i < n; i++) {
		if (consonant.find(text[i]) >= 0 && consonant.find(text[i]) < consonant.size()) {
			text.erase(i, 1);
			i--;
		}
		n = text.size();
	}
	cout << "result: " << text << endl;
}


void redaction_text() {
	string text;
	int flag_space = 0; // подсчет пробелов
	int begin_sentence = 1; // флаг начала предложения
	int defis = 0; // подсчет дефисов
	cout << "YOUR TEXT:" << endl;
	cin.clear();
	getline(cin, text);
	getline(cin, text);
	int i = 0;
	while (i < text.size()) {
		if (text[i] == ' ') { // начало слова
			defis = 0;
			if (flag_space > 0) {
				text.erase(i, 1); // удаление лишнего пробела
				i--;
			}
			else {
				flag_space++;
			}
		}
		else {
			if (text[i] == '-') {
				defis++;
				if (defis == 1) {
					if (flag_space != 1) { // перед дефисом нет пробела
						if (i != 0 && begin_sentence != 1){ // проверяем не первым ли элементом идет дефис
							text.insert(i, 1, ' '); // не первый элемент предложения, добавляем пробел перед дефисом
							i++;
							if (text[i+1] != ' ') {
								text.insert(i+1, 1, ' ');
								flag_space++;
								i++;
							}
						}
						else {
							text.erase(i, 1); // если дефис является первым элементом, то удаляем
							i--;
						}
					}
					else { // перед дефисом есть пробел
						if (i != 0 && begin_sentence != 1) {
							if (text[i+1] != ' ') { // есть ли пробел после дефиса
								text.insert(i+1, 1, ' ');
								flag_space++;
								i++;
							}
							else {
								flag_space = 0;
							}
						}
						else {
							text.erase(i, 1); // если дефис является первым элементом, то удаляем
							i--;
						}
					}
				}
				else {
					text.erase(i, 1);
					i--;
				}
				begin_sentence = 0;
			}
			else {
				flag_space = 0;
				defis = 0;
				if ((text[i] == '.') || (text[i] == '?') || (text[i] == '!')) {
					begin_sentence = 1;
				}
				else {
					begin_sentence = 0;
				}
			}
		}
		i++;
	}
	cout << text << endl;

}


#endif /* MODULE_H_ */
