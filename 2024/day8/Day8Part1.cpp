#include<iostream>
#include<vector>
#include<math.h>
#include<limits.h>
#include<unordered_set>
#include<unordered_map>
#include<algorithm>
#include<map>
#include<set>


using namespace std;
typedef long long ll;

/*
Anti node and can only created by same type of antenna so need a map to maintain them 
for every two nodes 2 will anti nodes get created 

.....a...b...x.....

.....x...a...b.....

anti node is external division of two points in 2:1 ration to get other point swap a point and b point

*/

void scanInput(vector<string>& g){
    string s;
    while(getline(cin,s)){
        g.push_back(s);
    }
}

void getMap(vector<string>& g, unordered_map<char,vector<vector<int>>>& map){
    int m=g.size(),n=g[0].size();
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(g[i][j]!='.') map[g[i][j]].push_back({i,j});
        }
    }
}

vector<int> getAntiNode(vector<int> a,vector<int> b){
    //external division of line segment in 2:1 ratio
    return {2*a[0]-b[0],2*a[1]-b[1]};
}

void findAntiNodes(vector<vector<int>> p,int& m,int& n,set<vector<int>>& s){
    int k=p.size();
    for(int i=0;i<k;i++){
        for(int j=i+1;j<k;j++){
            
            vector<int> temp= getAntiNode(p[i],p[j]);
            if(temp[0]>=0 && temp[0]<m && temp[1]>=0 && temp[1]<n) 
                s.insert(temp);
                
            temp= getAntiNode(p[j],p[i]);
            if(temp[0]>=0 && temp[0]<m && temp[1]>=0 && temp[1]<n) 
                s.insert(temp);
        }
    }
}

void solve(){
    vector<string> grid;
    scanInput(grid);
    int m=grid.size(),n=grid[0].size();
    unordered_map<char,vector<vector<int>>> map;
    getMap(grid,map);
    set<vector<int>> antiNodes;
    for(auto f:map){
        findAntiNodes(f.second,m,n,antiNodes);
    }
    cout<<antiNodes.size();
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