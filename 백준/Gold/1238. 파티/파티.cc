#include <bits/stdc++.h>

using namespace std;

int INTMAX = 2100000000;
int n, m, goal;
struct node{
    vector<pair<int, int>> to; 
};
node nodes[1001]; //nodes[a].to[b].first, second -> a가 first로 가는데 second만큼의 비용이 있다.

void input(){
    cin>>n>>m>>goal;
    for(int i=1;i<=m;i++){
        int x, y, c;
        cin>>x>>y>>c;
        nodes[x].to.push_back({y,c});
    }
}

int getCost(int start, int goal){
    vector<int> dist;
    dist.assign(n+1, INTMAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    //pq는 {cost, 현재 위치};
    int totalCost = 0;
    pq.push({0, start});
    dist[start]=0;
    while(!pq.empty()){
        int s = pq.top().second;
        int c = pq.top().first; pq.pop();
        if(dist[s]!=c) continue;
        if(s==goal){
            totalCost += c;
            break;
        }

        for(auto i : nodes[s].to){
            //s는 i.first로 갈 수 있고, 그 비용은 i.second
            if(dist[i.first]>c+i.second){
                dist[i.first] = c+i.second;
                pq.push({c+i.second, i.first});
            }
            
        }
    }

    while(!pq.empty()) pq.pop(); //pq를 비울거에요
    dist.clear();
    dist.assign(n+1, INTMAX);
    //이제 도착지에 도착을 했기 때문에 goal에서 start로 갈겁니다.
    pq.push({0, goal});
    dist[goal]=0;
    while(!pq.empty()){
        int s = pq.top().second;
        int c = pq.top().first; pq.pop();
        if(dist[s]!=c) continue;
        if(s == start){
            totalCost += c;
            break;
        }

        for(auto i : nodes[s].to){
            if(dist[i.first]>c+i.second){
                dist[i.first] = c+i.second;
                pq.push({c+i.second, i.first});
            }
        }
    }

    return totalCost;
}

void solution(){
    int maxTotalCost=0;
    for(int i=1;i<=n;i++){
        if(i==goal) continue;
        int start = i;
        int totalCost=0;

        //start에서 goal로 가고, 다시 goal에서 start로 가는 총 cost
        int tempCost = getCost(start, goal);
        if(tempCost>maxTotalCost) maxTotalCost = tempCost;
    }

    cout<<maxTotalCost;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}