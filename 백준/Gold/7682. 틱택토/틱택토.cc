//1번 x가 하나더 많거나, 둘이 수가 같아야 함
//2번 x가 수가 더 많은 경우는 O가 졌다는거임
//3번 수가 동일하면 x가 졌다는거임

#include <bits/stdc++.h>

using namespace std;

string str;
//int field[4][4];
int countOne; int countTwo;
unordered_map<int, int> whereOX;
bool isXwin = false; bool isOwin= false; 

void init(){   
    // for(int i=1;i<=3;i++){
    //     for(int j=1;j<=3;j++){
    //         field[i][j]=-1;
    //     }
    // }
    countOne = 0;
    countTwo = 0;
    whereOX.clear();
    isXwin=false; isOwin = false;
}

void makeField(){
    for(int i=1;i<=3;i++){
        for(int j=1;j<=3;j++){
            if(str[3*(i-1)+j-1]=='X'){
                countOne++;
                whereOX[3*(i-1)+j] = 1;
            }
            else if(str[3*(i-1)+j-1]=='O'){
                countTwo++;
                whereOX[3*(i-1)+j]=2;
            }
            else{
                whereOX[3*(i-1)+j]=0;
            }        
        }
    }
}

bool isLine(int a, int b, int c){
    if(whereOX.at(a)!=0 && whereOX.at(a)==whereOX.at(b) && whereOX.at(b)==whereOX.at(c)){
        if(whereOX.at(a)==1) isXwin=true;
        else isOwin = true;
        return true;
    }
    else return false;
}

int checkWhoWin(){
    //8개의 방향을 판단해야 한다.
    isLine(1,2,3);
    isLine(4,5,6);
    isLine(7,8,9);
    isLine(1,4,7);
    isLine(2,5,8);
    isLine(3,6,9);
    isLine(1,5,9);
    isLine(3,5,7);

    if(isXwin==true && isOwin==true){
        //둘다 이기는 경우는 존재하면 안돼
        return 0;
    }
    else if(isXwin==true && isOwin == false){
        return 1;
    }
    else if(isXwin==false && isOwin==true){
        return 2;
    }
    else return 3;
}

void solution(){
    init();
    makeField();

    //cout<<str<<"은 X : "<<countOne<<", O : "<<countTwo<<"\n";
    //cout<<str;
    if(!(countOne==countTwo || countOne == countTwo+1)){
        //cout<<"개수가 말이 안됨\n";
        cout<<"invalid\n";
        return;
    }
    if(countOne == countTwo+1){
        //1이 이긴거임 또는 판이 꽉 찼을 때
        int returnV = checkWhoWin();
        if(returnV==1){
            cout<<"valid\n";
        } 
        else if(returnV==3){
            if(countOne+countTwo==9){
                cout<<"valid\n";
            }
            else cout<<"invalid\n";
        }
        else cout<<"invalid\n";
    }
    if(countOne==countTwo){
        //2가 이긴거임
        int returnV = checkWhoWin();
        if(returnV==2) cout<<"valid\n";
        else if(returnV==3 && countOne+countTwo==9) cout<<"valid\n";
        else cout<<"invalid\n";
    }
    return;
}

void input(){
    cin>>str;
    while(str.compare("end")!=0){
        solution();  
        cin>>str;
    }
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
}