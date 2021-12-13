#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
int init(int, int);                 // 묵찌빠 동작함수 
int battle(int, int);               // 가위바위보 실행함수
int ComSelect();                    // 컴퓨터의 난수생성함수
int MJBbetting(int);
void RuleMJB();
void printfRes(int, int);
int Exit();                         // 종료명령호출 함수
extern int total;
int count4mjb = 0;


int MJB_game(int coin)
{
    int user, com;
    int result;                     // 최종결과, 유저가 이기면 7 지면 8 저장
    int mgbcount = 0;                  // 게임진행 횟수 저장
    int cur = 0;
    char exit[100];
    int winloss[2] = { 0, };        // winloss[0]에는 유저의 패배수, winloss[1] 유저의 승리수 저장
    int bettcoin = 0;
    int reward = 0;
    total = coin;

    user = 7;
    com = 8;


    while (1)
    {

        RuleMJB();
        cur = coin;
        //printf("현재 보유중인 코인: %d\n", coin);
        scanf("%s", exit);
        if (strcmp(exit,"exit")==0)
        {
            return total;
        }
        else
        {
            total = coin;
            bettcoin = MJBbetting(total);
            if (bettcoin == -1)
                return total;
            system("pause");
            mgbcount++;                     //게임 횟수 카운트
            result = init(user, com);
            if (result == 7)             //result 값이 7 혹은 8이면 승패출력 후 init함수 진입
            {
                system("pause");
                winloss[1]++;
 //               
                reward = 0.5 * bettcoin;
                printf("user가 승리했습니다 + 1승! ");
                printf("현재 %d전 %d승 %d패\n", mgbcount, winloss[1], winloss[0]);
                printf("코인 득실: +%d\n", reward);
                total = (cur + reward);
                coin = total;
                system("pause");
            }
            else if (result == 8)
            {
                system("pause");
                winloss[0]++;
//              
                reward = -0.5* bettcoin;
                printf("com이 승리했습니다 + 1패");
                printf("현재 %d전 %d승 %d패\n", mgbcount, winloss[1], winloss[0]);
                printf("코인 득실: %d\n", reward);
                total = (cur + reward);
                coin = total;
                system("pause");
            }
            if (total <= 0) {
                total = 0;
                break;
            }
            int MJB_game(int coin);              // 사용자가 종료명령어 입력하전까지 반복
        }



    }
}
int init(int user, int com)
{
    int KO = 0;                         // KO의 값에 따라 init함수, battle함수로 이동을 결정
    int res;                            // 유저의 가위바위보 결과를 저장   0 =  짐, 1 = 비김, 2 = 이김
    int userSelect, comSelect;          // 유저, 컴퓨터의 가위바위보 선택저장
    int exit = 1;                       // exit 값이 0이면 종료함수 호출
    char input[100];
    
    system("cls");

    printf("묵찌빠를 시작합니다! \n이긴쪽이 공격권을 갖고 비기면 가위바위보가 다시 진행됩니다!\n");
    printf("---------------------------------\n");
    printf("가위 ----- 1입력\n바위 ----- 2입력\n보 ------- 3입력\n");

    scanf("%s", input);                          // 1~3중에서 유저의 선택 저장
    userSelect = atoi(&input);
    while (userSelect != 1 && userSelect != 2 && userSelect != 3)
    {
        system("cls");
        printf("1~3 입력\n");
        scanf("%s", input);
        userSelect = atoi(&input);
        if (userSelect == 1 && userSelect == 2 && userSelect == 3)
            break;
    }
    
    comSelect = ComSelect();                            // 1~3에서의 난수 추출뒤 저장
    printfRes(userSelect, comSelect);
    if (comSelect == userSelect)                        // 가위바위보의 경우에 따라 res에 값 저장
                                                        // 0 =  짐, 1 = 비김, 2 = 이김
                                                        //가위바위보 로직 가위 = 1 바위 = 2 보 = 3
                                                        //비기는 경우는 (1,1) (2,2) (3,3) 이기 때문에 comSelect, userSelect 서로 같은 경우
                                                        //유저가 이기는 경우는 (3,2) (2,1) (1,3) 이기에 컴>(유저+1)%3으로 표현 가능
        res = 1;

    else if ((comSelect == 3) && (userSelect == 2))     // 사용자 2(바위) 컴퓨터 3(보) 일 경우 3>3%3이 참이므로  사용자가 패배했음에도 
                                                        //res = 2 즉 승리했다고 출력되는 것을 확인 위쪽에 이 경우를 대비한 코드 추가
        res = 0;
    else if (comSelect > (userSelect + 1) % 3)
        res = 2;
    else if ((comSelect == 2) && (userSelect == 1))
        res = 0;
    else if ((comSelect == 1) && (userSelect == 3))
        res = 0;



    switch (res) {
    case 1:                                                      // 비겼으므로 init 함수 호출

        printf("비겼습니다! 아무키나 누르면 가위바위보를 다시 진행합니다!\n");
        system("pause");
        KO = init(user, com);
        break;
    case 2:                                                    // 승패가 났으므로 battle 함수 호출
        printf("이겼습니다! 공격하세요!\n");
        KO = battle(user, com);
        break;
    case 0:
        printf("졌습니다! 방어하세요!\n");                     // 승패가 났으므로 battle 함수 호출
        KO = battle(com, user);
        break;
    }

    return KO;
}
//}

