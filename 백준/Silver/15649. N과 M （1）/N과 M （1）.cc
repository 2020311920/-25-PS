#include <bits/stdc++.h>

using namespace std;

int n,m;

int answer[9];
int visited[9]={0,};

void func(int count){
    if(count==m+1){
        for(int i=1;i<=m;i++) cout<<answer[i]<<" ";
        cout<<"\n";
        return;
    }
    else{
        for(int i=1;i<=n;i++){
            if(visited[i]!=1){
                //방문하지 않았다.
                answer[count] = i;
                visited[i]=1;
                func(count+1);
                visited[i]=0;
            }
        }
    }
}

int main(){
    cin>>n>>m;

    
    func(1);
}