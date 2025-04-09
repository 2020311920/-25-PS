#include <bits/stdc++.h>

using namespace std;

int n, t, p;
int arr[7];
int main(){
    cin>>n;

    for(int i=1;i<=6;i++){
        int num;
        cin>>num;
        arr[i]=num;
    }
    cin>>t>>p;
    int sum=0;
    for(int i=1;i<=6;i++){
        sum+=(arr[i]%t==0) ? arr[i]/t : (arr[i]/t)+1;
    }

    cout<<sum<<"\n"<<n/p<<" "<<n%p;
}