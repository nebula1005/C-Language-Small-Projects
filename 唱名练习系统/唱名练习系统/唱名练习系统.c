#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

void single_practice()
{
	system("cls");
	printf("%d", rand() % 7 + 1);
}
void consistent_practice(int n)
{
	system("cls");
	for (int i = 0; i < n; i++)
	{
		printf("%d", rand() % 7 + 1);
	}
}
int main()
{
	int mode, n, delay;
	srand((unsigned int)time(NULL));
	while (1)
	{
		system("cls");
		printf("唱名练习系统\n主菜单\n练习模式：\n1、单音练习\n2、连贯练习\n3、退出\n");
		scanf("%d", &mode);
		system("cls");
		if (mode == 1)
		{
			do
			{
				system("cls");
				printf("单音练习\n切换模式：\n1、手动模式\n2、自动模式\n3、返回上级菜单\n");
				scanf("%d", &mode);
				system("cls");
				if (mode == 1)
				{
					do
					{
						single_practice();
					} while (_getch() != 27);
				}
				else if (mode == 2)
				{
					printf("请输入切换延时（ms）：");
					scanf("%d", &delay);
					do
					{
						single_practice();
						Sleep(delay);
					} while (!(_kbhit() && _getch() == 27));
				}
				else if (mode == 3)
				{
					break;
				}
			} while (mode != 1 && mode != 2 && mode != 3);
		}
		else if (mode == 2)
		{
			do
			{
				system("cls");
				printf("连贯练习\n切换模式：\n1、手动模式\n2、自动模式\n3、返回上级菜单\n");
				scanf("%d", &mode);
				system("cls");
				if (mode == 1)
				{
					printf("请输入每次音符数量：");
					scanf("%d", &n);
					system("cls");
					do
					{
						consistent_practice(n);
					} while (_getch() != 27);
				}
				else if (mode == 2)
				{
					printf("请输入每次音符数量：");
					scanf("%d", &n);
					printf("请输入切换延时（ms）：");
					scanf("%d", &delay);
					system("cls");
					do
					{
						consistent_practice(n);
						Sleep(delay);
					} while (!(_kbhit() && _getch() == 27));
				}
			} while (mode != 1 && mode != 2 && mode != 3);
		}
		else if (mode == 3)
		{
			exit(0);
		}
	}
	return 0;
}