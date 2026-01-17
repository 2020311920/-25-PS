#include <bits/stdc++.h>

using namespace std;

int n;
int liquids[100001];
int s=1; int e;
int absMin = 2100000000;
int ans1=0, ans2=0;

void input(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>liquids[i];
    }
}

void solution(){
    e = n;

    while(s<e){
        
        int mix = liquids[e] + liquids[s];
        if(mix == 0){
            //마침 딱 0이야
            cout<<liquids[s]<<" "<<liquids[e];
            return;
        }
        if(abs(mix)<absMin){
            absMin = abs(mix);
            ans1 = liquids[s];
            ans2 = liquids[e];
        }

        if(mix>0) e--;
        else s++;
    }

    cout<<ans1<<" "<<ans2;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(0);

    input();
    solution();

}