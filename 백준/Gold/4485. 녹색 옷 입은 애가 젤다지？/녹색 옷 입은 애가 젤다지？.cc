#include <bits/stdc++.h>

using namespace std;

int n;
int field[126][126];
int problemCnt=0;


int dirX[4]={-1,1,0,0};
int dirY[4]={0,0,-1,1};

int visited[126][126];

void ansPrint(int ans){
    problemCnt++;
    cout<<"Problem "<<problemCnt<<": "<<ans<<"\n";
}

void init(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            visited[i][j]=0;
        }
    }
}


int bfs(){
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>,  greater<pair<int, pair<int, int>>>> pq;
    int sx = 1; int sy = 1;
    visited[sx][sy]=1;
    pq.push({field[sx][sy],{sx,sy}});

    while(!pq.empty()){
        auto start = pq.top(); pq.pop();
        int startX = start.second.first; int startY = start.second.second;
        int value = start.first;

        if(startX==n && startY==n){
            return value;
        }

        for(int i=0;i<4;i++){
            int nx = startX+dirX[i];
            int ny = startY+dirY[i];

            if(nx>=1 && nx<=n && ny>=1 && ny<=n){
                if(visited[nx][ny]==0){
                    visited[nx][ny]=1;
                    pq.push({value+field[nx][ny],{nx, ny}});
                }
            }
        }
    }

    return 0;
}

void solution(){
    init();
    int ans = bfs();
    ansPrint(ans);
}


void input(){
    cin>>n;

    while(n!=0){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                cin>>field[i][j];
            }
        }
        solution();

        cin>>n;
    }
    
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    //solution();
}