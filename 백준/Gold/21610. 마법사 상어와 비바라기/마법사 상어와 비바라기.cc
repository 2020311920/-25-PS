#include <bits/stdc++.h>

using namespace std;

int n,m;
int field[51][51];
pair<int, int> dir[9]={{0,0}, {0,-1}, {-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1}};
vector<pair<int, int>> raining;

void rain(int d, int s){

    //cout<<raining.size();
    for(int i=0;i<raining.size();i++){
        for(int j=1;j<=s;j++){
            raining[i].first+=dir[d].first;
            if(raining[i].first<1) raining[i].first+=n;
            else if(raining[i].first>n) raining[i].first-=n;

            raining[i].second += dir[d].second;
            if(raining[i].second<1) raining[i].second+=n;
            else if(raining[i].second>n) raining[i].second-=n;
        }

        field[raining[i].first][raining[i].second]++;
    }
    //cout<<"비내림 완료\n";
    // 이렇게 모든 비바라기 영역을 d 방향으로 s만큼 이동시키고 그 영역 비내림

    for(int i=0;i<raining.size();i++){
        //각 위치별로 대각선 확인
        int cnt=0;
        for(int j=2;j<=8;j+=2){
            int x, y;
            x = raining[i].first + dir[j].first;
            if(x<1 || x>n) continue;

            y = raining[i].second + dir[j].second;
            if(y<1 || y>n) continue;
            
            else{
                if(field[x][y]>0) cnt++;
            }
        }

        field[raining[i].first][raining[i].second]+=cnt;

    }
    ///cout<<"물복사 완료\n";
    //이렇게 물복사 성공

    vector<pair<int, int>> newRaining;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(field[i][j]>=2){
                bool check = true;
                for(auto k:raining){
                    //알고보니 이전에 이미 비온곳
                    if(i==k.first && j==k.second) check=false;
                }

                if(check){
                    field[i][j]-=2;
                    newRaining.push_back({i,j});
                }
            }
        }
    }
    //cout<<"새 구름들 생성 완료\n";

    raining.clear();

    for(auto i : newRaining) raining.push_back({i.first, i.second});
    newRaining.clear();

    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=n;j++){
    //         //sum+=field[i][j];
    //         cout<<field[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
}

int main(){
    // cin.tie(0);
    // ios::sync_with_stdio(0);

    cin>>n>>m;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>field[i][j];
        }
    }

    raining.push_back({n,1});
    raining.push_back({n,2});
    raining.push_back({n-1,1});
    raining.push_back({n-1,2});

    for(int i=1;i<=m;i++){
        int d, s;
        cin>>d>>s;

        // cout<<"현재 비구름 생성 위치는 ";
        // for(auto j : raining) cout<<j.first<<","<<j.second<<" ";
        // cout<<"\n";
        rain(d,s);
    }

    int sum = 0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            sum+=field[i][j];
            //cout<<field[i][j]<<" ";
        }
        //cout<<"\n";
    }
    cout<<sum;
}