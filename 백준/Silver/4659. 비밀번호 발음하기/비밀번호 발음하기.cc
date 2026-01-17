#include <bits/stdc++.h>

using namespace std;

string word;

char moeum[5] = {'a', 'e', 'i','o', 'u'};

void print(string word, bool ok){
    if(!ok) cout<<"<"<<word<<"> is not acceptable.\n";
    else cout<<"<"<<word<<"> is acceptable.\n";
}



void solution(string word){
    int totalM=0;
    int streakM=0; int streakJ=0;
    char prev=' ';
    for(auto character : word){
        
        //이전거랑 비교
        if(character!='e' && character!='o' && character == prev){
            print(word, false);
            return;
        }
        

        bool isMoeum = false;
        for(int c = 0;c<=4;c++){
            if(moeum[c]==character){
                isMoeum = true;
                break;
            }
        }

        if(isMoeum){
            //지금 철자가 모음이란 소리
            streakM++;
            streakJ=0;
            totalM++;
        }
        else{
            streakM=0;
            streakJ++;
        }

        if(streakM==3 || streakJ==3){
            print(word, false);
            return;
        }

        prev = character;
    }

    if(totalM>0) print(word, true);
    else print(word, false);
}

void input(){
    cin>>word;
    while(!(word == "end")){
        solution(word);

        cin>>word;
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
}