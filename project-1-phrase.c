#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

struct board{
    int n, m;
    int Map[100][100];
    int p1x, p1y, p2x, p2y;
    int p1w, p2w;
};

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
    int i, j, sw, n = GameMap.n, m = GameMap.m;
    int left, up, play;
    clearScreen();
    printf("This is the Map(O stands for player 1 and X stands for player 2): \n");
    setTextColor(1, 0);
    for (i = 0; i < n + 1; i++) {
        for (j = 0; j < m + 1; j++) {
            if (j == m) continue;
            left = GameMap.Map[i][j] / 100;
            up = (GameMap.Map[i][j] / 10) % 10;
            play = GameMap.Map[i][j] % 10;
            if (up == 1) printf("....");
            else {
    			setTextColor(4, 0);
				printf("====");
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
            if (left == 1) printf(":");
            else {
            	setTextColor(4, 0);
				printf("|");
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

int main() {
    int n, m, i, j;
    printf("Please enter the size of the map: \n");
    scanf("%d", &n);
    struct board gameMap;
    int x1, y1, x2, y2;
    m = n, gameMap.n = n, gameMap.m = m;
    do {
    	printf("please enter the location of the first player: \n");
    	scanf("%d %d", &gameMap.p1x, &gameMap.p1y);
    	if(!(0 <= gameMap.p1x && gameMap.p1x < gameMap.n && 0 <= gameMap.p1y && gameMap.p1y < gameMap.m)) printf("invalid input! try again: \n");
    	
	} while(!(0 <= gameMap.p1x && gameMap.p1x < gameMap.n && 0 <= gameMap.p1y && gameMap.p1y < gameMap.m));
	do {
    	printf("please enter the location of the second player: \n");
    	scanf("%d %d", &gameMap.p2x, &gameMap.p2y);
    	if (!(0 <= gameMap.p2x && gameMap.p2x < gameMap.n && 0 <= gameMap.p2y && gameMap.p2y < gameMap.m)&& gameMap.p2x != gameMap.p1x && gameMap.p2y != gameMap.p1y) printf("invalid input! try again: \n");
	} while(!(0 <= gameMap.p2x && gameMap.p2x < gameMap.n && 0 <= gameMap.p2y && gameMap.p2y < gameMap.m)&& gameMap.p2x != gameMap.p1x && gameMap.p2y != gameMap.p1y);
    for (i = 0; i < n + 2; i++) {
        for (j = 0; j < m + 1; j++) {
            gameMap.Map[i][j] = 110;
        }
    }
    gameMap.Map[gameMap.p1x][gameMap.p1y] = 111;
    gameMap.Map[gameMap.p2x][gameMap.p2y] = 112;
    int p1Wall, p2Wall;
    do {
    	printf("please enter the number of first player's walls: \n");
    	scanf("%d", &p1Wall);
    	if (p1Wall > 10) printf("you can not have more than 10 walls! try again: \n");
	} while(p1Wall > 10 || p1Wall % 1 != 0);
	int x, y;
	char c;
	for (i = 0; i < p1Wall; i++) {
		printf("player number 1, please enter the wall number %d starting location and type(H or V): \n", i + 1);
		scanf("%d %d %c", &x, &y, &c);
		if (x >= n - 1 || y >= m - 1) {
			printf("Error! you can not place a wall there! please try again: \n");
			i--;
		}
		else if ((c == 'H' || c == 'h') && ((gameMap.Map[x][y] / 10)) % 10 == 2 || (gameMap.Map[x][y + 1] / 10) % 10 == 2) {
			printf("Error! you can not place a wall there! please try again: \n");
			i--;
		}
		else if ((c == 'V' || c == 'v') && (gameMap.Map[x][y] / 100 == 2 || gameMap.Map[x + 1][y] / 100 == 2)) {
			printf("Error! you can not place a wall there! please try again: \n");
			i--;
		}
		else {
			if (c == 'H' || c == 'h') {
				gameMap.Map[x][y] += 10;
				gameMap.Map[x][y + 1] += 10;
			}
			else if (c == 'V' || c == 'v'){
				gameMap.Map[x][y] += 100;
				gameMap.Map[x + 1][y] += 100;
			}
			else {
				printf("Error! you have entered invalid charachter! try again: \n");
				i--;
			}
		}
	}
	do {
		printf("please enter the number of second player's walls: \n");
    	scanf("%d", &p2Wall);
    	if (p2Wall > 10) printf("you can not have more than 10 walls! try again: \n");
    	else if (p2Wall % 1 != 0) printf("the number of your walls can not be a float number! try again: \n");
	} while (p2Wall > 10 || p2Wall % 1 != 0);
	for (i = 0; i < p2Wall; i++) {
		printf("player number 2, please enter the wall number %d starting location and type(H or V): \n", i + 1);
		scanf("%d %d %c", &x, &y, &c);
		if (x >= n - 1 || y >= m - 1) {
			printf("Error! you have entered invalid location! try again: \n");
			i--;
		}
		else if ((c == 'H' || c == 'h') && ((gameMap.Map[x][y] / 10)) % 10 == 2 || (gameMap.Map[x][y + 1] / 10) % 10 == 2) {
			printf("Error! you can not place a wall there! please try again: \n");
			i--;
		}
		else if ((c == 'V' || c == 'v') && (gameMap.Map[x][y] / 100 == 2 || gameMap.Map[x + 1][y] / 100 == 2)) {
			printf("Error! you can not place a wall there! please try again: \n");
			i--;
		}
		else {
			if (c == 'H' || c == 'h') {
				gameMap.Map[x][y] += 10;
				gameMap.Map[x][y + 1] += 10;
			}
			else if (c == 'V' || c == 'h'){
				gameMap.Map[x][y] += 100;
				gameMap.Map[x + 1][y] += 100;
			}
			else {
				printf("Error! you have entered invalid charachter! try again: \n");
				i--;
			}
		}
	}
    PrintTheMap(gameMap);
}

