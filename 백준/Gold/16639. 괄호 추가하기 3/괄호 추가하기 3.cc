#include <bits/stdc++.h>

using namespace std;

long long INTMIN = -2147483647;
int n;
string str;
deque<long long> nums;
deque<char> gihos;
int numCnt=0;
int gihoCnt=0;

void input(){
    cin>>n;
    cin>>str;
    for(int i=0;i<n;i++){
        char ch =str[i];
        if(ch>='0' && ch<='9'){
            //이러면 숫자인거구요
            nums.push_back(ch-'0');
            numCnt++;
        }
        else{
            //기호들이니까
            gihos.push_back(ch);
            gihoCnt++;
        }
    }
}

long long maxAns = INTMIN;

long long calculate(int i){
    if(gihos[i]=='-'){
        return nums[i]-nums[i+1];
    }
    else if(gihos[i]=='+'){
        return nums[i]+nums[i+1];

    }
    else if(gihos[i]=='*'){
        return nums[i]*nums[i+1];
    }
    return -1;
}

void dfs(){//하.. 근데 이렇게 되면 deque가 너무 많아지는데 메모리가 괜찮나 모르겠네..;;
    if(gihos.size()==0){
        maxAns = max(maxAns, nums[0]);
        return;
    }

    // cout<<"현재 상태 : \n";
    // for(auto i : nums) cout<<i<<" ";
    // cout<<"\n";
    // for(auto i : gihos) cout<<i<<" ";
    // cout<<"\n";

    int gihoSize = gihos.size();
    int numSize = nums.size();
    for(int i=0;i<gihoSize;i++){
        //원하는 기호를 선택
        //i번째 기호를 택한거니까. 그럼 nums에서 i와 i+1이 무조건 존재할거야 범위 체크 안해도 돼
        //중간에 있으면 어떻게 그것만 쏘옥 빼놓느냐 그게 문제거덩

        //일단 nums[i] gihos[i] nums[i+1] 연산을 수행하긴 함
        long long result = calculate(i);

        deque<long long> saveNums = nums;
        deque<char> saveGihos = gihos;

        for(int j=0;j<numSize;j++){
            //그니까 num에서 i, i+1번쨰 애들은 빼고 넣는거야 근데 i+1번째 애를 뽑았으면 그때 result를 넣어주는거지
            long long num = nums.front(); nums.pop_front();
            if(i==j){
                //다시 넣어주지 마
                continue;
            }
            if(i+1==j){
                nums.push_back(result);
                continue;
            }
            nums.push_back(num);
        }

        for(int j=0;j<gihoSize;j++){
            char giho = gihos.front(); gihos.pop_front();
            if(i==j){
                continue;
            }
            gihos.push_back(giho);
        }

        dfs();

        //원상복귀
        nums = saveNums;
        gihos = saveGihos;
    }
}

void solution(){
    //흠.. 괄호를 어떻게 넣느냐를 고민하는 건 너무 어려워 보여. 어디에 괄호를 넣냐 안넣냐는 말이 안되고
    //괄호라는 것은 특정 연산을 먼저할것입니다라는 소리와 동일하거덩
    //그러니 어떤 연산을 먼저 할지를 고민하는거야
    //만약 이걸 DFS로 한다하면 기호의 최대 개수는 9개가되거덩 시간복잡도 2^9이 된다 낫배드네
    dfs();

    cout<<maxAns;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    input();
    solution();
}