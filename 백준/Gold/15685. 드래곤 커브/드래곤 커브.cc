#include <bits/stdc++.h>

using namespace std;

int n;
int x, y, d, g;
vector<pair<int, int>> curves[21];

int dirX[4]={1,0,-1,0};
int dirY[4]={0,-1,0,1};

int field[101][101];

int main(){
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin>>n;

    for(int i=1;i<=n;i++){
        //n개의 드래곤 커브를 입력 받는다.
        cin>>x>>y>>d>>g;

        curves[i].push_back({x,y});
        if(x>=0 && x<=100 && y>=0 && y<=100) field[x][y] = 1;
        //0세대는 기본으로
        curves[i].push_back({x+dirX[d], y+dirY[d]});
        if(x+dirX[d]>=0 && x+dirX[d]<=100 && y+dirY[d]>=0 && y+dirY[d]<=100) field[x+dirX[d]][y+dirY[d]]=1;



        int nowGen = 0;
        while(nowGen < g){
            nowGen++;

            //기준점을 정합시다
            int originX = curves[i].back().first;
            int originY = curves[i].back().second;

            //기준점으로부터 역순으로 회전시켜줘야 나중에 기준점이 마지막으로 들어간다.
            int length = curves[i].size();
            for(int j = length-2; j>=0; j--){
                int changeX = curves[i][j].first - originX;
                int changeY = curves[i][j].second - originY;

                //이 변화량을 계산한 시계방향 90도 회전 공식에 맞게 변환하면
                int temp = changeX;
                changeX = changeY*-1;
                changeY = temp;

                int afterX = originX + changeX;
                int afterY = originY + changeY;

                curves[i].push_back({afterX, afterY});
                if(afterX>=0 && afterX<=100 && afterY>=0 && afterY<=100) field[afterX][afterY] = 1;
            }
        }

    }

    int cnt=0;

    for(int i=0;i<=100;i++){
        for(int j=0;j<=100;j++){
            if(field[i][j]==1 && field[i+1][j]==1 && field[i][j+1]==1 && field[i+1][j+1]==1) cnt++;
        }
        
    }

    cout<<cnt;
    
}