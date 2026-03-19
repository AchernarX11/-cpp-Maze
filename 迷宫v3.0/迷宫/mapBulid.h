#pragma once
#ifndef MAP_BULID_H
#define MAP_BULID_H
#include<vector>
#include"mapConfig.h"

class MapBuild {
private:
	std::vector<std::vector<CellInfo>>map_Backend;
	std::vector<std::vector<CellInfo>>map_frontend;
	bool frontend = false;
	//v1.0
	void initializationMap(std::vector<std::vector<CellInfo>>&gameMap);//初始化地图
	void buildNewMap(std::vector<std::vector<CellInfo>>& gameMap);//地图建立
	void dfs(int x, int y,std::vector<std::vector<CellInfo>>& gameMap, int deep);//深度搜索迷宫建立
	//v2.0
	void endRoom(std::vector<std::vector<CellInfo>>& gameMap);//终点屋
	void boxRoom(std::vector<std::vector<CellInfo>>& gameMap);//盒子屋
	void markIntersection(std::vector<std::vector<CellInfo>>& gameMap);//路口标记
	//v3.0
	void SynchronizeMap(std::vector<std::vector<CellInfo>>& constMap, std::vector<std::vector<CellInfo>>& changeMap);//同步地图
	void draw(std::vector<std::vector<CellInfo>>& map_Backend, std::vector<std::vector<CellInfo>>& map_frontend,bool frontend);//地图绘画
	void mazeOptimization(std::vector<std::vector<CellInfo>>& gameMap);//迷宫优化
public:
	std::vector<std::vector<CellInfo>>& getMap() { return map_Backend; }
	void newMap() {buildNewMap(map_Backend);}
	void printMap_Dynamic();
	void printMap();//地图打印
	void doMarkIntersection() { markIntersection(map_Backend); }
};

#endif // !MAP_BULID_H
