#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> v;
int visited[100001];

void input(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int num;
        cin>>num;
        v.push_back(num);
    }
}

void solution(){
    //그냥 투포인터로 일단 l=0; r=0;해버리고, l을 시작점으로 해서, r을 최대로 뒤로 미루고 진행
    int l = 0; int r= 0;
    visited[v[l]]=1;
    long long sum = 0;
    while(l<=r && r<=n-1 && l<=n-1){
        //시작점이 l이라고 했을 때, r을 어디까지 미룰 수 있느냐
        while(1){
            if(r>=n-1) break;
            if(visited[v[r+1]]==0){
                visited[v[r+1]]=1;
                r++;
            }
            else{
                break;
            }
        }
        //r을 최대로 미뤘으니
        sum += (r-l+1);

        visited[v[l]]=0;
        if(l==r) r++;
        l++;
        visited[v[l]]=1;
    }

    cout<<sum;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}