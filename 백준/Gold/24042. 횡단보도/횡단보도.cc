#include <bits/stdc++.h>

using namespace std;

int n,m;
//vector<pair<int, int>> v; //{start, end} 인덱스가 곧 주기
//unordered_map<string, int> period;
vector<pair<int, int>> points[100001];

void input(){
    cin>>n>>m;

    for(int i=0;i<m;i++){
        int start, end;
        cin>>start>>end;
        //v.push_back({start, end});
        points[start].push_back({end, i});
        points[end].push_back({start, i});
    }
}

void solution(){
    long long visited[100001];
    for(int i=1;i<=n;i++) visited[i]=-1;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    //{현재 시간, 현재 위치}
    int startPos = 1;
    long long nowTime = 0;
    pq.push({nowTime, startPos});
    visited[1]=0;

    while(!pq.empty()){
        auto info = pq.top(); pq.pop();
        int where = info.second;
        long long now = info.first;
        //cout<<"현재 이동 이력 중 가장 짧은 시간은 "<<now<<"초에 "<<where<<"위치에 있습니다\n";
        if(visited[where]!=now) continue;
        if(where==n){
            cout<<now;
            break;
        }
        //현재 시간에 열려있는 신호등을 통해 탐험하지 말고
        //해당 위치에서 이동가능한 신호등을 이동한다고 생각하고, 대신 그 시간을 넣어주면 돼
        //cout<<"현재 위치에서 어떤 시간에 어디로 갈 수 있는지 확인합니다...\n";
        //현재위치에서 갈 수 있는 곳은 points[where]를 순회하면 되고
        for(auto i : points[where]){
            int end = i.first;
            long long nextTime = i.second;

            if(nextTime<now){
                long long k = (now-nextTime)%m==0 ? (now-nextTime)/m : (now-nextTime)/m+1;
                nextTime = nextTime + (m*k);
            }
            if(visited[end]>nextTime+1 || visited[end]==-1){
                //cout<<"오 "<<end<<"로 가는 최단 시간 갱신입니다 "<<nextTime+1<<"에 도착 가능합니다\n";
                visited[end]=nextTime+1;
                pq.push({nextTime+1, end});
            }
        }
    }

}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}