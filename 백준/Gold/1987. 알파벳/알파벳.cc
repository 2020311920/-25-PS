#include <bits/stdc++.h>

using namespace std;

int r,c;
int field[21][21];
int dist[21][21];
int dirX[4]={0,0,1,-1};
int dirY[4]={1,-1,0,0};
int maxAns=1;
int visited[26];

void input(){
    cin>>r>>c;

    for(int i=1;i<=r;i++){
        string str;
        cin>>str;
        for(int j=1;j<=c;j++){
            field[i][j] = str[j-1];
        }
    }
}


// //아래에 사용될 pq에 들어가는 pair안에 단순 int만 있는게 아니라서 필요할 것 같다는 생각에 만든다
// struct cmp{
//     bool operator()(const pair<int, pair<array<int, 26>, pair<int, int>>>& s1, const pair<int, pair<array<int, 26>, pair<int, int>>>& s2){
//         return s1.first<s2.first;
//     }
// };

void dfs(int sx, int sy, int cnt){    
    for(int i=0;i<4;i++){
        int nx = sx + dirX[i];
        int ny = sy + dirY[i];

        if(nx>=1 && nx<=r && ny>=1 && ny<=c){
            if(visited[field[nx][ny]-'A']==0){
                visited[field[nx][ny]-'A']=1;
                if(maxAns<cnt+1) maxAns = cnt+1;
                dfs(nx, ny, cnt+1);
                visited[field[nx][ny]-'A']=0;
            }
        }
    }
}

void solution(){
    visited[field[1][1]-'A']=1;//방문 처리
    dfs(1,1,1);//1,1에서 스타트, 현재 누적 칸수=1

    cout<<maxAns;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}