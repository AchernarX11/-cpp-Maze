#include "mapBulid.h"
#include"mapConfig.h"
#include<vector>
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<Windows.h>
#include<ctime>
#include<random>
#include <utility>
#include <string>
#include <conio.h>
#include<string.h>

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
	int end_x = rand() % 19 + 3; int end_y = rand() % 45 + 49;
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
	for (int i = 2; i <= 3; i++) {
		if(end_x+i<25)gameMap[end_x + i][end_y].Type = CellType::ROAD;
		if (end_x - i >0)gameMap[end_x - i][end_y].Type = CellType::ROAD;
		if (end_y + i < 101)gameMap[end_x][end_y + i].Type = CellType::ROAD;
		if (end_y - i > 0)gameMap[end_x][end_y-i].Type = CellType::ROAD;
	}
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
					int m_x = box_X + i, m_y= box_y + j;
					if (m_x > 0 && m_x < 25 && m_y>0 && m_y < 101) {
						if (gameMap[m_x][m_y].Type == CellType::WIN) {
							Legal = false;
						}
					}
				}
			}
		}
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				int m_x= box_X + i, m_y= box_y + j;
				if (m_x > 0 && m_x < 25 && m_y>0 && m_y < 101) {
					gameMap[m_x][m_y].Type = CellType::ROAD;
					gameMap[m_x][m_y].inter = ifIntersection::isINTERSECTION;
				}
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
	mazeOptimization(gameMap);
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
void MapBuild::SynchronizeMap(std::vector<std::vector<CellInfo>>& constMap, std::vector<std::vector<CellInfo>>& changeMap) {
	markIntersection(constMap);
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 101; j++) {
			changeMap[i][j].Type = constMap[i][j].Type;
			changeMap[i][j].inter = constMap[i][j].inter;
		}
	}
}
void setCursor(int x, int y) {
	COORD c = { SHORT(x), SHORT(y) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void MapBuild::draw(std::vector<std::vector<CellInfo>>& map_Backend, std::vector<std::vector<CellInfo>>& map_frontend, bool frontend) {
	setCursor(0, 0);
	std::string s;
	std::vector<std::vector<CellInfo>>& currentMap = frontend ? map_frontend : map_Backend;
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 101; j++) {
			if (currentMap[i][j].Type == CellType::PLAYER) s += "A";
			else if (currentMap[i][j].Type == CellType::WIN) s += "E";
			else if (currentMap[i][j].Type == CellType::BOX) s += "X";
			else if (currentMap[i][j].Type == CellType::BORDER) s += "@";
			else if (currentMap[i][j].Type == CellType::WALL) s += "#";
			else s += " ";
		}
		s += '\n';
	}
	std::cout << s;
}
void MapBuild::printMap() {//地图打印
	if (map_frontend.size() != map_Backend.size() || map_frontend[0].size() != map_Backend[0].size()) {
		map_frontend.resize(map_Backend.size(), std::vector<CellInfo>(map_Backend[0].size()));
	}
	for (int i = 0; i < map_Backend.size(); i++) {
		for (int j = 0; j < map_Backend[i].size(); j++) {
			map_frontend[i][j] = map_Backend[i][j];
		}
	}
	draw(map_Backend, map_frontend, frontend);
	frontend = !frontend;
}
void MapBuild::printMap_Dynamic() {//地图动态打印
	system("cls");
	//system("color 04");
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 101; j++) {
			if (map_Backend[i][j].Type == CellType::WIN)std::cout << "E";
			else if (map_Backend[i][j].Type == CellType::PLAYER)std::cout << "A";
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
			if (map_Backend[i][j].Type == CellType::BORDER)std::cout << "@";
			else if (map_Backend[i][j].Type == CellType::PLAYER)std::cout << "A";
			else if (map_Backend[i][j].Type == CellType::BOX)std::cout << "X";
			else if (map_Backend[i][j].Type == CellType::WIN)std::cout << "E";
			else std::cout << " ";
		}
		std::cout << "\n";
	}
	Sleep(500);
	system("pause");
	system("cls");
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 101; j++) {
			if (map_Backend[i][j].Type == CellType::PLAYER)std::cout << "A";
			else if (map_Backend[i][j].Type == CellType::WIN)std::cout << "E";
			else if (map_Backend[i][j].Type == CellType::BOX)std::cout << "X";
			else if (map_Backend[i][j].Type == CellType::BORDER)std::cout << "@";
			else if (map_Backend[i][j].Type == CellType::WALL)std::cout << "#";
			else std::cout << " ";
		}
		Sleep(40);
		std::cout << "\n";
	}
}
void MapBuild::mazeOptimization(std::vector<std::vector<CellInfo>>& gameMap) {
	int count = 0;
	while (count < 40) {
		int nx = rand() % 21 + 2, ny = rand() % 98 + 1;
		if (gameMap[nx][ny].Type == CellType::WALL) {
			if ((gameMap[nx + 1][ny].Type == CellType::ROAD && gameMap[nx - 1][ny].Type == CellType::ROAD)
				|| (gameMap[nx][ny + 1].Type == CellType::ROAD && gameMap[nx][ny - 1].Type == CellType::ROAD)) {
				gameMap[nx][ny].Type = CellType::ROAD;
				count++;
			}
		}
	}
	markIntersection(gameMap);
}
