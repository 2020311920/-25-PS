#include <bits/stdc++.h>

using namespace std;

int n;

vector<pair<pair<int, string>, int>> v;

bool myCompare(pair<pair<int, string>, int> v1, pair<pair<int, string>, int> v2){
    if(v1.first.first == v2.first.first) return v1.second < v2.second;
    return v1.first < v2.first;
}

int main(){
    cin>>n;

    for(int i=1;i<=n;i++){
        int age; string name;
        cin>>age>>name;

        v.push_back({{age, name}, i});
    }

    sort(v.begin(), v.end(), myCompare);

    for(auto i : v) cout<<i.first.first<<" "<< i.first.second << "\n";

}