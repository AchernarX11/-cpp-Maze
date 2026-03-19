#include "gameManager.h"
#include"mapBulid.h"
#include"player.h"
#include<Windows.h>
#include<stdlib.h>
#include"menu.h"

void GAME::lunch() {
	MapBuild map;
	Menu menu;
	MENU curres = MAIN_MENU;
	int choice;
	while (true) {
		switch (curres) {
		case MAIN_MENU:
			menu.showClearScreen();
			menu.showMainMenu();
			break;
		case SETTING_MAIN:
			menu.showClearScreen();
			menu.showSettingMenu();
			break;
		case SETTING_ONE:
			menu.showClearScreen();
			menu.showTxtOne();
			break;
		case SETTING_TWO:
			menu.showClearScreen();
			menu.showTxtTwo();
			break;
		case EXIT:
			menu.showClearScreen();
			exit(0);
		}
		if (!(std::cin >> choice)) {
			std::cin.clear();
			std::cin.ignore();
			std::cout << "非法输入，请重新选择\n";
			system("pause");
			continue;
		}
		switch (curres) {
		case MAIN_MENU:
			if (choice == 0)curres = EXIT;
			else if (choice == 1) {
				menu.showRules();
				system("pause");
				map.newMap();
				map.printMap_Dynamic();
				PLAYER player;
				player.go(map);
			}
			else if (choice == 2)curres = SETTING_MAIN;
			break;
		case SETTING_MAIN:
			if (choice == 0)curres = MAIN_MENU;
			else if (choice == 1)curres = SETTING_ONE;
			else if (choice == 2)curres = SETTING_TWO;
			break;
		case SETTING_ONE:
			if (choice == 0)curres = SETTING_MAIN;
			break;
		case SETTING_TWO:
			if (choice == 0)curres = SETTING_MAIN;
			break;
		}
	}
}