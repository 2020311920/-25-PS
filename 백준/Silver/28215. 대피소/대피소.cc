// #include <bits/stdc++.h>

// using namespace std;

// int n,k;
// vector<pair<int, int>> v;
// int selected[50];

// void input(){
//     cin>>n>>k;

//     for(int i=1;i<=n;i++){
//         int a,b;
//         cin>>a>>b;
//         v.push_back({a,b});
//     }
// }

// int minAns = 200001;

// int distMemoi[51];

// void calculate(int where){
//     if(distMemoi[where]>0){
//         //미리 구해졌다는 뜻
//         minAns = min(minAns, distMemoi[where]);
//         return;
//     }
//     int tempMax = 0;
//     int x = v[where].first; int y = v[where].second;
//     for(auto h : v){
//         int dist = abs(x-h.first)+abs(y-h.second);
//         tempMax = max(tempMax, dist);
//     }
//     distMemoi[where] = tempMax;
//     minAns = min(minAns, tempMax);
// }

// void dfs(int cnt, int where){
//     if(cnt==k){
//         //k개의 대피소 설치 완료
//         //매번 대피소를 고를 때 거리를 계산하는게 편할 듯, 왜냐
//         //고른 대피소 k개를 어디에 저장한 뒤에 그걸 가지고 계산하면 대피소 k개를 어딘가에 저장해둬야 하니 불편할 거 같음

//         return;
//     }

//     for(int i=where;i<n;i++){
//         if(selected[i]==0){
//             //해당 집을 대피소로 고르지 않음
//             selected[i]=1;
//             calculate(i);
//             dfs(cnt+1, i);
//             selected[i]=0;
//         }
//     }
// }
// void printDist(){
//     cout<<"\n";
//     for(int i=0;i<n;i++){
//         cout<<distMemoi[i]<<" ";
//     }
// }

// void solution(){
//     dfs(0,0);
//     cout<<minAns;
//     printDist();
// }

// int main(){
//     ios::sync_with_stdio(0);
//     cin.tie(0);

//     input();
//     solution();
// }

//초기 생각했던 풀이를 사용해보니 제대로 풀리지 않는다.
//특정 집이 대피소로 지정될 경우 모든 집까지의 거리 중 최대를 저장해놓고, 불러와서 비교해보려 했는데
//이러면 문제에서 원하는대로 비교하는 과정이 빠지게 되네.. 이렇게 하는게 시간적으로 매우 이득일 것이라 생각했다
//왜냐면 대피소를 지정하고, 이에 따라 모든 집이 모든 대피소를 각각 들러보며 계산하면 뭔가 손해처럼 느껴져서
//근데 위 풀이가 잘못됐으니, 손해라고 해도 꼼꼼히 푸는 전략으로 틀어보자.

#include <bits/stdc++.h>

using namespace std;

int n,k;
vector<pair<int, int>> v;
int selected[50];
vector<int> selectedInd;
int ansMin=200001;

void input(){
    cin>>n>>k;

    for(int i=1;i<=n;i++){
        int a,b;
        cin>>a>>b;
        v.push_back({a,b});
    }
}

int calculate(){
    //각 집마다 모든 대피소를 검색해서 최단 거리 체크
    int tempMax = 0;
    for(auto house : v){
        int tempMin=200001;
        for(auto exit : selectedInd){
            int dist = abs(house.first - v[exit].first)+abs(house.second - v[exit].second);
            tempMin = min(tempMin, dist);
        }
        //한 집이 모든 대피소까지의 거리 중 최소를 고름
        //그 거리중 최대를 찾아
        tempMax = max(tempMin, tempMax);
    }

    return tempMax;
}

void dfs(int cnt, int where){
    if(cnt==k){
        int tempMax = calculate();
        ansMin = min(ansMin, tempMax);
        return;
    }

    for(int i = where; i<n; i++){
        if(selected[i]==0){
            selected[i]=1;
            selectedInd.push_back(i);
            dfs(cnt+1, i+1);
            selected[i]=0;
            selectedInd.pop_back();
        }
    }
}

void solution(){
    dfs(0,0);
    cout<<ansMin;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}