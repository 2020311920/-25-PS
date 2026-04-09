/*
#include <string>
#include <vector>

using namespace std;

int solution(vector<int> food_times, long long k) {
    int answer = 0;
    long long time = 0;
    int foodN = food_times.size();
    int foodInd=0;
    while(time<k){
        while(food_times[foodInd]<=0){
            foodInd++;
            if(foodInd>=foodN) foodInd -= foodN;
        }
        food_times[foodInd]--;
        foodInd++;
        if(foodInd>=foodN) foodInd -= foodN;
        time++;
    }
    answer = foodInd+1;
    
    return answer;
}
*/

/*
처음에는 위의 내용처럼 풀었는데 그렇게 하면 안되겠어.
일단 먹을 음식이 없는 경우 어떻게 할 지도 처리를 안했을 뿐더러,
k라는 시간의 최대가 말도 안되게 크기에 시간을 단순히 흐르게 하는 것만으로도 시간초과가 세게 난다..

그렇다면 이건 시뮬레이션을 돌리는 개념의 문제가 아닌건가

일단 food_times의 모든 원소 합이 곧 다 먹는 데 걸리는 시간
다 먹게 된다면 사실상 vector에서 빠져도 되거덩?
food_times의 길이는 최대 20만, 약간 순회하면서 하나씩 pop하고, 1빼고, 0되면 안 넣고, 아니면 넣고 다시 순회하고..
걸리는 시간이 지금 최대 20조이기에 저때까지 순회하는 것 마저도 어렵다.

그렇다면 포인트는 순회라는 것을 하면 안된다는 것이다.
매 순간 food_times에 존재하는 0 초과의 개수를 알면, 한바퀴 돌았다 생각하면서 시간을 바로 빼버리면 좋지
최소 값을 알면 한바퀴 * 그 최솟값을 한번에 처리할 수도 있겠다.

대신, 전부 1씩 빠진다는게 포인트. 이런걸 바로바로 체크할 수 있어야 하는데

다 된다는 전제하에 시나리오는
매번 0이 아닌 원소의 개수를 체크, 그 중 최소 원소를 알면
개수*최소 원소 만큼의 시간을 걍 지났다고 해버릴 수 있다.
이러면 그 최소 원소는 0이 되는거고, 개수도 하나 줄겠지.
*/
#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(vector<int> food_times, long long k) {
    int answer = 0;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    
    int foodN = food_times.size();
    for(int i=0;i<foodN;i++){
        pq.push({food_times[i],i});
    }
    vector<int> leftFood;
    leftFood.assign(foodN,0);
    long long total = 0;
    while(!pq.empty()){
        auto a = pq.top(); pq.pop();
        a.first-=total;
        if(k<a.first*foodN){
            //다 돌기 전에 끝
            pq.push({a.first, a.second});
            k%=foodN;
            break;
        }
        leftFood[a.second]=1;//이미 이제 없는 음식
        total += a.first;
        k -= (a.first*foodN);
        foodN--;
    }
    
    if(pq.empty()) return -1;
    else{
        while(k>0){
            if(leftFood[answer]==0){
                k--;
            }
            answer++;
        }
    }
    while(leftFood[answer]==1) answer++;
    return answer+1;
}