#pragma once
#ifndef MAP_CONFIG_H
#define MAP_CONFIG_H
enum class CellType
{
	BORDER,
	ROAD,
	WALL,
	PLAYER,
	INTERSECTION,
	WIN,
	BOX,
	EMPTY
};
/*enum class Box {
	isBox,
	noBox
};*/
enum class ifIntersection
{
	isINTERSECTION,
	noINTERSECTION
};
/*enum class Win {
	Win,
	noWin
};*/
struct CellInfo
{
	//Box box;
	//Win win;
	CellType Type;
	ifIntersection inter;
};
#endif // !MAP_CONFIG_H