#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

//玩家为O，电脑为X

void gotoxy(int a, int b)
{
	HANDLE hout;
	COORD coord;
	coord.X = a - 1;  //调整左上角为(1,1)
	coord.Y = b - 1;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout, coord);
}
char menu()
{
	printf("1.电脑先手\n2.退出游戏\n");
	char run = getch();
	return run;
}
void print_board(char checkerboard[][3])
{
	for (int i = 0; i < 2; i++)
	{
		printf("     |     |\n");
		for (int j = 0; j < 2; j++)
		{
			printf("  %c  |", checkerboard[i][j]);
		}
		printf("  %c\n", checkerboard[i][2]);
		printf("     |     |\n");
		printf("-----|-----|-----\n");
	}
	printf("     |     |\n");
	for (int j = 0; j < 2; j++)
	{
		printf("  %c  |", checkerboard[2][j]);
	}
	printf("  %c", checkerboard[2][2]);
	printf("\n     |     |\n");
}
void print_info(int ai_win, int player_win, int draw)
{
	gotoxy(20, 1);
	printf("     第%d局", ai_win + player_win + draw + 1);
	gotoxy(20, 3);
	printf("电脑X  :  玩家O");
	gotoxy(20, 4);
	printf("  %-5d:%5d", ai_win, player_win);
	gotoxy(20, 5);
	printf("   平局: %d", draw);
	gotoxy(20, 7);
	printf("电脑胜率: %.2f%%", (float)ai_win / (ai_win + player_win + draw) * 100);
	gotoxy(20, 8);
	printf("电脑胜平率: %.2f%%", (float)(ai_win + draw) / (ai_win + player_win + draw) * 100);
}
void player(char checkerboard[][3], int player_choice[][2], int n)
{
	int i = 0, j = 0, x = 3, y = 2, flag = 0;
	char c;
	gotoxy(x, y);
	while (1)
	{
		c = getch();
		switch (c)
		{
		case 'w':
			if (i > 0)
			{
				i -= 1;
				y -= 4;
				gotoxy(x, y);
			}
			break;
		case 's':
			if (i < 2)
			{
				i += 1;
				y += 4;
				gotoxy(x, y);
			}
			break;
		case 'a':
			if (j > 0)
			{
				j -= 1;
				x -= 6;
				gotoxy(x, y);
			}
			break;
		case 'd':
			if (j < 2)
			{
				j += 1;
				x += 6;
				gotoxy(x, y);
			}
			break;
		case '\r':
			if (checkerboard[i][j] == ' ')
			{
				checkerboard[i][j] = 'O';
				flag = 1;
			}
			break;
		}
		if (flag)
		{
			break;
		}
	}
	player_choice[n-1][0] = i;
	player_choice[n-1][1] = j;
}
void ai(char checkerboard[][3], int player_choice[][2], int ai_choice[][2], int b, int n)  //b为0代表电脑先手；n代表电脑步数
{
	int i, j, flag;
	static int choice, choice2;  //choice为1表示玩家第一步走边
	//进攻模块（先手）
	//先下角，并占有三个角
	if (!b)
	{
		//第一步,随机抢第一个角
		if (n == 1)
		{
			if (rand() % 2 == 0) //50%概率
			{
				i = 0;
			}
			else
			{
				i = 2;
			}
			if (rand() % 2 == 0) //50%概率
			{
				j = 0;
			}
			else
			{
				j = 2;
			}
			checkerboard[i][j] = 'X';
			ai_choice[0][0] = i;
			ai_choice[0][1] = j;
		}
		//第二步
		else if (n == 2)
		{
			//判断玩家第一步
			//玩家第一步走边
			if ((player_choice[0][0] == 0 && player_choice[0][1] == 1) || (player_choice[0][0] == 1 && player_choice[0][1] == 0) || (player_choice[0][0] == 2 && player_choice[0][1] == 1) || (player_choice[0][0] == 1 && player_choice[0][1] == 2))
			{
				choice = 1;
				//抢三角形策略
				//若玩家第一个棋贴着ai第一步，则抢不夹着玩家棋也不是对角的那一步
				//若玩家第一个棋没有贴着ai的第一步，则抢除了对角外可以贴着玩家棋的角
				if (ai_choice[0][0] == 0 && ai_choice[0][1] == 0)  //第一步抢了左上
				{
					if (checkerboard[0][1] == 'O' || player_choice[0][0] == 2)
					{
						checkerboard[2][0] = 'X';
						ai_choice[1][0] = 2;
						ai_choice[1][1] = 0;
					}
					else if (checkerboard[1][0] == 'O' || player_choice[0][1] == 2)
					{
						checkerboard[0][2] = 'X';
						ai_choice[1][0] = 0;
						ai_choice[1][1] = 2;
					}
				}
				else if (ai_choice[0][0] == 0 && ai_choice[0][1] == 2)  //第一步抢了右上
				{
					if (checkerboard[0][1] == 'O' || player_choice[0][0] == 2)
					{
						checkerboard[2][2] = 'X';
						ai_choice[1][0] = 2;
						ai_choice[1][1] = 2;
					}
					else if (checkerboard[1][2] == 'O' || player_choice[0][1] == 0)
					{
						checkerboard[0][0] = 'X';
						ai_choice[1][0] = 0;
						ai_choice[1][1] = 0;
					}
				}
				else if (ai_choice[0][0] == 2 && ai_choice[0][1] == 0)  //第一步抢了左下
				{
					if (checkerboard[1][0] == 'O' || player_choice[0][1] == 2)
					{
						checkerboard[2][2] = 'X';
						ai_choice[1][0] = 2;
						ai_choice[1][1] = 2;
					}
					else if (checkerboard[2][1] == 'O' || player_choice[0][0] == 0)
					{
						checkerboard[0][0] = 'X';
						ai_choice[1][0] = 0;
						ai_choice[1][1] = 0;
					}
				}
				else if (ai_choice[0][0] == 2 && ai_choice[0][1] == 2)  //第一步抢了右下
				{
					if (checkerboard[2][1] == 'O' || player_choice[0][0] == 0)
					{
						checkerboard[0][2] = 'X';
						ai_choice[1][0] = 0;
						ai_choice[1][1] = 2;
					}
					else if (checkerboard[1][2] == 'O' || player_choice[0][1] == 0)
					{
						checkerboard[2][0] = 'X';
						ai_choice[1][0] = 2;
						ai_choice[1][1] = 0;
					}
				}
			}
			//玩家第一步走角
			else if (player_choice[0][0] != 1 && player_choice[0][1] != 1)
			{
				choice = 2;
				if (ai_choice[0][0] != player_choice[0][0])  //不在同一行
				{
					if (checkerboard[ai_choice[0][0]][0] == ' ')
					{
						checkerboard[ai_choice[0][0]][0] = 'X';
						ai_choice[1][0] = ai_choice[0][0];
						ai_choice[1][1] = 0;
					}
					else
					{
						checkerboard[ai_choice[0][0]][2] = 'X';
						ai_choice[1][0] = ai_choice[0][0];
						ai_choice[1][1] = 2;
					}
				}
				else  //不在同一列
				{
					if (checkerboard[0][ai_choice[0][1]] == ' ')
					{
						checkerboard[0][ai_choice[0][1]] = 'X';
						ai_choice[1][0] = 0;
						ai_choice[1][1] = ai_choice[0][1];
					}
					else
					{
						checkerboard[2][ai_choice[0][1]] = 'X';
						ai_choice[1][0] = 2;
						ai_choice[1][1] = ai_choice[0][1];
					}
				}
			}
			//玩家第一步走中
			else if (player_choice[0][0] == 1 && player_choice[0][1] == 1)
			{
				choice = 3;
				//下对角
				if (ai_choice[0][0] == 0 && ai_choice[0][1] == 0)
				{
					checkerboard[2][2] = 'X';
					ai_choice[1][0] = 2;
					ai_choice[1][1] = 2;
				}
				else if (ai_choice[0][0] == 0 && ai_choice[0][1] == 2)
				{
					checkerboard[2][0] = 'X';
					ai_choice[1][0] = 2;
					ai_choice[1][1] = 0;
				}
				else if (ai_choice[0][0] == 2 && ai_choice[0][1] == 0)
				{
					checkerboard[0][2] = 'X';
					ai_choice[1][0] = 0;
					ai_choice[1][1] = 2;
				}
				else if (ai_choice[0][0] == 2 && ai_choice[0][1] == 2)
				{
					checkerboard[0][0] = 'X';
					ai_choice[1][0] = 0;
					ai_choice[1][1] = 0;
				}
			}
		}
		//AI第三步
		else if (n == 3)
		{
			if (choice == 1)  //续玩家第一步走边的情况
			{
				//先看看有没有憨憨玩家不堵（直接赢不需要记录步位置了）  
				flag = 1;
				if (ai_choice[1][0] == ai_choice[0][0])  //第二步和第一步在同一行
				{
					if (checkerboard[ai_choice[1][0]][1] == ' ')
					{
						checkerboard[ai_choice[1][0]][1] = 'X';
						flag = 0;
					}
				}
				else  //第二步和第一步在同一列
				{
					if (checkerboard[1][ai_choice[1][1]] == ' ')
					{
						checkerboard[1][ai_choice[1][1]] = 'X';
						flag = 0;
					}
				}
				if (flag)
				{
					//继续抢角，也是抢中间不夹对方棋，即所在行或列中间边无棋
					for (i = 0; i < 2; i++)  //第i步棋
					{
						if (checkerboard[ai_choice[i][0]][1] == ' ')  //行检测
						{
							if (checkerboard[ai_choice[i][0]][0] == ' ')
							{
								checkerboard[ai_choice[i][0]][0] = 'X';
								ai_choice[2][0] = ai_choice[i][0];
								ai_choice[2][1] = 0;
							}
							else
							{
								checkerboard[ai_choice[i][0]][2] = 'X';
								ai_choice[2][0] = ai_choice[i][0];
								ai_choice[2][1] = 2;
							}
						}
						else if (checkerboard[1][ai_choice[i][1]] == ' ')  //列检测
						{
							if (checkerboard[0][ai_choice[i][1]] == ' ')
							{
								checkerboard[0][ai_choice[i][1]] = 'X';
								ai_choice[2][0] = 0;
								ai_choice[2][1] = ai_choice[i][1];
							}
							else
							{
								checkerboard[2][ai_choice[i][1]] = 'X';
								ai_choice[2][0] = 2;
								ai_choice[2][1] = ai_choice[i][1];
							}
						}
					}
				}
			}
			else if (choice == 2)  //续玩家第一步下角
			{
				//先看看有没有憨憨玩家不堵（直接赢不需要记录步位置了）  
				flag = 1;
				if (ai_choice[1][0] == ai_choice[0][0])  //第二步和第一步在同一行
				{
					if (checkerboard[ai_choice[1][0]][1] == ' ')
					{
						checkerboard[ai_choice[1][0]][1] = 'X';
						flag = 0;
					}
				}
				else  //第二步和第一步在同一列
				{
					if (checkerboard[1][ai_choice[1][1]] == ' ')
					{
						checkerboard[1][ai_choice[1][1]] = 'X';
						flag = 0;
					}
				}
				if (flag)
				{
					//抢剩下的一个角
					if (checkerboard[0][0] == ' ')
					{
						checkerboard[0][0] = 'X';
						ai_choice[2][0] = 0;
						ai_choice[2][1] = 0;
					}
					else if (checkerboard[0][2] == ' ')
					{
						checkerboard[0][2] = 'X';
						ai_choice[2][0] = 0;
						ai_choice[2][1] = 2;
					}
					else if (checkerboard[2][0] == ' ')
					{
						checkerboard[2][0] = 'X';
						ai_choice[2][0] = 2;
						ai_choice[2][1] = 0;
					}
					else
					{
						checkerboard[2][2] = 'X';
						ai_choice[2][0] = 2;
						ai_choice[2][1] = 2;
					}
				}
			}
			else if (choice == 3)  //续玩家第一步下中
			{
				//玩家第二步下边
				if ((player_choice[1][0] == 0 && player_choice[1][1] == 1))
				{
					choice2 = 1;
					checkerboard[2][1] = 'X';
					ai_choice[2][0] = 2;
					ai_choice[2][1] = 1;
				}
				else if (player_choice[1][0] == 2 && player_choice[1][1] == 1)
				{
					choice2 = 1;
					checkerboard[0][1] = 'X';
					ai_choice[2][0] = 0;
					ai_choice[2][1] = 1;
				}
				else if (player_choice[1][0] == 1 && player_choice[1][1] == 0)
				{
					choice2 = 1;
					checkerboard[1][2] = 'X';
					ai_choice[2][0] = 1;
					ai_choice[2][1] = 2;
				}
				else if (player_choice[1][0] == 1 && player_choice[1][1] == 2)
				{
					choice2 = 1;
					checkerboard[1][0] = 'X';
					ai_choice[2][0] = 1;
					ai_choice[2][1] = 0;
				}
				//玩家第二步下角，则塞对角整三角形
				else if (player_choice[1][0] == 0 && player_choice[1][1] == 0)
				{
					choice2 = 2;
					checkerboard[2][2] = 'X';
					ai_choice[2][0] = 2;
					ai_choice[2][1] = 2;
				}
				else if (player_choice[1][0] == 0 && player_choice[1][1] == 2)
				{
					choice2 = 2;
					checkerboard[2][0] = 'X';
					ai_choice[2][0] = 2;
					ai_choice[2][1] = 0;
				}
				else if (player_choice[1][0] == 2 && player_choice[1][1] == 0)
				{
					choice2 = 2;
					checkerboard[0][2] = 'X';
					ai_choice[2][0] = 0;
					ai_choice[2][1] = 2;
				}
				else if (player_choice[1][0] == 2 && player_choice[1][1] == 2)
				{
					choice2 = 2;
					checkerboard[0][0] = 'X';
					ai_choice[2][0] = 0;
					ai_choice[2][1] = 0;
				}
			}
		}
		//AI第四步
		else if (n == 4)
		{
			if (choice == 1 || choice == 2)  //续玩家第一步走边和走角
			{
				//先看堵不堵中间
				if (checkerboard[1][1] == ' ')
				{
					checkerboard[1][1] = 'X';
				}
				else if (ai_choice[2][0] == ai_choice[0][0] || ai_choice[2][0] == ai_choice[1][0])  //三和一或二同行
				{
					checkerboard[ai_choice[2][0]][1] = 'X';
				}
				else if (ai_choice[2][1] == ai_choice[0][1] || ai_choice[2][1] == ai_choice[1][1])  //三和一或二同列
				{
					checkerboard[1][ai_choice[2][1]] = 'X';
				}
			}
			else if (choice == 3 && choice2 == 1)  //续玩家第一步走中，第二步走边
			{
				//防憨憨，第三步所在行列有没有被堵，即所在行或列的一个角能不能填
				if (checkerboard[ai_choice[2][0]][0] == ' ')
				{
					checkerboard[ai_choice[2][0]][0] = 'X';
				}
				else if (checkerboard[ai_choice[2][0]][2] == ' ')
				{
					checkerboard[ai_choice[2][0]][2] = 'X';
				}
				else if (checkerboard[0][ai_choice[2][1]] == ' ')
				{
					checkerboard[0][ai_choice[2][1]] = 'X';
				}
				else if (checkerboard[2][ai_choice[2][1]] == ' ')
				{
					checkerboard[2][ai_choice[2][1]] = 'X';
				}
				//没憨憨的话肯定塞角了，那就肯定得堵剩下的一个角
				if (checkerboard[0][0] == ' ')
				{
					checkerboard[0][0] = 'X';
					ai_choice[2][0] = 0;
					ai_choice[2][1] = 0;
				}
				else if (checkerboard[0][2] == ' ')
				{
					checkerboard[0][2] = 'X';
					ai_choice[2][0] = 0;
					ai_choice[2][1] = 2;
				}
				else if (checkerboard[2][0] == ' ')
				{
					checkerboard[2][0] = 'X';
					ai_choice[2][0] = 2;
					ai_choice[2][1] = 0;
				}
				else
				{
					checkerboard[2][2] = 'X';
					ai_choice[2][0] = 2;
					ai_choice[2][1] = 2;
				}
			}
			else if (choice == 3 && choice2 == 2)
			{
				//第三步所在行或列的中部为空就填，憨不憨没区别
				if (checkerboard[ai_choice[2][0]][1] == ' ')
				{
					checkerboard[ai_choice[2][0]][1] = 'X';
				}
				else
				{
					checkerboard[1][ai_choice[2][1]] = 'X';
				}
			}
		}
		//AI第五步
		else if (n == 5)
		{
			//只有choice=3的情况能走到第五步了，剩下最后一个格子怼进去
			for (i = 0; i < 3; i++)
			{
				for (j = 0; j < 3; j++)
				{
					if (checkerboard[i][j] == ' ')
					{
						checkerboard[i][j] = 'X';
					}
				}
			}
		}
	}
}
int judge(char checkerboard[][3])  //返回1电脑赢，返回2玩家赢，返回3平局,返回0未结束
{
	for (int i = 0; i < 3; i++)
	{
		if (checkerboard[i][0] == 'X' && checkerboard[i][1] == 'X' && checkerboard[i][2] == 'X')
		{
			return 1;
		}
		if (checkerboard[i][0] == 'O' && checkerboard[i][1] == 'O' && checkerboard[i][2] == 'O')
		{
			return 2;
		}
	}
	for (int j = 0; j < 3; j++)
	{
		if (checkerboard[0][j] == 'X' && checkerboard[1][j] == 'X' && checkerboard[2][j] == 'X')
		{
			return 1;
		}
		if (checkerboard[0][j] == 'O' && checkerboard[1][j] == 'O' && checkerboard[2][j] == 'O')
		{
			return 2;
		}
	}
	if ((checkerboard[0][0] == 'X' && checkerboard[1][1] == 'X' && checkerboard[2][2] == 'X') || (checkerboard[0][2] == 'X' && checkerboard[1][1] == 'X' && checkerboard[2][0] == 'X'))
	{
		return 1;
	}
	if ((checkerboard[0][0] == 'O' && checkerboard[1][1] == 'O' && checkerboard[2][2] == 'O') || (checkerboard[0][2] == 'O' && checkerboard[1][1] == 'O' && checkerboard[2][0] == 'O'))
	{
		return 2;
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (checkerboard[i][j] == ' ')
			{
				return 0;
			}
		}
	}
	//上面所有return都没执行成功跳出证明全部不符合，只剩下塞满平局了
	return 3;
}
int main()
{
	int i, j, n, ai_win = 0, player_win = 0, draw = 0, player_choice[5][2] = { 0 }, ai_choice[5][2] = { 0 };
	char run, checkerboard[3][3] = { 0 };
	system("mode con: cols=42 lines=12");
	srand((unsigned int)time(NULL));
	while (1)
	{
		run = menu();
		switch (run)
		{
		case '1':
			while (1)  //局循环
			{
				//初始化棋盘
				for (i = 0; i < 3; i++)
				{
					for (j = 0; j < 3; j++)
					{
						checkerboard[i][j] = ' ';
					}
				}
				n = 1;
				while (1)  //走棋循环
				{
					ai(checkerboard, player_choice, ai_choice, 0, n);
					system("cls");
					print_board(checkerboard);
					print_info(ai_win, player_win, draw);
					if (judge(checkerboard) == 1)
					{
						gotoxy(24, 10);
						printf("电脑胜");
						ai_win++;
						break;
					}
					else if (judge(checkerboard) == 2)
					{
						gotoxy(24, 10);
						printf("玩家胜");
						player_win++;
						break;
					}
					else if (judge(checkerboard) == 3)
					{
						gotoxy(24, 10);
						printf("平局");
						draw++;
						break;
					}
					player(checkerboard, player_choice, n);
					system("cls");
					print_board(checkerboard);
					print_info(ai_win, player_win, draw);
					if (judge(checkerboard) == 1)
					{
						gotoxy(24, 10);
						printf("电脑胜");
						ai_win++;
						break;
					}
					else if (judge(checkerboard) == 2)
					{
						gotoxy(24, 10);
						printf("玩家胜");
						player_win++;
						break;
					}
					else if (judge(checkerboard) == 3)
					{
						gotoxy(24, 10);
						printf("平局");
						draw++;
						break;
					}
					n++;
				}
				gotoxy(21, 11);
				printf("继续请按回车");
				if (getch() == 27)
				{
					break;
				}
			}
			break;
		case '2':
			exit(0);
		}
		getchar();
	}
	return 0;
}