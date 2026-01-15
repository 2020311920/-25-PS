//Bronze3

#include <bits/stdc++.h>

using namespace std;

int a,b,c;

void checkTriangle(){
    if(max(max(a,b),c)*2>=(a+b+c)){
        cout<<"Invalid\n";
    }
    else if(a==b && b==c) cout<<"Equilateral\n";
    else if(a==b || b==c || c==a) cout<<"Isosceles\n";
    else cout<<"Scalene\n";
}

void solution(){
    checkTriangle();
}

void input(){
    cin>>a>>b>>c;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(0);

    input();
    while(!(a==0 && b==0 && c==0)){
        solution();
        input();
    }

}