int battle(int winner, int loser) {
    int KO = 0;                                                     // 결과에 따라 battle함수를 호출할지 승자값을 반환할지 결정
    int res;                                                        // 유저의 가위바위보 결과를 저장 0 =  짐, 1 = 비김, 2 = 이김
    int winnerSelect;
    int loserSelect;
    printf("---------------------------------\n");
    printf("가위 ----- 1입력\n바위 ----- 2입력\n보 ------- 3입력\n");

    if (winner == 7) {                                             // 승패자가 누구냐에 따라 winner, loserSelect에 값 대응
        scanf("%d", &winnerSelect);
        loserSelect = ComSelect();
        printfRes(winnerSelect, loserSelect);
    }
    else {
        scanf("%d", &loserSelect);
        winnerSelect = ComSelect();
        printfRes(loserSelect, winnerSelect);
    }
    if (winnerSelect == loserSelect)
        res = 1;
    else if ((loserSelect == 3) && (winnerSelect == 2))
    {
        res = 0;
    }
    else if (loserSelect > (winnerSelect + 1) % 3)
        res = 2;
    else
        res = 0;

    switch (res) {
    case 2:
        printf("%s가 가위바위보를 이겼습니다 공격권을 유지합니다!\n", winner == 7 ? "user" : "컴퓨터");
        KO = battle(winner, loser);                         //승패 결정나지 않음, battle함수 호출
        break;
    case 0:
        printf("%s가 가위바위보를 졌습니다 공격권을 빼앗깁니다!\n", winner == 7 ? "user" : "컴퓨터");
        KO = battle(loser, winner);
        break;                                             //승패 결정나지 않음, loser, winner 위치를 교환하여 battle 함수에 대입
    case 1:
        printf("묵찌빠가 끝났습니다 승자를 확인할까요?\n");
        return winner;                                     // 승패 결정남. winner 값반환
        break;
    }

}

int ComSelect() {                                           //컴퓨터의 난수생성함수
    int randomSelect;

    srand(time(NULL));
    randomSelect = rand() % 3 + 1;

    return randomSelect;
}
void printfRes(int userSelect, int comSelect) {
    printf("---------------결과--------------\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    printf("\n사용자는 %s를 냈습니다\n\n", (userSelect == 1 ? "\n□□□□■■□■■□\n□□□□■■□■■□\n□□□□■■□■■□\n□□□□■■□■■□\n□□□□■■□■■□\n□□■■■■■■■□\n□■■■■■■■■□\n□■■■■■■■■□\n□■■■■■■■■□\n□□■■■■■■■□" : userSelect == 2 ? "\n□□□□□□□□□□\n□□□□□□□□□□\n□□□□□□□□□□\n□□□□□□□□□□\n□□■■■■■■■□\n□■■■■■■■■□\n□■■■■■■■■□\n□■■■■■■■■□\n□■■■■■■■■□\n□□■■■■■■■□" : "\n□□■■□■■□■□\n□□■■□■■□■□\n□□■■□■■□■□\n□□■■□■■□■□\n■□■■■■■■■□\n■■■■■■■■■□\n■■■■■■■■■□\n■■■■■■■■■□\n□■■■■■■■■□\n□□■■■■■■■□"));
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    printf("\n컴퓨터는 %s를냈습니다\n\n", (comSelect == 1 ? "\n□□□□■■□■■□\n□□□□■■□■■□\n□□□□■■□■■□\n□□□□■■□■■□\n□□□□■■□■■□\n□□■■■■■■■□\n□■■■■■■■■□\n□■■■■■■■■□\n□■■■■■■■■□\n□□■■■■■■■□" : comSelect == 2 ? "\n□□□□□□□□□□\n□□□□□□□□□□\n□□□□□□□□□□\n□□□□□□□□□□\n□□■■■■■■■□\n□■■■■■■■■□\n□■■■■■■■■□\n□■■■■■■■■□\n□■■■■■■■■□\n□□■■■■■■■□" : "\n□□■■□■■□■□\n□□■■□■■□■□\n□□■■□■■□■□\n□□■■□■■□■□\n■□■■■■■■■□\n■■■■■■■■■□\n■■■■■■■■■□\n■■■■■■■■■□\n□■■■■■■■■□\n□□■■■■■■■□"));
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void RuleMJB()
{
    system("cls");
    printf("묵찌빠 게임에 오신 것을  환영합니다!\n");
    printf("게임을 시작하기 전에 베팅금액을 입력하고\n");
    printf("승리하면 1.5배의 패배하면 0.5만큼의 코인을 반환 받게됩니다\n");
    printf("\n게임 시작 ----- 아무거나 입력\n게임 종료 ----- exit입력\n");
}
int MJBbetting(int total)
{
    int bettcoin = 0;
    system("cls");
    bettcoin = betting(total);

    return bettcoin;
}
