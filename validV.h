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

int utility(struct board *state, struct Graph *g){
    int res=0;
    dijkastra(g,(state->p1x*(state->m+1)+state->p1y),*state);
    int opdis=INT_MAX;
    int i;
    for(i=0;i<state->m+1;i++){
        opdis = min(opdis,g->dist[((state->n-1)*(state->m+1)+1)+i]);
    }
    dijkastra(g,(state->p2x*(state->m+1)+state->p2y),*state);
    int mydis=INT_MAX;
    for(i=0;i<state->m+1;i++){
        mydis = min(mydis,g->dist[i]);
    }
    res+=(state->p1w-state->p2w);
    res+= opdis*2;
    res-= mydis*2;
    res+=(state->n-1-state->p1x);
    res-=(state->p2x);
    //printf("%d,%d .VS. %d,%d %d --> %d |||||| %d \n",state->p1x,state->p1y,state->p2x,state->p2y,res,opdis,mydis);
    //printf("\n");
    return res;
}