#include <bits/stdc++.h>

using namespace std;

int limit, n;
int arr[4];
int ans_max = 0;

void func(int num){

    if(num>limit) return;
    if(ans_max < num) ans_max = num;

    for(int i=1;i<=n;i++){
        num = num*10 + arr[i];
        func(num);
        num = (num-arr[i])/10;
    }
    
}

int main(){
    cin>>limit>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    

    func(0);
    cout<<ans_max;
}