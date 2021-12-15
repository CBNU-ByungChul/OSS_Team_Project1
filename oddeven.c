#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include <ctype.h>
#include <windows.h>

#define MAX 100
int total = 0;
int cur = 0;
int re = 0;
int betcoin = 0;
extern int cnt;
extern int game;

void rule_oddeven()
{
	if (cnt == 0)
	{
		printf("\b\n<홀짝 게임>\n\n");
		printf("규칙 : 1.게임머니를 배팅\n");
		printf("       2.홀수와 짝수를 골라 맞추면 2배 획득, 틀리면 모두 잃는다.\n");
		printf("       3.종료하려면 exit 입력\n");
		printf("----------------------------------------------------------------------\n");
		cnt++;
		return;
	}
	else if (cnt == 1 && re == 0)
	{
		printf("홀/짝 입력\n");
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

void retry()
{
	system("pause");
}

void broke()
{
	printf("남은 코인이 없습니다.\n");
	system("pause");
}

int betting(int coin)
{
	char bet[MAX];
	int bett = 0;

	printf("보유 코인 : %d\n", total);
	printf("배팅할 코인을 입력하세요 : ");
	scanf("%s", bet);

	if (strcmp(bet, "exit") == 0)
	{
		return -1;
	}

	printf("----------------\n");

	bett = atoi(&bet[0]);

	while (bett <= 0 || bett > coin || isdigit(bet[0]) == 0)
	{
		system("cls");
		if (game == 1)
		{
			cnt = 0;
			rule_oddeven();
		}
		else if (game == 2)
		{
			cnt = 0;
			rule_updown();
		}

		printf("보유한 코인 내에서 입력하세요.\n\n");
		printf("보유 코인 : %d\n", total);
		printf("배팅할 코인을 입력하세요 : ");
		scanf("%s", bet);
		if (strcmp(bet, "exit") == 0)
		{
			return -1;
		}
		printf("----------------\n");

		bett = atoi(&bet[0]);
	}
	return bett;
}

void odd(int coin)
{
	srand((unsigned int)time(NULL));
	int number = rand() % 10 + 1;

	if (number % 2 != 0)
	{
		printf("%d, 홀 정답\n", number);
		printf("----------------\n");
		printf("%d 코인 획득\n", coin * 2);
		printf("----------------\n\n");
		total = cur + (coin * 2);
		cur = total;
	}
	else
	{
		printf("%d, 짝 오답\n", number);
		printf("----------------\n");
		printf("코인을 잃었습니다.\n");
		printf("----------------\n\n");
		total = cur;
	}
}

void even(int coin)
{
	srand((unsigned int)time(NULL));
	int number = rand() % 10 + 1;

	if (number % 2 == 0)
	{
		printf("%d, 짝 정답\n", number);
		printf("----------------\n");
		printf("%d 코인 획득\n", coin * 2);
		printf("----------------\n\n");
		total = cur + (coin * 2);
		cur = total;
	}
	else
	{
		printf("%d, 홀 오답\n", number);
		printf("----------------\n");
		printf("코인을 잃었습니다.\n");
		printf("----------------\n\n");
		total = cur;
	}
}

int oddeven(int coin)
{
	char input[MAX];
	cnt = 0;
	total = coin;

	while (1)
	{
		system("cls");
		rule_oddeven();

		if (re == 0)
		{
			betcoin = betting(coin);
			if (betcoin == -1)
				break;
			cur = total - betcoin;
		}

		rule_oddeven();
		scanf("%s", input);

		if (strcmp(input, "홀") == 0)
		{
			odd(betcoin);
			if (total <= 0)
			{
				total = 0;
				broke();
				break;
			}
			retry();
		}
		else if (strcmp(input, "짝") == 0)
		{
			even(betcoin);
			if (total <= 0)
			{
				total = 0;
				broke();
				break;
			}
			retry();
		}
		else if (strcmp(input, "exit") == 0)
		{
			break;
		}
		else
		{
			cnt = 0;
			re = 1;
			oddeven(coin);
		}
		cnt = 0;
		re = 0;
		coin = total;
		if (total <= 0)
		{
			total = 0;
			broke();
			break;
		}
	}
	
	return total;
}
