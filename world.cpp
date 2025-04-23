#include "world.h"

void world::LoadTexturs() {
    worldTexturs[GRASS] = LoadTexture("C:\\Users\\alecu\\Desktop\\WFC\\assets\\Grass.png");
    worldTexturs[SAND] = LoadTexture("C:\\Users\\alecu\\Desktop\\WFC\\assets\\Sand.png");
    worldTexturs[WATER] = LoadTexture("C:\\Users\\alecu\\Desktop\\WFC\\assets\\Water.png");
    worldTexturs[TREES] = LoadTexture("C:\\Users\\alecu\\Desktop\\WFC\\assets\\Trees.png");
}

void world::Draw() {
    for (int i=0; i<tiles.size(); i++) {
        for (int j=0; j<tiles[i].size(); j++) {
            if (tiles[i][j][1]) DrawTexture(worldTexturs[GRASS],i*tilesize,j*tilesize,WHITE);
            if (tiles[i][j][2]) DrawTexture(worldTexturs[SAND],i*tilesize,j*tilesize,WHITE);
            if (tiles[i][j][3]) DrawTexture(worldTexturs[WATER],i*tilesize,j*tilesize,WHITE);
            if (tiles[i][j][4]) DrawTexture(worldTexturs[TREES],i*tilesize,j*tilesize,WHITE);
        }
    }
}

world::world() {
    tiles.resize(height/tilesize);
    for (int i=0; i<tiles.size(); i++) {
        tiles[i].resize(width/tilesize);
    }

    for (int i=0; i<tiles.size(); i++) {
        for (int j=0; j<tiles[i].size(); j++) {
            tiles[i][j] = 1+2+4+8+16;
        }
    }
}

bool isColl(std::bitset<5> x) {
    int cnt = 0;
    for (int i=1; i<5; i++) {
        if (x[i] == 1) cnt++;
    }
    return cnt == 1;
}

int GetPvalue(std::bitset<5> x) {
    int cnt = 0;
    for (int i=1; i<5; i++) {
        if (x[i] == 1) cnt = i;
    }
    return cnt;
}

int GetPvalueNr(std::bitset<5> x) {
    int cnt = 0;
    for (int i=1; i<5; i++) {
        if (x[i] == 1) cnt++;
    }
    return cnt;
}

void world::Generate() {

    clock_t T1 = clock();

    srand(time(0));

    int x = rand()%tiles.size();
    int y = rand()%tiles[x].size();
    int type = rand()%4 +1;
    
    for (int k=1; k<=4; k++) tiles[x][y][k] = 0;
    tiles[x][y][type] = 1;

    std::set<std::pair<int,int>> Options;
    std::queue<std::pair<int,int>> Q;

    int di[4] = {0,0,1,-1};
    int dj[4] = {1,-1,0,0};

    Q.push({x,y});

    int itNr = 0;

    //i'm using BFS (Flood Fill)
    while (!Q.empty()) {

        int ti = Q.front().first,tj = Q.front().second;

        std::cout<<"Current Position: ["<<ti<<","<<tj<<"]\n";

        for (int f=0; f<4; f++) {
            int i = ti + di[f],j = tj + dj[f];
            if (i >= tiles.size() || j >= tiles[i].size() || i < 0 || j < 0) continue;
            if (isColl(tiles[i][j])) continue;
            for (int k=1; k<=4; k++) {
                if (Rules[GetPvalue(tiles[ti][tj])-1][k-1] == 0) tiles[i][j][k] = 0;
            }
            Options.insert({i,j});
        }


        itNr++;

        int cnt = 0,fi = -1,fj = -1,Min = 9999;

        std::queue<std::pair<int,int>> Collapsed; 

        for (auto [i,j]:Options) {
            if (isColl(tiles[i][j])) {
                Q.push({i,j});
                Collapsed.push({i,j});
                cnt++;
                continue;
            }

            int aux = GetPvalueNr(tiles[i][j]);
            if (aux < Min) {
                Min = aux;
                fi = i;
                fj = j;
            }
            
        }

        while (!Collapsed.empty()) {
            Options.erase(Collapsed.front());
            Collapsed.pop();
        }

        if (Options.size() == 0) {
            Q.pop();
            continue;
        }

        if (itNr == 7) {
            std::cout<<"";
        }

        if (cnt == 0) { // if the a collapsed tile wasnt found
            Options.erase({fi,fj});

            int type = rand()%4+1;
            while (tiles[fi][fj][type] == 0) type = rand()%4+1;

            for (int i=1; i<=4; i++) tiles[fi][fj][i] = 0;
            tiles[fi][fj][type] = 1;
            Q.push({fi,fj});
        }

        Q.pop();
    }

    clock_t T2 = clock() - T1;

    std::cout<<"Finished Generation in: "<<((float)T2)/CLOCKS_PER_SEC<<" seconds\n";

}