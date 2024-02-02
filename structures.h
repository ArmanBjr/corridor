struct Graph{
    int visited[10000];
    int adjList[10000][4];
    int dist[10000];
    int visitSet[10000];
};

struct myWall{
    char typeH,typeV,Best;
    int sx,sy;
};

struct board{
    int n, m;
    int Map[100][100];
    int p1x, p1y, p2x, p2y;
    int p1w, p2w;
    int player1_walls[10][3];
    int player2_walls[10][3];
    int p1placedwalls, p2placedwalls;
    struct myWall vw[10000];
};