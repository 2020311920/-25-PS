#include <bits/stdc++.h>

using namespace std;

int t,k;
string w;
vector<int> character[27];

void initialize(){
    for(int i=0;i<27;i++) character[i].clear();
}

void solution(string w, int k){
    //w 문자열에서 특정 문자 k개가 든 문자열 길이
    
    int strLength = w.size();
    for(int i=0;i<strLength;i++){
        character[w[i]-'a'].push_back(i);
    }

    int minLength = 10001; int maxLength = -1;
    for(int i=0;i<27;i++){
        if(character[i].size()>=k){
            //이러면 체크해봐야지
            //character[i]가 위치한 곳들을 k개 고르는거야

            //1. 얘를 k개 포함하는 가장 짧은 연속 문자열 => 당연히 양쪽이 그 숫자여야겠지 그러니 k개를 고르고
            //그 양쪽 거리가 최소인거가 "짧은 연속 문자열의 길이"

            //2. 그 문자를 k개 포함하는데 첫번쨰와 마지막 글자가 그 해당문자로 같은 가장 긴 연속 문자열
            //->이게 1번이랑 다를게 없다는거지 ㅇㅇ 그 해당 문자가 k개 포함하는 가장 긴 연속문자열인거임

            //즉 k개 이상 있는 문자열들을 바탕으로 걔의 경우 최소 최대를 구해서 최종 최대 최소를 구하면 되는 문제였다리

            //근데 또 쉬운게 띄엄띄엄 고르면 말이 안돼 그래서 그냥 1,2,3,4,5 이렇게 있고 3개를 고르면
            //123,234,345 이렇게만 가능한거야
            int start = 0; //0번째 인덱스를 시작으로
            int end = character[i].size()-1;
            
            //즉 시작점은 end-(k-1)까지
            for(start=0; start<=end-(k-1);start++){
                //시작점 for문
                //즉 시작은 start, k개 고른 끝은 start+k-1;
                int tempLength = character[i][start+k-1]-character[i][start]+1;
                if(tempLength<minLength) minLength = tempLength;
                if(tempLength>maxLength) maxLength = tempLength;
            }
        }
    }

    if(minLength==10001 || maxLength == -1) cout<<-1<<"\n";
    else{
        cout<<minLength <<" "<<maxLength<<"\n";
    } 
}

void input(){
    cin>>t;

    for(int i=1;i<=t;i++){
        cin>>w>>k;
        initialize();
        solution(w,k);
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    //solution();
}