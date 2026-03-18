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
		}
	}
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 101; j++) {
			gameMap[i][j].inter = ifIntersection::noINTERSECTION;
		}
	}
}
void MapBuild::endRoom(std::vector<std::vector<CellInfo>>& gameMap) {
	int end_x = rand() % 18 + 4; int end_y = rand() % 46 + 50;
	int dx[5] = { -2,-1,0,1,2 };
	int dy[5] = { -2,-1,0,1,2 };
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			gameMap[end_x + dx[i]][end_y + dy[j]].Type = CellType::WALL;
			gameMap[end_x + dx[i]][end_y + dy[j]].inter = ifIntersection::isINTERSECTION;
		}
	}
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			gameMap[end_x + i][end_y + j].Type = CellType::ROAD;
		}
	}
	gameMap[end_x][end_y].Type = CellType::WIN;
	gameMap[end_x +2][end_y].Type = CellType::ROAD;
	gameMap[end_x -2][end_y].Type = CellType::ROAD;
	gameMap[end_x][end_y +2].Type = CellType::ROAD;
	gameMap[end_x][end_y -2].Type = CellType::ROAD;
}
void MapBuild::boxRoom(std::vector<std::vector<CellInfo>>& gameMap) {
	for (int times = 0; times < 2;times++) {
		bool Legal = false;
		int box_X; int box_y;
		while (!Legal) {
			box_X = rand() % 15 + 5;box_y = rand() % 85 + 6;
			Legal = true;
			for (int i = -5; i <= 5; i += 5) {
				if (!Legal) break;
				for (int j = -5; j <= 5; j += 5) {
					if (gameMap[box_X + i][box_y + j].Type == CellType::WIN) {
						Legal = false;
					}
				}
				
			}
		}
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				gameMap[box_X + i][box_y + j].Type = CellType::ROAD;
				gameMap[box_X + i][box_y + j].inter = ifIntersection::isINTERSECTION;
			}
		}
		gameMap[box_X][box_y].Type = CellType::BOX;
	}
}
void MapBuild::markIntersection(std::vector<std::vector<CellInfo>>& gameMap) {
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
	markIntersection(gameMap);
	gameMap[1][1].Type = CellType::PLAYER;
	endRoom(gameMap);
	boxRoom(gameMap);
	//gameMap[5][5].Type = CellType::WIN;
	//gameMap[4][4].Type = CellType::WIN;
	//gameMap[4][3].Type = CellType::WIN;
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
			if (map[i][j].Type == CellType::PLAYER)std::cout << "A";
			else if (map[i][j].Type == CellType::WIN)std::cout << "E";
			else if (map[i][j].Type == CellType::BOX)std::cout << "X";
			else if (map[i][j].Type == CellType::BORDER)std::cout << "@";
			else if (map[i][j].Type == CellType::WALL)std::cout << "#";
			else std::cout << " ";
		}
		std::cout << "\n";
	}
}
void MapBuild::printMap_Dynamic() {//地图动态打印
	system("cls");
	//system("color 04");
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 101; j++) {
			if (map[i][j].Type == CellType::WIN)std::cout << "E";
			else if (map[i][j].Type == CellType::PLAYER)std::cout << "A";
			else std::cout << " ";
		}
		std::cout << "\n";
	}
	Sleep(500);
	system("pause");
	system("cls");
	//system("color 07");
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 101; j++) {
			if (map[i][j].Type == CellType::BORDER)std::cout << "@";
			else if (map[i][j].Type == CellType::PLAYER)std::cout << "A";
			else if (map[i][j].Type == CellType::BOX)std::cout << "X";
			else if (map[i][j].Type == CellType::WIN)std::cout << "E";
			else std::cout << " ";
		}
		std::cout << "\n";
	}
	Sleep(500);
	system("pause");
	system("cls");
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 101; j++) {
			if (map[i][j].Type == CellType::PLAYER)std::cout << "A";
			else if (map[i][j].Type == CellType::WIN)std::cout << "E";
			else if (map[i][j].Type == CellType::BOX)std::cout << "X";
			else if (map[i][j].Type == CellType::BORDER)std::cout << "@";
			else if (map[i][j].Type == CellType::WALL)std::cout << "#";
			else std::cout << " ";
		}
		Sleep(40);
		std::cout << "\n";
	}
	std::cout << "开始游戏\n";
	system("pause");
}