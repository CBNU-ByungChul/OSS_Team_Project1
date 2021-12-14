#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int what_line = 0;
char name[1000];
int countline2=0;

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
   countline2 = count;
   return count;
}

int compare_profile(int count, char name[]) {
   struct profile p[1000];
   int temp = 0;
   FILE* fp;
   fp = fopen("data.txt", "r");
   if (fp == NULL) {
      printf("ERROR");
   }
   for (int i = 0;i < count; i++) {
      fscanf(fp, "%s %d", &p[i].name, &p[i].money);
      if (!strcmp(p[i].name, name)) {
         temp = 1;
         what_line = i;
         return p[i].money;
      }
   }
   if (temp == 0) {
      printf("          프로필이 없습니다.\n");
      printf("          프로필을 생성합니다.\n");
      return -10000;
   }
}

void write_profile(char name[],int count) {
   FILE* fp;
   fp = fopen("data.txt", "a");
   fprintf(fp, "%s %d\n", name, 10000);
   fclose(fp);
}

int profile() {
   int money = 0;
   struct profile p[1000];
   int count = countline();
   printf("이름을 입력하세요 : ");
   scanf("%s", name);
   money = compare_profile(count, name);
   if (money == -10000) {
      write_profile(name,count);
      money = 10000;
      printf("          기본 게임머니 : %d\n\n\n", money);
      system("pause");
   }
   else {
      printf("          현재 남은 게임머니 : %d\n\n\n", money);
      system("pause");
   }
   return money;
}

void save_profile(int coin) {
   struct profile p[1000];
   int i = 0;
   FILE* fp;
   FILE* fp2;
   fp = fopen("data.txt", "w");
   fp2 = fopen("temp.txt", "r");
   for (i = 0; i < countline2; i++) {
      fscanf(fp2, "%s %d", &p[i].name, &p[i].money);
      if (strcmp(name, p[i].name)==0) {
         continue;
      }else{
         fprintf(fp,"%s %d\n", p[i].name, p[i].money);
      }
   }
   fprintf(fp,"%s %d\n", name, coin);
   fclose(fp, fp2);
   FILE* fp1;
   fp1 = fopen("temp.txt", "w");
}
