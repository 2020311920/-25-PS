#include <bits/stdc++.h>

using namespace std;

int INTMAX = 2100000000;
int n, m, goal;
struct node{
    vector<pair<int, int>> to; 
};
node nodes[1001]; //nodes[a].to[b].first, second -> a가 first로 가는데 second만큼의 비용이 있다.
//역그래프
node rnodes[1001];

void input(){
    cin>>n>>m>>goal;
    for(int i=1;i<=m;i++){
        int x, y, c;
        cin>>x>>y>>c;
        nodes[x].to.push_back({y,c});
        rnodes[y].to.push_back({x,c});
    }
}

int toGoal[1001];
int fromGoal[1001];

void runDijk(node nodes[], int distArr[]){
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    //{cost, position}
    for(int i=1;i<=n;i++){
        distArr[i]=INTMAX;
    }

    pq.push({0,goal});
    distArr[goal] = 0;
    while(!pq.empty()){
        int s = pq.top().second;
        int c = pq.top().first;
        pq.pop();

        if(distArr[s]!=c){
            continue;
        }

        for(auto i : nodes[s].to){
            if(distArr[i.first]>c+i.second){
                distArr[i.first] = c+i.second;
                pq.push({c+i.second, i.first});
            }
        }
    }
}

void solution(){
    runDijk(nodes, fromGoal);
    //그래프 역방향으로
    runDijk(rnodes, toGoal);

    int maxCost = 0;
    for(int i=1;i<=n;i++){
        int sumV = fromGoal[i]+toGoal[i];
        if(sumV>maxCost) maxCost = sumV;
    }

    cout<<maxCost;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}