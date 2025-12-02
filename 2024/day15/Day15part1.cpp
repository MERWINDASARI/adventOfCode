#include<iostream>
#include<vector>
#include<math.h>
#include<limits.h>
#include<unordered_set>
#include<unordered_map>
#include<algorithm>
#include<map>


using namespace std;
typedef long long ll;

int m=0,n=0;

unordered_map<char,vector<int>> dir = {
    {'^',{-1,0}}, {'>',{0,1}}, {'v',{1,0}}, {'<',{0,-1}}
    };

void scanInput(vector<string>& g,string& moves){
    string s;
    while(getline(cin,s)){
        if(s[0]!='#') break;
        g.push_back(s);
    }
    while(getline(cin,s)){
        moves+=s;
    }
}

bool isBounded(vector<int>& pos){
    return pos[0]>=0 && pos[0]<m && pos[1]>=0 && pos[1]<n;
}

void update(vector<int>& a,vector<int>& b, vector<string>& g){
    g[a[0]][a[1]]='@';
    g[b[0]][b[1]]='.';
    b=a;
    return;
}

bool adjust(vector<int>& pos,vector<string>& g,char& d){
    //base case is genrally outofbound and seeing #
    if(g[pos[0]][pos[1]]=='#') return false;
    if(g[pos[0]][pos[1]]=='.') return true;
    if(g[pos[0]][pos[1]]=='O'){
        pos[0]=pos[0]+dir[d][0];
        pos[1]=pos[1]+dir[d][1];
        return adjust(pos,g,d);
    }
}

void move(vector<int>& pos,vector<string>& g,char& d){
    vector<int> newPos={pos[0]+dir[d][0],pos[1]+dir[d][1]};
    if(isBounded(newPos)){
        if(g[newPos[0]][newPos[1]]=='.'){
            update(newPos,pos,g);
            return;
        }else{
            vector<int> temp=newPos;
            if(adjust(temp,g,d)){
                g[temp[0]][temp[1]]='O';
                update(newPos,pos,g);
            }
        }
    }
}

void traverse(vector<int>& pos,vector<string>& g,string& moves){
    for(auto ch:moves){
        if(ch=='\n') continue;
        move(pos,g,ch);
    }
}

ll getGPSSum(vector<string> g){
    ll res=0;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(g[i][j]=='O'){
                res+=(100*i+j);
            }
        }
    }
    return res;
}

void solve(){
    vector<string> g;
    string moves;
    scanInput(g,moves);
    
    vector<int> intPos;
    m=g.size(),n=g[0].size();
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(g[i][j]=='@'){
                intPos.push_back(i);
                intPos.push_back(j);
            }
        }
    }
    
    traverse(intPos,g,moves);
    
    // for(int i=0;i<m;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<g[i][j];
    //     }
    //     cout<<'\n';
    // }
    
    cout<<getGPSSum(g);
    
}

int main(){
    
	ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int t=1;
    //cin>>t;
    while(t!=0){
        solve();
        t--;
    }
}