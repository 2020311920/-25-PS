#include <bits/stdc++.h>

using namespace std;

void input();
void solution();

int n;
string channels[101];
int myChannels[2];

int main(){
    cin.tie(0);
    ios::sync_with_stdio(0);

    input();
    solution();
}

void input(){
    cin>>n;

    for(int i=1;i<=n;i++){
        cin>>channels[i];

        if(channels[i]=="KBS1") myChannels[0] = i;
        if(channels[i]=="KBS2") myChannels[1] = i;
    }
}

void solution(){
    //만약 현재 기준 아래에 목적이 있으면 1보다는 3이 유리
    //만약 현재 기준 위에 목적이 있으면 2보다는 4가 유리 아니면 목적지로
    int now = 1;
    while(!(channels[now]=="KBS1")){
        now++;
        cout<<"1";
    }

    while(!(channels[1]=="KBS1")){
        now--;
        cout<<"4";
        swap(channels[now+1], channels[now]);
    }

    while(!(channels[now]=="KBS2")){
        now++;
        cout<<"1";
    }
    while(!(channels[2]=="KBS2")){
        now--;
        cout<<"4";
        swap(channels[now+1], channels[now]);
    }

    // for(int i=1;i<=n;i++){
    //     cout<<channels[i]<<" ";
    // }
}