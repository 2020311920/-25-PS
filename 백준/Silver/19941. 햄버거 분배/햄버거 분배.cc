#include <bits/stdc++.h>

using namespace std;

void input();
void solution();

int n, k;
int length;
int table[20001];
int visited[20001];


int main(){
    cin.tie(0);
    ios::sync_with_stdio(0);

    input();
    solution();
}

void input(){
    cin>>n>>k;

    string str;
    cin>>str;
    length = str.length();
    for(int i=1;i<=length;i++){
        if(str[i-1] == 'H') table[i] = 0;
        else table[i]=1;
    }
}

void solution(){
    int cnt=0;
    //그리디네 맨 앞 사람부터 시작해서, 가장 왼쪽 먼 햄버거를 차지한다는 식으로 하면 되겠음 ㅇㅇ
    for(int i=1;i<=length;i++){
        if(visited[i]==0){
            visited[i]=1;
            int e = i+k;
            if(e>length) e=length;

            int s = i-k;
            if(s<1) s=1;
            for(int j=s;j<=e;j++){
                if(visited[j]==0 && table[j]!=table[i]){
                    //cout<<i<<"랑 "<<j<<"가 매칭\n";
                    visited[j]=1;
                    cnt++;
                    break;
                }
            }
        }
    }

    cout<<cnt;
}