#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

//K를 보는 순간 딱 드는 생각이, 최악의 경우 한번 순회하는 것마저 시간초과가 뜨겠구나라는 생각.
/*
어떤 숫자를 보고, 이게 처리된 숫자인지 아닌지, 처리됐다면, 처리 안했던 숫자들 중 가장 작은걸 고르는 이 일련의 과정에
배열을 순회한다라는 진행방식이 있어서는 안된다는거야. 왜? 이미 1~ 10^12 -1만큼 채워졌는데 마지막 애가 1번을 요청하면, 
주르륵 키워가면서 찾다가 10000초가 지난다고

고민하다 든 생각인데 이걸 parent를 활용해보면 어떨까...
그니까
a방의 주인은 없지 그래서 빈공간이야.
근데 a방이 차지됐어. 그러면 이제 parent[a] = a+1이 되는거야, 저기를 접근하면 다음에 갈 곳을 알려주는거지.
그 뒤에 a방을 요청하면 parent[a]방을 주는거야. 
다만 이 아이디어는 그만큼의 배열을 만들수가 없다는거야. 

그러니 매핑을 해버릴까 um으로
오.. 나쁘지 않아보인다.

1 2 3 4 5 6 7 8 9 10
7 3 6 5 6 7
*/
unordered_map<long long, long long> parent;

long long getParent(long long a){
    long long b = a;
    vector<long long> v;
    v.push_back(b);
    while(1){
        auto it = parent.find(b);
        if(it==parent.end()){
            for(auto i : v) parent[i] = b+1;
            return b;
        }
        else{
            b = it->second;
            v.push_back(b);
        }
    }
}
vector<long long> solution(long long k, vector<long long> room_number) {
    vector<long long> answer;
    for(auto i : room_number){
        answer.push_back(getParent(i));
    }
    return answer;
}