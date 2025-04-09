#include <bits/stdc++.h>

using namespace std;

int num;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>num;

    int ans=1;
    while(ans<=num){
        int sum=ans;
        int temp = ans;
        while(temp>0){
            sum+=temp%10;
            temp/=10;
        }

        if(sum==num){
            cout<<ans;
            return 0;
        }
        ans++;
    }

    cout<<0;


}