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
    int leftCovered=0;
    for(int i=0;i<m;i++){
        if(v[i]-h <= leftCovered) leftCovered = v[i]+h;
    }
    if(leftCovered>=n) return true;
    else return false;
}

void solution(){
    //이분탐색이 맞는 것 같다
    int l = 0; int r = n;
    while(l<=r){
        int height = (l+r)/2;

        if(isCovered(height)){
            //높이 충분
            r = height-1;
        }
        else{
            //높이 불충분
            l = height+1;
        }
    }

    cout<<l;

    // maxDist = max(v[0]-0, n-v[m-1]);

    // for(int i=0;i<m-1;i++){
    //     int dist = v[i+1]-v[i];
    //     if(dist%2!=0) dist+=1;
    //     dist/=2;
    //     maxDist = max(maxDist, dist);
    // }

    // cout<<maxDist;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}