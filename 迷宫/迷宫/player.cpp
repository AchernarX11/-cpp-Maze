#include "player.h"
#include"mapBulid.h"
#include<conio.h>
#include<Windows.h>
#include"gameManager.h"
#include"mapConfig.h"
#include<iostream>
void endMenu(int x);
bool isPassable(const std::vector<std::vector<CellInfo>>& Map, int x, int y) {
    if (x < 0 || x >= Map.size() || y < 0 || y >= Map[0].size()) {
        return false;
    }
    CellType type = Map[x][y].Type;
    return (type == CellType::ROAD || type == CellType::INTERSECTION);
}
void PLAYER::playerOperation(MapBuild& gameMap) {
    GAME game;
    auto& Map = gameMap.getMap();
    char key;
    int nowX = 1, nowY = 1;
    bool judgmWin = false;
    bool gameRunning = true;
    while (gameRunning&&!judgmWin) {
        if (ifkey()) {
            key = getkey();
            int startX = nowX;
            int startY = nowY;
            switch (key) {
            case 'd':
            case 'D':
                if (isPassable(Map, nowX, nowY + 1)) {
                    int count = 0;
                    while (isPassable(Map, nowX, nowY + 1)) {
                        nowY++;
                        Map[nowX][nowY].Type = CellType::PLAYER;
                        count++;
                        if (Map[nowX][nowY].inter == ifIntersection::isINTERSECTION) {
                            break;
                        }
                        if (Map[nowX][nowY].win == Win::Win) {
                            judgmWin = true;
                            break;
                        }
                        system("cls");
                        gameMap.printMap();
                        gameDelay(20);
                    }
                    for (int i = 1; i <= count; i++) {
                        Map[nowX][nowY - i].Type = CellType::ROAD;
                    }
                }
                break;
            case 'a':
            case 'A':
                if (isPassable(Map, nowX, nowY - 1)) {
                    int count = 0;
                    while (isPassable(Map, nowX, nowY - 1)) {
                        nowY--;
                        Map[nowX][nowY].Type = CellType::PLAYER;
                        count++;
                        if (Map[nowX][nowY].inter == ifIntersection::isINTERSECTION) {
                            break;
                        }
                        if (Map[nowX][nowY].win == Win::Win) {
                            judgmWin = true;
                            break;
                        }
                        system("cls");
                        gameMap.printMap();
                        gameDelay(20);
                    }
                    for (int i = 1; i <= count; i++) {
                        Map[nowX][nowY + i].Type = CellType::ROAD;
                    }
                }
                break;
            case 'W':
            case 'w':
                if (isPassable(Map, nowX - 1, nowY)) {
                    int count = 0;
                    while (isPassable(Map, nowX - 1, nowY)) {
                        nowX--;
                        Map[nowX][nowY].Type = CellType::PLAYER;
                        count++;
                        if (Map[nowX][nowY].inter == ifIntersection::isINTERSECTION) {
                            break;
                        }
                        if (Map[nowX][nowY].win == Win::Win) {
                            judgmWin = true;
                            break;
                        }
                        system("cls");
                        gameMap.printMap();
                        gameDelay(20);
                    }
                    for (int i = 1; i <= count; i++) {
                        Map[nowX + i][nowY].Type = CellType::ROAD;
                    }
                }
                break;
            case 's':
            case 'S':
                if (isPassable(Map, nowX + 1, nowY)) {
                    int count = 0;
                    while (isPassable(Map, nowX + 1, nowY)) {
                        nowX++;
                        Map[nowX][nowY].Type = CellType::PLAYER;
                        count++;
                        if (Map[nowX][nowY].inter == ifIntersection::isINTERSECTION) {
                            break;
                        }
                        if (Map[nowX][nowY].win == Win::Win) {
                            judgmWin = true;
                            break;
                        }
                        system("cls");
                        gameMap.printMap();
                        gameDelay(20);
                    }
                    for (int i = 1; i <= count; i++) {
                        Map[nowX - i][nowY].Type = CellType::ROAD;
                    }
                }
                break;
            case 'h':
            case 'H':
                std::cout << "确定退出游戏\n";
                std::cout << "1.YES   2.NO\n";
                std::cout << "请输入  >";
                int choice;
                if (!(std::cin >> choice)) {
                    std::cin.clear();
                    std::cin.ignore();
                    choice = 3445229764;
                }
                switch (choice) {
                case 1:
                    game.doLunch();
                    gameRunning = false;
                    judgmWin = true;
                    break;
                case 2:
                    system("cls");
                    gameMap.printMap();
                    gameDelay(50);
                    break;
                default:
                    std::cout << "非法输入！请重新选择";
                    break;
                }
                break;
            }
            if ((nowX != startX) || (nowY != startY)) {
                system("cls");
                gameMap.printMap();
                gameDelay(50);
            }
        }
    }
    if (judgmWin && gameRunning) {
        system("color 04");
        gameMap.printMap();
        Sleep(200);
        system("cls");
        system("color 07");
        endMenu(step_count);
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore();
            choice = 3445229764;
        }
        switch (choice) {
        case 1:
            gameMap.newMap();
            gameMap.printMap_Dynamic();
            nowX = 1; nowY = 1;
            judgmWin = false;
            this->step_count++;
            this->playerOperation(gameMap);
            break;
        case 2:
            game.doLunch();
            break;
        default:
            std::cout << "非法输入！默认继续游戏";
            Sleep(500);
            gameMap.newMap();
            gameMap.printMap_Dynamic();
            nowX = 1; nowY = 1;
            judgmWin = false;
            this->playerOperation(gameMap);
            break;
        }

    }
}
void endMenu(int x) {
    std::cout << "######################################\n";
    std::cout << "#             恭喜过关               #\n";
    std::cout << "######################################\n";
    std::cout << "#                                   #\n";
    std::cout << "#             当前关卡               #\n";
    std::cout << "#                "<<x<<"                   #\n";
    std::cout << "#                                   #\n";
    std::cout << "######################################\n";
    std::cout << "#      1.继续           2.退出       #\n";
    std::cout << "######################################\n";
    std::cout << "请输入  >";
}
bool PLAYER::ifkey(){//判断输入
    return _kbhit();
}
char PLAYER::getkey() {//获取输入
    return _getch();
}
void PLAYER::gameDelay(int ms) {//延时
    Sleep(ms);
}
