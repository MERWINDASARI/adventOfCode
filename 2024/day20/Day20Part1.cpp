#include<bits/stdc++.h>


using namespace std;
typedef long long ll;
int m,n;
vector<vector<int>> dir={{-1,0},{0,1},{1,0},{0,-1}};

void scanInput(vector<string>& g){
    string s;
    while(getline(cin,s)) g.push_back(s);
}

bool isValid(vector<int>& pos){
    return pos[0]>=0 && pos[0]<m && pos[1]>=0 && pos[0]<n;
}

vector<vector<int>> bfs(vector<int>& s, vector<string>& grid){
    vector<vector<int>> dis(m,vector<int>(n,INT_MAX));
    queue<vector<int>> q;
    q.push(s);
    dis[s[0]][s[1]]=0;
    while(!q.empty()){
        vector<int> cur=q.front();q.pop();
        if(grid[cur[0]][cur[1]]=='#') continue;
        for(auto d:dir){
            vector<int> next={cur[0]+d[0],cur[1]+d[1]};
            if(isValid(next) && dis[next[0]][next[1]]==INT_MAX){
                dis[next[0]][next[1]]=dis[cur[0]][cur[1]]+1;
                q.push(next);
            }
        }
    }
    return dis;
}

void solve(){
    vector<string> grid;
    scanInput(grid);
    m=grid.size();
    n=grid[0].size();
    vector<int> s,e;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(grid[i][j]=='S'){
                grid[i][j]='.';
                s={i,j};
            }
            if(grid[i][j]=='E'){
                grid[i][j]='.';
                e={i,j};
            }
        }
    }
    
    vector<vector<int>> stoe=bfs(s,grid),etos=bfs(e,grid);
    int minimal=stoe[e[0]][e[1]];
    cout<<minimal<<'\n';
    
    int res=0;
    
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(grid[i][j]=='#'){
                for(auto d:dir){
                    vector<int> nib={i+d[0],j+d[1]};
                    if(isValid(nib) && grid[nib[0]][nib[1]]=='.'){
                        int temp=stoe[i][j]+etos[nib[0]][nib[1]]+1;
                        if(temp<=minimal-100) res++;
                    }
                }
            }
        }
    }
    cout<<res<<'\n';
    
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