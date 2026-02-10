#include <bits/stdc++.h>

using namespace std;

int n,c;
vector<int> pos;
void input(){
    cin>>n>>c;

    for(int i=1;i<=n;i++){
        int num;
        cin>>num;
        pos.push_back(num);
    }

    sort(pos.begin(), pos.end());
}

void solution(){
    //이게 그 유명한 min max다 아닌가...
    int l = 1;
    int r = 1000000000;
    int ans=l;
    while(l<=r){
        
        int mid = (l+r)/2;
        //cout<<mid<<"로 새롭게 세팅\n";
        int cnt=1;
        int prev = pos[0]; 
        for(int i=1;i<n;i++){
            if(pos[i]-prev >= mid){
                prev = pos[i];
                //cout<<pos[i]<<", ";
                cnt++;
            }
        }
        if(cnt>=c){
            //이러면 mid만큼의 간격으로 놓는게 가능한거니까
            l=mid+1;
            ans = mid;
        }
        else{
            //실패했다면 그 
            r = mid-1;
        }
        //cout<<"\n";
    }

    cout<<ans;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}