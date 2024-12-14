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

vector<string> scanInput(){
    vector<string> input;
    string s;
    while(getline(cin,s)){
        input.push_back(s);
    }
    return input;
}

void dfs(int i,int j,vector<string>& g,vector<vector<bool>>& v,int& a,int& p, char& type){
    int m=g.size(), n=g[0].size();
    if(i<0 || i>=m || j<0 || j>=n || g[i][j]!=type){
        //cout<<i<<" "<<j<<'\n';
        p++;
        return;
    }
    if(v[i][j]) return;
    v[i][j]=true;
    a++;
    for(auto d:dir){
        int ni=i+d[0];
        int nj=j+d[1];
        dfs(ni,nj,g,v,a,p,type);
    }
}

void solve(){
    vector<string> grid=scanInput();
    int m=grid.size(), n=grid[0].size();
    vector<vector<bool>> v(m,vector<bool>(n,false));
    
    int a=0,p=0;
    ll res=0;
    
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(!v[i][j]){
                char type=grid[i][j];
                cout<<type<<'\n';
                dfs(i,j,grid,v,a,p,type);
                res+=a*p;
                a=0;p=0;
            }
            cout<<'\n';
        }
    }
    cout<<res;
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