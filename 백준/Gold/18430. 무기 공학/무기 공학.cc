#include <bits/stdc++.h>

using namespace std;

int n,m;
int field[6][6];

int dirX[4][2]={
    {0,1},
    {0,-1},
    {-1,0},
    {1,0}
};
int dirY[4][2]={
    {-1,0},
    {-1,0},
    {0,1},
    {0,1}
};

void input(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>field[i][j];
        }
    }
}

int visited[6][6];
int maxSum=0;

bool isPossible(int a, int b){
    if(a>=1 && a<=n && b>=1 && b<=m){
        if(visited[a][b]==0){
            //범위 안이면서 방문을 안한 점이면
            return true;
        }
    }
    return false;
}

void dfs(int x, int y, int cnt, int sum){
    //cnt라 함은 현재 사용한 칸의 개수라고 하자고
    if(n*m-cnt<3){
        maxSum = max(maxSum, sum);
        return;
    }

    for(int i=x;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(visited[i][j]==0){
                //i,j로 하여금 중심점이 되게 한느거야
                
                for(int a=0;a<4;a++){
                    //모양 설정
                    //a라는 모양을 택했으니 나머지 좌표들 설정
                    int x1 = i+dirX[a][0];
                    int x2 = i+dirX[a][1];

                    int y1 = j+dirY[a][0];
                    int y2 = j+dirY[a][1];

                    //총 세점으로 이동이 가능한지 판단
                    if(isPossible(x1,y1) && isPossible(x2,y2)){
                        //실제로 체크하고 해당 세계관 열어
                        visited[i][j]=1;
                        visited[x1][y1]=1;
                        visited[x2][y2]=1;
                        
                        dfs(i,j,cnt+3, sum+(field[i][j]*2 + field[x1][y1] + field[x2][y2]));

                        visited[i][j]=0;
                        visited[x1][y1]=0;
                        visited[x2][y2]=0;
                    }
                }
            }
        }
    }

    //여기로 온다는 거는 ㄹㅇ로 칸이 있기는 한데 더이상 쪼갤 수가 없는 경우 아닌가
    maxSum = max(maxSum, sum);
    return;
}

void solution(){
    //특정 점을 골랐을 때 모양 4가지를 택하고, 그렇게 dfs로 가면 되기는 하겠다...ㅇㅇ;;
    //근데 너무 억지로 푸는 거 같긴 한데, 사실 다른 방법이 안떠오른다, 다른 방법은 뭐가 있을까..

    //역시나 어림도 없이 시간초과가 나는 구만..ㅇㅇ

    //이게 뒤에거를 만들고, 다시 앞에서부터 검색하면서 놓으면 중복이 되니까, 오른아래로만 검색할 수 있게 해야겠다.

    dfs(0,0,0,0);

    cout<<maxSum;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    input();
    solution();
}