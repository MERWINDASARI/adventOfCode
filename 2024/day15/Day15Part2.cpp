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

void modify(vector<string>& g){
    int m=g.size(),n=g[0].size();
    for(int i=0;i<m;i++){
        string s="";
        for(int j=0;j<n;j++){
            if(g[i][j]=='#') s+="##";
            if(g[i][j]=='O') s+="[]";
            if(g[i][j]=='.') s+="..";
            if(g[i][j]=='@') s+="@.";
        }
        g[i]=s;
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

bool adjustHor(vector<int> pos,vector<string>& g,char& d){
    if(g[pos[0]][pos[1]]=='#') return false;
    if(g[pos[0]][pos[1]]=='.') return true;
    vector<int> oldPos=pos;
    pos[0]=pos[0]+dir[d][0];
    pos[1]=pos[1]+dir[d][1];
    if(adjustHor(pos,g,d)){
        g[pos[0]][pos[1]]=g[oldPos[0]][oldPos[1]];
        return true;
    }
    return false;
}

bool canAdjustVer(vector<int>& pos,vector<string>& g,char& d){
    if(g[pos[0]][pos[1]]=='#') return false;
    if(g[pos[0]][pos[1]]=='.') return true;
    
    vector<int> posCntPart=pos;
    if(g[pos[0]][pos[1]]=='[') posCntPart[1]++;
    else posCntPart[1]--;
    
  
    pos[0]=pos[0]+dir[d][0];
    pos[1]=pos[1]+dir[d][1];
    
    
    posCntPart[0]=posCntPart[0]+dir[d][0];
    posCntPart[1]=posCntPart[1]+dir[d][1];
    
    
    return canAdjustVer(pos,g,d) && canAdjustVer(posCntPart,g,d);
}

bool adjustVer(vector<int> pos,vector<string>& g,char& d){
    if(g[pos[0]][pos[1]]=='#') return false;
    if(g[pos[0]][pos[1]]=='.') return true;
    
    vector<int> posCntPart=pos;
    if(g[pos[0]][pos[1]]=='[') posCntPart[1]++;
    else posCntPart[1]--;
    
    vector<int> oldPos=pos;
    vector<int> oldPosCntPart=posCntPart;
    
  
    pos[0]=pos[0]+dir[d][0];
    pos[1]=pos[1]+dir[d][1];
    
    
    posCntPart[0]=posCntPart[0]+dir[d][0];
    posCntPart[1]=posCntPart[1]+dir[d][1];
    
    
    if(adjustVer(pos,g,d) && adjustVer(posCntPart,g,d) ){
        g[pos[0]][pos[1]]=g[oldPos[0]][oldPos[1]];
        g[oldPos[0]][oldPos[1]]='.';
        g[posCntPart[0]][posCntPart[1]]=g[oldPosCntPart[0]][oldPosCntPart[1]];
        g[oldPosCntPart[0]][oldPosCntPart[1]]='.';
        return true;
    }
    return false;
}

bool adjust(vector<int>& pos,vector<string>& g,char& d){
    
    if(d=='<' || d=='>') return adjustHor(pos,g,d);
    else{
        vector<int> temp=pos;
        if(canAdjustVer(temp,g,d)){
            return adjustVer(pos,g,d);
        }
    }
    return false;
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
            if(g[i][j]=='['){
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
    modify(g);
    m=g.size(),n=g[0].size();
    
    vector<int> intPos;
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