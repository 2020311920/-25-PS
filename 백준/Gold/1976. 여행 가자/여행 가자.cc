#include <bits/stdc++.h>

using namespace std;

int n;
int m;
int field[201][201];
queue<int> q;

void solution(){
    
    int start = q.front(); q.pop();
    while(!q.empty()){
        int end = q.front(); q.pop();
        //start에서 end 로 갈 수 있니?

        queue<int> way;
        int visited[201];
        for(int i=1;i<=n;i++) visited[i]=0;
        visited[start]=1;
        bool arrived = false;
        way.push(start);
        while(!way.empty()){
            int s = way.front(); way.pop();
            if(s==end){
                //오 목적지 도착
                arrived = true;
                break;
            }
            for(int i=1;i<=n;i++){
                if(field[s][i]==1 && visited[i]==0){
                    //즉, s에서 i로 갈 수 있고, i를 아직 안갔다면
                    visited[i]=1;
                    way.push(i);
                }
            }
        }

        if(arrived){
            start = end;
        }
        else{
            cout<<"NO";
            return;
        }
    }

    cout<<"YES";
    
}

void input(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>field[i][j];
        }
    }

    for(int i=1;i<=m;i++){
        int num;
        cin>>num;
        q.push(num);
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}