#include<stdio.h>
#include<windows.h>
#include<conio.h>

int main()
{
	system("mode con: cols=60 lines=30");
	srand((unsigned int)time(NULL));
	printf("***************************̰����***************************\n\n�밴�س���ʼ��Ϸ...\n\n\n\n\nPS����Ϸ;�а��ո������ͣ����Esc�����˳�");
	getchar();
	system("cls");
	do
	{
		int x = 15, y = 15, len = 4, map[900] = { 0 }, i;
		char c = 'd', c1 = 'd', draw[1801] = {0};
		for (map[rand() % 900] = -1; 1; Sleep(100))
		{
			//���������벢ת��
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
			//�ж�ͷײǽ����������
			if (c == 'a' && --x < 0 || c == 'd' && ++x == 30 || c == 'w' && --y < 0 || c == 's' && ++y == 30)
			{
				Sleep(1000);
				system("cls");
				printf("����ʧ�ܣ����ո�����¿�ʼ...");
				break; 
			}
			//�жϳԵ��Լ�
			if (map[y*30+x] > 1)
			{
				Sleep(1000);
				system("cls");
				printf("����ʧ�ܣ����ո�����¿�ʼ...");
				break; 
			}
			//�жϳԵ�ʳ��
			if (map[y*30+x] == -1)
			{
				len++;
				//������ʳ��
				do
				{
					i = rand() % 900;
				} while (map[i] != 0);  //ȷ��ʳ�������ڿյ�
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
			map[y*30+x] = len;   //��ͷ��ֵ
			//���»��ƻ����������
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
