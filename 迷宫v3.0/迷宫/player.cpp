#include "player.h"
#include"mapBulid.h"
#include<conio.h>
#include<Windows.h>
#include"gameManager.h"
#include"mapConfig.h"
#include<iostream>
void endMenu(int x);
void PLAYER::temporaryMapDetection(int x, int y, MapBuild& gameMap) {
    auto& Map = gameMap.getMap();
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 101; j++) {
            if (Map[i][j].Type == CellType::PLAYER) {
                if (i != x || j != y) {
                    Map[i][j].Type = CellType::ROAD;
                }
            }
        }
    }
    gameMap.doMarkIntersection();
    gameMap.printMap();
}
bool isPassable(std::vector<std::vector<CellInfo>>& Map, int x, int y) {
    if (x < 0 || x >= Map.size() || y < 0 || y >= Map[0].size()) {
        return false;
    }
    CellType type = Map[x][y].Type;
    return (type == CellType::ROAD
         || type == CellType::INTERSECTION
         || Map[x][y].Type == CellType::BOX
         || type == CellType::WIN);
}
void PLAYER::boxEffect(int box_x, int box_y, MapBuild& gameMap) {
    GAME game;
    auto& Map = gameMap.getMap();
    int curres = rand() % 7;
    switch (curres) {
    case 0://向上打通10格
    {
        for (int i = 0; i < 20; i++) {
            int nx = box_x - i;
            if (nx >= 0 && nx < Map.size() && box_y >= 0 && box_y < Map[0].size() 
                && Map[nx][box_y].Type != CellType::WIN 
                && Map[nx][box_y].Type != CellType::BORDER
                && Map[nx][box_y].Type != CellType::PLAYER) {

                Map[nx][box_y].Type = CellType::ROAD;
                Sleep(20);
                gameMap.printMap();
            }
        }
        Map[box_x][box_y].Type = CellType::PLAYER;
        temporaryMapDetection(box_x, box_y, gameMap);
        break;
    }
    case 1://向下打通10格
    {
        for (int i = 0; i < 20; i++) {
            int nx = box_x + i;
            if (nx >= 0 && nx < Map.size() && box_y >= 0 && box_y < Map[0].size() 
                && Map[nx][box_y].Type != CellType::WIN 
                && Map[nx][box_y].Type != CellType::BORDER
                && Map[nx][box_y].Type != CellType::PLAYER) {
                Map[nx][box_y].Type = CellType::ROAD;
                Sleep(20);
                gameMap.printMap();
            }
        }
        Map[box_x][box_y].Type = CellType::PLAYER;
        temporaryMapDetection(box_x, box_y, gameMap);
        break;
    }
    case 2://向左打通10格
    {
        for (int i = 0; i < 20; i++) {
            int ny = box_y - i;
            if (box_x >= 0 && box_x < Map.size() && ny >= 0 && ny < Map[0].size() 
                && Map[box_x][ny].Type != CellType::WIN 
                && Map[box_x][ny].Type != CellType::BORDER
                && Map[box_x][ny].Type != CellType::PLAYER) {
                Map[box_x][ny].Type = CellType::ROAD;
                Sleep(20);
                gameMap.printMap();
            }
        }
        Map[box_x][box_y].Type = CellType::PLAYER;
        temporaryMapDetection(box_x, box_y, gameMap);

        break;
    }
    case 3://向右打通10格
    {
        for (int i = 0; i < 20; i++) {
            int ny = box_y + i;
            if (box_x >= 0 && box_x < Map.size() && ny >= 0 && ny < Map[0].size() 
                && Map[box_x][ny].Type != CellType::WIN 
                && Map[box_x][ny].Type != CellType::BORDER
                && Map[box_x][ny].Type != CellType::PLAYER) {
                Map[box_x][ny].Type = CellType::ROAD;
                Sleep(20);
                gameMap.printMap();
            }
        }
        Map[box_x][box_y].Type = CellType::PLAYER;
        temporaryMapDetection(box_x, box_y, gameMap);
        break;
    }
    case 4://5×5区域打通
    {
        for (int i = -2; i <= 2; i++) {
            for (int j = -2; j <= 2; j++) {
                int nx = box_x + i;
                int ny = box_y + j;
                if (nx >= 0 && nx < Map.size() && ny >= 0 && ny < Map[0].size() 
                    && Map[nx][ny].Type != CellType::WIN
                    && Map[nx][ny].Type != CellType::BORDER
                    && Map[nx][box_y].Type != CellType::PLAYER) {
                    Map[nx][ny].Type = CellType::ROAD;
                    Sleep(20);
                    gameMap.printMap();
                }
            }
        }
        Map[box_x][box_y].Type = CellType::PLAYER;
        temporaryMapDetection(box_x, box_y, gameMap);
        break;
    }
    case 5://生成新终点
    {
        int ny = box_y + 1;
        if (box_x >= 0 && box_x < Map.size() && ny >= 0 && ny < Map[0].size()) {
            Map[box_x][ny].Type = CellType::WIN;
        }
        Map[box_x][box_y].Type = CellType::PLAYER;
        temporaryMapDetection(box_x, box_y, gameMap);
        break;
    }
    case 6:// 死亡重启
    {
        system("cls");
        system("color 04");
        std::cout << "死亡！！！\n";
        Sleep(500);
        system("pause");
        system("color 07");
        game.doLunch();
        break;
    }
    default: {
        std::cout << "效果产生失败";
        system("pause");
    }
    }
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
                        if (Map[nowX][nowY].Type == CellType::WIN) {
                            Map[nowX][nowY].Type == CellType::PLAYER;
                            count++;
                            judgmWin = true;
                            break;
                        }
                        if (Map[nowX][nowY].Type == CellType::BOX) {
                            boxEffect(nowX, nowY, gameMap);
                            break;
                        }
                        Map[nowX][nowY].Type = CellType::PLAYER;
                        count++;
                        if (Map[nowX][nowY].inter == ifIntersection::isINTERSECTION) {
                            break;
                        }
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
                        if (Map[nowX][nowY].Type == CellType::WIN) {
                            Map[nowX][nowY].Type == CellType::PLAYER;
                            count++;
                            judgmWin = true;
                            break;
                        }
                        if (Map[nowX][nowY].Type == CellType::BOX) {
                            boxEffect(nowX, nowY, gameMap);
                            break;
                        }
                        Map[nowX][nowY].Type = CellType::PLAYER;
                        count++;
                        if (Map[nowX][nowY].inter == ifIntersection::isINTERSECTION) {
                            break;
                        }
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
                        if (Map[nowX][nowY].Type == CellType::WIN) {
                            Map[nowX][nowY].Type == CellType::PLAYER;
                            count++;
                            judgmWin = true;
                            break;
                        }
                        if (Map[nowX][nowY].Type == CellType::BOX) {
                            boxEffect(nowX, nowY, gameMap);
                            break;
                        }
                        Map[nowX][nowY].Type = CellType::PLAYER;
                        count++;
                        if (Map[nowX][nowY].inter == ifIntersection::isINTERSECTION) {
                            break;
                        }
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
                        if (Map[nowX][nowY].Type == CellType::WIN) {
                            Map[nowX][nowY].Type == CellType::PLAYER;
                            count++;
                            judgmWin = true;
                            break;
                        }
                        if (Map[nowX][nowY].Type == CellType::BOX) {
                            boxEffect(nowX, nowY, gameMap);
                            break;
                        }
                        Map[nowX][nowY].Type = CellType::PLAYER;
                        count++;
                        if (Map[nowX][nowY].inter == ifIntersection::isINTERSECTION) {
                            break;
                        }
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
                gameMap.printMap();
                gameDelay(50);
            }
        }
    }
    if (judgmWin && gameRunning) {
        system("color 04");
        gameMap.printMap();
        Sleep(200);
        system("color 07");
        system("cls");
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
