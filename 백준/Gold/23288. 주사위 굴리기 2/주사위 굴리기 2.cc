#include <bits/stdc++.h>

using namespace std;

int n, m, k;
int field[21][21];
int scoreBoard[21][21];

int dice[7]={0,1,3,6,4,5,2};
int dirX[4]={0,1,0,-1};//0 right, 1 down, 2 left, 3 up
int dirY[4]={1,0,-1,0};
int diceDir=0;
int sumScore=0;

void input(){
    cin>>n>>m>>k;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>field[i][j];
        }
    }
}

void rollDice(int dir){
    if(dir == 0){
        int temp = dice[1];
        dice[1] = dice[4];
        dice[4] = dice[3];
        dice[3] = dice[2];
        dice[2] = temp;


    }
    else if(dir ==1){
        int temp = dice[1];
        dice[1] = dice[6];
        dice[6] = dice[3];
        dice[3] = dice[5];
        dice[5] = temp;
    }
    else if(dir==2){
        int temp = dice[1];
        dice[1] = dice[2];
        dice[2] = dice[3];
        dice[3] = dice[4];
        dice[4] = temp;
    }
    else if(dir==3){
        int temp = dice[1];
        dice[1] = dice[5];
        dice[5] = dice[3];
        dice[3] = dice[6];
        dice[6] = temp;
    }
}

void changeDir(int x, int y){
    //x,y과 현재 주사위 좌표
    //cout<<"현재 주사위 바닥 : "<<dice[3]<<"\n";
    if(dice[3] > field[x][y]){
        //90도 시계방향
        diceDir++;
        diceDir%=4;
    }
    else if(dice[3]<field[x][y]){
        //90도 반시계
        diceDir+=3;
        diceDir%=4;
    }
    else{
        //유지
    }

    //그런데 이렇게 방향 바꿨는데 다음에 이동 못하면 또 귀찮으니까 방향 관련해서는 여기서 다 처리하자
    int nextX = x+dirX[diceDir];
    int nextY = y+dirY[diceDir];

    if(!(nextX>=1 && nextX<=n && nextY>=1 && nextY<=m)){
        diceDir+=2;
        diceDir%=4;
    }
}

void scoring(int x, int y){
    //현재 위치 x,y
    //cout<<x<<","<<y<<"에 있는 값인 "<<field[x][y]<<"와 연속되면 같은 칸들을 찾습니다.\n";
    if(scoreBoard[x][y]>0){
        sumScore += (field[x][y]*scoreBoard[x][y]);
        return;
    }
    int visited[21][21];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            visited[i][j]=0;
        }
    }
    queue<pair<int, int>> q;
    q.push({x,y});
    visited[x][y]=1;
    int num=1;
    while(!q.empty()){
        auto start = q.front(); q.pop();

        int sx = start.first; int sy = start.second;

        for(int i=0;i<=3;i++){
            int nx = sx + dirX[i];
            int ny = sy + dirY[i];
            //cout<<nx<<","<<ny<<"좌표 visited : "<< visited[nx][ny]<<"\n";

            if(nx>=1 && nx<=n && ny>=1 && ny<=m){
                if(visited[nx][ny]==0){
                    if(field[nx][ny]==field[x][y]){
                        num++;
                        visited[nx][ny]=1;
                        q.push({nx,ny});
                    }
                }
            }
        }
    }
    scoreBoard[x][y] = num;
    sumScore += (field[x][y]*num);
}

void solution(){
    int sx = 1; int sy = 1;
    while(k--){
        rollDice(diceDir);
        int nextX = sx + dirX[diceDir];
        int nextY = sy + dirY[diceDir];
        
        //cout<<nextX<<","<<nextY<<"로 이동함 시발거\n";

        scoring(nextX, nextY);

        changeDir(nextX, nextY);
        //cout<<diceDir<<"로 방향 변경\n";
        sx = nextX;
        sy = nextY;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(0);

    input();

    solution();

    cout<<sumScore;
}