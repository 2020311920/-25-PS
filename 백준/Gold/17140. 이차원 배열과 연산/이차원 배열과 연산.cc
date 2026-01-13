#include <bits/stdc++.h>

using namespace std;

int r,c,k;

vector<vector<int>> table;
int arr[101];

bool compare(pair<int, int> p1, pair<int, int> p2){
    
    if(p1.second==p2.second) return p1.first<p2.first;
    else{
        return p1.second < p2.second;
    }

    
}

void computeR(){
    for(int i=0;i<table.size();i++){
        vector<pair<int, int>> a;
        for(int j=0;j<table[i].size();j++){
            if(table[i][j]<=100) arr[table[i][j]]++;
        }

        for(int j=1;j<=100;j++){
            if(arr[j]>0) a.push_back({j,arr[j]});
        }
        
        sort(a.begin(), a.end(), compare);

        table[i].clear();
        for(auto j : a){
            table[i].push_back(j.first);
            table[i].push_back(j.second);
        }

        //arr초기화
        for(int j=0;j<=100;j++){
            arr[j]=0;
        }
    }

    int maxLength = 0;
    for(auto i : table){
        if(maxLength < i.size()) maxLength = i.size();
    }

    for(int i=0;i<table.size();i++){
        while(table[i].size()<maxLength){
            table[i].push_back(0);
        }
    }
}//포인트는 정렬계산을 해, 그걸 그 행을 초기화 한 뒤에 넣어, 마무리 한 뒤, 최대 길이만큼 나머지를 보정해

void transpose(){
    //table을 transpose하면 돼.
    vector<vector<int>> tempTable;
    int row = table.size();
    int col = table[0].size();
    for(int j=0;j<col;j++){
        vector<int> temp;
        for(int i=0;i<row;i++){
            temp.push_back(table[i][j]);
        }
        tempTable.push_back(temp);
    }
    table.clear();

    for(int i=0;i<col;i++){
        vector<int> v;
        for(int j=0;j<row;j++){
            v.push_back(tempTable[i][j]);
        }
        table.push_back(v);
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin>>r>>c>>k;

    for(int i=1;i<=3;i++){
        vector<int> v;
        for(int j=1;j<=3;j++){
            int num;
            cin>>num;

            v.push_back(num);
        }
        table.push_back(v);
    }

    // for(auto i : table){
    //     for(auto j : i){
    //         cout<<j<<" ";
    //     }
    //     cout<<"\n";
    // }



    // vector<pair<int, int>> a = {{1,4}, {3,2}, {2,2},{4,101},{5,1}};
    // sort(a.begin(), a.end(),compare);
    // for(auto i : a){
    //     if(i.second==101){

    //     }
    //     else{
    //         cout<<i.first<<" "<<i.second<<" ";
    //     }
    // }

    //computeR();

    int t=0;
    while(1){
        if(r-1>=0 && r-1<table.size() && c-1>=0 && c-1<table[0].size() && table[r-1][c-1]==k) break;
        if(t>100) break;

        t++;
        //cout<<t<<"입니다\n";
        int row = table.size();
        int col = table[0].size();

        if(row>100){
            while(table.size()>100) table.pop_back();
        }
        if(col>100){
            for(int i=0;i<table.size();i++){
                while(table[i].size()>100) table[i].pop_back();
            }
        }

        if(row>=col) computeR();
        else{
            //그냥 Transpose시키고 computeR하고 다시 transpose하면 돼
            transpose();
            computeR();
            transpose();
        }

        
    }
    

    if(t>100) cout<<-1;
    else cout<<t;

    
    
}