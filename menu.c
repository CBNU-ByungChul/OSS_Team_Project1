#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

int coin;
int game = 0;
int count4profile = 0;

void menu()
{
   printf("--------------\n");
   printf("보유 코인 : %d\n", coin);
   printf("--------------\n");
   printf("1. 홀짝 게임\n");
   printf("2. 업다운 게임\n");
   printf("3. 랜덤 타이밍 게임\n");
   printf("4. 가위바위보 게임\n");
   printf("5. 묵찌빠 게임\n");
   printf("6. 종료\n");
   printf("--------------\n\n");
}

void gotoxy(int x, int y) { 
   COORD pos = { 2 * x,y };
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void title() {
   int x = 5;
   int y = 4;  
   int cnt; 
   gotoxy(x, y + 0); printf("■■■■■■■■■■■■■■■"); Sleep(100);
   gotoxy(x, y + 1); printf("■□□□□□□□□□□□□□■"); Sleep(100);
   gotoxy(x, y + 2); printf("■□                      □■"); Sleep(100);
   gotoxy(x, y + 3); printf("■□                      □■"); Sleep(100);
   gotoxy(x, y + 4); printf("■□□□□□□□□□□□□□■"); Sleep(100);
   gotoxy(x, y + 5); printf("■■■■■■■■■■■■■■■"); Sleep(100);
   gotoxy(x + 5, y + 2); printf("S I M P L E"); Sleep(100);
   gotoxy(x + 5, y + 3); printf(" G A M E S "); Sleep(100);
   gotoxy(x, y + 9);
}

int main()
{
   int sel = 0;
   int sel2 = 0;
   int a = 0;

   while (sel != 6)
   {
      if (count4profile == 0) {
         count4profile++;
         title();
         coin = profile();
      }
      system("cls");
      menu();
      scanf("%d", &sel);

      switch (sel)
      {
      case 1:
         game = 1;
         coin = oddeven(coin);
         break;
      case 2:
         game = 2;
         coin = updown(coin);
         break;
      case 3:
         game = 3;
         coin = randomtiming(coin);
         break;
      case 4:
         game = 4;
         coin = rcp(coin);
         break;
      case 5:
         game = 5;
         coin = MJB_game(coin);
         break;
      }
      if (coin <= 0)
      {
         system("cls");
         printf("--------------\n");
         printf("코인이 없습니다.\n"); 
         printf("다시 10000코인을 지급합니다\n");
         printf("--------------\n");
         system("pause");
         coin = 10000;
         a = 0;
      }
   }
   system("copy data.txt temp.txt");
   save_profile(coin);
   return 0;
}
