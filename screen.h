#include <windows.h>
#include <time.h>
#include <conio.h>

void sleep(unsigned int mseconds) {
    clock_t goal = mseconds + clock();
    while(goal > clock());
}

void setTextColor(int textColor, int backColor) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int colorAttribute = backColor << 4 | textColor;
	SetConsoleTextAttribute(consoleHandle, colorAttribute);
}

void clearScreen() {
	system("cls");
}

void PrintTheMap(struct board GameMap) {
	setTextColor(15, 0);
    int i, j, n = GameMap.n, m = GameMap.m;
    int left, up, play;
    clearScreen();
    printf("player one has %d wall(s) left and player 2(or computer) has %d walls left\n", GameMap.p1w, GameMap.p2w);
    printf("This is the Map(O stands for player 1 and X stands for player 2): \n");
    setTextColor(11, 0);
    printf("    ");
    for(i = 0; i < m; i++){
        if(i / 10 == 0)
            printf("  %d ", i);
        else
            printf(" %d ", i);
    }
    printf("\n");
    setTextColor(1, 0);
    for (i = 0; i < n + 1; i++) {
        for (j = 0; j < m + 1; j++) {
            if (j == m) continue;
            left = GameMap.Map[i][j] / 100;
            up = (GameMap.Map[i][j] / 10) % 10;
            play = GameMap.Map[i][j] % 10;
            if (up == 1){
                if(j==0){
                    printf("    ....");
                }
                else{
                    printf("....");
                }
            }
            else {
    			setTextColor(4, 0);
				if(j==0){
                    printf("    ====");
                }
                else{
                    printf("====");
                }
				setTextColor(1, 0);
			}
        }
        printf(".");
        printf("\n");
        for (j = 0; j < m + 1; j++) {
        	if (i == n) break;
            left = GameMap.Map[i][j] / 100;
            up = (GameMap.Map[i][j] / 10) % 10;
            play = GameMap.Map[i][j] % 10;
            if (left == 1){
                if(j==0){
                    setTextColor(11,0);
                    if(i/10 == 0)
                        printf(" %d  ",i);
                    else
                        printf(" %d ",i);
                    setTextColor(1,0);
                }
                printf(":");
            }
            else {
				if(j==0){
                    setTextColor(11, 0);
                    if(i/10 == 0)
                        printf(" %d  ",i);
                    else
                        printf(" %d ",i);
                    setTextColor(4, 0);
                    printf("|");
				}
                else
                {
                    setTextColor(4, 0);
                    printf("|");
                }
				setTextColor(1, 0);
			}
            if (!play) printf("   ");
            else if (play == 1) {
            	setTextColor(2, 0);
				printf(" O ");
				setTextColor(1, 0);
			}
            else {
            	setTextColor(14, 0);
				printf(" X ");
				setTextColor(1, 0);
			}
        }
        printf("\n");
    }
}
