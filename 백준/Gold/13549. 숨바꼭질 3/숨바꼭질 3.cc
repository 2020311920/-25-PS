#include <bits/stdc++.h>

using namespace std;

int n,k;
int visited[100001];

void input(){
    cin>>n>>k;
}

void bfs(){
    deque<int> q;
    q.push_front(n);
    visited[n]=1;
    while(!q.empty()){
        int s = q.front(); q.pop_front();
        //if(s==k) break;

        if(s*2>=0 && s*2<=100000){
            if(visited[s*2]==0){
                visited[s*2]=visited[s]+0;
                q.push_front(s*2);
            }
            else if(visited[s*2]>visited[s]){
                visited[s*2]=visited[s]+0;
                q.push_front(s*2);
            }
        }

        if(s+1>=0 && s+1<=100000){
            if(visited[s+1]==0) {
                visited[s+1]=visited[s]+1;
                q.push_back(s+1);
            }
            
            else if(visited[s+1]>visited[s]+1){
                visited[s+1]=visited[s]+1;
                q.push_back(s+1);
            }
        }

        if(s-1>=0 && s-1<=100000){
            if(visited[s-1]==0) {
                visited[s-1]=visited[s]+1;
                q.push_back(s-1);
            }
            
            else if(visited[s-1]>visited[s]+1){
                visited[s-1]=visited[s]+1;
                q.push_back(s-1);
            }
        }

        
    }

    cout<<visited[k]-1;

}

void solution(){
    bfs();
    
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}