#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include<iostream>
#include"mapBulid.h"
#include"mapConfig.h"
class PLAYER {
private:
	int step_count = 1;
	bool ifkey();
	char getkey();
	void gameDelay(int ms);
	void playerOperation(MapBuild& gameMap);
	void boxEffect(int x, int y, MapBuild& gameMap);
	void temporaryMapDetection(int x, int y, MapBuild& gameMap);

public:
	void go(MapBuild& mapBuilder) { playerOperation(mapBuilder);}
};
#endif // !PLAYER_H
