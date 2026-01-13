#include <bits/stdc++.h>

using namespace std;

int n,m;
queue<pair<int, int>> virus;//virus 큐

int field[9][9];

int maxSum=0;

void wall(int k){//dfs 돌리면서 벽을 총 3개 세운다.
    if(k==3){
        //cout<<"벽을 3개 다 세웠으므로 해당 시나리오에서 바이러스 확산 시키겠습니다.\n";
        int tempField[9][9];
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                tempField[i][j] = field[i][j];
            }
        }
        queue<pair<int, int>> tempVirus = virus;
        //이때 바이러스 큐에서 하나씩 뺴고 확산, 새로운 애들 큐에 삽입해서 끝날 때까지 확산 진행
        //cout<<virus.size()<<"\n";
        while(!tempVirus.empty()){
            pair<int, int> p = tempVirus.front();
            tempVirus.pop();
            //cout<<"확산 중입니다...\n";
            //상
            if(p.first-1>=1){
                if(tempField[p.first-1][p.second]==0){
                    //cout<<"상으로 확산 성공\n";
                    tempField[p.first-1][p.second] = 2;
                    tempVirus.push({p.first-1, p.second});
                }
            }
            //하
            if(p.first+1<=n){
                if(tempField[p.first+1][p.second]==0){
                    tempField[p.first+1][p.second] = 2;
                    tempVirus.push({p.first+1, p.second}); 
                }
                
            }
            //좌
            if(p.second-1>=1){
                if(tempField[p.first][p.second-1]==0){
                    tempField[p.first][p.second-1] = 2;
                    tempVirus.push({p.first,p.second-1});
                }
                
            }
            //우
            if(p.second+1<=m){
                if(tempField[p.first][p.second+1]==0){
                    tempField[p.first][p.second+1] = 2;
                    tempVirus.push({p.first, p.second+1});
                }
                
            }
        }

        int sum=0;
        //확산 종료 뒤에 0인 칸 세기
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(tempField[i][j]==0) sum++;
            }
        }

        if(sum>=maxSum) maxSum=sum;

        // if(sum==32){
        //     for(int i=1;i<=n;i++){
        //         for(int j=1;j<=m;j++){
        //             cout<<tempField[i][j]<<" ";
        //         }
        //         cout<<"\n";
        //     }
        // }
        return;
    }

    //cout<<"현재 "<<k<<"개의 벽을 세웠습니다.\n";
    //벽 하나 더 세우기
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(field[i][j]==0){

                //벽을 세울 수 있는 위치이다.
                field[i][j]=1;
                wall(k+1);
                field[i][j]=0;
            }
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int num;
            cin>>num;
            field[i][j]=num;
            if(num==2){
                //cout<<"초기 바이러스 삽입\n";
                virus.push({i,j});
            }
        }
    }

    //cout<<virus.size()<<"\n";
    wall(0);

    cout<<maxSum;
}