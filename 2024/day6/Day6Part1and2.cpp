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
vector<vector<ll>> dir={{-1,0},{0,1},{1,0},{0,-1}};

vector<ll> getInput(vector<vector<bool>>& grid, ll& d){
    string s;
    vector<ll> pos={0,0};
    ll i=0;
    while(getline(cin,s)){
        vector<bool> temp;
        ll j=0;
        for(auto ch:s){
            if(ch=='.') temp.push_back(false);
            else if(ch=='#') temp.push_back(true);
            else {
                if(ch=='^') d=0;
                if(ch=='>') d=1;
                if(ch=='v') d=2;
                if(ch=='<') d=3;
                temp.push_back(false);
                pos={i,j};
            }
            j++;
        }
        grid.push_back(temp);
        i++;
    }
    return pos;
}

bool canMove(vector<ll>&nextPos,unordered_set<ll>& v,vector<vector<bool>>& grid, ll& d){
    
    ll m=grid.size(),n=grid[0].size();
    if(nextPos[0]<0 || nextPos[0]>=m || nextPos[1]<0 || nextPos[1]>=n ){
        //out of bound
        return false;
    }
    if(grid[nextPos[0]][nextPos[1]]){
        //block rotate
        nextPos[0]=nextPos[0]-dir[d][0];
        nextPos[1]=nextPos[1]-dir[d][1];
        d=(d+1)%4;
        return true;
    }
    if(v.count(nextPos[0]*n+nextPos[1]+m*n*d)){
        //seen with same dir cycle
        return false;
    }
    return true;

}


unordered_set<ll> traverse(vector<ll>& pos,vector<vector<bool>>& grid, ll d){
    ll m=grid.size(),n=grid[0].size();
    unordered_set<ll> v,upos;
    upos.insert(pos[0]*n+pos[1]);
    v.insert(pos[0]*n+pos[1]+m*n*d);
    while(1){
        pos[0]=pos[0]+dir[d][0];
        pos[1]=pos[1]+dir[d][1];
        if(!canMove(pos,v,grid,d)) break;
        
        v.insert(pos[0]*n+pos[1]+m*n*d);
        upos.insert(pos[0]*n+pos[1]);
    }
    
    return upos;
}

void solve(){
    vector<vector<bool>> grid;
    ll id=0;
    vector<ll> initPos=getInput(grid,id);
    ll m=grid.size(),n=grid[0].size();
    ll res=0;
    vector<ll> dinitPos=initPos;
    unordered_set<ll> gp=traverse(dinitPos,grid,id);
    cout<<gp.size()<<" "<<m*n<<'\n';
    
    //just put the blocks only in path
    for(auto p:gp){
        
        ll i=p/n,j=p%n;
        vector<ll> pos=initPos;
        ll d=id;
        if(i==pos[0]&&j==pos[1]) continue;
        grid[i][j]=true;
        unordered_set<ll> temp=traverse(pos,grid,d);
        if(pos[0]>=0 && pos[0]<m && pos[1]>=0 && pos[1]<n) res++;
        grid[i][j]=false;
    }
    
    cout<<res;
    
    
}

int main(){
    
	ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    ll t=1;
    //cin>>t;
    while(t!=0){
        solve();
        t--;
    }
}