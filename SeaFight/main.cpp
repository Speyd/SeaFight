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
#include "Windows.h"
#include <conio.h>
#include <algorithm>
#include <SFML/Audio.hpp>
using namespace std;
int amount_sunkboat_player = 0, amount_sunkboat_bot = 0, amount_attackedcell_player = 0, amount_attackedcell_bot = 0, setting_music = 1, choice_menu = 1;;
void ClearScrean() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
	//cout;
}
void Enter() {
	string enter;
	cin.ignore();
	do {
		cout << "Нажмит enter что-бы продолжить: ";
		getline(cin, enter);
	} while (!enter.empty());
}
void Filling(int choice, vector<vector<string>>& mass,int typeboad) {
	if (choice == 1) {
		int line = 0, column = 0,amount_empty=0,ship=1,line_sight = rand() % (4 - 1 + 1) + 1;
		char symbol = '1';
		do {
			line = rand() % (4 - 0 + 1) + 0; column = rand() % (4 - 0 + 1) + 0;
		} while (mass[line][column][0] != ' ');
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
				do {
					line = rand() % (4 - 0 + 1) + 0; column = rand() % (4 - 0 + 1) + 0;
				} while (mass[line][column][0] != ' ');
				i--;
			}
			else {
				amount_empty = 0;
				for (int l = 0; l != ship; l++) {
					if (l == 0) {
						if (typeboad == 0) { mass[line][column][0] = symbol; mass[line][column][1] = symbol; }
						else mass[line][column][1] = symbol;
					}
					else if(typeboad == 0){
						if (line_sight == 1) { mass[line - l][column][0] = symbol; mass[line - l][column][1] = symbol; }
						else if (line_sight == 2) { mass[line + l][column][0] = symbol; mass[line + l][column][1] = symbol; }
						else if (line_sight == 3) { mass[line][column + l][0] = symbol; mass[line][column + l][1] = symbol; }
						else if (line_sight == 4) { mass[line][column - l][0] = symbol; mass[line][column - l][1] = symbol; }
					}
					else if (typeboad == 1) {
						if (line_sight == 1) mass[line - l][column][1] = symbol; 
						else if (line_sight == 2) mass[line + l][column][1] = symbol; 
						else if (line_sight == 3) mass[line][column + l][1] = symbol; 
						else if (line_sight == 4) mass[line][column - l][1] = symbol; 
					}
				}
				do {
					line = rand() % (4 - 0 + 1) + 0; column = rand() % (4 - 0 + 1) + 0;
				} while (mass[line][column][0] != ' ');
				line_sight = rand() % (4 - 1 + 1) + 1;
				ship++;
				if (ship == 2)symbol = '2';
				else if (ship == 3)symbol = '3';
			}
		}
	}
}
void OutInfo(vector<vector<string>> mass) {
	cout << "    A   B   C   D   E\n  ---------------------"<<endl;
	for (int i = 0; i != 5; i++) {
		cout << i + 1 <<" | ";
		for (int l = 0; l != 5; l++) {
			if (mass[i][l][0] == 'X')cout << "\033[31m" << mass[i][l][0] << "\033[0m | ";
			else if (mass[i][l][0] == 'o')cout << mass[i][l][0] << " | ";
			else cout << "\033[32m" << mass[i][l][0] << "\033[0m | ";
		}
		cout << endl << "  ---------------------" << endl;
	}
}
void ResizeMass(vector<vector<string>>& mass) {
	mass.resize(5);
	for (int i = 0; i != 5; i++) {
		mass[i].resize(5);
		for (int l = 0; l != 5; l++) mass[i][l] = '  ';
	}
}
void InputSeaFight() {
	ClearScrean();
	setlocale(LC_ALL, "ru_RU.utf8");
	cout << u8"╔╗  ╔╗╔══╗╔═══╗╔══╗╔╗╔══╗╔══╗╔╗╩╔╗   ╔═══╗╔══╗╔╗╩╔╗" << endl;
	cout << u8"║║  ║║║╔╗║║╔═╗║║╔═╝║║║╔═╝║╔╗║║║ ║║   ║╔══╝║╔╗║║║ ║║" << endl;
	cout << u8"║╚╗╔╝║║║║║║╚═╝║║║  ║╚╝║  ║║║║║║ ║║   ║╚══╗║║║║║║ ║║" << endl;
	cout << u8"║╔╗╔╗║║║║║║╔══╝║║  ║╔╗║  ║║║║║║ ╔║   ║╔═╗║║║║║║║ ╔║" << endl;
	cout << u8"║║╚╝║║║╚╝║║║   ║╚═╗║║║╚═╗║╚╝║║╚═╝║   ║╚═╝║║╚╝║║╚═╝║" << endl;
	cout << u8"╚╝  ╚╝╚══╝╚╝   ╚══╝╚╝╚══╝╚══╝╚═══╝   ╚═══╝╚══╝╚═══╝" << endl;
	setlocale(LC_ALL, "Rus");
}
void Print(vector<vector<string>>& mass_bot, vector<vector<string>>& mass_player) {
	InputSeaFight();
	cout << "\t   Вы" << endl << endl;
	OutInfo(mass_player);
	cout << "\n\t   Бот" << endl << endl;
	OutInfo(mass_bot);
}
int Attack(string cell_map, vector<vector<string>>& mass) {
	int amount_sunkboat = 0;
	if (isdigit(mass[int(cell_map[1]) - 49][int(toupper(cell_map[0]) - 65)][1])) { mass[int(cell_map[1]) - 49][int(toupper(cell_map[0]) - 65)] = "XX"; amount_sunkboat++; }
	else mass[int(cell_map[1]) - 49][int(toupper(cell_map[0]) - 65)] = "oo";
	return amount_sunkboat;
}
void SetMusic(sf::Music& background_music) {
	int start_setting_music = setting_music,choice_music;
	if (setting_music == 1) background_music.pause();
	do {
		InputSeaFight();
		cout << "\t\033[1mМузыка\033[0m\n";
		if (setting_music == 1) cout << "[1] - Вкл. музыка   <---- Ваш выбор\n[2] - Выл. музыка\n"; 
		else if (setting_music == 2) cout << "[1] - Вкл. музыка\n[2] - Выл. музыка   <---- Ваш выбор\n"; 
		else cout << "[1] - Вкл. музыка\n[2] - Выл. музыка\n"; 
		choice_music = setting_music;
		if (choice_music == 3) { cout << "Нету такого выбора!\nВведите ваш выбор снова(0 для выхода / изменения настроек): "; cin >> setting_music; }
		else { cout << "Ваш выбор(0 для выхода/изменения настроек): "; cin >> setting_music; }
		if (setting_music < 0 || setting_music>2)choice_music = 3;
		if (setting_music == 0) { setting_music = choice_music; choice_music = 0; }
	} while (choice_music != 0);
	if (setting_music == 1 && start_setting_music == 2)background_music.play();
	else if (setting_music == 2 && start_setting_music == 1)background_music.stop();
}
void Menu(int choice, sf::Music& background_music) {
	do {
		do {
			InputSeaFight();
			if(choice == 3)cout << "[1] - Начать игру\n[2] - Настройки музыки\n[0] - Выйти из игры"<<endl;
			else cout << "[1] - Продолжить игру\n[2] - Настройки музыки\n[0] - Выйти из игры"<<endl;
			if (choice_menu >= 0 && choice_menu <= 2)cout << "Ваш выбор: ";
			else cout << "Нету такого выбора!\nВведите ваш выбор снова: ";
			cin >> choice_menu;
		} while (choice_menu < 0 || choice_menu > 2);
		if (choice_menu == 1 || choice_menu == 0)return;
		if (choice_menu == 2)SetMusic(background_music);
	} while (true);

}
void Shot_Sound(sf::Sound& shot_1, sf::Sound& shot_2, sf::Sound& shot_3, sf::Sound& shot_4) {
	int num = rand() % (4 - 1 + 1) + 1;
	if (num == 1)shot_1.play();
	else if(num == 2)shot_2.play();
	else if(num == 3)shot_3.play();
	else if(num == 4)shot_4.play();
}
int main() {
	srand(time(0));
	setlocale(LC_ALL, "Rus");
	#pragma region AddSound
	#pragma region Shot
	sf::SoundBuffer ShotBuff1;
	if (!ShotBuff1.loadFromFile("shot_1.ogg")) {
		return -1;
	}
	sf::Sound shot_1;
	shot_1.setBuffer(ShotBuff1);

	sf::SoundBuffer ShotBuff2;
	if (!ShotBuff2.loadFromFile("shot_2.ogg")) {
		return -1;
	}
	sf::Sound shot_2;
	shot_2.setBuffer(ShotBuff2);

	sf::SoundBuffer ShotBuff3;
	if (!ShotBuff3.loadFromFile("shot_3.ogg")) {
		return -1;
	}
	sf::Sound shot_3;
	shot_3.setBuffer(ShotBuff3);

	sf::SoundBuffer ShotBuff4;
	if (!ShotBuff4.loadFromFile("shot_4.ogg")) {
		return -1;
	}
	sf::Sound shot_4;
	shot_4.setBuffer(ShotBuff4);
	#pragma endregion
	#pragma region Win_Loss
	sf::SoundBuffer WinBuff;
	if (!WinBuff.loadFromFile("win.ogg")) {
		return -1;
	}
	sf::Sound win;
	win.setBuffer(WinBuff);

	sf::SoundBuffer LossBuff;
	if (!LossBuff.loadFromFile("loss.ogg")) {
		return -1;
	}
	sf::Sound loss;
	loss.setBuffer(LossBuff);
	#pragma endregion
	#pragma region Background_Music
	sf::Music background_music;
	if (!background_music.openFromFile("background_music.ogg")) {
		return -1;
	}
	#pragma endregion
	#pragma endregion
	int choice;
	background_music.play();
	Menu(3, background_music);
	while(choice_menu != 0){
		vector<vector<string>> mass_player; vector<vector<string>> mass_bot;
		ResizeMass(mass_player);
		ResizeMass(mass_bot);
		int move = 0; choice = 1;
		string cell_map;
		do {
			InputSeaFight();
			cout << "Выбере способ заполнения поля\n[1] - Заполнить рандомно" << endl;
			if (choice == 1)cout << "Ваш выбор: ";
			else cout << "Нету такого выбора!\nВведите ваш выбор снова: ";
			cin >> choice;
		} while (choice != 1);
		Filling(choice, mass_player, 0);
		Filling(choice, mass_bot, 1);
		do {
			if (background_music.getStatus() != 2 && setting_music == 1)background_music.play();
			Print(mass_bot, mass_player);
			if (move == 0) {
				do {
					if (!cell_map.empty())cout << "Введите снова ячейку в которою будем стрелять(пример: A1, 0 - меню): ";
					else cout << "Введите снова ячейку в которою будем стрелять(пример: A1, 0 - меню): ";
					cin >> cell_map;//int('A') - 64 == 1
					Print(mass_bot, mass_player);
					if (cell_map == "0") {
						Menu(choice, background_music);
						if (choice_menu == 0)return 0;
						cell_map = "";
					}
					else if (cell_map.size() == 2 && !isdigit(cell_map[0]) && isdigit(cell_map[1]) && int(toupper(cell_map[0])) <= 69 && int(toupper(cell_map[0])) >= 65) {
						if (int(cell_map[1]) - 48 <= 5 && int(cell_map[1]) - 48 > 0) {
							if (mass_bot[int(cell_map[1]) - 49][int(toupper(cell_map[0]) - 65)][0] != 'o' && mass_bot[int(cell_map[1]) - 49][int(toupper(cell_map[0]) - 65)][0] != 'X') break;
							else { cout << "Вы уже вводили эту строчку!";; cell_map = ""; }
						}
						else { cout << "Некоректный ввод!"; cell_map = ""; }
					}
					else { cout << "Некоректный ввод!"; cell_map = ""; }
				} while (true);
				Shot_Sound(shot_1, shot_2, shot_3, shot_4);
				int temp_num = Attack(cell_map, mass_bot);
				amount_sunkboat_bot += temp_num;
				if (temp_num == 0)move = 1;
				else if (temp_num >= 1) amount_attackedcell_player++;

			}
			else if (move == 1) {
				do {
					cell_map = "";
					cell_map = rand() % (69 - 65 + 1) + 65;
					cell_map += to_string(rand() % (5 - 1 + 1) + 1);
				} while (mass_player[int(cell_map[1]) - 49][int(toupper(cell_map[0]) - 65)][0] == 'o' || mass_player[int(cell_map[1]) - 49][int(toupper(cell_map[0]) - 65)][0] == 'X');
				cout << "Бот думает куда стрелять..." << endl;
				Sleep(3000);

				int temp_num = Attack(cell_map, mass_player);
				amount_sunkboat_player += temp_num;
				Shot_Sound(shot_1, shot_2, shot_3, shot_4);
				Print(mass_bot, mass_player);
				cout << "Бот стрельнул на ячейку " << cell_map << endl;
				Enter();
				if (temp_num == 0)move = 0;
				else if (temp_num >= 1) amount_attackedcell_bot++;
			}
			cell_map = "";
			if (amount_sunkboat_bot == 6) { Print(mass_bot, mass_player); win.play(); cout << "ВЫ ПОБЕДИЛИ!"<<endl; break; }
			else if (amount_sunkboat_player == 6) { Print(mass_bot, mass_player); loss.play(); cout << "БОТ ПОБЕДИЛИ!"<<endl; break; }
		} while (true);
		mass_bot.resize(0); mass_player.resize(0);
		Enter();
		Menu(3,background_music);
	}
	return 0;
}