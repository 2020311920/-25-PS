#include <bits/stdc++.h>

using namespace std;

int h,w;
int height[501];
int maxHeight=-1;
int maxInd=0;

void input(){
    cin>>h>>w;
    for(int i=1;i<=w;i++){
        cin>>height[i];
        if(height[i]>maxHeight){
            maxHeight = height[i];
            maxInd = i;
        }
    }
}

void solution(){
    int ans = 0;
    //각각 l, r에서 maxInd로 가는거야
    int l = 1; int r = w;
    int maxL=-1; int maxR = -1;
    int sumL=0; int sumR = 0;
    for(int i = l; i<=maxInd; i++){
        if(height[i]>=maxL){
            ans+=sumL;
            sumL=0;
            maxL = height[i];
        }
        else{
            sumL += (maxL-height[i]);
        }
    }

    for(int i = r; i>=maxInd; i--){
        if(height[i]>=maxR){
            ans+=sumR;
            sumR=0;
            maxR = height[i];
        }
        else{
            sumR += (maxR-height[i]);
        }
    }

    cout<<ans;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}