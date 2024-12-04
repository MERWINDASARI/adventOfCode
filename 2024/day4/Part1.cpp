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

void getInput(vector<string>& input){
    string s;
    while(getline(cin, s)){
        input.push_back(s);
    }
}
bool traverse(int si,int sj,vector<int>& d,vector<string>& input){
    string p="XMAS";
    int m=input.size(),n=input[0].size();
    for(int i=0;i<4;i++){
        vector<int> next={si+d[0]*i,sj+d[1]*i};
        if(next[0]>=0 && next[0]<m && next[1]>=0 && next[1]<n){
            if(input[next[0]][next[1]]!=p[i]) return false;
        }
        else return false;
    }
    return true;
}

int check(int si,int sj,vector<string>& input){
    vector<vector<int>> dir={{1,0},{0,1},{-1,0},{0,-1},{1,1},{-1,-1},{-1,1},{1,-1}};
    int res=0;
    for(auto d:dir){
        if(traverse(si,sj,d,input)) res++;
    }
    return res;
}

void solve(){
    vector<string> input;
    getInput(input);
    
    
    int m=input.size(),n=input[0].size();
    int res=0;
    
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(input[i][j]=='X'){
                res+=check(i,j,input);
            }
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