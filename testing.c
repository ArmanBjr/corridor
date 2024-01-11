#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

const int MAX_WALLS = 10;
int lock1 = 0, lock2 = 0;
struct board{
    int n, m;
    int Map[100][100];
    int p1x, p1y, p2x, p2y;
    int p1w, p2w;
    int player1_walls[10][3];
    int player2_walls[10][3];
    int p1placedwalls, p2placedwalls;
};

void sleep(unsigned int mseconds) {
    clock_t goal = mseconds + clock();
    while(goal > clock());
}

struct Graph{
    int visited[10000];
    int adjList[10000][4];
};

void setTextColor(int textColor, int backColor) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int colorAttribute = backColor << 4 | textColor;
	SetConsoleTextAttribute(consoleHandle, colorAttribute);
}

void max_walls_checker(struct board *gameMap) {
	int p1check;
	int p2check;
	if (gameMap->p1w > 10) {
		p1check = (gameMap->p1w) / 10;
		gameMap->p1w = p1check * 10;
	}
	if (gameMap->p2w > 10) {
		p2check = (gameMap->p2w - 1) / 10;
		gameMap->p2w = p2check * 10;
	}
	
} 
void addedge(int n,int m,int i,int j,struct Graph *mygraph){
    if(i >= n || j >= m){
        mygraph -> adjList[i * (m + 1) + j][0] = -1;
        mygraph->adjList[i * (m + 1) + j][1] = -1;
        mygraph->adjList[i * (m + 1) + j][2]= -1;
        mygraph->adjList[i * (m + 1) + j][3]= -1;
    }
    else if(i == 0){
        if(j == 0){
            mygraph -> adjList[i * (m + 1) + j][0]= i * (m + 1) + j + m + 1;
            mygraph -> adjList[i * (m + 1) + j][1]= i * (m + 1) + j + 1;
            mygraph -> adjList[i * (m + 1) + j][2]= -1;
            mygraph -> adjList[i * (m + 1) + j][3]= -1;
        }
        else if(j == m - 1){
            mygraph -> adjList[i * (m + 1) + j][0]= i * (m + 1) + j + m +1;
            mygraph -> adjList[i * (m + 1) + j][1]= i * (m + 1) + j - 1;
            mygraph -> adjList[i * (m + 1) + j][2]= -1;
            mygraph -> adjList[i * (m + 1) + j][3]= -1;
        }
        else{
            mygraph -> adjList[i * (m + 1) + j][0]= i *(m + 1) + j + m + 1;
            mygraph -> adjList[i * (m + 1) + j][1]= i * (m + 1) + j - 1;
            mygraph -> adjList[i * (m + 1) + j][2]= i * (m + 1) + j + 1;
            mygraph -> adjList[i * (m + 1) + j][3]= -1;
        }
    }
    else if(i == n - 1){
        if(j == 0){
            mygraph -> adjList[i * (m + 1) + j][0]= i * (m + 1) + j - m - 1;
            mygraph -> adjList[i * (m + 1) + j][1]= i * (m + 1) + j + 1;
            mygraph -> adjList[i * (m + 1) + j][2]= -1;
            mygraph -> adjList[i * (m + 1) + j][3]= -1;
        }
        else if(j == m - 1){
            mygraph -> adjList[i*(m+1)+j][0]= i*(m+1)+j-m-1;
            mygraph -> adjList[i * (m + 1) + j][1]= i * (m + 1) + j - 1;
            mygraph -> adjList[i * (m + 1) + j][2]= -1;
            mygraph->adjList[i * (m + 1) + j][3]= -1;
        }
        else{
            mygraph -> adjList[i * (m + 1) + j][0]= i * (m +1 ) + j - m - 1;
            mygraph -> adjList[i * (m + 1) + j][1]= i * (m + 1) + j - 1;
            mygraph -> adjList[i * (m + 1) + j][2]= i * (m + 1) + j + 1;
            mygraph -> adjList[i * (m + 1) + j][3]= -1;
        }
    }
    else{
        if(j == 0){
            mygraph -> adjList[i * (m + 1) + j][0]= i * (m + 1) + j + m + 1;
            mygraph -> adjList[i * (m + 1) + j][1]= i * (m + 1) + j - m - 1;
            mygraph -> adjList[i * (m + 1) + j][2] = i * (m + 1) + j + 1;
            mygraph -> adjList[i * (m + 1) + j][3] = -1;
        }
        else if(j == m - 1){
            mygraph -> adjList[i * (m + 1) + j][0] = i * (m + 1 ) + j + m + 1;
            mygraph -> adjList[i * (m + 1) + j][1] = i * (m + 1) + j - m - 1;
            mygraph -> adjList[i * (m + 1) + j][2] = i * (m + 1) + j - 1;
            mygraph -> adjList[i * (m + 1) + j][3]= -1;
        }
        else{
            mygraph -> adjList[i * (m + 1) + j][0] = i * (m + 1) + j + m + 1;
            mygraph->adjList[i * (m + 1) + j][1] = i * (m + 1) + j - m - 1;
            mygraph->adjList[i * (m + 1) + j][2] = i * (m + 1) + j - 1;
            mygraph->adjList[i * (m + 1) + j][3] = i * (m + 1) + j + 1;
        }
    }
}

