#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

//���ΪO������ΪX

void gotoxy(int a, int b)
{
	HANDLE hout;
	COORD coord;
	coord.X = a - 1;  //�������Ͻ�Ϊ(1,1)
	coord.Y = b - 1;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout, coord);
}
char menu()
{
	printf("1.��������\n2.�˳���Ϸ\n");
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
	printf("     ��%d��", ai_win + player_win + draw + 1);
	gotoxy(20, 3);
	printf("����X  :  ���O");
	gotoxy(20, 4);
	printf("  %-5d:%5d", ai_win, player_win);
	gotoxy(20, 5);
	printf("   ƽ��: %d", draw);
	gotoxy(20, 7);
	printf("����ʤ��: %.2f%%", (float)ai_win / (ai_win + player_win + draw) * 100);
	gotoxy(20, 8);
	printf("����ʤƽ��: %.2f%%", (float)(ai_win + draw) / (ai_win + player_win + draw) * 100);
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
void ai(char checkerboard[][3], int player_choice[][2], int ai_choice[][2], int b, int n)  //bΪ0����������֣�n������Բ���
{
	int i, j, flag;
	static int choice, choice2;  //choiceΪ1��ʾ��ҵ�һ���߱�
	//����ģ�飨���֣�
	//���½ǣ���ռ��������
	if (!b)
	{
		//��һ��,�������һ����
		if (n == 1)
		{
			if (rand() % 2 == 0) //50%����
			{
				i = 0;
			}
			else
			{
				i = 2;
			}
			if (rand() % 2 == 0) //50%����
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
		//�ڶ���
		else if (n == 2)
		{
			//�ж���ҵ�һ��
			//��ҵ�һ���߱�
			if ((player_choice[0][0] == 0 && player_choice[0][1] == 1) || (player_choice[0][0] == 1 && player_choice[0][1] == 0) || (player_choice[0][0] == 2 && player_choice[0][1] == 1) || (player_choice[0][0] == 1 && player_choice[0][1] == 2))
			{
				choice = 1;
				//�������β���
				//����ҵ�һ��������ai��һ�������������������Ҳ���ǶԽǵ���һ��
				//����ҵ�һ����û������ai�ĵ�һ�����������˶Խ���������������Ľ�
				if (ai_choice[0][0] == 0 && ai_choice[0][1] == 0)  //��һ����������
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
				else if (ai_choice[0][0] == 0 && ai_choice[0][1] == 2)  //��һ����������
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
				else if (ai_choice[0][0] == 2 && ai_choice[0][1] == 0)  //��һ����������
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
				else if (ai_choice[0][0] == 2 && ai_choice[0][1] == 2)  //��һ����������
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
			//��ҵ�һ���߽�
			else if (player_choice[0][0] != 1 && player_choice[0][1] != 1)
			{
				choice = 2;
				if (ai_choice[0][0] != player_choice[0][0])  //����ͬһ��
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
				else  //����ͬһ��
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
			//��ҵ�һ������
			else if (player_choice[0][0] == 1 && player_choice[0][1] == 1)
			{
				choice = 3;
				//�¶Խ�
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
		//AI������
		else if (n == 3)
		{
			if (choice == 1)  //����ҵ�һ���߱ߵ����
			{
				//�ȿ�����û�к�����Ҳ��£�ֱ��Ӯ����Ҫ��¼��λ���ˣ�  
				flag = 1;
				if (ai_choice[1][0] == ai_choice[0][0])  //�ڶ����͵�һ����ͬһ��
				{
					if (checkerboard[ai_choice[1][0]][1] == ' ')
					{
						checkerboard[ai_choice[1][0]][1] = 'X';
						flag = 0;
					}
				}
				else  //�ڶ����͵�һ����ͬһ��
				{
					if (checkerboard[1][ai_choice[1][1]] == ' ')
					{
						checkerboard[1][ai_choice[1][1]] = 'X';
						flag = 0;
					}
				}
				if (flag)
				{
					//�������ǣ�Ҳ�����м䲻�жԷ��壬�������л����м������
					for (i = 0; i < 2; i++)  //��i����
					{
						if (checkerboard[ai_choice[i][0]][1] == ' ')  //�м��
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
						else if (checkerboard[1][ai_choice[i][1]] == ' ')  //�м��
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
			else if (choice == 2)  //����ҵ�һ���½�
			{
				//�ȿ�����û�к�����Ҳ��£�ֱ��Ӯ����Ҫ��¼��λ���ˣ�  
				flag = 1;
				if (ai_choice[1][0] == ai_choice[0][0])  //�ڶ����͵�һ����ͬһ��
				{
					if (checkerboard[ai_choice[1][0]][1] == ' ')
					{
						checkerboard[ai_choice[1][0]][1] = 'X';
						flag = 0;
					}
				}
				else  //�ڶ����͵�һ����ͬһ��
				{
					if (checkerboard[1][ai_choice[1][1]] == ' ')
					{
						checkerboard[1][ai_choice[1][1]] = 'X';
						flag = 0;
					}
				}
				if (flag)
				{
					//��ʣ�µ�һ����
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
			else if (choice == 3)  //����ҵ�һ������
			{
				//��ҵڶ����±�
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
				//��ҵڶ����½ǣ������Խ���������
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
		//AI���Ĳ�
		else if (n == 4)
		{
			if (choice == 1 || choice == 2)  //����ҵ�һ���߱ߺ��߽�
			{
				//�ȿ��²����м�
				if (checkerboard[1][1] == ' ')
				{
					checkerboard[1][1] = 'X';
				}
				else if (ai_choice[2][0] == ai_choice[0][0] || ai_choice[2][0] == ai_choice[1][0])  //����һ���ͬ��
				{
					checkerboard[ai_choice[2][0]][1] = 'X';
				}
				else if (ai_choice[2][1] == ai_choice[0][1] || ai_choice[2][1] == ai_choice[1][1])  //����һ���ͬ��
				{
					checkerboard[1][ai_choice[2][1]] = 'X';
				}
			}
			else if (choice == 3 && choice2 == 1)  //����ҵ�һ�����У��ڶ����߱�
			{
				//������������������������û�б��£��������л��е�һ�����ܲ�����
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
				//û�����Ļ��϶������ˣ��ǾͿ϶��ö�ʣ�µ�һ����
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
				//�����������л��е��в�Ϊ�վ��������û����
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
		//AI���岽
		else if (n == 5)
		{
			//ֻ��choice=3��������ߵ����岽�ˣ�ʣ�����һ��������ȥ
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
int judge(char checkerboard[][3])  //����1����Ӯ������2���Ӯ������3ƽ��,����0δ����
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
	//��������return��ûִ�гɹ�����֤��ȫ�������ϣ�ֻʣ������ƽ����
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
			while (1)  //��ѭ��
			{
				//��ʼ������
				for (i = 0; i < 3; i++)
				{
					for (j = 0; j < 3; j++)
					{
						checkerboard[i][j] = ' ';
					}
				}
				n = 1;
				while (1)  //����ѭ��
				{
					ai(checkerboard, player_choice, ai_choice, 0, n);
					system("cls");
					print_board(checkerboard);
					print_info(ai_win, player_win, draw);
					if (judge(checkerboard) == 1)
					{
						gotoxy(24, 10);
						printf("����ʤ");
						ai_win++;
						break;
					}
					else if (judge(checkerboard) == 2)
					{
						gotoxy(24, 10);
						printf("���ʤ");
						player_win++;
						break;
					}
					else if (judge(checkerboard) == 3)
					{
						gotoxy(24, 10);
						printf("ƽ��");
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
						printf("����ʤ");
						ai_win++;
						break;
					}
					else if (judge(checkerboard) == 2)
					{
						gotoxy(24, 10);
						printf("���ʤ");
						player_win++;
						break;
					}
					else if (judge(checkerboard) == 3)
					{
						gotoxy(24, 10);
						printf("ƽ��");
						draw++;
						break;
					}
					n++;
				}
				gotoxy(21, 11);
				printf("�����밴�س�");
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