#include <bits/stdc++.h>

using namespace std;

int n,k;

vector<pair<int, int>> boseok;
vector<int> bag;

// priority_queue<int, vector<int>, less<int>> pq;

// struct s{
//     int a;
//     int b;
//     int c;
// };

// struct cmp{
//     bool operator()(const s& s1, const s& s2) const{
//         if(s1.a!=s2.a) return s1.a>s2.a;
//         else if(s1.b!=s2.b) return s1.b<s2.b;
//         else return s1.c>s2.c;
//     }
// };


// priority_queue<s, vector<s>, cmp> pq;
//대신 이렇게 하면, cmp에서는 구조체 s에게서 a가 클수록, b가 작을수록, c가 클수록  true가 나오기에 
//a가 작을수록, b가 클수록, c가 작을수록 top에 있도록 하는거야 맞아?

void input(){
    cin>>n>>k;

    for(int i=1;i<=n;i++){
        int price; int weight;
        cin>>weight>>price;
        boseok.push_back({weight, price});
    }
    sort(boseok.begin(), boseok.end());

    for(int i=1;i<=k;i++){
        int weight;
        cin>>weight;
        bag.push_back(weight);
    }
    sort(bag.begin(), bag.end());

    
}

void solution(){
    priority_queue<int, vector<int>, less<int>> pricePQ;
    int boseokInd=0;
    long long ans=0;
    for(int i=0;i<k;i++){
        int weight = bag[i];
        while(1){
            if(boseokInd<n && boseok[boseokInd].first <= weight){
                pricePQ.push(boseok[boseokInd].second);
                boseokInd++;
            }
            else break;
        }

        if(!pricePQ.empty()){
            ans+=pricePQ.top();
            pricePQ.pop();
        }
    }

    cout<<ans;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}