void delEdge(int s, int e, struct Graph *gg){
	int i;
    for(i = 0; i < 4; i++){
        if(gg -> adjList[s][i] == e)
            gg -> adjList[s][i] =- 1;
    }
    for(i = 0; i < 4; i++){
        if(gg -> adjList[e][i] == s)
            gg -> adjList[e][i] =- 1;
    }
}

void undoDeleteEdge(int s,int e, struct Graph *mg){
	int i;
    for(i = 0; i < 4; i++){
        if(mg -> adjList[s][i] == -1){
            mg -> adjList[s][i] = e;
            break;
        }
    }
    for(i = 0; i < 4; i++){
        if(mg -> adjList[e][i] == -1){
            mg -> adjList[e][i] = s;
            break;
        }
    }
}

int flag1 = 0, flag2 = 0;

int dfs(int str, int who,int n,int m,struct Graph *g){
    g -> visited[str] = 1;
    if(who == 2 && str <= m - 1)
        flag2 = 1;
    if(who == 1 && str >= (n - 1) * (m + 1)){
        flag1 = 1;
    }
    int i;
    for(i = 0; i < 4;i++){
        if(g -> adjList[str][i] != -1){
            if(g -> visited[g -> adjList[str][i]] == 0)
                dfs(g -> adjList[str][i], who, n, m, g);
        }
    }
}

