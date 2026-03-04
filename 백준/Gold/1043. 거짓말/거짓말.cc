// #include <bits/stdc++.h>

// using namespace std;

// int n,m;
// int knowPeople;
// int truths[51];
// int ans=0;

// void solution(vector<int> &members){
//     //members에 있는 사람들 중 한명이라도 truths에 있다면 땡인거임
//     int possible = true;
//     for(auto i : members){
//         if(truths[i]==1){
//             possible = false;
//             break;
//         }
//     }

//     if(possible) ans++;
//     else{
//         //이번 파티 사람들은 모두 진실을 알게 됨
//         for(auto i : members){
//             truths[i]=1;
//         }
//     }
// }

// void input(){
//     cin>>n>>m;
//     cin>>knowPeople;
//     for(int i=1;i<=knowPeople;i++){
//         int num;
//         cin>>num;
//         truths[num]=1;//num은 진실을 안다.
//     }

//     for(int i=1;i<=m;i++){
//         //파티마다 들어오는 사람
//         vector<int> members;
//         int membersSize;
//         cin>>membersSize;
//         for(int j=1;j<=membersSize;j++){
//             int num;
//             cin>>num;
//             members.push_back(num);
//         }

//         solution(members);
//     }
// }

// int main(){
//     ios_base::sync_with_stdio(0);
//     cin.tie(0); cout.tie(0);

//     input();
    
//     cout<<ans;
// }

/*와 그냥 위에처럼 쉽게 풀어버리려고 했는데, 거짓말을 했는데 나중에 진실을 아는 사람과 오면 망한다는 거임..!!
미쳤다... 그럼 어떡하냐 이거*/

//아 그럼 각 인원별로 언제 진실을 알게 될 지 미리 조사를 하고
//그걸 바탕으로 특정 파티에 모든 인원이 평생 진실을 알게 될 사람이 없을 경우에만 거짓을 말 할 수 있는거야
//와,..ㄷㄷ
// #include <bits/stdc++.h>

// using namespace std;

// int n,m;
// int knowPeople;
// int knows[51];
// vector<vector<int>> parties;
// void input(){
//     cin>>n>>m;
//     cin>>knowPeople;
//     for(int i=1;i<=knowPeople;i++){
//         int num;
//         cin>>num;
//         knows[num]=1;
//     }

//     for(int i=1;i<=m;i++){
//         vector<int> members;
//         int size;
//         cin>>size;
//         for(int j=1;j<=size;j++){
//             int num;
//             cin>>num;
//             members.push_back(num);
//         }

//         parties.push_back(members);
//     }
// }

// int cnt=0;

// void solution(){
//     //모든 n명에 대해서 언제 진실을 알게 되느냐.
//     //아니 언젠가는 알게 되는 애들과 아닌 애들을 구분하면 된다.
//     //파티가 순서대로 진행되니, 순서대로 알게되면 알게 되도록 설정하면 된다.
//     for(int i=0;i<m;i++){
//         //파티의 개수만큼 순회하는데 파티 자체는 vector이니 0부터 시작
//         bool theyKnow=false;
//         for(auto j : parties[i]){
//             //j가 한명이라도 knows에 걸리면 모든 j는 알게 된다.
//             if(knows[j]==1){
//                 theyKnow = true;
//                 break;
//             }
//         }

//         if(theyKnow){
//             for(auto j : parties[i]){
//                 knows[j]=1;
//             }
//         }
//     }
//     // 이렇게 되면 최종적으로 언젠가는 아는 애들은 1 아닌 애들은 0이 된다. 다시 처음부터 파티를 돌면서 
//     //평생 모를 애들만 모일 때 거짓말이 가능
//     for(int i=0;i<m;i++){
//         bool theyKnow = false;
//         for(auto j : parties[i]){
//             if(knows[j]==1){
//                 theyKnow = true;
//                 break;
//             }
//         }
//         if(!theyKnow) cnt++;
//     }

