#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void add(FILE *f) { // добавление текста в файл
	char ch;
	fopen_s(&f, "file.txt", "a"); // если файл не существует, будет создан новый, если существует, то текст запишется в конец
	printf("YOUR TEXT:\n");
	ch = getchar();
	while ((ch = getchar()) != '\n') fputc(ch, f);
	fclose(f);
}


int summing(FILE* f) {
	char a[10] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };
	char* alf = &a;
	int counter = 0;
	char s;
	fopen_s(&f, "file.txt", "r");
	while (feof(f) == 0) {
		s = fgetc(f);
		for (int i = 0; i < 10; i++) {
			if (s == alf[i]) counter = counter + alf[i] - 48; // если текущий символ - цифра, то из аски-кода вычитаем 48, чтобы получить ее значение
		}
	}
	fclose(f);
	return counter;
}


int vowels(FILE* f) {
	int counter = 0;
	char s;
	char vowel[12] = {'a', 'e', 'i', 'o', 'u', 'y', 'A', 'E', 'I', 'O', 'U', 'Y'};
	fopen_s(&f, "file.txt", "r");
	while (feof(f) == 0) {
		s = fgetc(f);
		for (int i = 0; i < 12; i++) {
			if (s == vowel[i]) counter++; // если символ - гласная
		}
	}
	fclose(f);
	return counter;
}


void new_file(FILE* f) { // создание нового файла с 6-буквенными словами
	FILE* new_f = NULL;
	char s; // текущий символ
	int flag = 0; // флаг начала нового слова
	int counter = 0; // подсчет количества символов в слове
	char word[7]; // текущее слово
	int position = 0, size = 0;
	fopen_s(&f, "file.txt", "r");
	fseek(f, 0, SEEK_END);
	size = ftell(f); // количество символов в файле
	fclose(f);
	printf("%d\n", size);
	while (position <= size) {
		fopen_s(&f, "file.txt", "r"); // чтение основного файла
		fseek(f, position, SEEK_SET);
		s = fgetc(f);
		printf("%c %d %d\n", s, counter, position);
		fclose(f);
		if ((s == ' ') || (s == '\n') || (s == '.') || (s == ',') || (s == ';') || (position == size)) { // окончание слова
			flag = 1;
			if (counter == 6) {
				fopen_s(&new_f, "new_file.txt", "a"); // открытие файла
				for (int i = 0; i < 6; i++) {
					fputc(word[i], new_f);
				}
				fputc('\n', new_f);
				fclose(new_f);
			}
			counter = 0;
		}
		else {
			flag = 0;
			if (counter <= 6) word[counter] = s;
			counter++;
		}
		position++;
	}
}


void longest(FILE* f) {
	char s;
	int counter = 1; // текущая длина
	int max_long = 1; // максимальная длина слова
	int size = 0, position = 0; // количество символов и текущая позиция
	char* word[100]; // текущее слово
	char* max_word[100]; // слово с максимальной длиной
	fopen_s(&f, "file.txt", "r");
	fseek(f, 0, SEEK_END);
	size = ftell(f); // количество символов в файле
	while (position <= size) {
		fseek(f, position, SEEK_SET);
		s = fgetc(f);
		if ((s == ' ') || (s == '\n') || (s == '.') || (s == ',') || (s == ';') || (position == size)) {
			if (counter > max_long) {
				max_long = counter;
				for (int i = 0; i < 100; i++) max_word[i] = word[i];
			}
			counter = 0;
		}
		else {
			word[counter] = s;
			counter++;
		}
		position++;
	}
	printf("the longest word: ");
	for (int i = 0; i < max_long; i++) printf("%c", max_word[i]);
	printf("\n");
	fclose(f);
}


