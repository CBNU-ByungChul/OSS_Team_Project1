#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

struct profile {
	char name[100];
	int money;
};

int countline() {
	int count = 0;
	char temp;
	FILE* fp;
	fp = fopen("data.txt", "r");
	if (fp == NULL) {
		printf("ERROR");
	}
	while (fscanf(fp, "%c", &temp) != EOF) {
		if (temp == '\n') {
			count++;
		}
	}
	return count;
}

int compare_profile(int count,char name[]) {
	struct profile p[1000];
	int temp=0;
	FILE* fp;
	fp = fopen("data.txt", "r");
	if (fp == NULL) {
		printf("ERROR");
	}
	for (int i = 0; i < count; i++) {
		fscanf(fp, "%s %d", &p[i].name, &p[i].money);
		if (!strcmp(p[i].name, name)) {
			temp = 1;
			printf("\n\n---프로필 불러오기 성공---\n\n");
			return p[i].money;
		}
	}
	if (temp == 0) {
		printf("\n\n---프로필이 없음---\n\n");
		printf("\n\n---프로필 생성 중---\n\n");
		return -1000;
	}
}

void write_profile(char name[]) {
	FILE* fp;
	fp = fopen("data.txt", "a");
	fprintf(fp, "%s %d\n", name, 10000);
	printf("\n\n---프로필 생성 완료---\n\n");
}

int main() {
	char name[1000];
	int money = 0;
	struct profile p[1000];
	int count = countline();
	printf("이름을 입력하세요 : ");
	scanf("%s", name);
	money=compare_profile(count,name);
	if (money == -1000) {
		write_profile(name);
		printf("\n\n기본 게임머니 : %d\n\n", 10000);
	}
	else {
		printf("\n\n현재 남은 게임머니 : %d\n\n", money);
	}
}
