#include <bits/stdc++.h>

using namespace std;

int n,m;
int field[9][9];

int dirX[4]={0,-1,0,1}; //0 right, 1 up, 2 left, 3 down
int dirY[4]={1,0,-1,0};

deque<pair<pair<int, int>, pair<int, int>>> cctv;
//cctv[?].second.second는 회전 정도
deque<int> cctvRotate[6]={
    {},
    {0,1,2,3},
    {0,1}, //2번 cctv인데 회전정도가 0이면 0, 2를, 1이면 1,3을
    {0,1,2,3}, // 3번 cctv니까 0이면 0,1/ 1이면 1,2...
    {0,1,2,3},
    {0}
};

deque<int> cctvCover[6]={
    {},
    {0},
    {0,2},
    {0,1},
    {0,1,2},
    {0,1,2,3}
};
int initialBlack = 0;
int minArea = 100;

void input(){
    cin>>n>>m;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>field[i][j];
            if(field[i][j]>=1 && field[i][j]<=5){
                cctv.push_back({{i,j},{field[i][j],0}});
            }

            if(field[i][j]==0) initialBlack++;
        }
    }
}

void calculate(){
    //cout<<"새 세계선 오픈\n";
    int temp[9][9];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            temp[i][j] = field[i][j];
        }
    }
    //해당 세계관을 위한 새로운 필드 복사
    int tempInitialBlack = initialBlack;
    for(auto i : cctv){
        //우선 이 cctv i의 정보들을 가져오자
        int x = i.first.first;
        int y = i.first.second;
        int ver = i.second.first;
        int startDir = i.second.second;

        
        
        deque<int> iCover = cctvCover[ver];
        //cout<<x<<","<<y<<"에 있는 cctv의 버전은 "<<ver<<"이고 지금은 "<<startDir<<"을 바라봅니다.\n";
        //cout<<"커버영역은 ";
        //for(auto j : iCover) cout<<(startDir+j)<<" ";
        //cout<<"입니다.\n";

        for(auto j : iCover){
            int nowDir = startDir + j;
            if(nowDir>3) nowDir-=4;

            //현재 x,y에서 nowDir 방향으로 쭈욱 -1로 채우는데, 벽을 만나면 스탑 그게 아니면 걍 ㄱㄱ;
            
            int nextX = x;
            int nextY = y;

            while(nextX>=1 && nextX<=n && nextY>=1 && nextY<=m){
                //이동
                if(temp[nextX][nextY]==0){
                    temp[nextX][nextY]=-1;
                    tempInitialBlack--;
                }
                else if(temp[nextX][nextY]==6) break;

                nextX += dirX[nowDir];
                nextY += dirY[nowDir];
            }
        }
    }

    if(tempInitialBlack<minArea){
        minArea=tempInitialBlack;
        // cout<<"갱신!\n";
        // for(int i=1;i<=n;i++){
        //     for(int j=1;j<=m;j++){
        //         cout<<temp[i][j]<<" ";
        //     }
        //     cout<<"\n";
        // }
    }
}

void cctvMode(int k){
    if(k==cctv.size()){
        calculate();
        return;
    }

    k++;
    
    //pair<pair<int, int>, pair<int, int>> c =cctv[k];
    int num = cctv[k-1].second.first;
    deque<int> myRotate = cctvRotate[num];
    //myRotate에는 내가 현재 다루는 cctv가 회전하는 경우의 수들이 적혀있음

    for(auto i : myRotate){
        cctv[k-1].second.second = i;
        cctvMode(k);
    }
}

void solution(){
    //먼저 모든 시시티비들의 모드를 정하자
    //모드 -> 1번 시시티비는 4가지 모드가 가능, 2번 시시티비는 2가지 모드가 가능...
    cctvMode(0);
    cout<<minArea;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(0);

    input();
    solution();

}