void red_def(FILE* f) {
	FILE* time_file = NULL;
	char s;
	int counter = 0; // количество пробелов
	int position = 0; // текущая позиция
	int size = 0, i = 0;
	fopen_s(&f, "file.txt", "r");
	fseek(f, 0, SEEK_END);
	size = ftell(f); // количество символов в файле
	fclose(f);
	while (position <= size) { // копия начального файла
		fopen_s(&f, "file.txt", "r");
		fseek(f, position, SEEK_SET);
		s = getc(f);
		fclose(f);
		fopen_s(&time_file, "time.txt", "a");
		fseek(time_file, position, SEEK_SET);
		fputc(s, time_file);
		fclose(time_file);
		position++;
	}
	position = 0;
	remove("file.txt");
	while (position <= size) {
		fopen_s(&time_file, "time.txt", "r");
		fseek(time_file, position, SEEK_SET);
		s = getc(time_file);
		fclose(time_file);
		fopen_s(&f, "file.txt", "a");
		fseek(f, i, SEEK_SET);
		if (s == ' ') {
			counter++;
			if (counter == 1) {
				fputc(s, f);
				i++;
			}
		}
		else {
			if (s == '-') {
				if (counter == 0) {
					fputc(' ', f);
					i++;
					fseek(f, i, SEEK_SET);
					fputc(s, f);
					i++;
					fseek(f, i, SEEK_SET);
					fputc(' ', f);
					i++;
					counter = 1;
				}
				else {
					fputc(s, f);
					i++;
					fseek(f, i, SEEK_SET);
					fputc(' ', f);
					i++;
					counter = 1;
				}
			}
			else {
				fputc(s, f);
				counter = 0;
				i++;
			}
		}
		fclose(f);
		position++;
	}
	remove("time.txt");
}


void red_points(FILE* f) {
	FILE* time_file = NULL;
	char s;
	int counter = 0; // количество пробелов
	int position = 0; // текущая позиция
	int size = 0, i = 0;
	int flag = 0; // флаг состояния символов
	fopen_s(&f, "file.txt", "r");
	fseek(f, 0, SEEK_END);
	size = ftell(f); // количество символов в файле
	fclose(f);
	while (position <= size) { // копия начального файла
		fopen_s(&f, "file.txt", "r");
		fseek(f, position, SEEK_SET);
		s = getc(f);
		fclose(f);
		fopen_s(&time_file, "time.txt", "a");
		fseek(time_file, position, SEEK_SET);
		fputc(s, time_file);
		fclose(time_file);
		position++;
	}
	position = 0;
	remove("file.txt");
	while (position < size) {
		fopen_s(&time_file, "time.txt", "r");
		fseek(time_file, position, SEEK_SET);
		s = getc(time_file);
		fclose(time_file);
		fopen_s(&f, "file.txt", "a");
		fseek(f, i, SEEK_SET);
		if ((s != '.') && (s != ' ')) {
			if (flag == 1) { // если перед этим была точка
				s = toupper(s);
				fputc(s, f);
				flag = 0;
			}
			else {
				fputc(s, f);
			}
			counter = 0;
			i++;
		}
		else {
			if (s == '.') {
				flag = 1;
				counter = 0;
				fputc(s, f);
				i++;
				fseek(f, i, SEEK_SET);
				s = ' ';
				fputc(s, f);
				i++;
			}
			else {
				counter++;
				if ((flag != 1) && (counter == 1)) {
					fputc(s, f);
					i++;
				}
			}
		}
		fclose(f);
		position++;
	}
	remove("time.txt");
}


void show_text(FILE* f) {
	char s;
	int size = 0, position = 0;
	fopen_s(&f, "file.txt", "r");
	fseek(f, 0, SEEK_END);
	size = ftell(f); // количество символов в файле
	while (position <= size) {
		fseek(f, position, SEEK_SET);
		s = fgetc(f);
		printf("%c", s);
		position++;
	}
	fclose(f);
}


int main() {
	FILE* f = NULL;
	char* max_word;
	int itog = 0;
	enum Menu{ add_text = 1, sum, count_vowels, new_text_6, longest_word, redaction_def, redaction_point, show, exit } M;
	do {
		printf("MENU:\n");
		printf("1 - add_text\n2 - sum_all_digets\n3 - count_vowels\n4 - creat_new_text_with_6_words\n5 - print_the_longest_word\n6 - redaction_defis\n7 - redaction_points\n8 - show_text\n9 - exit\n");
		scanf_s("%d", &M);
		switch (M) {
		case add_text:
			add(f);
			getch();
			break;
		case sum:
			itog = summing(f);
			printf("sum: %d\n", itog);
			getch();
			break;
		case count_vowels:
			itog = vowels(f);
			printf("number of vowels: %d\n", itog);
			getch();
			break;
		case new_text_6:
			new_file(f);
			getch();
			break;
		case longest_word:
			longest(f);
			getch();
			break;
		case redaction_def:
			red_def(f);
			getch();
			break;
		case redaction_point:
			red_points(f);
			getch();
			break;
		case show:
			show_text(f);
			getch();
			break;
		case exit:
			break;
		default:
			break;
		};
	} while (M != 9);
}