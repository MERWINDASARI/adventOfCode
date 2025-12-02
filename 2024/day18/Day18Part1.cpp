#include<iostream>
#include<vector>
#include<math.h>
#include<limits.h>
#include<unordered_set>
#include<unordered_map>
#include<algorithm>
#include<map>
#include<queue>

using namespace std;
typedef long long ll;

vector<vector<ll>> dir = {
    {-1,0},{0,1},{1,0},{0,-1}
    };

int n=71,m=71;
int limit=1024;

ll getDigit(int& i,string& s){
    ll num=0;
    while(i<s.size() && isdigit(s[i])){
        num=num*10;
        num+=s[i]-'0';
        i++;
    }
    return num;
}

void scanInput(vector<vector<int>>& bytePos){
    string s;
    
    while(getline(cin,s)){
        int i=0;
        vector<int> pos;
        pos.push_back(getDigit(i,s));
        i++;
        pos.push_back(getDigit(i,s));
        bytePos.push_back(pos);
    }
}

bool canGo(vector<int>& pos,map<vector<int>,int>& indexMap){
    
    if(pos[0]<0 || pos[0]>=m || pos[1]<0 || pos[1]>=n) return false;
    if(indexMap.count({pos[1],pos[0]})){
        int fallenTime=indexMap[{pos[1],pos[0]}];
        if(fallenTime<limit) return false;
    }
    
    return true;
}

bool traverse(map<vector<int>,int>& indexMap, int& t){
    vector<vector<bool>> v(m,vector<bool>(n,false));
    queue<vector<int>> q;
    vector<int> end={n-1,m-1};
    q.push({0,0});
    v[0][0]=true;
    int levelCnt=1;
    while(!q.empty()){
        if(levelCnt==0){
            // cout<<"\n";cout<<"("<<t<<","<<q.size()<<")"<<"-";
            levelCnt=q.size();
            t++;
        }
        vector<int> cur=q.front();q.pop();
        if(cur==end) return true;
        
        // cout<<cur[0]<<cur[1]<<",";
        
        for(auto d:dir){
            vector<int> next={d[0]+cur[0],d[1]+cur[1]};
            if(canGo(next,indexMap) && !v[next[0]][next[1]]){
                q.push(next);
                v[next[0]][next[1]]=true;
            }
        }
        levelCnt--;
    }
    return false;
 }


void solve(){
    vector<vector<int>> bytePos;
    scanInput(bytePos);
    
    map<vector<int>,int> indexMap;
    
    for(int i=0;i<=bytePos.size();i++) indexMap[bytePos[i]]=i;
    int t=0;
    
    traverse(indexMap,t);
    cout<<t<<'\n';
    
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