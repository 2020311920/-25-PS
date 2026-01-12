#include <bits/stdc++.h>

using namespace std;

int n,m,x,y,k;
int field[21][21];

int dice[7];//1 up, 2 down, 3 east, 4 west, 5 south, 6 north

bool rollDice(int k, bool work){
    if(k==1 && y+1<=m){
        //동쪽으로 굴릴 수 있으니 명령대로 굴린다.
        int up = dice[1];
        dice[1] = dice[4];// 서쪽에 있던 애가 위로
        dice[4] = dice[2];//아래에 있던 애가 서로
        dice[2] = dice[3];//동쪽에 있던 애가 아래로
        dice[3] = up; //위에 있던 애가 동쪽으로 

        y+=1;
        return work;
    }

    if(k==2 && y-1>=1){
        //서쪽으로 굴릴 수 있으니 굴린다.

        int up = dice[1];
        dice[1] = dice[3];
        dice[3] = dice[2];
        dice[2] = dice[4];
        dice[4] = up;

        y-=1;
        return work;
    }

    if(k==4 && x+1<=n){
        //남쪽으로 굴릴 수 있으니 굴린다.
        int up = dice[1];
        dice[1] = dice[6];
        dice[6] = dice[2];
        dice[2] = dice[5];
        dice[5] = up;

        x+=1;
        return work;
    }

    if(k==3 && x-1>=1){
        //북쪽으로 굴릴 수 있으니 굴린다,
        int up = dice[1];
        dice[1] = dice[5];
        dice[5] = dice[2];
        dice[2] = dice[6];
        dice[6] = up;

        x-=1;
        return work;
    }

    else return !work;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>x>>y>>k;

    x+=1;
    y+=1; //나는 1,1이 편하니까

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>field[i][j];
        }
    }

    for(int i=1;i<=k;i++){
        int dir;
        cin>>dir;
        //1 east, 2 west, 3 north, 4 south
        //이제 k에 따라서 시뮬레이션이 돌아간다.
        
        //시뮬이 정상적으로 진행될 수도, 바깥으로 이동명령이라 무시될 수도 있으니
        bool work = true;
        work = rollDice(dir, work); //각 면이 이동했고, 주사위 좌표도 이동함

        if(!work) continue; // 만약 명령 무시면 그냥 다음 명령 입력

        //1. 이동한 칸은 x,y 이게 0이면, 주사위의 바닥 dice[2]의 수가 칸으로
        if(field[x][y]==0) field[x][y] = dice[2];

        else{
            //이동한 칸의 수가 0이 아니면, 그 수가 dice[2]로 복사되고, 그 칸이 0이 됨
            dice[2] = field[x][y];
            field[x][y] = 0;
        }

        //이런 룰이 다 진행됐다면 dice[1]을 출력
        cout<<dice[1]<<"\n";
    }
}