#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int selected[50000];

int getAnswer(vector<int> &people, int limit){
    int boatCnt=0;
    int peopleCnt = people.size();

    int l = 0 ; int r = peopleCnt-1;
    while(l<r){
        if(people[r]+people[l]<=limit){
            l++;
            r--;
        }
        else{
            r--;
        }
        boatCnt++;
    }
    if(l==r) boatCnt++;
    return boatCnt;
}

int solution(vector<int> people, int limit) {
    int answer = 0;
    sort(people.begin(), people.end());
    answer = getAnswer(people, limit);
    return answer;
}