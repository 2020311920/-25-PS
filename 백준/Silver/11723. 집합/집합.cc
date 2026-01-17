#include <bits/stdc++.h>

using namespace std;

int n;
int s[21];

void addF(int num){
    if(s[num]==0){
        s[num]++;
    }
}

void removeF(int num){
    if(s[num]>0) s[num]=0;
}

void checkF(int num){
    cout<<s[num]<<"\n";
}

void toggleF(int num){
    if(s[num]>0) s[num]=0;
    else s[num]=1;
}

void allF(){
    for(int i=1;i<=20;i++){
        s[i]=1;
    }
}

void emptyF(){
    for(int i=1;i<=20;i++) s[i]=0;
}

void input(){
    cin>>n;

    for(int i=1;i<=n;i++){
        string str;
        int num;
        cin>>str;

        if(str=="add"){
            cin>>num;
            addF(num);
        }
        else if(str=="remove"){
            cin>>num;
            removeF(num);
        }
        else if(str == "check"){
            cin>>num;
            checkF(num);
        }
        else if(str == "toggle"){
            cin>>num;
            toggleF(num);
        }
        else if(str == "all"){
            allF();
        }
        else if(str == "empty"){
            emptyF();
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
}