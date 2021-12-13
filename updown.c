#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <ctype.h>

#define MAX 100
extern int total;
extern int cur;
extern int game;
extern int re;
extern int betcoin;
int rannum = 0;
int cnt = 0;

void reward(int bet)
{
	if (cnt == 1)
	{
		total = cur + (bet * 100);
		printf("%d 코인 획득\n", bet * 100);
	}
	else if (cnt == 2)
	{
		total = cur + (bet * 20);
		printf("%d 코인 획득\n", bet * 20);
	}
	else if (cnt == 3)
	{
		total = cur + (bet * 10);
		printf("%d 코인 획득\n", bet * 10);
	}
	else if (cnt == 4)
	{
		total = cur + (bet * 5);
		printf("%d 코인 획득\n", bet * 5);
	}
	else if (cnt == 5)
	{
		total = cur + (bet * 3);
		printf("%d 코인 획득\n", (bet * 3));
	}
	else if (cnt == 6)
	{
		total = cur + (bet * 2);
		printf("%d 코인 획득\n", (bet * 2));
	}
	else if (cnt == 7)
	{
		total = cur + (bet * 1.5);
		printf("%.0f 코인 획득\n", (bet * 1.5));
	}
	else
	{
		total = cur;
		printf("코인을 잃었습니다.\n");
	}
	printf("--------------\n");
}

void rule_updown()
{
	if (cnt == 0)
	{
		system("cls");
		printf("\b\n<업다운 게임>\n\n");
		printf("규칙 : 1.게임머니를 배팅\n");
		printf("       2.1~100 사이의 숫자를 입력\n");
		printf("       3.입력한 숫자가 정답보다 작으면 up, 크면 down이 출력된다.\n");
		printf("       4.1회 100배, 2회 20배, 3회 10배, 4회 5배, 5회 3배, 6회 2배, 7회 1.5배 획득, 8회 이상은 모두 잃음\n");
		printf("       5.종료하려면 exit 입력\n");
		printf("----------------------------------------------------------------------\n");
		return;
	}
}

void count()
{
	cnt++;
	printf("시도 횟수 : %d\n", cnt);
}

int updown(int coin)
{
	char input[MAX];
	int num[MAX];
	int number = 0;
	int bet = 0;
	int j = 0;

	cnt = 0;
	total = coin;

	srand((unsigned)time(NULL));
	rannum = (rand() % 100) + 1;

	while (1)
	{
		rule_updown();
		if (cnt == 0 && re == 0)
		{
			betcoin = betting(total);
			if (betcoin == -1)
				break;
			cur = total - betcoin;
		}
		re = 0;
		printf("숫자 입력\n");
		scanf("%s", input);

		if (strcmp(input, "exit") == 0)
		{
			cnt = 0;
			break;
		}

		number = atoi(&input);
		num[cnt] = number;

		if (rannum > number && number > 0)
		{
			printf(">up\n");
			count();
			printf("----------------\n");
		}
		else if (rannum < number && number <= 100)
		{
			printf(">down\n");
			count();
			printf("----------------\n");
		}
		else if (rannum == number)
		{
			srand((unsigned int)time(NULL));
			rannum = (rand() % 100) + 1;
			printf("정답\n");
			count();
			printf("--------------\n");
			reward(betcoin);
			if (total <= 0)
			{
				total = 0;
				broke();
				break;
			}
			retry();
			cnt = 0;
			re = 0;
			system("cls");
		}
		else if (number <= 0 || number > 100)
		{
			re = 1;
			if (cnt == 0)
			{
				printf("1~100 사이의 숫자를 입력하세요.\n");
				printf("----------------\n");
				printf("보유 코인 : %d\n", total);
				printf("배팅할 코인을 입력하세요 : %d", betcoin);
				printf("----------------\n");
			}
			else if (cnt >= 1)
			{
				j = cnt;
				cnt = 0;
				rule_updown();
				cnt = j;
				printf("1~100 사이의 숫자를 입력하세요.\n");
				printf("----------------\n");
				for (int i = 0; i < cnt; i++)
				{
					if (num[i] > rannum && num[i] <= 100)
					{
						printf("%d\n", num[i]);
						printf(">down\n");
						printf("시도 횟수 : %d\n", i + 1);
						printf("----------------\n");
					}
					else if (num[i] < rannum && num[i] > 0)
					{
						printf("%d\n", num[i]);
						printf(">up\n");
						printf("시도 횟수 : %d\n", i + 1);
						printf("----------------\n");
					}
				}
			}
		}
		if (total <= 0) {
			total = 0;
			broke();
			break;
		}
	}
	return total;
}
