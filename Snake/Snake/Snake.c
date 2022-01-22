#include<stdio.h>
#include<windows.h>
#include<conio.h>

int main()
{
	system("mode con: cols=60 lines=30");
	srand((unsigned int)time(NULL));
	printf("***************************贪吃蛇***************************\n\n请按回车开始游戏...\n\n\n\n\nPS：游戏途中按空格键可暂停，按Esc键可退出");
	getchar();
	system("cls");
	do
	{
		int x = 15, y = 15, len = 4, map[900] = { 0 }, i;
		char c = 'd', c1 = 'd', draw[1801] = {0};
		for (map[rand() % 900] = -1; 1; Sleep(100))
		{
			//检测键盘输入并转向
			if (_kbhit() && (c1 = _getch()))
			{
				switch (c1)
				{
				case 'a':case 'A':
					if (c != 'd')
					{
						c = 'a';
					}
					break;
				case 's':case 'S':
					if (c != 'w')
					{
						c = 's';
					}
					break;
				case 'd':case 'D':
					if (c != 'a')
					{
						c = 'd';
					}
					break;
				case 'w':case 'W':
					if (c != 's')
					{
						c = 'w';
					}
					break;
				case 27:
					exit(0);
				case ' ':
					_getch();
					break;
				}
			}
			//判断头撞墙并更新坐标
			if (c == 'a' && --x < 0 || c == 'd' && ++x == 30 || c == 'w' && --y < 0 || c == 's' && ++y == 30)
			{
				Sleep(1000);
				system("cls");
				printf("你已失败，按空格键重新开始...");
				break; 
			}
			//判断吃到自己
			if (map[y*30+x] > 1)
			{
				Sleep(1000);
				system("cls");
				printf("你已失败，按空格键重新开始...");
				break; 
			}
			//判断吃到食物
			if (map[y*30+x] == -1)
			{
				len++;
				//生成新食物
				do
				{
					i = rand() % 900;
				} while (map[i] != 0);  //确保食物生成在空地
				map[i] = -1;
			}
			else
			{
				for (i = 0; i < 900; i++)
				{
					if (map[i] > 0)
					{
						map[i] -= 1;
					}
				}
			}
			map[y*30+x] = len;   //蛇头赋值
			//更新绘制缓存避免闪屏
			for (i = 0; i < 1800; i++)
			{
				if (map[i / 2] == 0)
				{
					draw[i] = ' ';
				}
				else if (map[i / 2] > 0)
				{
					if ((i % 2) == 1)
					{
						draw[i] = ')';
					}
					else
					{
						draw[i] = '(';
					}
				}
				else
				{
					draw[i] = '0';
				}
			}
				system("cls");
				printf(draw);
		}
	} while (_getch() == ' ');
	return 0;
}
