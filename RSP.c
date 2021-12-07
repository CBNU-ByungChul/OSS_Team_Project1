#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int user;
    int com;
    srand((unsigned)time(NULL));
    while (1)
    {
        com = rand() % 3 + 1;
        printf(" -- / 1 : 가위  / 2 : 바위 / 3 : 보 / -- \n");
        scanf_s("%d", &user);
        if (user == com)
        {
            printf("컴퓨터의 선택 : %d\n", com);
            printf("컴퓨터와 비겼습니다. 재경기를 진행합니다.\n");
        }
        else
            break;
    }
        if ((user == 1 && com == 2) || (user == 2 && com == 3) || (user == 3 && com == 1))
        {
            printf("컴퓨터의 선택 : %d\n", com);
            printf("패배하셨습니다.\n");
        }  
        else
        {
            printf("컴퓨터의 선택 : %d\n", com);
            printf("승리하셨습니다.\n");
        }
    return 0;
}