//     cout<<cnt;
// }

// int main(){
//     ios_base::sync_with_stdio(0);
//     cin.tie(0); cout.tie(0);

//     input();
//     solution();
// }

/*하 근데 또 이렇게 하면 안되는게, 
4번이 알고 있어
1,2
2,3
3,4 
이렇게 파티 멤버가 짜여져있으면 3번은 미래에 알게되고, 그렇게 2번도 알게되고, 1번도 알게되는데
내가 짠 코드대로 되면 그게 안되는거임 

뭐... 또다시 연결 그래프다! 결국 같이 온 애들은 묶이게 되고, 알고있는 부모랑 엮인다면 엮히도록 해야하는거야...

그니까 1-2 엮이고 부모는 둘다 1
2-3 엮이고 부모는 둘다 1이 될거고
3-4 엮이고 부모는 둘다 1이 되는데 4가 진실을 아니, 1이 부모인 애들은 전부 진실을 알게된다로 가는거임...*/

#include <bits/stdc++.h>

using namespace std;

int n,m;
int knowPeople;
//int knows[51];
vector<vector<int>> parties;

int cnt=0;
int parent[51];

int getParent(int a){
    if(parent[a]==a) return a;
    else{
        parent[a] = getParent(parent[a]);
        return parent[a];
    }
}

void unionFind(int a, int b){
    //자 일단 a와 b가 엮인다는 소리를 하는거야
    int parentA = getParent(a);
    int parentB = getParent(b);

    if(parentA<parentB){
        parent[parentB] = parentA;
    }
    else{
        parent[parentA] = parentB;
    }
}

void input(){
    cin>>n>>m;
    cin>>knowPeople;
    for(int i=1;i<=knowPeople;i++){
        int num;
        cin>>num;
        //knows[num]=1;
        unionFind(0,num);//0이라는 사람은 무조건 안다고 생각하자고 ㅇㅇ
    }

    for(int i=1;i<=m;i++){
        vector<int> members;
        int size;
        cin>>size;
        for(int j=1;j<=size;j++){
            int num;
            cin>>num;
            members.push_back(num);
        }

        parties.push_back(members);
    }
}

// void bfs(){
//     //일단 이미 알고 있는 사람들을 넣어주자.
//     queue<int> q;
//     for(int i=1;i<=n;i++){
//         if(knows[i]==1) q.push(i);
//     }

//     while(!q.empty()){
//         //연결된 것들은 전부 전파
//         int num = q.front(); q.pop();
//         int parentNum = getParent(num);
//         for(int i=1;i<=n;i++){
//             if(i==num) continue;
//             if(getParent(i)==parentNum){
//                 //일단 엮인 놈인데
//                 if(knows[i]==0){
//                     //그럼 이제 알게 되는거지
//                     knows[i]=1;
//                     q.push(i);
//                 }
//             }
//         }
//     }//시간복잡도 n^2인가
// }

void solution(){
    //이제 각 파티 맴버들끼리 엮어주자
    for(int i=0;i<m;i++){
        int size = parties[i].size();
        if(size == 1){
            continue;
        }
        else{
            //엮일 사람들이 존재한다는 거
            int president = parties[i][0];
            for(int j=1;j<size;j++){
                unionFind(president, parties[i][j]);
            }
        }
    }

    //다 엮어줬으니, 이미 알고 있는 사람들을 시작으로 해서, 지들과 엮인 모두를 타고타고 넘어가도록 하자
    //bfs(); 
    //0이라는 애가 부모이면 그냥 아는 놈이 되는거임

    //이러면 그냥 첫 원소가 알고있냐 아니냐로 판단해도 돼
    for(int i=0;i<m;i++){
        if(getParent(parties[i][0])!=0) cnt++;
    }

    cout<<cnt;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    for(int i=1;i<=50;i++){
        parent[i]=i;
    }

    input();
    solution();
}