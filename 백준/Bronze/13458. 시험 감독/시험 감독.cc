#include <bits/stdc++.h>

using namespace std;

int N;
int room[1000001];
int b, c;

int main(){
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin>>N;

    for(int i=1; i<=N;i++){
        cin>>room[i];
    }

    cin>>b>>c;

    /*일단 1차적으로 드는 생각
    총감독관 컨트롤 가능 수만큼 전부다 빼고, 한바퀴 돌면서
    부감독관 컨트롤 가능 수로 나눠서 답 확인*/
    long ans=N;

    for(int i=1;i<=N;i++){
        room[i]-=b;

        if(room[i]>0){
            ans+=(room[i]%c ==0 ? room[i]/c : room[i]/c + 1);
            //cout<<(room[i]%c ==0 ? room[i]/c : room[i]/c + 1)<<"만큼이 더 필요\n";
        }
    }

    cout<<ans;
    
}