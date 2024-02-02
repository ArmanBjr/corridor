int mindist (const struct Graph *gr, struct board mapp){
    int minimum = INT_MAX, min_index;
    int i;
    for(i = 0;i<(mapp.n+2)*(mapp.m+1);i++){
        if(gr->visitSet[i]==0 && gr->dist[i]<=minimum){
            minimum = gr->dist[i];
            min_index = i;
        }
    }
    return min_index;
}

void dijkastra(struct Graph *gr,int src,struct board mapp){
	int i;
    for(i=0;i<(mapp.n+2)*(mapp.m+1);i++){
        gr->dist[i] = INT_MAX;
        gr->visitSet[i]=0;
    }
    gr->dist[src]=0;
    int j, k;
    for(i=0;i<(mapp.n+2)*(mapp.m+1);i++){
        int u = mindist(gr,mapp);
        gr->visitSet[u] = 1;
        int adj[] = {0,0,0,0};
        for(k=0;k<4;k++){
            if(gr->adjList[u][k]!=-1)
                adj[k]=gr->adjList[u][k];
        }
        for(j=0;j<(mapp.n+2)*(mapp.m+1);j++){
            if(gr->visitSet[j]==0){
                for(k=0;k<4;k++){
                    if(gr->adjList[u][k] == j && gr->dist[u]!=INT_MAX){
                        if(gr->dist[u]+1<gr->dist[j]){
                            gr->dist[j]=gr->dist[u]+1;
                        }
                    }
                }
            }
        }
    }
}

//left = GameMap.Map[i][j] / 100;
//up = (GameMap.Map[i][j] / 10) % 10;

void findMoves(struct board gameState, int w, int arr[]){
    int x,y;
    if(w==1){
        x=gameState.p1x;
        y=gameState.p1y;
    }
    else{
        x=gameState.p2x;
        y=gameState.p2y;
    }
    if(gameState.Map[x][y]/100 == 1 && y > 0)
        arr[0] = 1;
    if(gameState.Map[x][y + 1]/100 == 1 && y < gameState.m - 1)
        arr[1] = 1;
    if((gameState.Map[x][y]/10)%10 == 1 && x > 0)
        arr[2] = 1;
    if((gameState.Map[x + 1][y]/10)%10 == 1 && x < gameState.n - 1)
        arr[3] = 1;
    return;
}

void findWalls(struct board *gameState, struct Graph *gr){
    struct Graph g = *gr;
    int i, j;
    for(i=0;i<gameState->n+2;i++){
        for(j=0;j<gameState->m+1;j++){
            gameState->vw[i*(gameState->m + 1)+j].sx = i;
            gameState->vw[i*(gameState->m + 1)+j].sy = j;
            gameState->vw[i*(gameState->m + 1)+j].typeH = 'A';
            gameState->vw[i*(gameState->m + 1)+j].typeV = 'A';
            if (i >= gameState->n || j >= gameState->m - 1) {
                gameState->vw[i*(gameState->m + 1)+j].typeH = 'N';
            }
            if (i >= gameState->n - 1 || j >= gameState->m) {
                gameState->vw[i*(gameState->m + 1)+j].typeV = 'N';
            }
            if(gameState->vw[i*(gameState->m + 1)+j].typeH != 'N'){
                g = *gr;
                if(validWallH('h',i,j,*gameState,&g))
                    gameState->vw[i*(gameState->m + 1)+j].typeH = 'Y';
            }
            if(gameState->vw[i*(gameState->m + 1)+j].typeV != 'N'){
                g = *gr;
                if(validWallV('v',i,j,*gameState,&g))
                    gameState->vw[i*(gameState->m + 1)+j].typeV = 'Y';
            }
        }
    }
}

int terminal_state(struct board mymap){
    if (mymap.p2x == 0)
        return 2;
    else if(mymap.p1x == mymap.n - 1)
        return 1;
    else
        return 0;
}

int mini(int depth, struct board *gamemap, struct Graph *mygraph,int alpha, int beta);

