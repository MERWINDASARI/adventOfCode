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

void scanInput(vector<string>& g){
    string s;
    while(getline(cin,s)){
        g.push_back(s);
    }
}

int getTurns(int cd,int nd){
    if(cd==nd) return 0;
    else if(cd&1==nd&1) return 2;
    return 1;
}

vector<vector<ll>> traverse(vector<string>& g,vector<ll>& s,vector<ll>& e){
    
    ll m=g.size(),n=g[0].size();
    vector<vector<ll>> dist(m,vector<ll>(n,LLONG_MAX));
    vector<vector<bool>> v(m,vector<bool>(n,false));
    
    dist[s[0]][s[1]]=0;
    
    
    priority_queue<vector<ll>> q;
    q.push({0,s[0],s[1],1});
    while(!q.empty()){
        vector<ll> cur=q.top();q.pop();
        if(v[cur[1]][cur[2]]) continue;
        v[cur[1]][cur[2]]=true;
        
        for(ll i=0;i<4;i++){
            vector<ll> newPos={cur[1]+dir[i][0],cur[2]+dir[i][1]};
            if(g[newPos[0]][newPos[1]]!='#'){
                ll w=1 + 1000*getTurns(cur[3],i);
                if(dist[newPos[0]][newPos[1]]==LLONG_MAX){
                    dist[newPos[0]][newPos[1]]=dist[cur[1]][cur[2]]+w;
                    q.push({-dist[newPos[0]][newPos[1]],newPos[0],newPos[1],i});
                }
                else if(dist[cur[1]][cur[2]]+w<dist[newPos[0]][newPos[1]]){
                    dist[newPos[0]][newPos[1]]=dist[cur[1]][cur[2]]+w;
                    q.push({-dist[newPos[0]][newPos[1]],newPos[0],newPos[1],i});
                }
            }
        }
        
    }
    
    return dist;
    
}

void solve(){
    vector<string> g;
    scanInput(g);
    
    ll m=g.size(),n=g[0].size();
    vector<ll> initPos,desPos;
    for(ll i=0;i<m;i++){
        for(ll j=0;j<n;j++){
            if(g[i][j]=='S'){
                initPos.push_back(i);
                initPos.push_back(j);
            }
            if(g[i][j]=='E'){
                desPos.push_back(i);
                desPos.push_back(j);
            }
        }
    }
   
    vector<vector<ll>> minDistStoE=traverse(g,initPos,desPos);
    
    // for(int i=0;i<m;i++){
    //     for(int j=0;j<n;j++){
    //         if(g[i][j]=='.'){
    //             cout<<minDistStoE[i][j]<<" ";
    //         }else cout<<g[i][j]<<" ";
    //     }
    //     cout<<'\n';
    // }
    cout<<minDistStoE[desPos[0]][desPos[1]];
    
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