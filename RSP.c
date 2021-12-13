#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern int total;
extern int cur;
extern int cnt;
extern int game;
extern int re;
extern int betcoin;

void rule_rcp()
{
    if (cnt == 0)
    {
        printf("\b\n<가위바위보 게임>\n\n");
        printf("규칙 : 1.게임머니를 배팅\n");
        printf("       2.가위바위보 진행\n");
        printf("       3.이기면 2배, 비기면 재경기, 지면 잃음\n");
        printf("       4.종료하려면 exit 입력\n");
        printf("----------------------------------------------------------------------\n");
        cnt++;
        return;
    }
    else if (cnt == 1 && re == 0)
    {
        printf(" -- / 1 : 가위  / 2 : 바위 / 3 : 보 / --  입력\n");
        printf("종료 하려면 exit\n");
        printf("----------------\n");
        return;
    }
    else
    {
        re = 0;
        printf("보유 코인 : %d\n", total);
        printf("배팅할 코인을 입력하세요 : %d\n", total - cur);
        rule_oddeven();
        printf("정확하게 입력하세요.\n");
    }
}

int rcp(int coin)
{
    char input[100];
    int user = 0;
    int com;
    srand((unsigned)time(NULL));
    cnt = 0;
    total = coin;
    while (1)
    {
        system("cls");
        rule_rcp();
        if (re == 0)
        {
            betcoin = betting(coin);
            if (betcoin == -1)
                break;
            cur = total - betcoin;
        }
        
        com = rand() % 3 + 1;
        printf(" -- / 1 : 가위  / 2 : 바위 / 3 : 보 / -- \n");
        scanf("%s", input);
        user = atoi(&input);
        if (strcmp(input, "exit") == 0)
            break;
        if (user == com)
        {
            printf("컴퓨터의 선택 : %d\n", com);
            printf("컴퓨터와 비겼습니다. 재경기를 진행합니다.\n");
            retry();
        }
       else if ((user == 1 && com == 2) || (user == 2 && com == 3) || (user == 3 && com == 1))
        {
            printf("컴퓨터의 선택 : %d\n", com);
            printf("패배하셨습니다.\n");
            total = cur;
            retry();
        }
        else if ((user == 1 && com == 3) || (user == 2 && com == 1) || (user == 3 && com == 2))
        {
            printf("컴퓨터의 선택 : %d\n", com);
            printf("승리하셨습니다.\n");
            total = cur + betcoin * 2;
            printf("%d 코인 획득\n", betcoin * 2);
            retry();
        }
        cnt = 0;
    }        
    return total;
}
