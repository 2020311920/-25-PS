#include <bits/stdc++.h>

using namespace std;

int n;
deque<pair<int, int>> people;

void input(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int a,b;
        cin>>a>>b;
        people.push_back({a,b});
    }
}

void solution(){

    for(int i=0;i<n;i++){
        int level=1;
        for(int j=0;j<n;j++){
            //i가 어디 위치인지를 알아야 해.
            if(people[i].first<people[j].first && people[i].second<people[j].second){
                level++;
            }
        }

        
        cout<<level<<" ";
    }


}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(0);

    input();
    solution();
}