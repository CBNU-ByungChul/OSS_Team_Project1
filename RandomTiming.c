#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

extern int total;
extern int cur;
extern int cnt;
extern int game;
extern int re;
extern int betcoin;

void rule_randomtiming()
{
	if (cnt == 0)
	{
		printf("\b\n<랜덤 타이밍 게임>\n\n");
		printf("규칙 : 1.게임머니를 배팅\n");
		printf("       2.1~10초 사이에 나타나는 숫자를 정확하게 입력.\n");
		printf("       3.1초 안에 입력 시 1.5배, 1~1.5초 1.2배, 1.5~2초 원금, 2초~ 실패\n");
		printf("       4.종료하려면 exit 입력\n");
		printf("----------------------------------------------------------------------\n");
		cnt++;
		return;
	}
	else if (cnt == 1 && re == 0)
	{
		printf("정확하게 입력하시오.\n");
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

int RandomNum() {
	srand((unsigned int)time(NULL));
	int randn = 0;
	randn = rand() % 101;
	if (randn == 0) RandomNum();
	else return randn;
}

int RandomTime() {
	srand((unsigned int)time(NULL));
	int randtm = 0;
	randtm = rand() % 6;
	if (randtm == 0) RandomTime();
	else return randtm;
}


int randomtiming(int coin) {
	int num,time,input_num=0;
	double start, end,taken_time;
	cnt = 0;
	total = coin;
	
	while (1) {
		system("cls");
		rule_randomtiming();

		if (re == 0)
		{
			betcoin = betting(coin);
			if (betcoin == -1)
				break;
			cur = total - betcoin;
		}
		
		while (cnt == 1)
		{
			printf("정확하게 입력하시오.\n");

			time = RandomTime();
			num = RandomNum();
			Sleep(time * 1000);
			printf("%d\n", num);

			start = (double)clock() / 1000;
			scanf_s("%d", &input_num);
			end = (double)clock() / 1000;
			taken_time = end - start;

			printf("걸린 시간 : %.3f\n\n", taken_time);

			if (input_num == num) {
				if (taken_time < 1) {
					printf("A\n\n");
					total = cur + betcoin * 1.5;
					printf("%.0f 코인 획득\n\n", betcoin * 1.5);
				}
				else if (1 <= taken_time && taken_time < 1.5) {
					printf("B\n\n");
					total = cur + betcoin * 1.2;
					printf("%.0f 코인 획득\n\n", betcoin * 1.2);
				}
				else {
					printf("C\n\n");
					printf("%d 코인 획득\n\n", betcoin);
				}
			}
			else {
				printf("D\n\n");
				total = cur;
				printf("%d 코인 상실\n\n", betcoin);
			}
			retry();
			cnt = 0;
		}
	}
	return total;
}
