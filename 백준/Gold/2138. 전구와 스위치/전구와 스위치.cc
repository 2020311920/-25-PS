#include <bits/stdc++.h>

using namespace std;

int n;
vector<bool> now;
vector<bool> result;

int ans=100001;

void input(){
    cin>>n;
    string str;
    cin>>str;
    for(int i=0;i<n;i++){
        now.push_back(str[i]-'0');
    }

    cin>>str;
    for(int i=0;i<n;i++){
        result.push_back(str[i]-'0');
    }
}

void scenario(int k, int cnt){
    if(k==n){
        //n-1번 스위치까지 처리한 상태
        //이때의 cnt를 ans와 비교
        if(now[k-1] == result[k-1] && cnt<ans) ans = cnt;
        return;
    }
    //k번째 스위치를 건들려 합니다.
    //k-1의 상태가 최종 결정 영원히 결정되는거임
    if(now[k-1]==result[k-1]){
        //이미 같은 상황이면 굳이 건들지 마
        scenario(k+1, cnt);
    }
    else{
        now[k-1] = !now[k-1];
        now[k] = !now[k];
        if(k+1<n) now[k+1] = !now[k+1];
        scenario(k+1, cnt+1);
        now[k-1] = !now[k-1];
        now[k] = !now[k];
        if(k+1<n) now[k+1] = !now[k+1];
    }
}

void solution(){
    scenario(1,0);


    now[0]=!now[0];
    now[1] = !now[1];
    scenario(1,1);

    if(ans<100001) cout<<ans;
    else cout<<-1;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}