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

string getCorners(int si,int sj,vector<string>& input){
    vector<vector<int>> dir={{-1,-1},{-1,1},{1,-1},{1,1}};
    string s="";
    int m=input.size(),n=input[0].size();
    for(auto d:dir){
        vector<int> next={si+d[0],sj+d[1]};
        if(next[0]>=0 && next[0]<m && next[1]>=0 && next[1]<n){
            s+=input[next[0]][next[1]];
        }else break;
    }
    return s;
}

void solve(){
    vector<string> input;
    getInput(input);
    
    
    int m=input.size(),n=input[0].size();
    int res=0;
    
    unordered_set<string> h = {"MMSS","MSMS","SSMM","SMSM"};
    
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(input[i][j]=='A'){
                string s=getCorners(i,j,input);
                //cout<<s<<'\n';
                if(h.count(s)) res++;
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