#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include "dfs.h"
#include "screen.h"
#include "sp.h"
#include "validV.h"
#include "minimax.h"

const int maxDepth = 4;
const int MAX_WALLS = 10;
int lock1 = 0, lock2 = 0;

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

int main() {
    int n, m, i, j;
    int dif;
    int sw = 1;
    while(sw){
        printf("Please enter the size of the map: \n");
        scanf("%d", &n);
        if(n>=5)
                break;
        else
            printf("Wrong Input!!! Try Again : \n");
    }
    m = n;
    struct board gameMap;
    struct Graph mygraph;
    gameMap.p1y = floor(n/2);
    gameMap.p2y = gameMap.p1y;
    gameMap.p1x= 0;
    gameMap.p2x = n-1;
    gameMap.n = n;
    gameMap.m = m;
    gameMap.p1w = MAX_WALLS;
    gameMap.p2w = MAX_WALLS;
    gameMap.p1placedwalls = 0;
    gameMap.p2placedwalls = 0;
    for (i = 0; i < n + 2; i++) {
        for (j = 0; j < m + 1; j++) {
            gameMap.Map[i][j] = 110;
            addedge(n,m,i,j,&mygraph);
        }
    }
    makeUnVisit(&mygraph);
    char s;
    while(sw){
        printf("choose you opponent(c for computer and h for human): \n");
        scanf("\n%c", &s);
        if (!(s == 'c' || s == 'C' || s == 'H' || s == 'h')) {
                printf("invalid input! try again: \n");
        }
        else
            break;
    }
    int key = 0, move;
    if(s == 'C' || s=='c'){
        while(sw){
            printf("choose dificulity of AI you want to play with : \n");
            printf("1 for Beginner\n");//random
            printf("2 for Semi-pro\n");//random with rules
            printf("3 for Pro\n");//random with better ruls
            printf("4 for Legend\n");//minimax with depth 2
            printf("5 for Ultimate\n");//minimax with depth 4 and alpha-beta puring
            scanf("%d",&dif);
            if(dif>=1 && dif<=5)
                break;
            else
                printf("invalid input! try again: \n");
        }
    }
    gameMap.Map[gameMap.p1x][gameMap.p1y] = 111;
    gameMap.Map[gameMap.p2x][gameMap.p2y] = 112;
    PrintTheMap(gameMap);
    if (s == 'h' || s == 'H') {
    do {
        max_walls_checker(&gameMap);
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
            if (lock1 > 0) {
                printf("player 1 tough to your last round spell you can't move this round!\n");
                sleep(DELAY);
                lock1--;
                key++;
               	continue;
            }
    		printf("player 1's turn(0 to exit , W for placing wall , arrows to move): \n");
    		int randomNumber = random_maker(0, 1);
            if (randomNumber) {
                printf("you have gotten a present:\n");
                makePresent(&gameMap, key);
                printf("\n");
            }
            else {
            	printf("you have been spelled!\n");
                int situation = makeSpell(&gameMap, &mygraph, key);
                if (situation == 1) {
                    key++;
                    sleep(DELAY);
                    continue;
                }
                else if (situation == 2) {
                    key++;
                    lock1 = 1;
                    sleep(DELAY);
                    continue;
                }
			}
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
				if (gameMap.p1w == 0) {
					printf("you can't place anymore walls!");
					continue;
				}
                printf("enter the wall starting location and (H) for horizontal and (V) for vertical\n");
                int x,y;
                char c;
                while(1){
                    scanf("%d %d %c",&x,&y,&c);
                    if ((c == 'h' || c == 'H' ) && (x >= gameMap.n || y >= gameMap.m - 1)) {
                        printf("Error! you have entered invalid location(you can not place a wall there)! try again: \n");
                        continue;
                    }
                    else if ((c == 'v' || c == 'V') && (x >= gameMap.n - 1 || y >= gameMap.m)) {
                        printf("Error! you have entered invalid location(you can not place a wall there)! try again: \n");
                        continue;
                    }
                    else if(validWallH(c, x, y, gameMap, &mygraph)) {
                        gameMap.player1_walls[gameMap.p1placedwalls][0] = x;
                        gameMap.player1_walls[gameMap.p1placedwalls][1] = y;
                        gameMap.player1_walls[gameMap.p1placedwalls][2] = 0;
                        gameMap.Map[x][y] += 10;
                        gameMap.Map[x][y + 1] += 10;
                        key++;
                        gameMap.p1w--;
                        gameMap.p1placedwalls++;
                        break;
                    }
                    else if(validWallV(c, x, y, gameMap, &mygraph)){
                        gameMap.player1_walls[gameMap.p1placedwalls][0] = x;
                        gameMap.player1_walls[gameMap.p1placedwalls][1] = y;
                        gameMap.player1_walls[gameMap.p1placedwalls][2] = 1;
                        gameMap.Map[x][y] += 100;
                        gameMap.Map[x + 1][y] += 100;
                        key++;
                        gameMap.p1w--;
                        gameMap.p1placedwalls++;
                        break;
                    }
                    else{
                        printf("Error! you have entered invalid character(you can not place a wall there)! try again: \n");
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
            if (lock2 > 0) {
                printf("player 2 tough to your last round spell you can't move this round!\n");
                sleep(DELAY);
                lock2--;
                key++;
                continue;
            }
			printf("player 2's turn(0 to exit , W for placing wall , arrows to move): \n");
    		int randomNumber = random_maker(0, 1);
            if (randomNumber) {
                printf("you have gotten a present:\n");
                makePresent(&gameMap, key);
                printf("\n");
            }
            else {
            	printf("you have been spelled!\n");
                int situation = makeSpell(&gameMap, &mygraph, key);
                if (situation == 1) {
                    key++;
                    sleep(DELAY);
                    continue;
                }
                else if (situation == 2) {
                    key++;
                    lock2 = 1;
                    sleep(DELAY);
                    continue;
                }
			}
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
				if (gameMap.p2w == 0) {
					printf("you can't place anymore walls!");
					continue;
				}
                printf("enter the wall starting location and (H) for horizontal and (V) for vertical\n");
                int x,y;
                char c;
                while(1){
                    scanf("%d %d %c",&x,&y,&c);
                    if ((c == 'h' || c == 'H' ) && (x >= gameMap.n || y >= gameMap.m - 1)) {
                        printf("Error! you have entered invalid location(you can not place a wall there)! try again: \n");
                        continue;
                    }
                    else if ((c == 'v' || c == 'V') && (x >= gameMap.n - 1 || y >= gameMap.m)) {
                        printf("Error! you have entered invalid location(you can not place a wall there)! try again: \n");
                        continue;
                    }
                    else if(validWallH(c, x, y, gameMap, &mygraph)){
                        gameMap.player2_walls[gameMap.p2placedwalls][0] = x;
                        gameMap.player2_walls[gameMap.p2placedwalls][1] = y;
                        gameMap.player2_walls[gameMap.p2placedwalls][2] = 0;
                        gameMap.Map[x][y] += 10;
                        gameMap.Map[x][y + 1] += 10;
                        key++;
                        gameMap.p2w--;
                        gameMap.p2placedwalls++;
                        break;
                    }
                    else if(validWallV(c, x, y, gameMap, &mygraph)){
                        gameMap.player2_walls[gameMap.p2placedwalls][0] = x;
                        gameMap.player2_walls[gameMap.p2placedwalls][1] = y;
                        gameMap.player2_walls[gameMap.p2placedwalls][2] = 1;
                        gameMap.Map[x][y] += 100;
                        gameMap.Map[x + 1][y] += 100;
                        key++;
                        gameMap.p2placedwalls++;
                        gameMap.p2w--;
                        break;
                    }
                    else{
                        printf("Error! you have entered invalid character or wrong location(you can not place a wall there)! try again: \n");
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
	}
	else if (s == 'c' || s == 'C') {
    int pre = 4;
	do {
        max_walls_checker(&gameMap);
    	PrintTheMap(gameMap);
    	if (gameMap.p1x == gameMap.n - 1) {
            setTextColor(2,0);
			printf("human is the winner!");
			setTextColor(15,0);
			break;
		}
		else if(gameMap.p2x == 0) {
            setTextColor(14,0);
			printf("computer is the winner!");
            setTextColor(15,0);
			break;
		}
    	if (!(key % 2)) {
            if (lock1 > 0) {
                lock1--;
                key++;
               	continue;
            }
    		printf("player 1's turn(0 to exit , W for placing wall , arrows to move): \n");
    		int randomNumber = random_maker(0, 1);
            if (randomNumber) {
                printf("you have gotten a present:\n");
                makePresent(&gameMap, key);
                printf("\n");
            }
            else {
            	printf("you have been spelled!\n");
                int situation = makeSpell(&gameMap, &mygraph, key);
                if (situation == 1) {
                    key++;
                    sleep(DELAY);
                    continue;
                }
                else if (situation == 2) {
                    key++;
                    lock1 = 1;
                    sleep(DELAY);
                    continue;
                }
			}
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
				if (gameMap.p1w == 0) {
					printf("you can't place anymore walls!");
					continue;
				}
                printf("enter the wall starting location and (H) for horizontal and (V) for vertical\n");
                int x,y;
                char c;
                while(1){
                    scanf("%d %d %c",&x,&y,&c);
                    if ((c == 'h' || c == 'H' ) && (x >= gameMap.n || y >= gameMap.m - 1)) {
                        printf("Error! you have entered invalid location(you can not place a wall there)! try again: \n");
                        continue;
                    }
                    else if ((c == 'v' || c == 'V') && (x >= gameMap.n - 1 || y >= gameMap.m)) {
                        printf("Error! you have entered invalid location(you can not place a wall there)! try again: \n");
                        continue;
                    }
                    else if(validWallH(c, x, y, gameMap, &mygraph)) {
                        gameMap.player1_walls[gameMap.p1placedwalls][0] = x;
                        gameMap.player1_walls[gameMap.p1placedwalls][1] = y;
                        gameMap.player1_walls[gameMap.p1placedwalls][2] = 0;
                        gameMap.Map[x][y] += 10;
                        gameMap.Map[x][y + 1] += 10;
                        key++;
                        gameMap.p1w--;
                        gameMap.p1placedwalls++;
                        break;
                    }
                    else if(validWallV(c, x, y, gameMap, &mygraph)){
                        gameMap.player1_walls[gameMap.p1placedwalls][0] = x;
                        gameMap.player1_walls[gameMap.p1placedwalls][1] = y;
                        gameMap.player1_walls[gameMap.p1placedwalls][2] = 1;
                        gameMap.Map[x][y] += 100;
                        gameMap.Map[x + 1][y] += 100;
                        key++;
                        gameMap.p1w--;
                        gameMap.p1placedwalls++;
                        break;
                    }
                    else{
                        printf("Error! you have entered invalid character(you can not place a wall there)! try again: \n");
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
			if (lock2 > 0) {
                printf("computer can not move this round!\n");
                sleep(DELAY);
                lock2--;
                key++;
               	continue;
            }
    		printf("computer's' turn(0 to exit , W for placing wall , arrows to move): \n");
    		int randomNumber = random_maker(0, 1);
    		printf("to computer:\n");
            if (randomNumber) {
                printf("you have gotten a present:\n");
                makePresent(&gameMap, key);
                printf("\n");
            }
            else {
            	printf("you have been spelled!\n");
                int situation = makeSpell(&gameMap, &mygraph, key);
                if (situation == 1) {
                    key++;
                    sleep(DELAY);
                    continue;
                }
                else if (situation == 2) {
                    key++;
                    lock2 = 1;
                    sleep(DELAY);
                    continue;
                }
			}
			struct myWall bestWall;
			int dobest = 0;
			if(dif == 1){
                dobest = 0;
                move = rand();
                if (move % 7 == 5 || move % 7 == 0) {
                    move += 1;
                }
                move = move % 7;
			}
			else if(dif == 2){
                int g = rand();
                g = g%9;
                if(g<3){
                    dobest = 1;
                    move = minimax(maxDepth,&gameMap,&mygraph,INT_MIN,INT_MAX,&bestWall,pre);
                }
                else{
                    dobest = 0;
                    move = rand();
                    if (move % 7 == 5 || move % 7 == 0) {
                        move += 1;
                    }
                    move = move % 7;
                }
			}
			else if(dif == 3){
                int g = rand();
                g = g%9;
                if(g<5){
                    dobest = 1;
                    move = minimax(maxDepth,&gameMap,&mygraph,INT_MIN,INT_MAX,&bestWall,pre);
                }
                else{
                    dobest = 0;
                        move = rand();
                    if (move % 7 == 5 || move % 7 == 0) {
                        move += 1;
                    }
                    move = move % 7;
                }
			}
			else if(dif == 4){
                int g = rand();
                g = g%9;
                printf("%d\n",g);
                int r;
                scanf("%d",&r);
                if(g<7){
                    dobest = 1;
                    move = minimax(maxDepth,&gameMap,&mygraph,INT_MIN,INT_MAX,&bestWall,pre);
                }
                else{
                    dobest = 0;
                    move = rand();
                    if (move % 7 == 5 || move % 7 == 0) {
                        move += 1;
                    }
                    move = move % 7;
                }
			}
			else{
                dobest = 1;
                findWalls(&gameMap,&mygraph);
                move = minimax(maxDepth,&gameMap,&mygraph,INT_MIN,INT_MAX,&bestWall,pre);
                pre = move;
			}
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
                                continue;
                            }
                        }
                    }
				}
				else {
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
                                continue;
                            }
                        }
                    }
				}
				else {
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
                                continue;
                            }
                        }
					}
				}
				else {
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
                                continue;
                            }
                        }
					}
				}
				else {
					continue;
				}
			}
			else if(move == 6){
                int x,y, z;
                char c;
                while(1){
                    x = rand() % (gameMap.n - 1);
                    y = rand() % (gameMap.m - 1);
                    z = rand() % 2;
                    if (z) c = 'h';
					else c = 'v';
                    if ((c == 'h') && (x >= gameMap.n || y >= gameMap.m - 1)) {
                        x--, y--;
                    }
                    else if ((c == 'v') && (x >= gameMap.n - 1 || y >= gameMap.m)) {
                        x--, y--;
                    }
                    if (gameMap.p2w == 0) {
					continue;
				}
                    else if(validWallH(c, x, y, gameMap, &mygraph)){
                        gameMap.player2_walls[10 - gameMap.p2w][0] = x;
                        gameMap.player2_walls[10 - gameMap.p2w][1] = y;
                        gameMap.player2_walls[10 - gameMap.p2w][2] = 0;
                        gameMap.Map[x][y] += 10;
                        gameMap.Map[x][y + 1] += 10;
                        key++;
                        gameMap.p2w--;
                        break;
                    }
                    else if(validWallV(c, x, y, gameMap, &mygraph)){
                        gameMap.player2_walls[10 - gameMap.p2w][0] = x;
                        gameMap.player2_walls[10 - gameMap.p2w][1] = y;
                        gameMap.player2_walls[10 - gameMap.p2w][2] = 0;
                        gameMap.Map[x][y] += 100;
                        gameMap.Map[x + 1][y] += 100;
                        key++;
                        gameMap.p2w--;
                        break;
                    }
                    else{
                        continue;
                    }
                }
            }
			else {
				continue;
			}
		}
	} while(1);
	}
    return 0;
}
