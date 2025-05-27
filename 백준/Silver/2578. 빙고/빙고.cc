#include <bits/stdc++.h>

using namespace std;

pair<int, int> my[26];
int row[6];
int col[6];
int cross[3];

int main(){
    for(int i=1;i<=5;i++){
        for(int j=1;j<=5;j++){
            int num;
            cin>>num;
            my[num].first = i;
            my[num].second = j;
        }
    }
    int ans=0; 
    int result; 
    bool found = false;
    int i=1;
    for(;i<=25;i++){
        int k;
        cin>>k;

        //이렇게 하면 검색이 겁나게 편하겠지?
        
        if(row[my[k].first]==4){
            ans++;
            //cout<<"빙고 발생\n";
        }
        row[my[k].first]++;
         
        if(col[my[k].second]==4){
            ans++;
            //cout<<"빙고 발생\n";
        }
        col[my[k].second]++;
        if(my[k].first == my[k].second){
            if(cross[1]==4){
                ans++;
                //cout<<"빙고 발생\n";
            }
            cross[1]++;
        }
        
        
        if(my[k].first+my[k].second==6){ 
            if(cross[2]==4){
                ans++;
                //cout<<"빙고 발생\n";
            }
            cross[2]++;
        }

        if(ans>=3 && found == false){
            result=i;
            found = true;
        }

    }

    cout<<result;
}