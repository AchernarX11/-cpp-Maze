#pragma once
#ifndef MENU_H
#define MENU_H
enum MENU {
	EXIT=0,
	MAIN_MENU,
	SETTING_MAIN,
	SETTING_ONE,
	SETTING_TWO
};
class Menu {
private:
	void mainMenu();
	void settingMenu();
	void timeMenu();
	void txtOne();
	void txtTwo();
	void clearScreen();
	void wait();
	void rules();
public:
	void showMainMenu() { mainMenu(); }
	void showSettingMenu() { settingMenu(); }
	void showTimeMenu() { timeMenu(); }
	void showTxtOne() { txtOne(); }
	void showTxtTwo() { txtTwo(); }
	void showClearScreen(){ clearScreen(); }
	void showWait(){ wait(); }
	void showRules() { rules(); }
};
#endif // !MENU_H

