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
		printf("������ϰϵͳ\n���˵�\n��ϰģʽ��\n1��������ϰ\n2��������ϰ\n3���˳�\n");
		scanf("%d", &mode);
		system("cls");
		if (mode == 1)
		{
			do
			{
				system("cls");
				printf("������ϰ\n�л�ģʽ��\n1���ֶ�ģʽ\n2���Զ�ģʽ\n3�������ϼ��˵�\n");
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
					printf("�������л���ʱ��ms����");
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
				printf("������ϰ\n�л�ģʽ��\n1���ֶ�ģʽ\n2���Զ�ģʽ\n3�������ϼ��˵�\n");
				scanf("%d", &mode);
				system("cls");
				if (mode == 1)
				{
					printf("������ÿ������������");
					scanf("%d", &n);
					system("cls");
					do
					{
						consistent_practice(n);
					} while (_getch() != 27);
				}
				else if (mode == 2)
				{
					printf("������ÿ������������");
					scanf("%d", &n);
					printf("�������л���ʱ��ms����");
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