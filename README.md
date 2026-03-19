-说明-该项目基于cpp开发，使用的是vs2022，有相同的新手，独立开发一些好玩的程序，可以借鉴，主要代码文件：迷宫\迷宫
-Description- This project is developed based on C++, using VS2022. For beginners who are similar, independently developing some interesting programs, it can be used as a reference. Main code files: 迷宫\迷宫

-迷宫v2.0-
鉴于单纯走迷宫太过于无聊(其实这个游戏本身就很无聊),在v2.0版本做了以下更新
1.终点不再是固定的了，而是随机分布在地图的右板块，并且对终点做了一个固定房间
2.在地图上面添加了道具"X"，当玩家触碰到道具后会有7种随机不同效果
3.在首次打开地图的时候做了动态地图生成，帮助玩家快速定位地图中的重要元素
-Maze v2.0-
Considering that simply walking through the maze is too boring (actually, this game itself is very boring), the following updates have been made in version 2.0:
1. The endpoint is no longer fixed, but randomly distributed in the right section of the map, and a fixed room has been made for the endpoint.
2. Added an item "X" on the map. When the player touches the item, it will trigger one of seven different random effects.
3. When the map is opened for the first time, dynamic map generation is performed to help players quickly locate important elements on the map.

-迷宫v3.0-
更新内容如下
1.基于迷宫地图大小为25x101，不断清空打印地图出现的闪烁效果太过于强烈，于是对此方法做了优化，使用了前后双端打印方法来避免了闪烁效果
2.在MapBuild类中添加了mazeOptimization方法，对dfs后的迷宫经行了优化，使迷宫路径更加多元化
-Maze v3.0-
Update contents are as follows:
1. Based on a maze map size of 25x101, constantly clearing and printing the map caused the flickering effect to be too strong, so this method was optimized by using a front-and-back dual-end printing method to avoid the flickering effect.
2. Added the mazeOptimization method in the MapBuild class, which optimizes the maze after DFS, making the maze paths more diverse.
