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

//提示：运行请把控制台宽度改为120

//更新日志
// 0.1.0  完成了输入、显示模块
// 0.2.0  增加了统计、查询模块
// 1.0.0  完成了程序初定所有功能
// 1.0.1  修复了已知问题
// 1.1.0  更改了学号储存方式，支持学号含有英文字母
// 1.1.1  更改了菜单结构
// 1.1.2  修复了已知问题
// 1.1.3  优化了部分代码结构
// 1.2.0  升级了学号排序方式，学号长度可不同
// 1.2.1  优化了程序页面美工
// 1.2.2  修复了已知问题
// 写着玩的！
char version[] = { "V1.2.2" };

//定义TC环境下才能用的clrscr()和gotoxy()
void gotoxy(int a, int b)
{
    HANDLE hout;
    COORD coord;
    coord.X = a - 1;  //调整左上角为(1,1)
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
void sort_score(char name[][name_maxlength], char id[][id_maxlength], float score[][5], int n, int s)//s表示分数下标
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
void print_info(char name[][name_maxlength], char id[][id_maxlength], float score[][5], int n) //这个n是学生下标
{
    printf("%15s%15s", name[n], id[n]);
    for (int i = 0; i < 4; i++)  //四科成绩
    {
        printf("%15.1f", score[n][i]);
    }
    printf("%15.2f\n", score[n][4]);
}
//输入密码（可退格）返回密码位数
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
//信息输入
void input(char name[][name_maxlength], char sex[][3], char id[][id_maxlength], float score[][5], int n)
{
    window();
    gotoxy(57, 10);
    printf("信息输入");
    gotoxy(49, 11);
    printf("姓名：");
    gotoxy(49, 12);
    printf("性别：");
    gotoxy(49, 13);
    printf("学号：");
    gotoxy(49, 14);
    printf("高数：");
    gotoxy(49, 15);
    printf("英语：");
    gotoxy(49, 16);
    printf("C语言：");
    gotoxy(49, 17);
    printf("物理：");
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
//信息显示
void display(char name[][name_maxlength], char id[][id_maxlength], float score[][5], int n)
{
    int i, j;
    printf("%65s\n%65s\n", "----------", "*所有学生*");
    line();
    printf("%15s%15s%15s%15s%15s%15s%15s\n", "姓名", "学号", "高数", "英语", "C语言", "物理", "平均分");
    for (i = 0; i < n; i++)  //学生循环
    {
        print_info(name, id, score, i);
    }
    line();
    printf("\n\n%65s\n%65s\n", "----------", "*补考名单*");
    line();
    printf("%15s%15s%37s", "姓名", "学号", "补考科目及成绩");
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
                        printf("%11s%5.1f", "高数:", score[i][j]);
                        break;
                    case 1:
                        printf("%11s%5.1f", "英语:", score[i][j]);
                        break;
                    case 2:
                        printf("%11s%5.1f", "C语言:", score[i][j]);
                        break;
                    case 3:
                        printf("%11s%5.1f", "物理:", score[i][j]);
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
//信息统计
void count(char name[][name_maxlength], char id[][id_maxlength], float score[][5], int n)
{
    int i, j, count;
    float sum, avg;
    //各科平均分
    printf("%66s\n%66s\n","------------","*各科平均分*");
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
            printf("高数：%.2f", avg);
            break;
        case 1:
            printf("英语：%.2f", avg);
            break;
        case 2:
            printf("C语言：%.2f", avg);
            break;
        case 3:
            printf("物理：%.2f", avg);
            break;
        }
    }
    printf("\n");
    line();
    //学生排序
    char name_copy[max_number][name_maxlength] = { 0 };
    char id_copy[max_number][id_maxlength];
    float score_copy[max_number][5];
    //复制原列表
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
    //学号排序
    printf("\n\n%65s\n%65s\n","----------","*学号升序*");
    line();
    sort_id(name_copy, id_copy, score_copy, n);
    printf("%15s%15s%15s%15s%15s%15s%15s\n", "姓名", "学号", "高数", "英语", "C语言", "物理", "平均分");
    for (i = 0; i < n; i++)
    {
        print_info(name_copy, id_copy, score_copy, i);
    }
    line();
    //成绩排序
    for (j = 0; j < 5; j++)
    {
        
        switch (j)
        {
        case 0:
            printf("\n\n%67s\n%67s\n", "--------------", "*高数成绩排名*");
            break;
        case 1:
            printf("\n\n%67s\n%67s\n", "--------------", "*英语成绩排名*");
            break;
        case 2:
            printf("\n\n%68s\n%68s\n", "----------------", "*C语言成绩排名*");
            break;
        case 3:
            printf("\n\n%67s\n%67s\n", "--------------", "*物理成绩排名*");
            break;
        case 4:
            printf("\n\n%67s\n%67s\n", "--------------", "*平均成绩排名*");
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
    //各科补考统计
    printf("\n\n%67s\n%67s\n", "--------------", "*各科补考统计*");
    line();
    for (j = 0; j < 4; j++)
    {
        count = 0;
        switch (j)
        {
        case 0:
            printf("高数补考名单：\n");
            break;
        case 1:
            printf("\n英语补考名单：\n");
            break;
        case 2:
            printf("\nC语言补考名单：\n");
            break;
        case 3:
            printf("\n物理补考名单：\n");
            break;
        }
        for (i = 0; i < n; i++)
        {
            if (score[i][j] < 60)
            {
                printf("  %s（%.1f）\n", name[i], score[i][j]);
                count++;
            }
        }
        printf("  共%d人\n", count);
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
        printf("查询");
        gotoxy(47, 14);
        printf("1:姓名查询  2:分数段查询");
        gotoxy(47, 16);
        printf("3:男女数据  Esc:返回上级菜单");
        run = getch();
        if (run == 27)
        {
            break;
        }
        clrscr();
        switch (run)
        {
        case '1':
            printf("请输入姓名：");
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
                printf("查无此人\n");
            }
            line();
            getchar();
            break;
        case '2':
            while (1)
            {
                window();
                gotoxy(57, 11);
                printf("查询科目");
                gotoxy(49, 14);
                printf("1:高数    2:英语");
                gotoxy(49, 15);
                printf("3:C语言   4:物理");
                gotoxy(49, 16);
                printf("5:平均分  Esc:返回上级菜单");
                sub = getch();
                if (sub == 27)
                {
                    break;
                }
                while (1)
                {
                    clrscr();
                    printf("请输入分数段：    -\n");
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
                        printf("起始值须大于结束值，请重新输入。");
                        getchar();
                    }
                }
                flag = 1;
                clrscr();
                switch (sub)
                {
                case '1':
                    printf("高数成绩在%.1f-%.1f\n", begin, end);
                    printf("%15s%15s%15s%15s%15s%15s%15s\n", "姓名", "学号", "高数", "英语", "C语言", "物理", "平均分");
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
                        printf("无\n");
                    }
                    break;
                case '2':
                    printf("英语成绩在%.1f-%.1f\n", begin, end);
                    printf("%15s%15s%15s%15s%15s%15s%15s\n", "姓名", "学号", "高数", "英语", "C语言", "物理", "平均分");
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
                        printf("无\n");
                    }
                    break;
                case '3':
                    printf("C语言成绩在%.1f-%.1f\n", begin, end);
                    printf("%15s%15s%15s%15s%15s%15s%15s\n", "姓名", "学号", "高数", "英语", "C语言", "物理", "平均分");
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
                        printf("无\n");
                    }
                    break;
                case '4':
                    printf("物理成绩在%.1f-%.1f\n", begin, end);
                    printf("%15s%15s%15s%15s%15s%15s%15s\n", "姓名", "学号", "高数", "英语", "C语言", "物理", "平均分");
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
                        printf("无\n");
                    }
                    break;
                case '5':
                    printf("平均分在%.2f-%.2f\n", begin, end);
                    printf("%15s%15s%15s%15s%15s%15s%15s\n", "姓名", "学号", "高数", "英语", "C语言", "物理", "平均分");
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
                        printf("无\n");
                    }

                    break;
                }
                line();
                getchar();
                getchar();
            }
            break;
        case '3':
            printf("%62s\n%62s\n", "----", "*男*");
            line();
            printf("%15s%15s%15s%15s%15s%15s%15s\n", "姓名", "学号", "高数", "英语", "C语言", "物理", "平均分");
            for (i = 0; i < n; i++)
            {
                if (!strcmp(sex[i], "男\0"))
                {
                    print_info(name, id, score, i);
                }
            }
            line();
            printf("\n\n%62s\n%62s\n", "----", "*女*");
            line();
            printf("%15s%15s%15s%15s%15s%15s%15s\n", "姓名", "学号", "高数", "英语", "C语言", "物理", "平均分");
            for (i = 0; i < n; i++)
            {
                if (!strcmp(sex[i], "女\0"))
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
    //进入系统前的密码保护
    for (i = 2; i >=0; i--)
    {
        window();
        gotoxy(52, 11);
        printf("学生管理系统 %s", version);
        gotoxy(54, 14);
        printf("用户名：admin");
        gotoxy(62, 17);
        printf("by JNU.伍家栋");
        gotoxy(54, 15);
        printf("密码：");
        get_password(password);
        clrscr();
        if (!strcmp(password, correct_password))
        {
            window();
            gotoxy(48, 14);
            printf("密码正确,即将进入系统！");
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
                printf("密码错误,还有%d次机会", i);
                getchar();
            }
            else
            {
                window();
                gotoxy(52, 13);
                printf("已连续输错三次密码");
                gotoxy(50, 14);
                printf("1小时内禁止登录此系统！\n\n\n\n\n");
                exit(0);
            }
        }
    }
    while (1)
    {
        window();
        gotoxy(52, 11);
        printf("学生管理系统 %s", version);
        gotoxy(50, 14);
        printf("1:信息输入  2:信息显示");
        gotoxy(50, 16);
        printf("3:信息统计  4:信息查询");
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
                printf("录入成功");
                gotoxy(54, 14);
                printf("按回车键继续");
                gotoxy(52, 15);
                printf("按Esc键返回主菜单");
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