#pragma once
#ifndef MAP_BULID_H
#define MAP_BULID_H
#include<vector>
#include"mapConfig.h"

class MapBuild {
private:
	std::vector<std::vector<CellInfo>>map;
	void initializationMap(std::vector<std::vector<CellInfo>>&gameMap);//初始化地图
	void buildNewMap(std::vector<std::vector<CellInfo>>& gameMap);//地图建立
	void dfs(int x, int y,std::vector<std::vector<CellInfo>>& gameMap, int deep);//深度搜索迷宫建立
public:
	std::vector<std::vector<CellInfo>>& getMap() { return map; }
	void newMap() {buildNewMap(map);}
	void printMap_Dynamic();
	void printMap();//地图打印
};

#endif // !MAP_BULID_H