int maxi(int depth, struct board *gamemap, struct Graph *mygraph,int alpha, int beta) {
    if(terminal_state(*gamemap) == 1)
        return (-1000);
    else if(terminal_state(*gamemap) == 2)
        return 2000;
    if (depth == 0) {
        //printf("DEPTH = 0 & -> p1x,p1y:%d,%d & p2x,p2y:%d,%d -> utility:%d\n",gamemap.p1x,gamemap.p1y,gamemap.p2x,gamemap.p2y,utility(gamemap,mygraph));
        return utility(gamemap,mygraph);
    }
    int best_value = INT_MIN;
    // Generate all possible moves for the maximizing player
    int moves[] = {0,0,0,0};
    findMoves(*gamemap,2,moves);
    int my = -1;
    int yy = depth;
    if(moves[2] == 1){
        //printf("(%d,%d) -> ",gamemap->p2x,gamemap->p2y);
        gamemap->p2x--;
        //printf("maxi in move 3 ::: depth = %d & -> p1x,p1y:%d,%d & p2x,p2y:%d,%d -> utility:%d\n",depth,gamemap->p1x,gamemap->p1y,gamemap->p2x,gamemap->p2y,utility(gamemap,mygraph));
        my = mini(yy-1,gamemap,mygraph,alpha,beta);
        best_value = max(best_value,my);
        //printf("maxi %d ::: in depth %d\n",best_value,depth);
        gamemap->p2x++;
        //printf("\n");
        beta = min(beta,best_value);
        if(beta <= alpha)
            return best_value;
    }
    if(moves[0] == 1){
        //printf("(%d,%d) -> ",gamemap->p2x,gamemap->p2y);
        gamemap->p2y--;
        //printf("maxi in move 1 ::: depth = %d & -> p1x,p1y:%d,%d & p2x,p2y:%d,%d -> utility:%d\n",depth,gamemap->p1x,gamemap->p1y,gamemap->p2x,gamemap->p2y,utility(gamemap,mygraph));
        my = mini(yy-1,gamemap,mygraph,alpha,beta);
        best_value = max(best_value,my);
        //printf("maxi %d ::: in depth %d\n",best_value,depth);
        gamemap->p2y++;
        //printf("\n");
        beta = min(beta,best_value);
        if(beta <= alpha)
            return best_value;
    }
    if(moves[1] == 1){
        //printf("(%d,%d) -> ",gamemap->p2x,gamemap->p2y);
        gamemap->p2y++;
        //printf("maxi in move 2 ::: depth = %d & -> p1x,p1y:%d,%d & p2x,p2y:%d,%d -> utility:%d\n",depth,gamemap->p1x,gamemap->p1y,gamemap->p2x,gamemap->p2y,utility(gamemap,mygraph));
        my = mini(yy-1,gamemap,mygraph,alpha,beta);
        best_value = max(best_value,my);
        //printf("maxi %d ::: in depth %d\n",best_value,depth);
        gamemap->p2y--;
        //printf("\n");
        beta = min(beta,best_value);
        if(beta <= alpha)
            return best_value;
    }
    if(moves[3] == 1){
        //printf("(%d,%d) -> ",gamemap->p2x,gamemap->p2y);
        gamemap->p2x++;
        //printf("maxi in move 4 ::: depth = %d & -> p1x,p1y:%d,%d & p2x,p2y:%d,%d -> utility:%d\n",depth,gamemap->p1x,gamemap->p1y,gamemap->p2x,gamemap->p2y,utility(gamemap,mygraph));
        my = mini(yy-1,gamemap,mygraph,alpha,beta);
        best_value = max(best_value,my);
        //printf("maxi %d ::: in depth %d\n",best_value,depth);
        gamemap->p2x--;
        //printf("\n");
        beta = min(beta,best_value);
        if(beta <= alpha)
            return best_value;
    }
    if(gamemap->p2w > 0 && gamemap->p1x>=(gamemap->n/2 - 1)){
    	int i, j;
    	
        for(i=1;i<gamemap->n;i++){
            for(j=0;j<gamemap->m;j++){
                //printf("%d %d -> %c & %c\n",i,j,gamemap->vw[i*(gamemap->m+1)+j].typeH,gamemap->vw[i*(gamemap->m+1)+j].typeV);
                if(gamemap->vw[i*(gamemap->m+1)+j].typeH == 'Y' && i>gamemap->p1x  && j>=gamemap->p1y-1 && j<=gamemap->p1y+1){
                    delEdge((i*(gamemap->m+1)+j),(i*(gamemap->m+1)+j-gamemap->m-1),mygraph);
                    delEdge((i*(gamemap->m+1)+j+1),(i*(gamemap->m+1)+j-gamemap->m),mygraph);
                    gamemap->Map[i][j] += 10;
                    gamemap->Map[i][j + 1] += 10;
                    gamemap->p2w--;
                    gamemap->vw[i*(gamemap->m+1)+j].typeH == 'N';
                    my = mini(yy-1,gamemap,mygraph,alpha,beta);
                    best_value = max(best_value,my);
                    undoDeleteEdge((i*(gamemap->m+1)+j),(i*(gamemap->m+1)+j-gamemap->m-1),mygraph);
                    undoDeleteEdge((i*(gamemap->m+1)+j+1),(i*(gamemap->m+1)+j-gamemap->m),mygraph);
                    gamemap->Map[i][j] -= 10;
                    gamemap->Map[i][j + 1] -= 10;
                    gamemap->vw[i*(gamemap->m+1)+j].typeH == 'Y';
                    gamemap->p2w++;
                    beta = min(beta,best_value);
                    if(beta <= alpha)
                        return best_value;
                }
                if(gamemap->vw[i*(gamemap->m+1)+j].typeV == 'Y' && i>=gamemap->p1x - 1 && j>=gamemap->p1y-2 && j<=gamemap->p1y+3){
                    delEdge((i*(gamemap->m+1)+j),(i*(gamemap->m+1)+j-1),mygraph);
                    delEdge((i*(gamemap->m+1)+j+gamemap->m+1),(i*(gamemap->m+1)+j+gamemap->m),mygraph);
                    gamemap->Map[i][j] += 100;
                    gamemap->Map[i + 1][j] += 100;
                    gamemap->p2w--;
                    gamemap->vw[i*(gamemap->m+1)+j].typeV = 'N';
                    my = mini(yy-1,gamemap,mygraph,alpha,beta);
                    best_value = max(best_value,my);
                    undoDeleteEdge((i*(gamemap->m+1)+j),(i*(gamemap->m+1)+j-1),mygraph);
                    undoDeleteEdge((i*(gamemap->m+1)+j+gamemap->m+1),(i*(gamemap->m+1)+j+gamemap->m),mygraph);
                    gamemap->Map[i][j] -= 100;
                    gamemap->Map[i + 1][j] -= 100;
                    gamemap->p2w++;
                    gamemap->vw[i*(gamemap->m+1)+j].typeV = 'Y';
                    beta = min(beta,best_value);
                    if(beta <= alpha)
                        return best_value;
                }
            }
        }
    }
    //printf("maxi FINAL IN DEPTH : %d ::: %d\n",depth,best_value);
    return best_value;
}