void makeUnVisit(struct Graph *g){
	int i;
    for(i = 0; i < 10000;i++){
        g -> visited[i] = 0;
    }
    return;
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

int random_maker(int lower, int upper) {
    int number = (rand() % (upper - lower + 1)) + lower;
    return number;
}

void deleteWalls(struct board *gameMap, struct Graph *g, int x, int y, bool check) {
    if (!check) {
        (*gameMap).Map[x][y] -= 10;
        (*gameMap).Map[x][y + 1] -= 10;
        undoDeleteEdge((x*(gameMap->m+1)+y),(x*(gameMap->m+1)+y-gameMap->m-1),g);
        undoDeleteEdge((x*(gameMap->m+1)+y+1),(x*(gameMap->m+1)+y-gameMap->m),g);
    }
    else {
        (*gameMap).Map[x][y] -= 100;
        (*gameMap).Map[x + 1][y] -= 100;
        undoDeleteEdge((x*(gameMap->m+1)+y),(x*(gameMap->m+1)+y-1),g);
        undoDeleteEdge((x*(gameMap->m+1)+y+gameMap->m+1),(x*(gameMap->m+1)+y+gameMap->m),g);
    }
}

int makeSpell(struct board *gameMap, struct Graph *g, int key) {
    srand(time(0));
    int first = random_maker(1, 3), second;
    int i, j;
    if (!(key % 2)) {
    
        if (first == 1 && gameMap->p1placedwalls == 0) {
            first++;
        }
        else if (first == 2 && (*gameMap).p1w <= 1) first++;
        if (first == 1) {
            for (i = 0; i < gameMap->p1placedwalls; i++) {
                deleteWalls(gameMap, g, (*gameMap).player1_walls[i][0], (*gameMap).player1_walls[i][1], (*gameMap).player1_walls[i][2]);
            }
            gameMap->p1placedwalls = 0;
            sleep(1000);
            max_walls_checker(gameMap);
            PrintTheMap(*gameMap);
            printf("you have lost your placed walls!\n");
            printf("player %d 's turn: \n", key % 2 + 1);
            return 10;
        }
        else if (first == 2) {
            do {
                second = random_maker(2, 5);
            } while(!(second != 4 && (*gameMap).p1w >= second));
            (*gameMap).p1w -= second;
            sleep(1000);
            max_walls_checker(gameMap);
            PrintTheMap(*gameMap);
            printf("you have lost %d walls\n", second);
            printf("player %d 's turn: \n", key % 2 + 1);
            return 20;
        }
        else if (first == 3) {
            second = random_maker(1, 2);
            printf("you can not move for %d round(s)", second);
            return second;
        }
    }
    else {
        if (first == 1 && gameMap->p2placedwalls == 0) {
            first++;
        }
        else if (first == 2 && gameMap->p2placedwalls <= 1) first++;
        if (first == 1) {
            for (i = 0; i < gameMap->p2placedwalls; i++) {
                deleteWalls(gameMap, g, (*gameMap).player2_walls[i][0], (*gameMap).player2_walls[i][1], (*gameMap).player2_walls[i][2]);
            }
            gameMap->p2placedwalls = 0;
            sleep(1000);
            max_walls_checker(gameMap);
            PrintTheMap(*gameMap);
            printf("you have lost your placed walls!\n");
            printf("player %d 's turn: \n", key % 2 + 1);
            return 10;
        }
        else if (first == 2) {
            do {
                second = random_maker(2, 5);
            } while(!(second != 4 && (*gameMap).p2w >= second));
            (*gameMap).p2w -= second;
            sleep(1000);
            max_walls_checker(gameMap);
            PrintTheMap(*gameMap);
            printf("you have lost %d walls\n", second);
            printf("player %d 's turn: \n", key % 2 + 1);
            return 20;
        }
        else if (first == 3) {
            second = random_maker(1, 2);
            printf("you can not move for %d round(s)", second);
            return second;
        }
    }
}

int makePresent(struct board *gameMap, int key) {
    srand(time(0));
    int ran, mines, plus;
	ran = random_maker(1, 2);
    if (!(key % 2)) {
        if (ran == 1 && gameMap->p2w >= 2) {
            do {
                mines = random_maker(1, 2);
            } while(mines > gameMap->p2w);
            gameMap->p2w -= mines;
            gameMap->p1w += mines;
            sleep(1000);
            max_walls_checker(gameMap);
            PrintTheMap(*gameMap);
            printf("your enemy has lost %d walls and you have %d more walls\n", mines, mines);
            printf("player %d 's turn: \n", key % 2 + 1);
        }
        else {
            do {
                plus = random_maker(2, 5);
            } while(plus == 4);
            gameMap->p1w += plus;

            sleep(1000);
            max_walls_checker(gameMap);
            PrintTheMap(*gameMap);
            printf("you have %d more walls now\n", plus);
            printf("player %d 's turn: \n", key % 2 + 1);
        }
    }
    else {
        if (ran == 1 && gameMap->p1w >= 2) {
            do {
                mines = random_maker(1, 2);
            } while(mines > gameMap->p1w);
            gameMap->p1w -= mines;
            gameMap->p2w += mines;
            sleep(1000);
            max_walls_checker(gameMap);
            PrintTheMap(*gameMap);
            printf("your enemy has lost %d walls and you have %d more walls\n", mines, mines);
            printf("player %d 's turn: \n", key % 2 + 1);
        }
        else {
            do {
                plus = random_maker(2, 5);
            } while(plus == 4);
            gameMap->p2w += plus;
            sleep(1000);
            max_walls_checker(gameMap);
            PrintTheMap(*gameMap);
            printf("you have %d more walls now\n", plus);
            printf("player %d 's turn: \n", key % 2 + 1);
        }
    }
}
bool validWallH(char c, int x, int y, struct board gameMap , struct Graph *gr) {
    if ((c == 'H' || c == 'h') && (gameMap.Map[x][y]/10)%10 != 2 && (gameMap.Map[x][y + 1]/10)%10 != 2) {
        if ((gameMap.Map[x][y + 1]/100 == 2) && (gameMap.Map[x - 1][y + 1]/100 == 2)) {
            if (!(gameMap.Map[x - 2][y + 1]/100 == 2 && gameMap.Map[x + 1][y + 1]/100 == 2)) return 0;
        }
        delEdge((x*(gameMap.m+1)+y),(x*(gameMap.m+1)+y-gameMap.m-1),gr);
        delEdge((x*(gameMap.m+1)+y+1),(x*(gameMap.m+1)+y-gameMap.m),gr);
        makeUnVisit(gr);
        flag1 = 0;
        flag2 =0;
        dfs( (gameMap.p1x*(gameMap.m+1)+gameMap.p1y),1,gameMap.n,gameMap.m,gr );
        if(flag1==1){
            makeUnVisit(gr);
            dfs( (gameMap.p2x*(gameMap.m+1)+gameMap.p2y),2,gameMap.n,gameMap.m,gr );
            if(flag2==1){
                return 1;
            }
            else{
                undoDeleteEdge((x*(gameMap.m+1)+y),(x*(gameMap.m+1)+y-gameMap.m-1),gr);
                undoDeleteEdge((x*(gameMap.m+1)+y+1),(x*(gameMap.m+1)+y-gameMap.m),gr);
                return 0;
            }
        }
        else{
            undoDeleteEdge((x*(gameMap.m+1)+y),(x*(gameMap.m+1)+y-gameMap.m-1),gr);
            undoDeleteEdge((x*(gameMap.m+1)+y+1),(x*(gameMap.m+1)+y-gameMap.m),gr);
            return 0;
        }
    }
    return 0;
}

bool validWallV(char c, int x, int y, struct board gameMap , struct Graph *gr) {
    if ((c == 'V' || c == 'v') && gameMap.Map[x][y]/100 != 2 && gameMap.Map[x + 1][y]/100 != 2) {
        if ((gameMap.Map[x + 1][y]/10) % 10 == 2 && (gameMap.Map[x + 1][y - 1]/10) % 10 == 2) {
            if (!((gameMap.Map[x + 1][y + 1]/10) % 10 == 2 && (gameMap.Map[x + 1][y - 2]/10) % 10 == 2)) return 0;
        }
        delEdge((x*(gameMap.m+1)+y),(x*(gameMap.m+1)+y-1),gr);
        delEdge((x*(gameMap.m+1)+y+gameMap.m+1),(x*(gameMap.m+1)+y+gameMap.m),gr);
        makeUnVisit(gr);
        flag1=0;
        flag2=0;
        dfs( (gameMap.p2x*(gameMap.m+1)+gameMap.p2y),2,gameMap.n,gameMap.m,gr );
        if(flag2==1){
            makeUnVisit(gr);
            dfs( (gameMap.p1x*(gameMap.m+1)+gameMap.p1y),1,gameMap.n,gameMap.m,gr );
            if(flag1==1){
                return 1;
            }
            else{
                undoDeleteEdge((x*(gameMap.m+1)+y),(x*(gameMap.m+1)+y-1),gr);
                undoDeleteEdge((x*(gameMap.m+1)+y+gameMap.m+1),(x*(gameMap.m+1)+y+gameMap.m),gr);
                return 0;
            }
        }
        else{
            undoDeleteEdge((x*(gameMap.m+1)+y),(x*(gameMap.m+1)+y-1),gr);
            undoDeleteEdge((x*(gameMap.m+1)+y+gameMap.m+1),(x*(gameMap.m+1)+y+gameMap.m),gr);
            return 0;
        }
    }
    return 0;
}

int main() {
    int n, m, i, j;
    printf("Please enter the size of the map: \n");
    scanf("%d", &n);
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
    int sw;
    do {
    	sw = 0;
    	printf("choose you opponent(c for computer and h for human): \n");
    	scanf("\n%c", &s);
    	if (!(s == 'c' || s == 'C' || s == 'H' || s == 'h')) {
    		printf("invalid input! try again: \n");
    		sw = 1;
		}
	} while (sw);
    gameMap.Map[gameMap.p1x][gameMap.p1y] = 111;
    gameMap.Map[gameMap.p2x][gameMap.p2y] = 112;
    PrintTheMap(gameMap);
    int key = 0, move;
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
                    sleep(2000);
                    continue;
                }
                else if (situation == 2) {
                    key++;
                    lock1 = 1;
                    sleep(2000);
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
                    sleep(2000);
                    continue;
                }
                else if (situation == 2) {
                    key++;
                    lock2 = 1;
                    sleep(2000);
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
                    sleep(2000);
                    continue;
                }
                else if (situation == 2) {
                    key++;
                    lock1 = 1;
                    sleep(2000);
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
			printf("computer's turn, please wait\n'");
			sleep(1000);
    		move = rand();
    		if (move % 7 == 5 || move % 7 == 0) {
    			move += 1;
			}
			move = move % 7;
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
