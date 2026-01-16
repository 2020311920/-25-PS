#include <bits/stdc++.h>

using namespace std;

int n,q;
int field[65][65];

int dirX[4] = {0,1,0,-1};
int dirY[4] = {1,0,-1,0};
queue<int> levels;
int iceSum=0;


void input(){
    cin>>n>>q;

    n = pow(2,n);

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>field[i][j];
            iceSum+=field[i][j];
        }
    }

    for(int i=1;i<=q;i++){
        int level;
        cin>>level;

        levels.push(level);
    }
}

void rotation(int sx, int ex, int sy, int ey){
    int length = ex-sx+1;
    int temp[65][65];
    for(int i=sx; i<=ex;i++){
        for(int j=sy ; j<=ey; j++){
            temp[i][j] = field[i][j];
        }
    }

    //다 복사해놓고
    for(int i=sx; i<=ex;i++){
        for(int j=sy; j<=ey; j++){
            field[sx-(sy-j)][ey+(sx-i)] = temp[i][j]; //와 이거 분석하는게 너무 어려운데?
        }
    }
}

void solution(){
    while(!levels.empty()){
        int level = levels.front(); levels.pop();
        int length = pow(2, level);
        //구역을 쪼개자
        for(int i=1;i<=n;i++){
            int sx = i; int ex = i+length-1;
            for(int j=1;j<=n;j++){
                int sy = j;
                int ey = j+length-1;

                rotation(sx, ex, sy, ey);
                j = ey;
            }
            i = ex;
        }

        // cout<<"쪼개서 회전 후 : \n";
        // for(int i=1;i<=pow(2,n);i++){
        //     for(int j=1;j<=pow(2,n);j++){
        //         cout<<field[i][j]<<" ";
        //     }
        //     cout<<"\n";
        // }

        queue<pair<int, int>> minus;

        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                int cnt=0;
                for(int dirInd = 0; dirInd<=3;dirInd++){
                    int nextX = i + dirX[dirInd];
                    int nextY = j + dirY[dirInd];

                    if(nextX>=1 && nextX<=n && nextY>=1 && nextY<=n){
                        if(field[nextX][nextY]>0) cnt++;
                    }
                }

                if(cnt<3){
                    //현재 위치의 얼음이 1 녹아야 하는데, 이걸 매번 하면 나중거에 영향이 갈거야 
                    //즉, 앞으로 줄어들 후보로 설정해야 한다.
                    minus.push({i,j});
                }
            }
        }

        

        while(!minus.empty()){
            field[minus.front().first][minus.front().second]--;
            minus.pop();
        }

        // cout<<"녹인 후\n";
        // for(int i=1;i<=pow(2,n);i++){
        //     for(int j=1;j<=pow(2,n);j++){
        //         cout<<field[i][j]<<" ";
        //     }
        //     cout<<"\n";
        // }
    }

    int ans1=0; int ans2 = 0;
    int visited[65][65];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(field[i][j]>0) ans1+=field[i][j];
            visited[i][j] = 0;
        }
    }

    
    

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(visited[i][j]==1) continue;
            queue<pair<int, int>> continents;
            visited[i][j]=1;
            int size=0;
            if(field[i][j]>0){
                continents.push({i,j});
                size++;
            }
            
            while(!continents.empty()){
                pair<int, int> start = continents.front(); continents.pop();

                int sx = start.first; int sy = start.second;

                for(int dirInd=0;dirInd<=3;dirInd++){
                    int nextX = sx + dirX[dirInd];
                    int nextY = sy + dirY[dirInd];

                    if(nextX>=1 && nextX<=n && nextY>=1 && nextY<=n){
                        if(visited[nextX][nextY]==0){
                            visited[nextX][nextY]=1;
                            if(field[nextX][nextY]>0){
                                size++;
                                continents.push({nextX, nextY});
                            }
                        } 
                    }
                }
            }

            if(size>ans2) ans2 = size;
        }
    }

    cout<<ans1<<"\n"<<ans2;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(0);

    input();
    solution();
}