int mini(int depth, struct board *gamemap, struct Graph *mygraph, int alpha, int beta) {
    if(terminal_state(*gamemap) == 1)
        return (-1000);
    else if(terminal_state(*gamemap) == 2)
        return 2000;
    if (depth == 0) {
        //printf("DEPTH = 0 & -> p1x,p1y:%d,%d & p2x,p2y:%d,%d -> utility:%d\n",gamemap.p1x,gamemap.p1y,gamemap.p2x,gamemap.p2y,utility(gamemap,mygraph));
        return utility(gamemap,mygraph);
    }
    int best_value = INT_MAX;
    // Generate all possible moves for the maximizing player
    int moves[] = {0,0,0,0};
    findMoves(*gamemap,1,moves);
    //printf("%d %d %d %d\n",moves[0],moves[1],moves[2],moves[3]);
    int my = -1;
    int yy = depth;
    if(moves[2] == 1){
        gamemap->p1x--;
        //printf("mini in move 3 ::: depth = %d & -> p1x,p1y:%d,%d & p2x,p2y:%d,%d -> utility:%d\n",depth,gamemap->p1x,gamemap->p1y,gamemap->p2x,gamemap->p2y,utility(gamemap,mygraph));
        my = maxi(yy-1,gamemap,mygraph,alpha,beta);
        best_value = min(best_value,my);
        //printf("mini > %d ::: in depth %d\n",best_value,depth);
        gamemap->p1x++;
        alpha = max(alpha,best_value);
        if(beta <= alpha)
            return best_value;
    }
    if(moves[0] == 1){
        gamemap->p1y--;
        //printf("mini in move 1 ::: depth = %d & -> p1x,p1y:%d,%d & p2x,p2y:%d,%d -> utility:%d\n",depth,gamemap->p1x,gamemap->p1y,gamemap->p2x,gamemap->p2y,utility(gamemap,mygraph));
        my = maxi(yy-1,gamemap,mygraph,alpha,beta);
        best_value = min(best_value,my);
        //printf("mini ! %d ::: in depth %d\n",best_value,depth);
        gamemap->p1y++;
        alpha = max(alpha,best_value);
        if(beta <= alpha)
            return best_value;
    }
    if(moves[1] == 1){
        gamemap->p1y++;
        //printf("mini in move 2 ::: depth = %d & -> p1x,p1y:%d,%d & p2x,p2y:%d,%d -> utility:%d\n",depth,gamemap->p1x,gamemap->p1y,gamemap->p2x,gamemap->p2y,utility(gamemap,mygraph));
        my = maxi(yy-1,gamemap,mygraph,alpha,beta);
        best_value = min(best_value,my);
        //printf("mini < %d ::: in depth %d\n",best_value,depth);
        gamemap->p1y--;
        alpha = max(alpha,best_value);
        if(beta <= alpha)
            return best_value;
    }
    if(moves[3] == 1){
        gamemap->p1x++;
        //printf("mini in move 4 ::: depth = %d & -> p1x,p1y:%d,%d & p2x,p2y:%d,%d -> utility:%d\n",depth,gamemap->p1x,gamemap->p1y,gamemap->p2x,gamemap->p2y,utility(gamemap,mygraph));
        my = maxi(yy-1,gamemap,mygraph,alpha,beta);
        best_value = min(best_value,my);
        //printf("mini ? %d ::: in depth %d\n",best_value,depth);
        gamemap->p1x--;
        alpha = max(alpha,best_value);
        if(beta <= alpha)
            return best_value;
    }
    if(gamemap->p1w > 0 && gamemap->p2x<=(gamemap->n/2 + 1)){
    	int i, j;
        for(i=1;i<gamemap->n;i++){
            for(j=0;j<gamemap->m+2;j++){
                if(gamemap->vw[i*(gamemap->m+1)+j].typeH == 'Y' && i<gamemap->p2x  && j>=gamemap->p2y-1 && j<=gamemap->p2y+1){
                    delEdge((i*(gamemap->m+1)+j),(i*(gamemap->m+1)+j-gamemap->m-1),mygraph);
                    delEdge((i*(gamemap->m+1)+j+1),(i*(gamemap->m+1)+j-gamemap->m),mygraph);
                    gamemap->Map[i][j] += 10;
                    gamemap->Map[i][j + 1] += 10;
                    gamemap->p1w--;
                    gamemap->vw[i*(gamemap->m+1)+j].typeH == 'N';
                    my = maxi(yy-1,gamemap,mygraph,alpha,beta);
                    best_value = min(best_value,my);
                    undoDeleteEdge((i*(gamemap->m+1)+j),(i*(gamemap->m+1)+j-gamemap->m-1),mygraph);
                    undoDeleteEdge((i*(gamemap->m+1)+j+1),(i*(gamemap->m+1)+j-gamemap->m),mygraph);
                    gamemap->Map[i][j] -= 10;
                    gamemap->Map[i][j + 1] -= 10;
                    gamemap->p1w++;
                    gamemap->vw[i*(gamemap->m+1)+j].typeH == 'Y';
                    alpha = max(alpha,best_value);
                    if(beta <= alpha)
                        return best_value;
                }
                if(gamemap->vw[i*(gamemap->m+1)+j].typeV == 'Y' && i>=gamemap->p2x + 1 && j>=gamemap->p2y-2 && j<=gamemap->p2y+3){
                    delEdge((i*(gamemap->m+1)+j),(i*(gamemap->m+1)+j-1),mygraph);
                    delEdge((i*(gamemap->m+1)+j+gamemap->m+1),(i*(gamemap->m+1)+j+gamemap->m),mygraph);
                    gamemap->Map[i][j] += 100;
                    gamemap->Map[i + 1][j] += 100;
                    gamemap->p1w--;
                    gamemap->vw[i*(gamemap->m+1)+j].typeV == 'N';
                    my = maxi(yy-1,gamemap,mygraph,alpha,beta);
                    best_value = min(best_value,my);
                    undoDeleteEdge((i*(gamemap->m+1)+j),(i*(gamemap->m+1)+j-1),mygraph);
                    undoDeleteEdge((i*(gamemap->m+1)+j+gamemap->m+1),(i*(gamemap->m+1)+j+gamemap->m),mygraph);
                    gamemap->Map[i][j] -= 100;
                    gamemap->Map[i + 1][j] -= 100;
                    gamemap->p1w++;
                    gamemap->vw[i*(gamemap->m+1)+j].typeV == 'Y';
                    alpha = max(alpha,best_value);
                    if(beta <= alpha)
                        return best_value;
                }
            }
        }
    }
    //printf("mini FINAL IN DEPTH : %d ::: %d\n",depth,best_value);
    return best_value;
}

