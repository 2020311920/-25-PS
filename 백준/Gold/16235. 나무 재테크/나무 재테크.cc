// #include <bits/stdc++.h>

// using namespace std;

// int n,m,k;

// int field[11][11];
// int tempField[11][11];
// vector<pair<pair<int, int>, int>> trees;

// int x,y,age;
// int ans;

// bool isValid(int x, int y){
//     if(x>=1 && x<=n && y>=1 && y<=n) return true;
//     return false;
// }

// bool compare(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b){
    

//     if(a.first.first==b.first.first){
//         //x좌표가 일치하다면
//         if(a.first.second==b.first.second){
//             //y좌표까지 일치하다면
//             return a.second>b.second;
//         }
        
//         //x만 일치
//         return a.first.second>b.first.second;
//     }

//     return a.first.first>b.first.first;

// }


// int main(){
//     ios::sync_with_stdio(0);
//     cin.tie(0);

//     cin>>n>>m>>k;

//     for(int i=1;i<=n;i++){
//         for(int j=1;j<=n;j++){
//             cin>>tempField[i][j];
//             field[i][j] = 5;
//         }
//     }

//     for(int i=1;i<=m;i++){
//         cin>>x>>y>>age;
//         trees.push_back({{x,y}, age});
//     }

//     // sort(trees.begin(), trees.end(), compare);

//     // for(auto i : trees){
//     //     cout<<i.first.first<<","<<i.first.second<<" 위치에 "<<i.second<<"나이의 나무\n";
//     // }

//     // pair<pair<int, int>, int> p = trees.back();
//     // cout<<p.first.first<<","<<p.first.second<<" 위치에 "<<p.second<<"나이의 나무\n";

//     while(k){
//         k--;
//         vector<pair<pair<int, int>, int>> tempTrees;
//         //vector<pair<pair<int, int>, int>> dieTrees;
//         sort(trees.begin(), trees.end());
//         reverse(trees.begin(), trees.end());

//         //봄
        
//         //나무들 돌면서 양분 먹기
//         bool dieTrigger = false;
//         int prevX=0, prevY=0;
//         while(trees.size()!=0){
//             pair<pair<int, int>,int> tree = trees.back();
//             trees.pop_back();
//             int treeAge = tree.second;
//             int treeX = tree.first.first;
//             int treeY = tree.first.second;
//             if(treeX == prevX && treeY == prevY){
//                 //같다는 건, 중복 칸에 여러 나무 처리 중이라는 뜻
//             }
//             else{
//                 prevX = treeX; prevY = treeY;
//                 //동시에 다른 좌표로 넘어간거니까,
//                 dieTrigger= false;
                
//             }

//             if(field[treeX][treeY]>=treeAge && !dieTrigger){
//                 field[treeX][treeY] -= treeAge;
//                 tree.second++;

//                 //양분을 먹고 자랐으니, 다시 trees 큐에 넣어줘야 하는데, 새로운 곳에 넣었다가 trees로 변환
//                 tempTrees.push_back(tree);
//             }

//             else{
//                 //죽는거니까 그냥 진행
                
//                 //dieTrees.push_back(tree);
                
//                 //원래는 죽는 애들 따로 모아서 했는데 시간 아끼려고 봄에 처리하려고 함, 근데 이때 주의해야하는게
//                 //원래라면 해당 칸과 같은 뒤의 나무들은 주욱 죽어야 하는데, 양분 추가되면 사는 경우도 생기므로 아싸리 처리해야 함.
//                 //근데 또 이때 다른 칸으로 이동 시에는 다이트리거를 다시 풀어줘야 하거덩
//                 dieTrigger = true;
//                 int energy = treeAge/2;
//                 field[treeX][treeY] += energy;
//             }

//         }

//         //여름 - dietrees에서 뽑아내면서 양분 추가
//         //이거 봄에서 죽을 때 처리 가능, 왜냐 애초에 나이 어린 순으로 양분 맥이니까, 죽기 시작하면 전부 처리하면 되네
//         // for(auto i : dieTrees){
//         //     int energy = i.second/2;

//         //     field[i.first.first][i.first.second] +=energy;
//         // }
//         // dieTrees.clear();


//         //가을-나무 번식
//         int nowTreeCnt = tempTrees.size();
//         for(int i=0;i<nowTreeCnt;i++){
//             if(tempTrees[i].second % 5 == 0){
//                 //번식을 진행
//                 int treeX = tempTrees[i].first.first;
//                 int treeY = tempTrees[i].first.second;

