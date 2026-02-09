#include <bits/stdc++.h>

using namespace std;

int n,m;
int field[1001][1001];
// int dirX[3] = {0, 0, 1};//0왼, 1오, 2아래
// int dirY[3] = {-1, 1, 0};

void solution(){
    for(int i=1;i<=m-1;i++){
        field[1][i+1] += field[1][i];
    }
    //1열은 무조건 왼쪽에서 오는 개념이니까
    //
    for(int i=2;i<=n;i++){
        int leftMax[1001];
        leftMax[0]=-2100000000;
        int rightMax[1001];
        rightMax[m+1]=-2100000000;
        for(int j=1;j<=m;j++){
            leftMax[j] = max(field[i-1][j], leftMax[j-1]) + field[i][j];
            rightMax[m-j+1] = max(field[i-1][m-j+1], rightMax[m-j+2]) + field[i][m-j+1];
        }

        for(int j=1;j<=m;j++){
            field[i][j] = max(leftMax[j], rightMax[j]);
        }
    }

    cout<<field[n][m];
}

void input(){
    cin>>n>>m;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>field[i][j];
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}