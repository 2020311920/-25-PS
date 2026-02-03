#include <bits/stdc++.h>

using namespace std;

int n;
deque<pair<int, int>> v;

void input(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int x, h;
        cin>>x>>h;
        v.push_back({x,h});
    }
    
}

void solution(){
    int cnt=0;
    deque<pair<int, int>> hdq;
    hdq.push_back({0,0});
    // int l = v[0].first; int r = v[n-1].first; 
    // int coveredL=2100000000; int coveredR = 0;
    for(auto i : v){
        int x= i.first;
        int h = i.second;

        if(h>hdq.back().second){
            hdq.push_back({x,h});
        }

        else{
            while(hdq.back().second>h){
                //hdq.back().first 부터 x까지 커버가 된다
                // if(hdq.back().first<coveredL) coveredL = hdq.back().first;
                // if(x>coveredR) coveredR = x;

                hdq.pop_back();
                cnt++;
                //cout<<"건물 추가 총 : "<<cnt<<"\n";
            }
            if(hdq.back().second<h) hdq.push_back({x,h});
        }
    }

    if(hdq.size()>1) cnt+=(hdq.size()-1);

    cout<<cnt;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}