//                 if(isValid(treeX-1, treeY-1)) tempTrees.push_back({{treeX-1, treeY-1}, 1});
//                 if(isValid(treeX-1, treeY)) tempTrees.push_back({{treeX-1, treeY}, 1});
//                 if(isValid(treeX-1, treeY+1)) tempTrees.push_back({{treeX-1, treeY+1}, 1});
//                 if(isValid(treeX, treeY-1)) tempTrees.push_back({{treeX, treeY-1}, 1});
//                 if(isValid(treeX, treeY+1)) tempTrees.push_back({{treeX, treeY+1}, 1});
//                 if(isValid(treeX+1, treeY-1)) tempTrees.push_back({{treeX+1, treeY-1}, 1});
//                 if(isValid(treeX+1, treeY)) tempTrees.push_back({{treeX+1, treeY}, 1});
//                 if(isValid(treeX+1, treeY+1)) tempTrees.push_back({{treeX+1, treeY+1}, 1});

//             }
//         }

//         //겨울
//         for(int i=1;i<=n;i++){
//             for(int j=1;j<=n;j++){
//                 field[i][j] += tempField[i][j];
//             }
//         }

//         trees.clear(); ans =0;

//         for(auto i : tempTrees){
//             trees.push_back(i);
//             ans++;
//         }
//         tempTrees.clear();
        
//         // sort(trees.begin(), trees.end(), compare);
        
//         // for(auto i : trees){
//         //     cout<<i.first.first<<","<<i.first.second<<" 위치에 "<<i.second<<"나이의 나무\n";
//         // }
//         // cout<<"현재 땅의 양분\n";
//         // for(int i=1;i<=n;i++){
//         //     for(int j=1;j<=n;j++){
//         //         cout<<field[i][j]<<" ";
//         //     }
//         //     cout<<"\n";
//         // }
//         // cout<<"\n";
//     }

//     cout<<ans;

//     // sort(trees.begin(), trees.end(), compare);

//     // cout<<"현재 땅의 양분\n";
//     // for(int i=1;i<=n;i++){
//     //     for(int j=1;j<=n;j++){
//     //         cout<<field[i][j]<<" ";
//     //     }
//     //     cout<<"\n";
//     // }

//     // for(auto i : trees){
//     //     cout<<i.first.first<<","<<i.first.second<<" 위치에 "<<i.second<<"나이의 나무\n";
//     // }

// }

//다시 풀어보겠습니다.

#include <bits/stdc++.h>

using namespace std;

int n,m,k;

int field[11][11];
int tempField[11][11]; // 매해 겨울 추가되는 양분
int dieField[11][11];

deque<int> whereTree[11][11]; //현재 필드에 있는 나무의 나이들

int dirX[8]={-1,-1,-1,0,0,1,1,1};
int dirY[8]={-1,0,1,-1,1,-1,0,1};

int x, y, z;

bool isValid(int x, int y){
    if(x>=1 && x<=n && y>=1 && y<=n) return true;
    else return false;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin>>n>>m>>k;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>tempField[i][j];
            field[i][j] = 5; // 처음에는 모든 땅에 양분 5
        }
    }

    for(int i=1;i<=m;i++){
        cin>>x>>y>>z;

        //x,y 위치에 나무가 있고 걔 나이가 z이다.
        //처음 입력받을 때는 나무들이 겹치지 않는댔어
        whereTree[x][y].push_back(z);
    }

    while(k){
        k--;

        //봄
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                //필드들을 돌며 나무가 있으면 처리하자
                if(whereTree[i][j].size()>0){
                    int length = whereTree[i][j].size();//딱 그시점 총길이
                    //나무가 있다.
                    for(int ind=0;ind<length;ind++){
                        if(field[i][j]>=whereTree[i][j][ind]){
                            field[i][j]-=whereTree[i][j][ind];
                            whereTree[i][j][ind]++;
                        }
                        else{
                            //나무가 죽음 이때부터는 뒤에가 다 죽음
                            //dieField에 차곡차곡 모아서 나중에 더해줘
                            //그니까 whereTree[i][j]의 뒤부터 딱 저 ind까지 pop하면서 
                            for(int last = length-1;last>=ind;last--){
                                dieField[i][j] += whereTree[i][j][last]/2;
                                whereTree[i][j].pop_back();
                            }
                            break; //이렇게 바로 탈출
                        }
                    }
                }
            }
        }
        //여름
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                field[i][j] += dieField[i][j];
                dieField[i][j]=0;
            }
        }

        //가을-번식할 때 deque에 잘만 넣어주면 돼

        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                int length = whereTree[i][j].size();
                //현시점 i,j에 있는 나무들의 개수
                for(int ind = 0; ind<length;ind++){
                    //i,j에 있는 나무들에 접근하면서 번식
                    if(whereTree[i][j][ind]%5==0){
                        for(int dirInd=0;dirInd<8;dirInd++){
                            if(isValid(i+dirX[dirInd], j+dirY[dirInd])){
                                whereTree[i+dirX[dirInd]][j+dirY[dirInd]].push_front(1);
                            }
                        }
                    }
                }

                //겨울 여기에 흡수
                field[i][j] += tempField[i][j];
            }
        }

    }
    int cnt=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cnt += whereTree[i][j].size();
        }
    }
    cout<<cnt;
}