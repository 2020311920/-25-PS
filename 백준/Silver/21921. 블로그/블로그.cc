#include <bits/stdc++.h>

using namespace std;

int n,x;

vector<int> visited;
vector<int> maxP;

void input(){
    cin>>n>>x;
    for(int i=1;i<=n;i++){
        int num;
        cin>>num;
        visited.push_back(num);
    }
}

void solution(){
    //visited를 돌면서 연속 x일의 합이 최대가 되는 놈을 찾는다
    int maxSum=0;
    int tempSum=0;
    for(int i=1;i<=x;i++){
        tempSum += visited[i-1];
    }
    //처음 x일의 합
    maxSum = tempSum;
    int cnt = 1;
    for(int i=x+1;i<=n;i++){
        tempSum-=visited[i-1-x];
        tempSum+=visited[i-1];
        if(tempSum>maxSum){
            //갱신
            cnt=1;
            maxSum=tempSum;
        }
        else if(tempSum==maxSum){
            cnt++;
        }
    }

    if(maxSum!=0) cout<<maxSum<<"\n"<<cnt;
    else cout<<"SAD";
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}