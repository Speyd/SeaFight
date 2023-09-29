#include <iostream>
#include <random>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cstring>
#include <string>
#include <fstream>
#include <chrono>
#include <algorithm>
using namespace std;
void ClearScrean() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
	cout << "\tМорской бой"<<endl;
}
vector<vector<string>> mass;
void Filling(int choice) {
	if (choice == 2) {
		int line = rand() % (4 - 0 + 1) + 0, column = rand() % (4 - 0 + 1) + 0,amount_empty=0,ship=1,line_sight = rand() % (4 - 1 + 1) + 1;
		char symbol = '1';
		while (mass[line][column][0] != ' ') {
			line = rand() % (4 - 0 + 1) + 0; column = rand() % (4 - 0 + 1) + 0;
		}
		for (int i = 0; i != 3; i++) {
			for (int l = 0; l != ship; l++) {
				if (l == 0)amount_empty++;
				else {
					if (line_sight == 1 && line - l > 0 && mass[line - l][column][0] == ' ')amount_empty++;
					else if (line_sight == 2 && line + l < 4 && mass[line + l ][column][0] == ' ')amount_empty++;
					else if (line_sight == 3 && column + l < 4 && mass[line][column + l ][0] == ' ')amount_empty++;
					else if (line_sight == 4 && column - l > 0 && mass[line][column - l][0] == ' ')amount_empty++;
				}
			}
			if (amount_empty != ship) {
				amount_empty = 0;
				line_sight = rand() % (4 - 1 + 1) + 1;
				while (mass[line][column][0] != ' ') {
					line = rand() % (4 - 0 + 1) + 0; column = rand() % (4 - 0 + 1) + 0;
				}
				i--;
			}
			else {
				amount_empty = 0;
				for (int l = 0; l != ship; l++) {
					if (l == 0)mass[line][column][0] = symbol;
					else {
						if (line_sight == 1)mass[line - l][column][0] = symbol;
						else if (line_sight == 2)mass[line + l][column][0] = symbol;
						else if (line_sight == 3)mass[line][column + l ][0] = symbol;
						else if (line_sight == 4)mass[line][column - l][0] = symbol;
					}
				}
				while (mass[line][column][0] != ' ') {
					line = rand() % (4 - 0 + 1) + 0; column = rand() % (4 - 0 + 1) + 0;
				}
				line_sight = rand() % (4 - 1 + 1) + 1;
				ship++;
				if (ship == 2)symbol = '2';
				else if (ship == 3)symbol = '3';
			}
		}
	}
}
void OutInfo() {
	cout << "------------"<<endl;
	for (int i = 0; i != 5; i++) {
		cout << '|';
		for (int l = 0; l != 5; l++)cout<<mass[i][l][0] << ' ';
		cout <<'|' << endl;
	}
	cout << "------------";
}
int main() {
	srand(time(0));
	setlocale(LC_ALL, "Rus");
	mass.resize(5);
	for (int i = 0; i != 5; i++) {
		mass[i].resize(5);
		for (int l = 0; l != 5; l++) mass[i][l] = '  ';
	}
	int choice = 1;
	do {
		ClearScrean();
		cout << "Выбере способ заполнения поля\n[1] - Заполнить самому   |   [2] - Заполнить рандомно"<<endl;
		if (choice <= 1 && choice >= 2)cout << "Ваш выбор: ";
		else cout << "Нету такого выбора!\nВведите ваш выбор снова: ";
		cin >> choice;
	} while (choice < 1 || choice > 2);
	Filling(choice);
	ClearScrean();
	OutInfo();
}