#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<int> v;
int maxDist;

void input(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int num;
        cin>>num;
        v.push_back(num);
    }
}

bool isCovered(int h){
    int field[100001];
    for(int i=0;i<=n;i++) field[i]=0;
    for(int i=0;i<m;i++){
        for(int j=v[i]-h ; j<=v[i]+h; j++){
            if(j>=0 && j<=n) field[j]=1;
        }
    }

    bool covered = true;
    for(int i=0;i<=n;i++){
        if(field[i]==0){
            covered=false;
            break;
        }
    }
    return covered;
}

void solution(){
    // //이분탐색이 맞는 것 같다
    // int l = 1; int r = n;
    // int height = l;
    // while(l<=r){
    //     height = (l+r)/2;

    //     if(isCovered(height)){
    //         //높이 충분
    //         r = height-1;
    //     }
    //     else{
    //         //높이 불충분
    //         l = height+1;
    //     }
    // }

    // cout<<height;

    maxDist = max(v[0]-0, n-v[m-1]);

    for(int i=0;i<m-1;i++){
        int dist = v[i+1]-v[i];
        if(dist%2!=0) dist+=1;
        dist/=2;
        maxDist = max(maxDist, dist);
    }

    cout<<maxDist;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}