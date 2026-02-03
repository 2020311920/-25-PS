#include <bits/stdc++.h>

using namespace std;

int p, m;
struct player{
    int level;
    string nickname;
};
vector<player> players;

struct room{
    int numPlayer;
    vector<player> players;
    int low = 0;
    int high = 0;
};

vector<room> rooms;

void input(){
    cin>>p>>m;

    for(int i=1;i<=p;i++){
        int level; string nickname;
        cin>>level>>nickname;

        players.push_back(player{level, nickname});
    }
}

bool compare(const player &p1, const player &p2){
    if(p1.nickname!=p2.nickname) return p1.nickname<p2.nickname;
    else return p1.level<p2.level;
}

void printPlayers(int success, const room& r){
    if(success==1){
        cout<<"Started!\n";
    }
    else{
        cout<<"Waiting!\n";
    }

    room temp = r;
    sort(temp.players.begin(), temp.players.end(), compare);

    for(auto i : temp.players){
        cout<<i.level<<" "<<i.nickname<<"\n";
    }
}

void solution(){
    for(auto p : players){
        string nickname = p.nickname;
        int level = p.level;
        bool isIn = false;
        int roomN = rooms.size();
        for(int i=0;i<roomN;i++){
            if(rooms[i].numPlayer<m && rooms[i].low<=level && level<=rooms[i].high){
                rooms[i].numPlayer++;
                rooms[i].players.push_back(player{level, nickname});
                isIn=true;
                break;
            }
        }

        if(isIn) continue;
        else{
            //방을 생성하면 된다.
            room r;
            r.high = level+10;
            r.low = level-10;
            r.numPlayer = 1;
            r.players.push_back({level, nickname});

            rooms.push_back(r);
        }
    }

    for(auto &r : rooms){
        if(r.numPlayer==m){
            printPlayers(1, r);
        }
        else{
            printPlayers(0, r);
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}