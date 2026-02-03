#include <bits/stdc++.h>

using namespace std;

int t;
int n;
vector<long long> v;

void solution(){
    vector<int> buyOrSell;
    buyOrSell.assign(n, 0);
    int maxV = 0;
    int maxInd = n;
    for(int i=n-1;i>=0;i--){
        if(v[i]>maxV){
            maxV = v[i];
            maxInd = i;
        }
        buyOrSell[i] = maxInd;
    }

    int cnt=0;
    long long buy=0;
    long long benefit=0;

    for(int i=0;i<n;i++){
        if(i==buyOrSell[i]){
            benefit += (v[i]*cnt - buy);
            cnt=0;
            buy=0;
        }
        else{
            //사야할 때
            cnt++;
            buy+=v[i];
        }
    }

    cout<<benefit<<"\n";
}

void input(){
    cin>>t;
    for(int i=1;i<=t;i++){
        v.clear();
        cin>>n;
        for(int j=1;j<=n;j++){
            int num;
            cin>>num;
            v.push_back(num);
        }

        solution();
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
}