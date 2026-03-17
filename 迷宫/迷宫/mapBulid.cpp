#include "mapBulid.h"
#include"mapConfig.h"
#include<vector>
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<Windows.h>
#include<ctime>
#include<random>
void MapBuild::initializationMap(std::vector<std::vector<CellInfo>>&gameMap) {//初始化地图
	gameMap.resize(25, std::vector<CellInfo>(101));
	for (int i = 1; i < 25; i++) {
		for (int j = 1; j < 101; j++) {
			gameMap[i][j].Type = CellType::WALL;
			gameMap[i][j].inter = ifIntersection::noINTERSECTION;
			gameMap[i][j].win = Win::noWin;
		}
	}
}
void MapBuild::buildNewMap(std::vector<std::vector<CellInfo>>& gameMap) {//地图建立
	std::srand(std::time(nullptr));
	initializationMap(gameMap);
	dfs(1, 1, gameMap,0);
	for (int i = 0; i < 25; i++) {
		gameMap[i][0].Type = CellType::BORDER;
		gameMap[i][100].Type = CellType::BORDER;
	}
	for (int i = 0; i < 101; i++) {
		gameMap[0][i].Type = CellType::BORDER;
		gameMap[24][i].Type = CellType::BORDER;
	}
	for (int i = 1; i < 25; i++) {
		for (int j = 1; j < 101; j++) {
			if (gameMap[i][j].Type == CellType::ROAD) {
				short count = 0;
				int dx[4] = { 0,1,0,-1 };
				int dy[4] = { 1,0,-1,0 };
				std::vector<int>dir = { 0,1,2,3 };
				for (int t : dir) {
					if (gameMap[i + dx[t]][j + dy[t]].Type == CellType::ROAD) {
						count++;
					}
				}
				if (count >= 3) {
					gameMap[i][j].inter = ifIntersection::isINTERSECTION;
				}
			}
		}
	}
	gameMap[1][1].Type = CellType::PLAYER;
	//gameMap[5][5].win = Win::Win;
	//gameMap[4][4].win = Win::Win;
	//gameMap[4][3].win = Win::Win;
	gameMap[23][99].win = Win::Win;
}
void MapBuild::dfs(int x, int y, std::vector<std::vector<CellInfo>>& gameMap,int deep) {//深度搜索迷宫建立
	if (deep > 1000)return;
	int dx[4] = { 0,1,0,-1 };
	int dy[4] = { 1,0,-1,0 };
	gameMap[x][y].Type = CellType::ROAD;
	std::vector<int>dir = { 0,1,2,3 };
	std::random_shuffle(dir.begin(), dir.end());
	for (int t : dir) {
		int nx = x + 2 * dx[t];
		int ny = y + 2 * dy[t];
		int mx = x + dx[t];
		int my = y + dy[t];
		if (nx > 0 && nx < 25 && ny > 0 && ny < 101 &&
			gameMap[nx][ny].Type == CellType::WALL) {
			gameMap[mx][my].Type = CellType::ROAD;
			dfs(nx, ny, gameMap, deep + 1);
		}
	}
}
void MapBuild::printMap() {//地图打印
	system("cls");
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 101; j++) {
			if (map[i][j].Type == CellType::WALL)std::cout << "#";
			else if (map[i][j].Type == CellType::BORDER)std::cout << "@";
			else if (map[i][j].Type == CellType::PLAYER)std::cout << "A";
			else if (map[i][j].win == Win::Win)std::cout << "E";
			//else if (map[i][j].inter == ifIntersection::isINTERSECTION)std::cout << "o";
			else std::cout << " ";
		}
		std::cout << "\n";
	}
}
void MapBuild::printMap_Dynamic() {
	system("cls");
	system("color 04");
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 101; j++) {
			if (i==23&&j==99)std::cout << "E";
			else if (map[i][j].Type == CellType::PLAYER)std::cout << "A";
			else std::cout << " ";
		}
		std::cout << "\n";
	}
	Sleep(500);
	system("pause");
	system("cls");
	system("color 07");
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 101; j++) {
			if (map[i][j].Type == CellType::BORDER)std::cout << "@";
			else if (map[i][j].Type == CellType::PLAYER)std::cout << "A";
			else if (map[i][j].win == Win::Win)std::cout << "E";
			else std::cout << " ";
		}
		std::cout << "\n";
	}
	Sleep(500);
	system("pause");
	system("cls");
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 101; j++) {
			if (map[i][j].Type == CellType::WALL)std::cout << "#";
			else if (map[i][j].Type == CellType::BORDER)std::cout << "@";
			else if (map[i][j].Type == CellType::PLAYER)std::cout << "A";
			else if (map[i][j].win == Win::Win)std::cout << "E";
			//else if (map[i][j].inter == ifIntersection::isINTERSECTION)std::cout << "o";
			else std::cout << " ";
		}
		std::cout << "\n";
	}
}