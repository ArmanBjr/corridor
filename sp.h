const int DELAY = 1800;

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
            sleep(DELAY);
            max_walls_checker(gameMap);
            PrintTheMap(*gameMap);
            printf("player %d's turn(0 to exit , W for placing wall , arrows to move): \n", key % 2 + 1);
            printf("you have lost your placed walls!\n");
            sleep(DELAY - 1000);
            return 10;
        }
        else if (first == 2) {
            do {
                second = random_maker(2, 5);
            } while(!(second != 4 && (*gameMap).p1w >= second));
            (*gameMap).p1w -= second;
            sleep(DELAY);
            max_walls_checker(gameMap);
            PrintTheMap(*gameMap);
            printf("player %d's turn(0 to exit , W for placing wall , arrows to move): \n", key % 2 + 1);
            printf("you have lost %d walls\n", second);
            sleep(DELAY - 1000);
            return 20;
        }
        else if (first == 3) {
            second = random_maker(1, 2);
            sleep(DELAY);
            printf("you can not move for %d round(s)", second);
            sleep(DELAY - 1000);
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
            sleep(DELAY);
            max_walls_checker(gameMap);
            PrintTheMap(*gameMap);
            printf("player %d's turn(0 to exit , W for placing wall , arrows to move): \n", key % 2 + 1);
            printf("you have lost your placed walls!\n");
            sleep(DELAY - 1000);
            return 10;
        }
        else if (first == 2) {
            do {
                second = random_maker(2, 5);
            } while(!(second != 4 && (*gameMap).p2w >= second));
            (*gameMap).p2w -= second;
            sleep(DELAY);
            max_walls_checker(gameMap);
            PrintTheMap(*gameMap);
            printf("player %d's turn(0 to exit , W for placing wall , arrows to move): \n", key % 2 + 1);
            printf("you have lost %d walls\n", second);
            sleep(DELAY - 1000);
            return 20;
        }
        else if (first == 3) {
            second = random_maker(1, 2);
            sleep(DELAY);
            printf("you can not move for %d round(s)", second);
            sleep(DELAY - 1000);
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
            sleep(DELAY);
            max_walls_checker(gameMap);
            PrintTheMap(*gameMap);
            printf("player %d's turn(0 to exit , W for placing wall , arrows to move): \n", key % 2 + 1);
            printf("your enemy has lost %d walls and you have %d more walls\n", mines, mines);
            sleep(DELAY - 1000);
        }
        else {
            do {
                plus = random_maker(2, 5);
            } while(plus == 4);
            gameMap->p1w += plus;

            sleep(DELAY);
            max_walls_checker(gameMap);
            PrintTheMap(*gameMap);
            printf("player %d's turn(0 to exit , W for placing wall , arrows to move): \n", key % 2 + 1);
            printf("you have %d more walls now\n", plus);
            sleep(DELAY - 1000);
        }
    }
    else {
        if (ran == 1 && gameMap->p1w >= 2) {
            do {
                mines = random_maker(1, 2);
            } while(mines > gameMap->p1w);
            gameMap->p1w -= mines;
            gameMap->p2w += mines;
            sleep(DELAY);
            max_walls_checker(gameMap);
            PrintTheMap(*gameMap);
            printf("player %d's turn(0 to exit , W for placing wall , arrows to move): \n", key % 2 + 1);
            printf("your enemy has lost %d walls and you have %d more walls\n", mines, mines);
            sleep(DELAY - 1000);
        }
        else {
            do {
                plus = random_maker(2, 5);
            } while(plus == 4);
            gameMap->p2w += plus;
            sleep(DELAY);
            max_walls_checker(gameMap);
            PrintTheMap(*gameMap);
            printf("player %d's turn(0 to exit , W for placing wall , arrows to move): \n", key % 2 + 1);
            printf("you have %d more walls now\n", plus);
            sleep(DELAY - 1000);
        }
    }
}
