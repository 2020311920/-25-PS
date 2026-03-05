#include <bits/stdc++.h>

using namespace std;

int n,c;
int m;

/*거의 한시간동안 여러가지 방법에 대해 고민했다.
처음에는 현재 위치에서 뭐뭐를 받을지는 지금 정할 수 없다. 그러니 나는 역으로 하겠다
이러면서 역으로 몇개를 받아야 하니, 이전에는 몇개를 실은채로 올 수 있다 이렇게 접근했는데, 너무 어렵더라고

그러다가 머리를 스치는 한가지 아이디어가 떠올랐고 이게 상당히 좋다고 생각했다.
특정 위치에서 어떤 박스를 챙길 것인지는 사실 언제 이걸 전달해서 털어내느냐가 참 중요하다. 이게 곧 가중치로 
접근할 수 있는거야. 그래서 가중치가 높은(거리가 작은)애를 최대로 담는다. 공간이 남으면 다음 가중치로 채우는거지
그러고 거리가 0이 되면 sum에 더할 수 있고. 남은 거리는 또 현재 위치에서 가중치가 높은 상자로 채우는건데, 만약 현재 들고 있는 것보다 적은 가중치를 더 많이 담을 수 있으면 이미 들고 있는 걸 버려서라도 채우는게 이득인거야. 물론 다 버린다기보단 그니까 차등적으로 가져간다는 거지. 이렇게 하면 되게 이상적이야 ㄷㄷㄷ 

내가 생각해도 이걸 스스로 어떻게 생각해냈나 싶다 지렸다.*/
vector<pair<int, int>> town[2001];

void input(){
    cin>>n>>c;
    cin>>m;
    for(int i=1;i<=m;i++){
        int from, to, vol;
        cin>>from>>to>>vol;
        town[from].push_back({to-from, vol});
    }
}

void testPrint(deque<pair<int, int>> &myBag){
    //cout<<"현재 위치"<<nowPos<<"가방 안 :\n";
    for(auto i : myBag){
        cout<<"dist : "<<i.first<<", vol : "<<i.second<<"\n";
    }
}

void solution(){
    //매 타운에서는 어디로 몇개 보낼지가 벡터로 정리되어있는 상태
    //이걸 정렬해주면 알아서 가까운 곳으로 보내는 것으로 정리되어있을 것이라서
    int ans = 0;
    int nowPos = 1;
    int nowCap = 0;
    deque<pair<int,int>> myBag;//{dist, vol} 앞으로 가야할 거리, 개수
    while(nowPos<=n){
        // cout<<"물품 내리기 전 현재 위치 : "<<nowPos<<"\n";
        // testPrint(myBag);
        //myBag에 있는 모든 애들 dist를 줄이고 0이면 sum에 더해줘라 ㅇㅇ
        for(auto &i : myBag){
            i.first -= 1;
        }
        //myBag에는 애초에 거리 순으로 넣어져있기에 맨 앞이 0이 아닐때까지 빼면서 sum에 더해주면 돼
        while(!myBag.empty()){
            if(myBag.front().first == 0){
                ans += myBag.front().second; //도착했으니 비워주면서 처리된 물품 수
                nowCap -= myBag.front().second;
                myBag.pop_front();
            }
            else break;
        }

        // cout<<"물품 내린 후 현재 상태 : \n";
        // testPrint(myBag);
        //현재 위치에서 보낼 물건들을 챙겨보자
        auto things = town[nowPos];
        while(!myBag.empty()){
            int dist = myBag.front().first;
            int vol = myBag.front().second;
            myBag.pop_front();
            things.push_back({dist, vol});
        }
        nowCap=0;
        sort(things.begin(), things.end());
        //c만큼을 순서대로 다시 bag에 넣어주자
        for(auto i : things){
            if(nowCap==c) break;
            else{
                int dist = i.first;
                int vol = i.second;
                if(vol<=c-nowCap){
                    //딱 넣을 수 있는 만큼 있거나 부족한거면 걍 넣어줘도 돼
                    myBag.push_back({dist, vol});
                    nowCap+=vol;
                }
                else{
                    //넘친다면 가능한 만큼만 넣는거지 
                    //vol>c-nowCap
                    myBag.push_back({dist, c-nowCap});
                    nowCap+=(c-nowCap);
                }
            }
        }
        
        // cout<<"추가 물품 챙긴 뒤 상태 : \n";
        // testPrint(myBag);
        nowPos++;
    }

    cout<<ans;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    input();
    solution();
}