#include <bits/stdc++.h>

using namespace std;

int n, l, max_w;
queue<int> q;
queue<int> bridge;
int main(){
    cin>>n>>l>>max_w;

    for(int i=1;i<=n;i++){
        int weight;
        cin>>weight;
        q.push(weight);
    }
    int ans=0;
    int now_weight=0;
    while(!q.empty()){
        //cout<<"현재 bridge에 올라간 놈 수 : "<<bridge.size()<<"\n";
        if(bridge.size()>=l){
            
            now_weight -= bridge.front();
            bridge.pop();
        }

        if(now_weight+q.front()<=max_w){
            bridge.push(q.front());
            //cout<<"방금 "<<q.front()<<"짜리가 올라감\n";
            now_weight+=q.front();
            q.pop();
            ans++;
        }
        else{
            bridge.push(0);
            //cout<<"아무도 못올라가서 그냥 시간 흐름\n";
            ans++;
        }

        
    }

    
    cout<<ans+l;
}