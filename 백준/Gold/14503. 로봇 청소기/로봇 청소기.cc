#include <bits/stdc++.h>

using namespace std;

int nowR, nowC;
int n,m;
int d;

pair<int, int> back[4] = {{1,0},{0,-1},{-1, 0}, {0, 1}};
pair<int, int> front[4] = {{-1,0},{0,1},{1, 0}, {0, -1}};
int roomState[51][51]; //0=청소필요, 1=벽, 2=청소완료

int ans = 0;

void cleaning(int nowR, int nowC, int d){
    //cout<<"현재 위치는 "<<nowR<<","<<nowC<<" 입니다\n";
    if(roomState[nowR][nowC]==0){
        //cout<<"현재위치에서 청소가 가능하므로 청소합니다.";
        ans++;
        //cout<<"현재 청소한 칸은 "<<ans<<"개입니다\n";
        roomState[nowR][nowC] = 2;
    }

    if(roomState[nowR+1][nowC]!=0 && roomState[nowR][nowC+1]!=0 && roomState[nowR-1][nowC]!=0 && roomState[nowR][nowC-1]!=0){
        //주변에 청소할 곳이 없는거야.
        //cout<<"더이상 청소할 곳이 없습니다 후진을 시도합니다.\n";
        if(roomState[nowR+back[d].first][nowC+back[d].second]==1){
            //심지어 후진하면 벽이야
            //cout<<"후진 불가, 운행을 종료합니다.\n";
            return;
        }
        else{
            //후진이 가능해
            nowR += back[d].first;
            nowC += back[d].second;
            //cout<<"후진이 가능합니다. 후진한 뒤 다시 청소를 시작합니다\n";
            //cleaning(nowR, nowC, d);
        }
    }
    
    if(roomState[nowR+1][nowC]==0 || roomState[nowR][nowC+1]==0 || roomState[nowR-1][nowC]==0 || roomState[nowR][nowC-1]==0){
        //한 군데라도 청소가 가능한거임
        int count = 4;
        while(count>0){
            count--;
            //cout<<"청소가 가능합니다. 회전하며 가능한 순간 즉시 전진합니다.\n";
            d--;
            if(d<0) d=3;
            if(roomState[nowR+front[d].first][nowC+front[d].second]==0){
                //바라보는 방향 앞쪽이 청소안된거임
                nowR += front[d].first;
                nowC += front[d].second;
                //cout<<"전집합니다.\n";
                //cleaning(nowR, nowC, d);
                break; //while안에 있기에 멈춰줘야 함. 안그럼 세계선이 열리니까 ㅇㅇ
            }
        }
        
    }

    cleaning(nowR, nowC, d);
}

int main(){
    cin>>n>>m;

    cin>>nowR>>nowC>>d;

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>roomState[i][j];
        }
    }

    cleaning(nowR, nowC, d);
    cout<<ans;
    // cout<<"\n";
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<m;j++){
    //         cout<<roomState[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
}