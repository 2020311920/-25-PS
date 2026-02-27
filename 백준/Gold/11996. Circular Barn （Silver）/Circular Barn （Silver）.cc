#include <bits/stdc++.h>

using namespace std;

int room[1001];
int n;
int getInd(){
    int minAns=2100000000;
    int ans=0;
    int ind = 1;
    for(int i=1;i<=n;i++){
        ans+=(room[i]-1);
        if(minAns>ans){
            //ans 갱신
            minAns = ans;
            if(room[i] == 0) ind = i;
        }
    }

    return ind;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    int finalAns = 0;
    for(int i=1;i<=n;i++) cin>>room[i];

    //결손치라는 것을 구해서 가장 부족하면서 0인 공간부터 반시계로 시작
    int s = getInd();
    int cycle = n;
    while(cycle--){
        //s와 반시계로 가장 가까운 소를 걍 데리고 옴
        int pos = s;
        int dist = 0;
        while(room[pos]<=0){
            pos--;
            dist++;
            if(pos<1) pos+=n;
        }

        finalAns += dist*dist;
        room[pos]--;
        room[s]++;
        s--;
        if(s<1) s+=n;

        // cout<<"now : ";
        // for(int i=1;i<=10;i++) cout<<room[i]<<" ";
        // cout<<"\n";
    }

    cout<<finalAns;
}