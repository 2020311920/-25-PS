#include <bits/stdc++.h>

using namespace std;

int n;
string name;
set<string> names;
int ans  = 0;

int main(){
    cin>>n;

    for(int i=1;i<=n;i++){
        cin>>name;
        if(name=="ENTER") names.clear();

        else if(names.find(name)!=names.end()){
            //있다는 소리 = 이미 한마디 한 놈놈
        }
        else{
            ans++;
            names.insert(name);
        }
    }

    cout<<ans;
}