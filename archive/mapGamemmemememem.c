#include <stdio.h>
#include <conio.h>
struct board{
    int n, m;
    int Map[100][100];
    int p1x, p1y, p2x, p2y;
    int p1w, p2w;
};

void PrintTheMap(struct board GameMap) {
    int i, j, sw, n = GameMap.n, m = GameMap.m;
    int left, up, play;
    printf("This is the Map(O stands for player 1 and X stands for player 2)\n");
    for (i = 0; i < n + 1; i++) {
        for (j = 0; j < m + 1; j++) {
            if (j == m) continue;
            left = GameMap.Map[i][j] / 100;
            up = (GameMap.Map[i][j] / 10) % 10;
            play = GameMap.Map[i][j] % 10;
            if (up == 1) printf("....");
            else printf("====");
        }
        printf(".");
        printf("\n");
        for (j = 0; j < m + 1; j++) {
        	if (i == n) break;
            left = GameMap.Map[i][j] / 100;
            up = (GameMap.Map[i][j] / 10) % 10;
            play = GameMap.Map[i][j] % 10;
            if (left == 1) printf(":");
            else printf("|");
            if (!play) printf("   ");
            else if (play == 1) printf(" O ");
            else printf(" X ");
        }
        printf("\n");
    }
}

int main() {
    int n, m, i, j;
    printf("Please enter the size of the map: \n");
    scanf("%d %d", &n, &m);
    struct board gameMap;
    int x1, y1, x2, y2;
    printf("please enter the location of the first player: \n");
    scanf("%d %d", &gameMap.p1x, &gameMap.p1y);
    printf("please enter the location of the second player: \n");
    scanf("%d %d", &gameMap.p2x, &gameMap.p2y);
    gameMap.n = n;
    gameMap.m = m;
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
	} while(p1Wall > 10);
	int x, y, c;
	for (i = 0; i < p1Wall; i++) {
			printf("player number 1, please enter the wall number %d starting location and type(H or V): \n", i + 1);
		scanf("%d %d %c", &x, &y, &c);
		if (x >= n || y >= m) {
			printf("Error! you have entered invalid location! try again: \n");
			i--;
		}
		else {
			if (c == 'H') {
				gameMap.Map[x][y] += 10;
				gameMap.Map[x][y + 1] += 10;
			}
			else if (c == 'V'){
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
	} while (p2Wall > 10);
	for (i = 0; i < p2Wall; i++) {
			printf("player number 2, please enter the wall number %d starting location and type(H or V): \n", i + 1);
		scanf("%d %d %c", &x, &y, &c);
		if (x >= n || y >= m) {
			printf("Error! you have entered invalid location! try again: \n");
			i--;
		}
		else {
			if (c == 'H') {
				gameMap.Map[x][y] += 10;
				gameMap.Map[x][y + 1] += 10;
			}
			else if (c == 'V'){
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
    return 0;
}
