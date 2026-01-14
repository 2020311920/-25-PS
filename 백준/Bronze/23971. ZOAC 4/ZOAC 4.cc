#include <bits/stdc++.h>

using namespace std;

int h,w,n,m;

int main(){
    cin>>h>>w>>n>>m;

    //그냥 돌리면 무조건 터지는 케이스
    //h=1부터 n씩, w=1부터 m씩
    int cnt=0;
    for(int i=1;i<=h;i+=(n+1)){
        for(int j=1;j<=w;j+=(m+1)){
            //cout<<i<<","<<j<<"에 앉음\n";
            cnt++;
        }
    }

    cout<<cnt;
}