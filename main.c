#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

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


int getTheDirect() {
	int c = getch(), d = 0;
	if (c == 224) d = getch();
	else if(c == '0') return 5;
	else if(c=='W' || c=='w') return 6;
	if (d == 72) return 3;
	else if (d == 77) return 2;
	else if (d == 80) return 4;
	else if (d == 75) return 1;
	else return 0;
}

void clearScreen() {
	system("cls");
}

void PrintTheMap(struct board GameMap) {
	setTextColor(15, 0);
    int i, j, n = GameMap.n, m = GameMap.m;
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

bool validWallH(char c, int x, int y, struct board gameMap) {
	if ((c == 'H' || c == 'h') && (gameMap.Map[x][y]/10)%10 != 2 && (gameMap.Map[x][y + 1]/10)%10 != 2) {
		if ((gameMap.Map[x][y + 1]/100 == 2) && (gameMap.Map[x - 1][y + 1]/100 == 2)) {
			if (!(gameMap.Map[x - 2][y + 1]/100 == 2 && gameMap.Map[x + 1][y + 1]/100 == 2)) return 0;
		}
		return 1;
	}
	return 0;
}

bool validWallV(char c, int x, int y, struct board gameMap) {
	if ((c == 'V' || c == 'v') && gameMap.Map[x][y]/100 != 2 && gameMap.Map[x + 1][y]/100 != 2) {
		if ((gameMap.Map[x + 1][y]/10) % 10 == 2 && (gameMap.Map[x + 1][y - 1]/100 == 2)) {
			if (!((gameMap.Map[x + 1][y + 1]/10) % 10 == 2 && (gameMap.Map[x + 1][y - 2]/10) % 10 == 2)) return 0;
		}
		return 1;
	}
	return 0;
}

int main() {
    int n, m, i, j;
    printf("Please enter the size of the map: \n");
    scanf("%d %d", &n, &m);
    struct board gameMap;
    gameMap.p1y = floor(n/2);
    gameMap.p2y = gameMap.p1y;
    gameMap.p1x= 0;
    gameMap.p2x = n-1;
    gameMap.n = n;
    gameMap.m = m;
    for (i = 0; i < n + 2; i++) {
        for (j = 0; j < m + 1; j++) {
            gameMap.Map[i][j] = 110;
        }
    }
    gameMap.Map[gameMap.p1x][gameMap.p1y] = 111;
    gameMap.Map[gameMap.p2x][gameMap.p2y] = 112;
    PrintTheMap(gameMap);
    int key = 0, move;
    do {
    	PrintTheMap(gameMap);
    	if (gameMap.p1x == gameMap.n - 1) {
            setTextColor(2,0);
			printf("player 1 is the winner!");
			setTextColor(15,0);
			break;
		}
		else if(gameMap.p2x == 0) {
            setTextColor(14,0);
			printf("player 2 is the winner!");
            setTextColor(15,0);
			break;
		}
    	if (!(key % 2)) {
    		printf("player 1's turn(0 to exit , W for placing wall , arrows to move): \n");
    		move = getTheDirect();
    		if (!move){
    			printf("wrong input!\n");
    			continue;
			}
			else if (move == 5) break;
    		if (move == 1) {
    			if (gameMap.p1y > 0 && gameMap.Map[gameMap.p1x][gameMap.p1y] / 100 == 1) {
                    if(gameMap.Map[gameMap.p1x][gameMap.p1y - 1] % 10 == 0){
                        gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                        gameMap.p1y--;
                        gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                        key++;
                    }
                    else if(gameMap.Map[gameMap.p1x][gameMap.p1y - 1] % 10 == 2){
                        if(gameMap.p1y > 1){
                            if(gameMap.Map[gameMap.p1x][gameMap.p1y - 1] / 100 == 1){
                                gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                gameMap.p1y -= 2;
                                gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                key++;
                            }
                            else{
                                int validmove[] = {0,0};
                                if((gameMap.Map[gameMap.p1x][gameMap.p1y - 1] / 10) % 10 == 1)
                                    validmove[0]=1;
                                if((gameMap.Map[gameMap.p1x + 1][gameMap.p1y - 1] / 10) % 10 == 1)
                                    validmove[1]=1;
                                if(validmove[0] && validmove[1]){
                                    printf("You can choose between going 1.forward-up(By push up arrow) or 2.forward-down(by push down arrow) : ");
                                    do{
                                        int where = getTheDirect();
                                        if(where == 3){
                                            gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                            gameMap.p1y--;
                                            gameMap.p1x--;
                                            gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                            key++;
                                            break;
                                        }
                                        else if(where == 4){
                                            gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                            gameMap.p1y--;
                                            gameMap.p1x++;
                                            gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                            key++;
                                            break;
                                        }
                                        else{
                                            printf("wrong move! try again\n");
                                            continue;
                                        }
                                    }while(1);
                                }
                                else if(validmove[0]==1){
                                    gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                    gameMap.p1y--;
                                    gameMap.p1x--;
                                    gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                    key++;
                                }
                                else if(validmove[1]==1){
                                    gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                    gameMap.p1y--;
                                    gameMap.p1x++;
                                    gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                    key++;
                                }
                                else{
                                    printf("wrong move! try again\n");
                                    continue;
                                }
                            }
                        }
                        else{
                            int validmove[] = {0,0};
                            if((gameMap.Map[gameMap.p1x][gameMap.p1y - 1] / 10) % 10 == 1)
                                validmove[0]=1;
                            if((gameMap.Map[gameMap.p1x + 1][gameMap.p1y - 1] / 10) % 10 == 1)
                                validmove[1]=1;
                            if(validmove[0] && validmove[1]){
                                printf("You can choose between going 1.forward-up(By push up arrow) or 2.forward-down(by push down arrow) : ");
                                do{
                                    int where = getTheDirect();
                                    if(where == 3){
                                        gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                        gameMap.p1y--;
                                        gameMap.p1x--;
                                        gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                        key++;
                                        break;
                                    }
                                    else if(where == 4){
                                        gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                        gameMap.p1y--;
                                        gameMap.p1x++;
                                        gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                        key++;
                                        break;
                                    }
                                    else{
                                        printf("wrong move! try again\n");
                                        continue;
                                    }
                                }while(1);
                            }
                            else if(validmove[0]==1){
                                gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                gameMap.p1y--;
                                gameMap.p1x--;
                                gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                key++;
                            }
                            else if(validmove[1]==1){
                                gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                gameMap.p1y--;
                                gameMap.p1x++;
                                gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                key++;
                            }
                            else{
                                printf("wrong move! try again\n");
                                continue;
                            }
                        }
                    }
				}
				else {
					printf("wrong move! try again\n");
					continue;
				}
			}
			else if (move == 2) {
				if (gameMap.p1y < gameMap.m - 1 && gameMap.Map[gameMap.p1x][gameMap.p1y + 1] / 100 == 1) {
                    if(gameMap.Map[gameMap.p1x][gameMap.p1y + 1] % 10 == 0){
                        gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                        gameMap.p1y++;
                        gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                        key++;
                    }
                    else if(gameMap.Map[gameMap.p1x][gameMap.p1y + 1] % 10 == 2){
                        if(gameMap.p1y < gameMap.m - 2){
                            if(gameMap.Map[gameMap.p1x][gameMap.p1y + 2] / 100 == 1){
                                gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                gameMap.p1y += 2;
                                gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                key++;
                            }
                            else{
                                int validmove[] = {0,0};
                                if((gameMap.Map[gameMap.p1x][gameMap.p1y + 1] / 10) % 10 == 1)
                                    validmove[0]=1;
                                if((gameMap.Map[gameMap.p1x + 1][gameMap.p1y + 1] / 10) % 10 == 1)
                                    validmove[1]=1;
                                if(validmove[0] && validmove[1]){
                                    printf("You can choose between going 1.forward-up(By push up arrow) or 2.forward-down(by push down arrow) : ");
                                    do{
                                        int where = getTheDirect();
                                        if(where == 3){
                                            gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                            gameMap.p1y++;
                                            gameMap.p1x--;
                                            gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                            key++;
                                            break;
                                        }
                                        else if(where == 4){
                                            gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                            gameMap.p1y++;
                                            gameMap.p1x++;
                                            gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                            key++;
                                            break;
                                        }
                                        else{
                                            printf("wrong move! try again\n");
                                            continue;
                                        }
                                    }while(1);
                                }
                                else if(validmove[0]==1){
                                    gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                    gameMap.p1y++;
                                    gameMap.p1x--;
                                    gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                    key++;
                                }
                                else if(validmove[1]==1){
                                    gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                    gameMap.p1y++;
                                    gameMap.p1x++;
                                    gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                    key++;
                                }
                                else{
                                    printf("wrong move! try again\n");
                                    continue;
                                }
                            }
                        }
                        else{
                            int validmove[] = {0,0};
                            if((gameMap.Map[gameMap.p1x][gameMap.p1y + 1] / 10) % 10 == 1)
                                validmove[0]=1;
                            if((gameMap.Map[gameMap.p1x + 1][gameMap.p1y + 1] / 10) % 10 == 1)
                                validmove[1]=1;
                            if(validmove[0] && validmove[1]){
                                printf("You can choose between going 1.forward-up(By push up arrow) or 2.forward-down(by push down arrow) : ");
                                    do{
                                int where = getTheDirect();
                                        if(where == 3){
                                        gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                        gameMap.p1y++;
                                        gameMap.p1x--;
                                        gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                        key++;
                                        break;
                                    }
                                    else if(where == 4){
                                        gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                        gameMap.p1y++;
                                        gameMap.p1x++;
                                        gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                        key++;
                                        break;
                                    }
                                    else{
                                        printf("wrong move! try again\n");
                                        continue;
                                    }
                                }while(1);
                            }
                            else if(validmove[0]==1){
                                gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                gameMap.p1y++;
                                gameMap.p1x--;
                                gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                key++;
                            }
                            else if(validmove[1]==1){
                                gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                gameMap.p1y++;
                                gameMap.p1x++;
                                gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                key++;
                            }
                            else{
                                printf("wrong move! try again\n");
                                continue;
                            }
                        }
                    }
				}
				else {
					printf("wrong move! try again\n");
					continue;
				}
			}
			else if (move == 3) {
				if (gameMap.p1x > 0 && (gameMap.Map[gameMap.p1x][gameMap.p1y] / 10) % 10 == 1) {
					if(gameMap.Map[gameMap.p1x - 1][gameMap.p1y] % 10 == 0){
                        gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                        gameMap.p1x--;
                        gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                        key++;
                    }
					else if(gameMap.Map[gameMap.p1x - 1][gameMap.p1y] % 10 == 2){
                        if(gameMap.p1x > 1){
                            if((gameMap.Map[gameMap.p1x - 1][gameMap.p1y] / 10) % 10 == 1){
                                gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                gameMap.p1x-=2;
                                gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                key++;
                            }
                            else{
                                int validmove[] = {0,0};
                                if(gameMap.Map[gameMap.p1x - 1][gameMap.p1y] / 100 == 1)
                                    validmove[0]=1;
                                if(gameMap.Map[gameMap.p1x - 1][gameMap.p1y + 1] / 100 == 1)
                                    validmove[1]=1;
                                if(validmove[0] && validmove[1]){
                                    printf("You can choose between going 1.forward-right(By push right arrow) or 2.forward-left(by push left arrow) : ");
                                    do{
                                        int where = getTheDirect();
                                        if(where == 1){
                                            gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                            gameMap.p1y--;
                                            gameMap.p1x--;
                                            gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                            key++;
                                            break;
                                        }
                                        else if(where == 2){
                                            gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                            gameMap.p1y++;
                                            gameMap.p1x--;
                                            gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                            key++;
                                            break;
                                        }
                                        else{
                                            printf("wrong move! try again\n");
                                            continue;
                                        }
                                    }while(1);
                                }
                                else if(validmove[0]==1){
                                    gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                    gameMap.p1y--;
                                    gameMap.p1x--;
                                    gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                    key++;
                                }
                                else if(validmove[1]==1){
                                    gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                    gameMap.p1y++;
                                    gameMap.p1x--;
                                    gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                    key++;
                                }
                                else{
                                    printf("wrong move! try again\n");
                                    continue;
                                }
                            }
                        }
                        else{
                            int validmove[] = {0,0};
                            if(gameMap.Map[gameMap.p1x - 1][gameMap.p1y] / 100 == 1)
                                validmove[0]=1;
                            if(gameMap.Map[gameMap.p1x - 1][gameMap.p1y + 1] / 100 == 1)
                                validmove[1]=1;
                            if(validmove[0] && validmove[1]){
                                printf("You can choose between going 1.forward-right(By push up arrow) or 2.forward-left(by push down arrow) : ");
                                do{
                                    int where = getTheDirect();
                                    if(where == 1){
                                        gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                        gameMap.p1y--;
                                        gameMap.p1x--;
                                        gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                        key++;
                                        break;
                                    }
                                    else if(where == 2){
                                        gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                        gameMap.p1y++;
                                        gameMap.p1x--;
                                        gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                        key++;
                                        break;
                                    }
                                    else{
                                        printf("wrong move! try again\n");
                                        continue;
                                    }
                                }while(1);
                            }
                            else if(validmove[0]==1){
                                gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                gameMap.p1y--;
                                gameMap.p1x--;
                                gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                key++;
                            }
                            else if(validmove[1]==1){
                                gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                gameMap.p1y++;
                                gameMap.p1x--;
                                gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                key++;
                            }
                            else{
                                printf("wrong move! try again\n");
                                continue;
                            }
                        }
					}
				}
				else {
					printf("wrong move! try again\n");
					continue;
				}
			}
			else if (move == 4) {
				if (gameMap.p1x < gameMap.n - 1 && (gameMap.Map[gameMap.p1x + 1][gameMap.p1y] / 10) % 10 == 1) {
					if(gameMap.Map[gameMap.p1x + 1][gameMap.p1y] % 10 == 0){
                        gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                        gameMap.p1x++;
                        gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                        key++;
                    }
					else if(gameMap.Map[gameMap.p1x + 1][gameMap.p1y] % 10 == 2){
                        if(gameMap.p1x < gameMap.n - 2){
                            if((gameMap.Map[gameMap.p1x + 2][gameMap.p1y] / 10) % 10 == 1){
                                gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                gameMap.p1x+=2;
                                gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                key++;
                            }
                            else{
                                int validmove[] = {0,0};
                                if(gameMap.Map[gameMap.p1x + 1][gameMap.p1y] / 100 == 1)
                                    validmove[0]=1;
                                if(gameMap.Map[gameMap.p1x + 1][gameMap.p1y + 1] / 100 == 1)
                                    validmove[1]=1;
                                if(validmove[0] && validmove[1]){
                                    printf("You can choose between going 1.forward-right(By push right arrow) or 2.forward-left(by push left arrow) : ");
                                    do{
                                        int where = getTheDirect();
                                        if(where == 1){
                                            gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                            gameMap.p1y--;
                                            gameMap.p1x++;
                                            gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                            key++;
                                            break;
                                        }
                                        else if(where == 2){
                                            gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                            gameMap.p1y++;
                                            gameMap.p1x++;
                                            gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                            key++;
                                            break;
                                        }
                                        else{
                                            printf("wrong move! try again\n");
                                            continue;
                                        }
                                    }while(1);
                                }
                                else if(validmove[0]==1){
                                    gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                    gameMap.p1y--;
                                    gameMap.p1x++;
                                    gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                    key++;
                                }
                                else if(validmove[1]==1){
                                    gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                    gameMap.p1y++;
                                    gameMap.p1x++;
                                    gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                    key++;
                                }
                                else{
                                    printf("wrong move! try again\n");
                                    continue;
                                }
                            }
                        }
                        else{
                            int validmove[] = {0,0};
                            if(gameMap.Map[gameMap.p1x + 1][gameMap.p1y] / 100 == 1)
                                validmove[0]=1;
                            if(gameMap.Map[gameMap.p1x + 1][gameMap.p1y + 1] / 100 == 1)
                                validmove[1]=1;
                            if(validmove[0] && validmove[1]){
                                printf("You can choose between going 1.forward-right(By push up arrow) or 2.forward-left(by push down arrow) : ");
                                do{
                                    int where = getTheDirect();
                                    if(where == 1){
                                        gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                        gameMap.p1y--;
                                        gameMap.p1x++;
                                        gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                        key++;
                                        break;
                                    }
                                    else if(where == 2){
                                        gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                        gameMap.p1y++;
                                        gameMap.p1x++;
                                        gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                        key++;
                                        break;
                                    }
                                    else{
                                        printf("wrong move! try again\n");
                                        continue;
                                    }
                                }while(1);
                            }
                            else if(validmove[0]==1){
                                gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                gameMap.p1y--;
                                gameMap.p1x++;
                                gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                key++;
                            }
                            else if(validmove[1]==1){
                                gameMap.Map[gameMap.p1x][gameMap.p1y]--;
                                gameMap.p1y++;
                                gameMap.p1x++;
                                gameMap.Map[gameMap.p1x][gameMap.p1y]++;
                                key++;
                            }
                            else{
                                printf("wrong move! try again\n");
                                continue;
                            }
                        }
					}
				}
				else {
					printf("wrong move! try again\n");
					continue;
				}
			}
			else if(move == 6){
                printf("enter the wall starting location and (H) for horizontal and (V) for vertical\n");
                int x,y;
                char c;
                while(1){
                    scanf("%d %d %c",&x,&y,&c);
                    if (x >= gameMap.n - 1 || y >= gameMap.m - 1) {
                        printf("Error! you have entered invalid location! try again: \n");
                        continue;
                    }
                    else if(validWallH(c, x, y, gameMap)) {
                        gameMap.Map[x][y] += 10;
                        gameMap.Map[x][y + 1] += 10;
                        key++;
                        break;
                    }
                    else if(validWallV(c, x, y, gameMap)){
                        gameMap.Map[x][y] += 100;
                        gameMap.Map[x + 1][y] += 100;
                        key++;
                        break;
                    }
                    else{
                        printf("Error! you have entered invalid character! try again: \n");
                        continue;
                    }
                }
            }
			else {
				printf("you have entered invalid character! try again!\n");
				continue;
			}
		}
		else {
			printf("player 2's turn(0 to exit , W for placing wall , arrows to move): \n");
    		move = getTheDirect();
    		if (!move){
    			printf("wrong input!\n");
    			continue;
			}
			else if (move == 5) break;
    		if (move == 1) {
    			if (gameMap.p2y > 0 && gameMap.Map[gameMap.p2x][gameMap.p2y] / 100 == 1) {
                    if(gameMap.Map[gameMap.p2x][gameMap.p2y - 1] % 10 == 0){
                        gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                        gameMap.p2y--;
                        gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                        key++;
                    }
                    else if(gameMap.Map[gameMap.p2x][gameMap.p2y - 1] % 10 == 1){
                        if(gameMap.p2y > 1){
                            if(gameMap.Map[gameMap.p2x][gameMap.p2y - 1] / 100 == 1){
                                gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                gameMap.p2y -= 2;
                                gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                key++;
                            }
                            else{
                                int validmove[] = {0,0};
                                if((gameMap.Map[gameMap.p2x][gameMap.p2y - 1] / 10) % 10 == 1)
                                    validmove[0]=1;
                                if((gameMap.Map[gameMap.p2x + 1][gameMap.p2y - 1] / 10) % 10 == 1)
                                    validmove[1]=1;
                                if(validmove[0] && validmove[1]){
                                    printf("You can choose between going 1.forward-up(By push up arrow) or 2.forward-down(by push down arrow) : ");
                                    do{
                                        int where = getTheDirect();
                                        if(where == 3){
                                            gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                            gameMap.p2y--;
                                            gameMap.p2x--;
                                            gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                            key++;
                                            break;
                                        }
                                        else if(where == 4){
                                            gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                            gameMap.p2y--;
                                            gameMap.p2x++;
                                            gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                            key++;
                                            break;
                                        }
                                        else{
                                            printf("wrong move! try again\n");
                                            continue;
                                        }
                                    }while(1);
                                }
                                else if(validmove[0]==1){
                                    gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                    gameMap.p2y--;
                                    gameMap.p2x--;
                                    gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                    key++;
                                }
                                else if(validmove[1]==1){
                                    gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                    gameMap.p2y--;
                                    gameMap.p2x++;
                                    gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                    key++;
                                }
                                else{
                                    printf("wrong move! try again\n");
                                    continue;
                                }
                            }
                        }
                        else{
                            int validmove[] = {0,0};
                            if((gameMap.Map[gameMap.p2x][gameMap.p2y - 1] / 10) % 10 == 1)
                                validmove[0]=1;
                            if((gameMap.Map[gameMap.p2x + 1][gameMap.p2y - 1] / 10) % 10 == 1)
                                validmove[1]=1;
                            if(validmove[0] && validmove[1]){
                                printf("You can choose between going 1.forward-up(By push up arrow) or 2.forward-down(by push down arrow) : ");
                                do{
                                    int where = getTheDirect();
                                    if(where == 3){
                                        gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                        gameMap.p2y--;
                                        gameMap.p2x--;
                                        gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                        key++;
                                        break;
                                    }
                                    else if(where == 4){
                                        gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                        gameMap.p2y--;
                                        gameMap.p2x++;
                                        gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                        key++;
                                        break;
                                    }
                                    else{
                                        printf("wrong move! try again\n");
                                        continue;
                                    }
                                }while(1);
                            }
                            else if(validmove[0]==1){
                                gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                gameMap.p2y--;
                                gameMap.p2x--;
                                gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                key++;
                            }
                            else if(validmove[1]==1){
                                gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                gameMap.p2y--;
                                gameMap.p2x++;
                                gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                key++;
                            }
                            else{
                                printf("wrong move! try again\n");
                                continue;
                            }
                        }
                    }
				}
				else {
					printf("wrong move! try again\n");
					continue;
				}
			}
			else if (move == 2) {
				if (gameMap.p2y < gameMap.m - 1 && gameMap.Map[gameMap.p2x][gameMap.p2y + 1] / 100 == 1) {
                    if(gameMap.Map[gameMap.p2x][gameMap.p2y + 1] % 10 == 0){
                        gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                        gameMap.p2y++;
                        gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                        key++;
                    }
                    else if(gameMap.Map[gameMap.p2x][gameMap.p2y + 1] % 10 == 1){
                        if(gameMap.p2y < gameMap.m - 2){
                            if(gameMap.Map[gameMap.p2x][gameMap.p2y + 2] / 100 == 1){
                                gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                gameMap.p2y += 2;
                                gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                key++;
                            }
                            else{
                                int validmove[] = {0,0};
                                if((gameMap.Map[gameMap.p2x][gameMap.p2y + 1] / 10) % 10 == 1)
                                    validmove[0]=1;
                                if((gameMap.Map[gameMap.p2x + 1][gameMap.p2y + 1] / 10) % 10 == 1)
                                    validmove[1]=1;
                                if(validmove[0] && validmove[1]){
                                    printf("You can choose between going 1.forward-up(By push up arrow) or 2.forward-down(by push down arrow) : ");
                                    do{
                                        int where = getTheDirect();
                                        if(where == 3){
                                            gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                            gameMap.p2y++;
                                            gameMap.p2x--;
                                            gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                            key++;
                                            break;
                                        }
                                        else if(where == 4){
                                            gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                            gameMap.p2y++;
                                            gameMap.p2x++;
                                            gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                            key++;
                                            break;
                                        }
                                        else{
                                            printf("wrong move! try again\n");
                                            continue;
                                        }
                                    }while(1);
                                }
                                else if(validmove[0]==1){
                                    gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                    gameMap.p2y++;
                                    gameMap.p2x--;
                                    gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                    key++;
                                }
                                else if(validmove[1]==1){
                                    gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                    gameMap.p2y++;
                                    gameMap.p2x++;
                                    gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                    key++;
                                }
                                else{
                                    printf("wrong move! try again\n");
                                    continue;
                                }
                            }
                        }
                        else{
                            int validmove[] = {0,0};
                            if((gameMap.Map[gameMap.p2x][gameMap.p2y + 1] / 10) % 10 == 1)
                                validmove[0]=1;
                            if((gameMap.Map[gameMap.p2x + 1][gameMap.p2y + 1] / 10) % 10 == 1)
                                validmove[1]=1;
                            if(validmove[0] && validmove[1]){
                                printf("You can choose between going 1.forward-up(By push up arrow) or 2.forward-down(by push down arrow) : ");
                                    do{
                                int where = getTheDirect();
                                        if(where == 3){
                                        gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                        gameMap.p2y++;
                                        gameMap.p2x--;
                                        gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                        key++;
                                        break;
                                    }
                                    else if(where == 4){
                                        gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                        gameMap.p2y++;
                                        gameMap.p2x++;
                                        gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                        key++;
                                        break;
                                    }
                                    else{
                                        printf("wrong move! try again\n");
                                        continue;
                                    }
                                }while(1);
                            }
                            else if(validmove[0]==1){
                                gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                gameMap.p2y++;
                                gameMap.p2x--;
                                gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                key++;
                            }
                            else if(validmove[1]==1){
                                gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                gameMap.p2y++;
                                gameMap.p2x++;
                                gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                key++;
                            }
                            else{
                                printf("wrong move! try again\n");
                                continue;
                            }
                        }
                    }
				}
				else {
					printf("wrong move! try again\n");
					continue;
				}
			}
			else if (move == 3) {
				if (gameMap.p2x > 0 && (gameMap.Map[gameMap.p2x][gameMap.p2y] / 10) % 10 == 1) {
					if(gameMap.Map[gameMap.p2x - 1][gameMap.p2y] % 10 == 0){
                        gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                        gameMap.p2x--;
                        gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                        key++;
                    }
					else if(gameMap.Map[gameMap.p2x - 1][gameMap.p2y] % 10 == 1){
                        if(gameMap.p2x > 1){
                            if((gameMap.Map[gameMap.p2x - 1][gameMap.p2y] / 10) % 10 == 1){
                                gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                gameMap.p2x-=2;
                                gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                key++;
                            }
                            else{
                                int validmove[] = {0,0};
                                if(gameMap.Map[gameMap.p2x - 1][gameMap.p2y] / 100 == 1)
                                    validmove[0]=1;
                                if(gameMap.Map[gameMap.p2x - 1][gameMap.p2y + 1] / 100 == 1)
                                    validmove[1]=1;
                                if(validmove[0] && validmove[1]){
                                    printf("You can choose between going 1.forward-right(By push right arrow) or 2.forward-left(by push left arrow) : ");
                                    do{
                                        int where = getTheDirect();
                                        if(where == 1){
                                            gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                            gameMap.p2y--;
                                            gameMap.p2x--;
                                            gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                            key++;
                                            break;
                                        }
                                        else if(where == 2){
                                            gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                            gameMap.p2y++;
                                            gameMap.p2x--;
                                            gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                            key++;
                                            break;
                                        }
                                        else{
                                            printf("wrong move! try again\n");
                                            continue;
                                        }
                                    }while(1);
                                }
                                else if(validmove[0]==1){
                                    gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                    gameMap.p2y--;
                                    gameMap.p2x--;
                                    gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                    key++;
                                }
                                else if(validmove[1]==1){
                                    gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                    gameMap.p2y++;
                                    gameMap.p2x--;
                                    gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                    key++;
                                }
                                else{
                                    printf("wrong move! try again\n");
                                    continue;
                                }
                            }
                        }
                        else{
                            int validmove[] = {0,0};
                            if(gameMap.Map[gameMap.p2x - 1][gameMap.p2y] / 100 == 1)
                                validmove[0]=1;
                            if(gameMap.Map[gameMap.p2x - 1][gameMap.p2y + 1] / 100 == 1)
                                validmove[1]=1;
                            if(validmove[0] && validmove[1]){
                                printf("You can choose between going 1.forward-right(By push up arrow) or 2.forward-left(by push down arrow) : ");
                                do{
                                    int where = getTheDirect();
                                    if(where == 1){
                                        gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                        gameMap.p2y--;
                                        gameMap.p2x--;
                                        gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                        key++;
                                        break;
                                    }
                                    else if(where == 2){
                                        gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                        gameMap.p2y++;
                                        gameMap.p2x--;
                                        gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                        key++;
                                        break;
                                    }
                                    else{
                                        printf("wrong move! try again\n");
                                        continue;
                                    }
                                }while(1);
                            }
                            else if(validmove[0]==1){
                                gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                gameMap.p2y--;
                                gameMap.p2x--;
                                gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                key++;
                            }
                            else if(validmove[1]==1){
                                gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                gameMap.p2y++;
                                gameMap.p2x--;
                                gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                key++;
                            }
                            else{
                                printf("wrong move! try again\n");
                                continue;
                            }
                        }
					}
				}
				else {
					printf("wrong move! try again\n");
					continue;
				}
			}
			else if (move == 4) {
				if (gameMap.p2x < gameMap.n - 1 && (gameMap.Map[gameMap.p2x + 1][gameMap.p2y] / 10) % 10 == 1) {
					if(gameMap.Map[gameMap.p2x + 1][gameMap.p2y] % 10 == 0){
                        gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                        gameMap.p2x++;
                        gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                        key++;
                    }
					else if(gameMap.Map[gameMap.p2x + 1][gameMap.p2y] % 10 == 1){
                        if(gameMap.p2x < gameMap.n - 2){
                            if((gameMap.Map[gameMap.p2x + 2][gameMap.p2y] / 10) % 10 == 1){
                                gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                gameMap.p2x+=2;
                                gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                key++;
                            }
                            else{
                                int validmove[] = {0,0};
                                if(gameMap.Map[gameMap.p2x + 1][gameMap.p2y] / 100 == 1)
                                    validmove[0]=1;
                                if(gameMap.Map[gameMap.p2x + 1][gameMap.p2y + 1] / 100 == 1)
                                    validmove[1]=1;
                                if(validmove[0] && validmove[1]){
                                    printf("You can choose between going 1.forward-right(By push right arrow) or 2.forward-left(by push left arrow) : ");
                                    do{
                                        int where = getTheDirect();
                                        if(where == 1){
                                            gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                            gameMap.p2y--;
                                            gameMap.p2x++;
                                            gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                            key++;
                                            break;
                                        }
                                        else if(where == 2){
                                            gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                            gameMap.p2y++;
                                            gameMap.p2x++;
                                            gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                            key++;
                                            break;
                                        }
                                        else{
                                            printf("wrong move! try again\n");
                                            continue;
                                        }
                                    }while(1);
                                }
                                else if(validmove[0]==1){
                                    gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                    gameMap.p2y--;
                                    gameMap.p2x++;
                                    gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                    key++;
                                }
                                else if(validmove[1]==1){
                                    gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                    gameMap.p2y++;
                                    gameMap.p2x++;
                                    gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                    key++;
                                }
                                else{
                                    printf("wrong move! try again\n");
                                    continue;
                                }
                            }
                        }
                        else{
                            int validmove[] = {0,0};
                            if(gameMap.Map[gameMap.p2x + 1][gameMap.p2y] / 100 == 1)
                                validmove[0]=1;
                            if(gameMap.Map[gameMap.p2x + 1][gameMap.p2y + 1] / 100 == 1)
                                validmove[1]=1;
                            if(validmove[0] && validmove[1]){
                                printf("You can choose between going 1.forward-right(By push up arrow) or 2.forward-left(by push down arrow) : ");
                                do{
                                    int where = getTheDirect();
                                    if(where == 1){
                                        gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                        gameMap.p2y--;
                                        gameMap.p2x++;
                                        gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                        key++;
                                        break;
                                    }
                                    else if(where == 2){
                                        gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                        gameMap.p2y++;
                                        gameMap.p2x++;
                                        gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                        key++;
                                        break;
                                    }
                                    else{
                                        printf("wrong move! try again\n");
                                        continue;
                                    }
                                }while(1);
                            }
                            else if(validmove[0]==1){
                                gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                gameMap.p2y--;
                                gameMap.p2x++;
                                gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                key++;
                            }
                            else if(validmove[1]==1){
                                gameMap.Map[gameMap.p2x][gameMap.p2y]-=2;
                                gameMap.p2y++;
                                gameMap.p2x++;
                                gameMap.Map[gameMap.p2x][gameMap.p2y]+=2;
                                key++;
                            }
                            else{
                                printf("wrong move! try again\n");
                                continue;
                            }
                        }
					}
				}
				else {
					printf("wrong move! try again\n");
					continue;
				}
			}
			else if(move == 6){
                printf("enter the wall starting location and (H) for horizontal and (V) for vertical\n");
                int x,y;
                char c;
                while(1){
                    scanf("%d %d %c",&x,&y,&c);
                    if (x >= gameMap.n || y >= gameMap.m) {
                        printf("Error! you have entered invalid location! try again: \n");
                        continue;
                    }
                    else if(validWallH(c, x, y, gameMap)){
                        gameMap.Map[x][y] += 10;
                        gameMap.Map[x][y + 1] += 10;
                        key++;
                        break;
                    }
                    else if(validWallV(c, x, y, gameMap)){
                        gameMap.Map[x][y] += 100;
                        gameMap.Map[x + 1][y] += 100;
                        key++;
                        break;
                    }
                    else{
                        printf("Error! you have entered invalid character! try again: \n");
                        continue;
                    }
                }
            }
			else {
				printf("you have entered invalid character! try again!\n");
				continue;
			}
		}
	} while(1);
    return 0;
}