int minimax(int depth, struct board *gamemap, struct Graph *mygraph,int alpha, int beta, struct myWall *theBest, int pre){
    int best_value = INT_MIN;
    int best2 = best_value;
    int best_move = 0;
    // Generate all possible moves for the maximizing player
    int moves[] = {0,0,0,0};
    findMoves(*gamemap,2,moves);
    int my = -1;
    if(moves[3] == 1){
        gamemap->p2x++;
        my = mini(depth,gamemap,mygraph,alpha,beta);
        if(best_value<=my){
            best_value = my;
            best_move = 4;
        }
        gamemap->p2x--;
        //printf("-----------------down-------|%d|----------|%d|--------------------------------------------------------------------------------\n",my,best_value);
    }
    if(moves[1] == 1){
        gamemap->p2y++;
        my = mini(depth,gamemap,mygraph,alpha,beta);
        if(best_value<=my){
            best_value = my;
            best_move = 2;
        }
        gamemap->p2y--;
        //printf("-----------------right-------|%d|----------|%d|-----------------------------------------------------------------------------\n",my,best_value);
    }
    if(moves[2] == 1){
        gamemap->p2x--;
        my = mini(depth,gamemap,mygraph,alpha,beta);
        if(best_value<=my){
            best_value = my;
            best_move = 3;
        }
        gamemap->p2x++;
        //printf("-----------------up---------|%d|--------|%d|----------------------------------------------------------------------------------\n",my,best_value);
    }
    if(moves[0] == 1){
        gamemap->p2y--;
        my = mini(depth,gamemap,mygraph,alpha,beta);
        if(best_value<=my){
            best_value = my;
            best_move = 1;
        }
        gamemap->p2y++;
        //printf("-----------------left-------|%d|----------|%d|----------------------------------------------------------------------------\n",my,best_value);
    }
    if(gamemap->p2w > 0 && gamemap->p1x>=(gamemap->n/2 - 1)){
    	int i, j;
        for(i=gamemap->n;i>0;i--){
            for(j=0;j<gamemap->m;j++){
                //printf("%d %d -> %c & %c\n",i,j,gamemap->vw[i*(gamemap->m+1)+j].typeH,gamemap->vw[i*(gamemap->m+1)+j].typeV);
                //printf("%d ::: %d\n",gamemap->p1x,i);
                if(gamemap->vw[i*(gamemap->m+1)+j].typeH == 'Y' && i>gamemap->p1x && j>=gamemap->p1y-1 && j<=gamemap->p1y+1){
                    //printf("H----------%d %d----------:",i,j);
                    delEdge((i*(gamemap->m+1)+j),(i*(gamemap->m+1)+j-gamemap->m-1),mygraph);
                    delEdge((i*(gamemap->m+1)+j+1),(i*(gamemap->m+1)+j-gamemap->m),mygraph);
                    gamemap->Map[i][j] += 10;
                    gamemap->Map[i][j + 1] += 10;
                    gamemap->p2w--;
                    my = mini(depth,gamemap,mygraph,alpha,beta);
                    //printf("%d\n",my);
                    if(best2<=my){
                        best2 = my;
                        theBest->sx = i;
                        theBest->sy = j;
                        theBest->Best = 'H';
                    }
                    undoDeleteEdge((i*(gamemap->m+1)+j),(i*(gamemap->m+1)+j-gamemap->m-1),mygraph);
                    undoDeleteEdge((i*(gamemap->m+1)+j+1),(i*(gamemap->m+1)+j-gamemap->m),mygraph);
                    gamemap->Map[i][j] -= 10;
                    gamemap->Map[i][j + 1] -= 10;
                    gamemap->p2w++;
                }
            }
        }

        for(i=gamemap->n;i>0;i--){
            for(j=0;j<gamemap->m;j++){
                //printf("%d %d -> %c & %c\n",i,j,gamemap->vw[i*(gamemap->m+1)+j].typeH,gamemap->vw[i*(gamemap->m+1)+j].typeV);
                if(gamemap->vw[i*(gamemap->m+1)+j].typeV == 'Y' && i>=gamemap->p1x - 1 && j>=gamemap->p1y-2 && j<=gamemap->p1y+3){
                    //printf("V----------%d %d----------:",i,j);
                    delEdge((i*(gamemap->m+1)+j),(i*(gamemap->m+1)+j-1),mygraph);
                    delEdge((i*(gamemap->m+1)+j+gamemap->m+1),(i*(gamemap->m+1)+j+gamemap->m),mygraph);
                    gamemap->Map[i][j] += 100;
                    gamemap->Map[i + 1][j] += 100;
                    gamemap->p2w--;
                    my = mini(depth,gamemap,mygraph,alpha,beta);
                    //printf("%d\n",my);
                    if(best2<=my){
                        best2 = my;
                        theBest->sx = i;
                        theBest->sy = j;
                        theBest->Best = 'V';
                    }
                    undoDeleteEdge((i*(gamemap->m+1)+j),(i*(gamemap->m+1)+j-1),mygraph);
                    undoDeleteEdge((i*(gamemap->m+1)+j+gamemap->m+1),(i*(gamemap->m+1)+j+gamemap->m),mygraph);
                    gamemap->Map[i][j] -= 100;
                    gamemap->Map[i + 1][j] -= 100;
                    gamemap->p2w++;
                }
            }
        }
    }
    if(best2>best_value)
        best_move = 6;
    //printf("-----------------walls-----------------|%d|-----------|%d|---------------------------------------------------------------------\n",best_value,best_move);
    //printf("%c in (%d,%d)\n",theBest->Best,theBest->sx,theBest->sy);
    return best_move;
}
