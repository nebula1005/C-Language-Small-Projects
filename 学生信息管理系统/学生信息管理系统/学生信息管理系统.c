#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include <conio.h>
#define width 120
#define height 30
#define password_maxlength 10
#define name_maxlength 15
#define id_maxlength 15
#define max_number 50

//��ʾ��������ѿ���̨��ȸ�Ϊ120

//������־
// 0.1.0  ��������롢��ʾģ��
// 0.2.0  ������ͳ�ơ���ѯģ��
// 1.0.0  ����˳���������й���
// 1.0.1  �޸�����֪����
// 1.1.0  ������ѧ�Ŵ��淽ʽ��֧��ѧ�ź���Ӣ����ĸ
// 1.1.1  �����˲˵��ṹ
// 1.1.2  �޸�����֪����
// 1.1.3  �Ż��˲��ִ���ṹ
// 1.2.0  ������ѧ������ʽ��ѧ�ų��ȿɲ�ͬ
// 1.2.1  �Ż��˳���ҳ������
// 1.2.2  �޸�����֪����
// д����ģ�
char version[] = { "V1.2.2" };

//����TC�����²����õ�clrscr()��gotoxy()
void gotoxy(int a, int b)
{
    HANDLE hout;
    COORD coord;
    coord.X = a - 1;  //�������Ͻ�Ϊ(1,1)
    coord.Y = b - 1;
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hout, coord);
}
void clrscr()
{
    system("cls");
}
void window()
{
    clrscr();
    gotoxy(46, 9);
    printf("------------------------------");
    for (int i = 0; i < 9; i++)
    {
        gotoxy(46, i + 10);
        printf("|");
        gotoxy(75, i + 10);
        printf("|");
    }
    gotoxy(46, 18);
    printf("------------------------------");
}
void line()
{
    for (int i = 0; i < width; i++)
    {
        printf("-");
    }
}
void exchange(char name[][name_maxlength], char id[][id_maxlength], float score[][5], int i, int k)
{
    char temp_name[name_maxlength] = { 0 };
    strcpy(temp_name, name[k]);
    strcpy(name[k], name[i]);
    strcpy(name[i], temp_name);
    char temp_id[id_maxlength] = { 0 };
    strcpy(temp_id, id[k]);
    strcpy(id[k], id[i]);
    strcpy(id[i], temp_id);
    for (int j = 0; j < 5; j++)
    {
        float temp_score = score[k][j];
        score[k][j] = score[i][j];
        score[i][j] = temp_score;
    }
}
void sort_id(char name[][name_maxlength], char id[][id_maxlength], float score[][5], int n)
{
    int i, j, k, temp;
    for (i = 0; i < n - 1; i++)
    {
        k = i;
        for (j = i + 1; j < n; j++)
        {
            //if (atoll(id[j]) < atoll(id[k]))
            if (strlen(id[j]) < strlen(id[k]))
            {
                k = j;
            }
            else if (strlen(id[j]) == strlen(id[k]))
            {
                if (strcmp(id[j], id[k]) < 0)
                {
                    k = j;
                }
            }
        }
        exchange(name, id, score, i, k);
    }
}
void sort_score(char name[][name_maxlength], char id[][id_maxlength], float score[][5], int n, int s)//s��ʾ�����±�
{
    int i, j, k;
    for (i = 0; i < n - 1; i++)
    {
        k = i;
        for (j = i + 1; j < n; j++)
        {
            if (score[j][s] > score[k][s])
            {
                k = j;
            }
        }
        exchange(name, id, score, i, k);
    }
}
void print_info(char name[][name_maxlength], char id[][id_maxlength], float score[][5], int n) //���n��ѧ���±�
{
    printf("%15s%15s", name[n], id[n]);
    for (int i = 0; i < 4; i++)  //�ĿƳɼ�
    {
        printf("%15.1f", score[n][i]);
    }
    printf("%15.2f\n", score[n][4]);
}
//�������루���˸񣩷�������λ��
int get_password(char password[])
{
    int i = 0;
    char ch;
    while (1)
    {
        ch = getch();
        if (ch == '\r')
        {
            password[i] = '\0';
            break;
        }
        else if (ch == '\b')
        {
            printf("\b \b");
            i--;
        }
        else
        {
            password[i] = ch;
            i++;
            printf("*");
        }
    }
    return i;
}
//��Ϣ����
void input(char name[][name_maxlength], char sex[][3], char id[][id_maxlength], float score[][5], int n)
{
    window();
    gotoxy(57, 10);
    printf("��Ϣ����");
    gotoxy(49, 11);
    printf("������");
    gotoxy(49, 12);
    printf("�Ա�");
    gotoxy(49, 13);
    printf("ѧ�ţ�");
    gotoxy(49, 14);
    printf("������");
    gotoxy(49, 15);
    printf("Ӣ�");
    gotoxy(49, 16);
    printf("C���ԣ�");
    gotoxy(49, 17);
    printf("����");
    gotoxy(57, 11);
    gets(name[n]);
    gotoxy(57, 12);
    gets(sex[n]);
    gotoxy(57, 13);
    gets(id[n]);
    for (int i = 0; i < 4; i++)
    {
        gotoxy(57, i + 14);
        scanf("%f", &score[n][i]);
        getchar();
    }
    score[n][4] = (score[n][0] + score[n][1] + score[n][2] + score[n][3]) / 4;
}
//��Ϣ��ʾ
void display(char name[][name_maxlength], char id[][id_maxlength], float score[][5], int n)
{
    int i, j;
    printf("%65s\n%65s\n", "----------", "*����ѧ��*");
    line();
    printf("%15s%15s%15s%15s%15s%15s%15s\n", "����", "ѧ��", "����", "Ӣ��", "C����", "����", "ƽ����");
    for (i = 0; i < n; i++)  //ѧ��ѭ��
    {
        print_info(name, id, score, i);
    }
    line();
    printf("\n\n%65s\n%65s\n", "----------", "*��������*");
    line();
    printf("%15s%15s%37s", "����", "ѧ��", "������Ŀ���ɼ�");
    for (i = 0; i < n; i++)
    {
        if (score[i][0] < 60 || score[i][1] < 60 || score[i][2] < 60 || score[i][3] < 60)
        {
            printf("\n%15s%15s", name[i], id[i]);
            for (j = 0; j < 4; j++)
            {
                if (score[i][j] < 60)
                {
                    switch (j)
                    {
                    case 0:
                        printf("%11s%5.1f", "����:", score[i][j]);
                        break;
                    case 1:
                        printf("%11s%5.1f", "Ӣ��:", score[i][j]);
                        break;
                    case 2:
                        printf("%11s%5.1f", "C����:", score[i][j]);
                        break;
                    case 3:
                        printf("%11s%5.1f", "����:", score[i][j]);
                        break;
                    }
                }
            }
        }
    }
    printf("\n");
    line();
    getchar();
}
//��Ϣͳ��
void count(char name[][name_maxlength], char id[][id_maxlength], float score[][5], int n)
{
    int i, j, count;
    float sum, avg;
    //����ƽ����
    printf("%66s\n%66s\n","------------","*����ƽ����*");
    line();
    for (j = 0; j < 4; j++)
    {
        gotoxy(53, j + 4);
        sum = 0;
        for (i = 0; i < n; i++)
        {
            sum += score[i][j];
        }
        avg = sum / n;
        switch (j)
        {
        case 0:
            printf("������%.2f", avg);
            break;
        case 1:
            printf("Ӣ�%.2f", avg);
            break;
        case 2:
            printf("C���ԣ�%.2f", avg);
            break;
        case 3:
            printf("����%.2f", avg);
            break;
        }
    }
    printf("\n");
    line();
    //ѧ������
    char name_copy[max_number][name_maxlength] = { 0 };
    char id_copy[max_number][id_maxlength];
    float score_copy[max_number][5];
    //����ԭ�б�
    for (i = 0; i < n; i++)
    {
        strcpy(name_copy[i], name[i]);
    }
    for (i = 0; i < n; i++)
    {
        strcpy(id_copy[i], id[i]);
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < 5; j++)
        {
            score_copy[i][j] = score[i][j];
        }
    }
    //ѧ������
    printf("\n\n%65s\n%65s\n","----------","*ѧ������*");
    line();
    sort_id(name_copy, id_copy, score_copy, n);
    printf("%15s%15s%15s%15s%15s%15s%15s\n", "����", "ѧ��", "����", "Ӣ��", "C����", "����", "ƽ����");
    for (i = 0; i < n; i++)
    {
        print_info(name_copy, id_copy, score_copy, i);
    }
    line();
    //�ɼ�����
    for (j = 0; j < 5; j++)
    {
        
        switch (j)
        {
        case 0:
            printf("\n\n%67s\n%67s\n", "--------------", "*�����ɼ�����*");
            break;
        case 1:
            printf("\n\n%67s\n%67s\n", "--------------", "*Ӣ��ɼ�����*");
            break;
        case 2:
            printf("\n\n%68s\n%68s\n", "----------------", "*C���Գɼ�����*");
            break;
        case 3:
            printf("\n\n%67s\n%67s\n", "--------------", "*����ɼ�����*");
            break;
        case 4:
            printf("\n\n%67s\n%67s\n", "--------------", "*ƽ���ɼ�����*");
            break;
        }
        line();
        sort_score(name_copy, id_copy, score_copy, n, j);
        if (j != 4)
        {
            for (i = 0; i < n; i++)
            {
                printf("%53s%19.1f\n", name_copy[i], score_copy[i][j]);
            }
        }
        else
        {
            for (i = 0; i < n; i++)
            {
                printf("%53s%19.2f\n", name_copy[i], score_copy[i][j]);
            }
        }
        line();
    }
    //���Ʋ���ͳ��
    printf("\n\n%67s\n%67s\n", "--------------", "*���Ʋ���ͳ��*");
    line();
    for (j = 0; j < 4; j++)
    {
        count = 0;
        switch (j)
        {
        case 0:
            printf("��������������\n");
            break;
        case 1:
            printf("\nӢ�ﲹ��������\n");
            break;
        case 2:
            printf("\nC���Բ���������\n");
            break;
        case 3:
            printf("\n������������\n");
            break;
        }
        for (i = 0; i < n; i++)
        {
            if (score[i][j] < 60)
            {
                printf("  %s��%.1f��\n", name[i], score[i][j]);
                count++;
            }
        }
        printf("  ��%d��\n", count);
    }
    line();
    getchar();
}
void search(char name[][name_maxlength], char sex[][3], char id[][id_maxlength], float score[][5], int n)
{
    int i, flag;
    float begin, end;
    char name_input[name_maxlength] = { 0 }, run, sub;
    while (1)
    {
        window();
        gotoxy(59, 11);
        printf("��ѯ");
        gotoxy(47, 14);
        printf("1:������ѯ  2:�����β�ѯ");
        gotoxy(47, 16);
        printf("3:��Ů����  Esc:�����ϼ��˵�");
        run = getch();
        if (run == 27)
        {
            break;
        }
        clrscr();
        switch (run)
        {
        case '1':
            printf("������������");
            gets(name_input);
            line();
            printf("\n");
            flag = 1;
            for (i = 0; i < n; i++)
            {
                if (!strcmp(name[i], name_input))
                {
                    print_info(name, id, score, i);
                    flag = 0;
                }
            }
            if (flag)
            {
                printf("���޴���\n");
            }
            line();
            getchar();
            break;
        case '2':
            while (1)
            {
                window();
                gotoxy(57, 11);
                printf("��ѯ��Ŀ");
                gotoxy(49, 14);
                printf("1:����    2:Ӣ��");
                gotoxy(49, 15);
                printf("3:C����   4:����");
                gotoxy(49, 16);
                printf("5:ƽ����  Esc:�����ϼ��˵�");
                sub = getch();
                if (sub == 27)
                {
                    break;
                }
                while (1)
                {
                    clrscr();
                    printf("����������Σ�    -\n");
                    line();
                    gotoxy(15, 1);
                    scanf("%f", &begin);
                    gotoxy(20, 1);
                    scanf("%f", &end);
                    if (begin < end)
                    {
                        break;
                    }
                    else
                    {
                        printf("��ʼֵ����ڽ���ֵ�����������롣");
                        getchar();
                    }
                }
                flag = 1;
                clrscr();
                switch (sub)
                {
                case '1':
                    printf("�����ɼ���%.1f-%.1f\n", begin, end);
                    printf("%15s%15s%15s%15s%15s%15s%15s\n", "����", "ѧ��", "����", "Ӣ��", "C����", "����", "ƽ����");
                    line();
                    for (i = 0; i < n; i++)
                    {
                        if (score[i][0] >= begin && score[i][0] <= end)
                        {
                            print_info(name, id, score, i);
                            flag = 0;
                        }
                    }
                    if (flag)
                    {
                        printf("��\n");
                    }
                    break;
                case '2':
                    printf("Ӣ��ɼ���%.1f-%.1f\n", begin, end);
                    printf("%15s%15s%15s%15s%15s%15s%15s\n", "����", "ѧ��", "����", "Ӣ��", "C����", "����", "ƽ����");
                    line();
                    for (i = 0; i < n; i++)
                    {
                        if (score[i][1] >= begin && score[i][1] <= end)
                        {
                            print_info(name, id, score, i);
                            flag = 0;
                        }
                    }
                    if (flag)
                    {
                        printf("��\n");
                    }
                    break;
                case '3':
                    printf("C���Գɼ���%.1f-%.1f\n", begin, end);
                    printf("%15s%15s%15s%15s%15s%15s%15s\n", "����", "ѧ��", "����", "Ӣ��", "C����", "����", "ƽ����");
                    line();
                    for (i = 0; i < n; i++)
                    {
                        if (score[i][2] >= begin && score[i][2] <= end)
                        {
                            print_info(name, id, score, i);
                            flag = 0;
                        }
                    }
                    if (flag)
                    {
                        printf("��\n");
                    }
                    break;
                case '4':
                    printf("����ɼ���%.1f-%.1f\n", begin, end);
                    printf("%15s%15s%15s%15s%15s%15s%15s\n", "����", "ѧ��", "����", "Ӣ��", "C����", "����", "ƽ����");
                    line();
                    for (i = 0; i < n; i++)
                    {
                        if (score[i][3] >= begin && score[i][3] <= end)
                        {
                            print_info(name, id, score, i);
                            flag = 0;
                        }
                    }
                    if (flag)
                    {
                        printf("��\n");
                    }
                    break;
                case '5':
                    printf("ƽ������%.2f-%.2f\n", begin, end);
                    printf("%15s%15s%15s%15s%15s%15s%15s\n", "����", "ѧ��", "����", "Ӣ��", "C����", "����", "ƽ����");
                    line();
                    for (i = 0; i < n; i++)
                    {
                        if (score[i][4] >= begin && score[i][4] <= end)
                        {
                            print_info(name, id, score, i);
                            flag = 0;
                        }
                    }
                    if (flag)
                    {
                        printf("��\n");
                    }

                    break;
                }
                line();
                getchar();
                getchar();
            }
            break;
        case '3':
            printf("%62s\n%62s\n", "----", "*��*");
            line();
            printf("%15s%15s%15s%15s%15s%15s%15s\n", "����", "ѧ��", "����", "Ӣ��", "C����", "����", "ƽ����");
            for (i = 0; i < n; i++)
            {
                if (!strcmp(sex[i], "��\0"))
                {
                    print_info(name, id, score, i);
                }
            }
            line();
            printf("\n\n%62s\n%62s\n", "----", "*Ů*");
            line();
            printf("%15s%15s%15s%15s%15s%15s%15s\n", "����", "ѧ��", "����", "Ӣ��", "C����", "����", "ƽ����");
            for (i = 0; i < n; i++)
            {
                if (!strcmp(sex[i], "Ů\0"))
                {
                    print_info(name, id, score, i);
                }
            }
            line();
            getchar();
            break;
        }
    }
}
int main()
{

    int i, j, n=0;
    char run;
    char password[password_maxlength], correct_password[password_maxlength] = { "123456" }, name[max_number][name_maxlength] = { 0 }, sex[max_number][3] = { 0 }, id[max_number][id_maxlength] = { 0 };
    float score[max_number][5];
    //����ϵͳǰ�����뱣��
    for (i = 2; i >=0; i--)
    {
        window();
        gotoxy(52, 11);
        printf("ѧ������ϵͳ %s", version);
        gotoxy(54, 14);
        printf("�û�����admin");
        gotoxy(62, 17);
        printf("by JNU.��Ҷ�");
        gotoxy(54, 15);
        printf("���룺");
        get_password(password);
        clrscr();
        if (!strcmp(password, correct_password))
        {
            window();
            gotoxy(48, 14);
            printf("������ȷ,��������ϵͳ��");
            for (j = 0; j < 3; j++)
            {
                printf(".");
                Sleep(500);
            }
            break;
        }
        else
        {
            if (i > 0)
            {
                window();
                gotoxy(51, 14);
                printf("�������,����%d�λ���", i);
                getchar();
            }
            else
            {
                window();
                gotoxy(52, 13);
                printf("�����������������");
                gotoxy(50, 14);
                printf("1Сʱ�ڽ�ֹ��¼��ϵͳ��\n\n\n\n\n");
                exit(0);
            }
        }
    }
    while (1)
    {
        window();
        gotoxy(52, 11);
        printf("ѧ������ϵͳ %s", version);
        gotoxy(50, 14);
        printf("1:��Ϣ����  2:��Ϣ��ʾ");
        gotoxy(50, 16);
        printf("3:��Ϣͳ��  4:��Ϣ��ѯ");
        run = getch();
        clrscr();
        switch (run)
        {
        case '1':
            do
            {
                input(name, sex, id, score, n);
                n++;
                window();
                gotoxy(57, 12);
                printf("¼��ɹ�");
                gotoxy(54, 14);
                printf("���س�������");
                gotoxy(52, 15);
                printf("��Esc���������˵�");
            } while (getch() != 27);
            break;
        case '2':
            display(name, id, score, n);
            break;
        case '3':
            count(name, id, score, n);
            break;
        case '4':
            search(name, sex, id, score, n);
            break;
        case 27:
            exit(0);
        }
    }
	return 0;
}