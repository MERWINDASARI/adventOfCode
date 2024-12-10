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

vector<vector<int>> dir={{-1,0},{0,1},{1,0},{0,-1}};

vector<vector<int>> scanInput(){
    string s;
    vector<vector<int>> input;
    while(getline(cin,s)){
        vector<int> temp;
        for(auto ch:s) temp.push_back(ch-'0');
        input.push_back(temp);
    }
    return input;
}

void dfs(int& si,int& sj, unordered_set<int>& s,int& trailCount,vector<vector<int>>& g){
    int m=g.size(),n=g[0].size();
    if(g[si][sj]==9){
        trailCount++;
        s.insert(si*n+sj);
        return;
    }
    for(auto d:dir){
        vector<int> nexPos={si+d[0],sj+d[1]};
        if(nexPos[0]>=0 && nexPos[0]<m && nexPos[0]>=0 && nexPos[0]<n && g[si][sj]+1==g[nexPos[0]][nexPos[1]]){
            dfs(nexPos[0],nexPos[1],s,trailCount,g);
        }
    }
    
}

void solve(){
    vector<vector<int>> g=scanInput();
    int m=g.size(),n=g[0].size();
    int res1=0,res2=0;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(g[i][j]==0){
                unordered_set<int> s;
                int trailCount=0;
                dfs(i,j,s,trailCount,g);
                res1+=s.size();
                res2+=trailCount;
            }
        }
    }
    cout<<res1<<" "<<res2;
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