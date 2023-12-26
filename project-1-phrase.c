#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

struct board{ //this the structue that we need to save the board
    int n, m; // size of thg map
    int Map[100][100]; // an array so show the status of each cell
    int p1x, p1y, p2x, p2y; // the location of players
    int p1w, p2w; // the number of player's walls
};

void setTextColor(int textColor, int backColor) { // a function to change the color
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int colorAttribute = backColor << 4 | textColor;
	SetConsoleTextAttribute(consoleHandle, colorAttribute);
}

void clearScreen() { // a function to clear the screen
	system("cls");
}


void PrintTheMap(struct board GameMap) { // a function to print the map
// each cell has a 3-digit number, the first number shows if there is a wall at the left of that cell or not, the second
// one shows if there is a wall at the top of that cell or not and the last one shows wheter there is a player or not(0 stands as nothing, 1 stands as player 1 and so does 2)
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
            if (up == 1) printf("...."); // a normal way
            else {
    			setTextColor(4, 0);
				printf("===="); // a wall
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
            if (left == 1) printf(":"); // a normal way
            else {
            	setTextColor(4, 0);
				printf("|"); // a wall
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
    scanf("%d", &n); // it gets the size of the map
    struct board gameMap;
    int x1, y1, x2, y2;
    m = n, gameMap.n = n, gameMap.m = m;
    do { 
    	printf("please enter the location of the first player: \n");
    	scanf("%d %d", &gameMap.p1x, &gameMap.p1y);
    	if(!(0 <= gameMap.p1x && gameMap.p1x < gameMap.n && 0 <= gameMap.p1y && gameMap.p1y < gameMap.m)) printf("invalid input! try again: \n"); //it check if the location is valid or not
		// a location is not valid if it is outside the map, it is also considered that the location of the first cell is (0, 0) and the last cell is (n - 1, n - 1)
    	
	} while(!(0 <= gameMap.p1x && gameMap.p1x < gameMap.n && 0 <= gameMap.p1y && gameMap.p1y < gameMap.m));
	do {
    	printf("please enter the location of the second player: \n");
    	scanf("%d %d", &gameMap.p2x, &gameMap.p2y);
    	if (!(0 <= gameMap.p2x && gameMap.p2x < gameMap.n && 0 <= gameMap.p2y && gameMap.p2y < gameMap.m)&& gameMap.p2x != gameMap.p1x && gameMap.p2y != gameMap.p1y) printf("invalid input! try again: \n");
		// same as the previous one, but it also checks if it is placing in the place of the 1st player or not
	} while(!(0 <= gameMap.p2x && gameMap.p2x < gameMap.n && 0 <= gameMap.p2y && gameMap.p2y < gameMap.m)&& gameMap.p2x != gameMap.p1x && gameMap.p2y != gameMap.p1y);

    for (i = 0; i < n + 2; i++) {
        for (j = 0; j < m + 1; j++) {
            gameMap.Map[i][j] = 110;
        } // fulfiling tha map as if there is no player and wall
    }
    gameMap.Map[gameMap.p1x][gameMap.p1y] = 111; // puting the player 1 at the right place
    gameMap.Map[gameMap.p2x][gameMap.p2y] = 112; // doing the same thing for player number 2
    int p1Wall, p2Wall;
    do {
    	printf("please enter the number of first player's walls: \n");
    	scanf("%d", &p1Wall);
    	if (p1Wall > 10) printf("you can not have more than 10 walls! try again: \n"); // we know that there can be only 10 walls for each player
		//it is also considered that the user does not enter a charachter that is not integer
	} while(p1Wall > 10 || p1Wall % 1 != 0);
	int x, y;
	char c;
	for (i = 0; i < p1Wall; i++) {
		printf("player number 1, please enter the wall number %d starting location and type(H or V): \n", i + 1);
		scanf("%d %d %c", &x, &y, &c); // getting the location of each player's walls
		if (x >= n - 1 || y >= m - 1) { // checking if it is valid or not
			printf("Error! you can not place a wall there! please try again: \n");
			i--;
		}
		else if ((c == 'H' || c == 'h') && ((gameMap.Map[x][y] / 10)) % 10 == 2 || (gameMap.Map[x][y + 1] / 10) % 10 == 2) { // checking if there was a wall from before or not
			printf("Error! you can not place a wall there! please try again: \n");
			i--;
		}
		else if ((c == 'V' || c == 'v') && (gameMap.Map[x][y] / 100 == 2 || gameMap.Map[x + 1][y] / 100 == 2)) { // same as the previous one
			printf("Error! you can not place a wall there! please try again: \n");
			i--;
		}
		else {
			if (c == 'H' || c == 'h') {
				gameMap.Map[x][y] += 10; // we said that the second digit stands as a symbol for existing of a wall at the left(1 as no 2 as yes) so of there is 
				// going to be a wall the second digit should be 2, we know that it is already ..1.. sth like 110 so if we add 10 to the number it shows the correct status
				gameMap.Map[x][y + 1] += 10;
			}
			else if (c == 'V' || c == 'v'){
				gameMap.Map[x][y] += 100; // same for the first digit
				gameMap.Map[x + 1][y] += 100;
			}
			else {
				printf("Error! you have entered invalid charachter! try again: \n"); //if they input an inlvalid charachter like 'b'
				i--;
			}
		}
	}
	do { // the same for the second player(if the game becomes a 4-person game this to do-whiles should be made into functions which will be done in upcomming projects)
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
    PrintTheMap(gameMap); // it prints the map
}
/* 
there is still sth missing. you might have understood it. yes exactly! we know that the user should not close the way of the opponent to the ohter side 
but this programm does not check that. a bfs is needed and it will be presented in upcomming days. thank you:)
*/

