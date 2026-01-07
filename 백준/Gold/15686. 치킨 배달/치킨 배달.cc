#include <bits/stdc++.h>

using namespace std;

int n;
int m;
//int city[51][51];

vector<pair<int, int>> home;
vector<pair<int, int>> chicken;
int chickenCnt;
int chickenVisited[14];

int minCityDist=2000000000;

void dfs(int k, int i){
    if(k==m){
        //m개의 치킨집을 고른거야
        //chickenVisited가 1인 위치의 집들만 남은거야
        int sum=0;
        // cout<<"내가 살리기로 한 치킨 집 : ";
        // for(int j=1;j<=chickenCnt;j++){
        //     if(chickenVisited[j]==1) cout<<j<<" ";
        // }
        // cout<<"\n";
        for(auto h : home){
            int minSum=2000000000;
            //디버그용 최소치킨집정보
            //int a,b;
            //i와 m개의 치킨집 거리 계산해서 최소를 계산
            for(int j=0;j<chickenCnt;j++){
                if(chickenVisited[j+1]==1){
                    int dist = abs(h.first-chicken[j].first) + abs(h.second-chicken[j].second);
                    // cout<<chicken[j].first<<","<<chicken[j].second<<"까지의 거리 = "<<dist<<"\n";
                    if(dist<minSum){
                        minSum=dist;
                        //a=chicken[j].first;
                        //b=chicken[j].second;
                    }
                }
            }
            // cout<<"현재 집("<<h.first<<","<<h.second<<")에서 치킨집("<<a<<","<<b<<") 최소거리 : "<<minSum<<"\n";
            sum+=minSum;
        }

        if(sum < minCityDist) minCityDist = sum;
        //cout<<"이거일때의 minCityDist : "<<minCityDist<<"\n";
        return;
    }

    else{
        for(int c=i;c<=chickenCnt;c++){
            if(chickenVisited[c]==0){
                chickenVisited[c]=1;
                dfs(k+1,c);
                chickenVisited[c]=0;
            }
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin>>n>>m;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int a;
            cin>>a;
            if(a==1){
                home.push_back({i,j});
            }
            else if(a==2){
                chicken.push_back({i,j});
                chickenCnt++;
            }
        }
    }

    dfs(0,1);
    cout<<minCityDist;
    
}