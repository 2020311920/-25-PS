#include <bits/stdc++.h>

using namespace std;

int lightBulb[101];

void change(int n){
    if(lightBulb[n]==1) lightBulb[n]=0;
    else lightBulb[n]=1;
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>lightBulb[i];
    }

    int numP;
    cin>>numP;

    for(int i=1;i<=numP;i++){
        int sex, p;
        cin>>sex>>p;

        if(sex==1){
            int k=p;
            while(k<=n){
                change(k);
                k +=p;
            }
        }
        else{
            int interval = 1;
            change(p);
            while(p-interval>0 && p+interval<=n){
                if(lightBulb[p-interval]==lightBulb[p+interval]){
                    change(p-interval);
                    change(p+interval);
                    interval++;
                }
                else break;

            }

        }
    }

    for(int i=1;i<=n;i++){
        cout<<lightBulb[i]<<" ";
        if(i%20==0) cout<<"\n";
    }
}