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


/*
simulate the process
will need a map to reduce no of operations
for the result order of numbers does not matter 
*/

vector<ll> scanInput(){
    vector<ll> res;
    ll temp;
    while(cin>>temp) res.push_back(temp);
    return res;
}


unordered_map<ll,ll> change(unordered_map<ll,ll>& cur){
    unordered_map<ll,ll> temp;
    for(auto pair:cur){
            ll num=pair.first;
            if(num==0) temp[1]+=cur[0];
            else{
                string s=to_string(num);
                ll p=s.size();
                if(p%2) temp[num*2024]+=cur[num];
                else{
                    int newLen=p/2;
                    temp[stol(s.substr(0,newLen))]+=cur[num];
                    temp[stol(s.substr(newLen,newLen))]+=cur[num];
                }
                
            }
    }
    return temp;
}

void solve(){
    vector<ll> input=scanInput();
    ll m=75;
    unordered_map<ll,ll> map;
    for(auto num:input) map[num]++;
    unordered_map<ll,ll> cur=map;
    while(m){
        cur=change(cur);
        m--;
    }
    ll res=0;
    for(auto p:cur) res+=p.second;
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