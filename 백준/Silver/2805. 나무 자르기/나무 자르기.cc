#include <bits/stdc++.h>

using namespace std;

long long treeN, want;
long long tree[1000001];
long long tallest;

long long cut(long long height){
    long long sum = 0;
    for(int i=1;i<=treeN;i++){
        if(tree[i]-height>0) sum+=(tree[i]-height);
    }
    return sum;
}

long long myFind(){
    long long l, r, mid;
    l=0;
    r=tallest;

    while(l<=r){
        mid = (l+r)/2;
        //cout<<mid<<"높이로 자르면, "<<cut(mid)<<"만큼 자르게 됩니다.\n";
        if(want<cut(mid)) l = mid+1;
        else if(want>cut(mid)) r = mid-1;
        else return mid;
    }
    return r;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>treeN>>want;

    for(int i=1;i<=treeN;i++){
        long long length;
        cin>>length;
        tree[i] = length;
    }

    sort(tree+1, tree+1+treeN);

    tallest = tree[treeN];

    cout<<myFind();
}