#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

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


int main() {
	int num,time,input_num;
	double start, end,taken_time;
	while (1) {
		printf("정확하게 입력하시오.\n");
		time = RandomTime();
		num = RandomNum();
		Sleep(time*1000);
		printf("%d\n", num);
		start = (double)clock()/1000;
		scanf_s("%d", &input_num);
		end = (double)clock()/1000;
		taken_time = end - start;
		printf("걸린 시간 : %.3f\n\n", taken_time);
		if (input_num == num) {
			if (taken_time < 1) {
				printf("A\n\n");
			}
			else if (1<= taken_time && taken_time < 1.5) {
				printf("B\n\n");
			}
			else {
				printf("C\n\n");
			}
		}
		else {
			printf("D\n\n");
		}
	}
}
