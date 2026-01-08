#include <bits/stdc++.h>

using namespace std;

int n;
int students[401][5];
pair<int, int> studentsCoord[401];
int room[21][21];

int main(){
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin>>n;

    for(int i=1;i<=n*n;i++){
        int student;
        cin>>student;
        students[i][0]=student;
        for(int j=1;j<=4;j++){
            cin>>students[i][j];
        }
    }

    for(int i=1;i<=n*n;i++){
        int me = students[i][0]; //이게 나야
        int like[4]={students[i][1], students[i][2], students[i][3], students[i][4]};
        vector<pair<int, int>> myPlace; //최종 me의 위치
        int maxLikeCnt=-1;
        for(int j=1;j<=n;j++){
            for(int k=1;k<=n;k++){
                if(room[j][k]!=0) continue;
                //교실을 다 돌면서 각 위치에서 인접에 친구가 있는지
                //현재 위치는 j,k
                int likeCnt=0;
                for(int l=0;l<=3;l++){
                    if(abs(studentsCoord[like[l]].first-j)+abs(studentsCoord[like[l]].second-k)==1){
                        likeCnt++;
                    }
                }

                if(likeCnt>=maxLikeCnt){
                    if(likeCnt>maxLikeCnt) myPlace.clear();
                    maxLikeCnt=likeCnt;
                    myPlace.push_back({j,k});
                }
            }
        }

        // cout<<me<<"학생은 현재 maxLikeCnt가 "<<maxLikeCnt<<"입니다.\n";
        // for(auto j : myPlace){
        //     cout<<"{"<<j.first<<","<<j.second<<"}, ";
        // }
        // cout<<"\n";
        vector<pair<int, int>> myPlace2;
        int maxZeroCnt=-1;
        for(auto j : myPlace){
            int zeroCnt=0;
            if(j.first-1>0 && j.second>0 && j.first-1<=n && j.second<=n && room[j.first-1][j.second]==0) zeroCnt++;
            if(j.first>0 && j.second-1>0 && j.first<=n && j.second-1<=n && room[j.first][j.second-1]==0) zeroCnt++;
            if(j.first+1>0 && j.second>0 && j.first+1<=n && j.second<=n && room[j.first+1][j.second]==0) zeroCnt++;
            if(j.first>0 && j.second+1>0 && j.first<=n && j.second+1<=n && room[j.first][j.second+1]==0) zeroCnt++;

            if(zeroCnt>=maxZeroCnt){
                if(zeroCnt>maxZeroCnt) myPlace2.clear();
                maxZeroCnt=zeroCnt;
                myPlace2.push_back({j.first, j.second});
            }
        }

        // cout<<me<<"학색은 이제 maxZeroCnt가 "<<maxZeroCnt<<"이므로\n";
        // for(auto j : myPlace2){
        //     cout<<"{"<<j.first<<","<<j.second<<"}, ";
        // }
        // cout<<"\n";

        sort(myPlace2.begin(), myPlace2.end());

        room[myPlace2[0].first][myPlace2[0].second] = me;
        
        studentsCoord[me]={myPlace2[0].first, myPlace2[0].second};
        
    }

    
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=n;j++){
    //         cout<<room[i][j]<<" ";
    //     }   
    //     cout<<"\n";
    // }

    //만족도 조사
    int ans=0;
    for(int i=1;i<=n*n;i++){
        int me = students[i][0]; //이게 나야
        int like[4]={students[i][1], students[i][2], students[i][3], students[i][4]};

        int likeCnt=0;
        for(int l=0;l<=3;l++){
            if(abs(studentsCoord[like[l]].first-studentsCoord[me].first)+abs(studentsCoord[like[l]].second-studentsCoord[me].second)==1){
                likeCnt++;
            }
        }
        ans+=(likeCnt>0 ? pow(10, likeCnt-1) : 0);
    }

    cout<<ans;

}