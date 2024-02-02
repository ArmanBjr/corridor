#include "structures.h"
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
