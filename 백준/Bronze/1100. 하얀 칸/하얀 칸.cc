#include <bits/stdc++.h>

using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int cnt=0;
    bool white = false;
    for(int i=1;i<=8;i++){
        white = !white;
        string str;
        cin>>str;
        for(int j=1;j<=8;j++){
            int num = str[j-1];
            if(num=='F' && white) cnt++;
            white = !white;
        }
    }

    cout<<cnt;
}