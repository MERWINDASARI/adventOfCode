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

void parseInput(string& s,vector<int>& nums,ll& val){
    int i=0;
    while(isdigit(s[i])){
        val*=10;
        val+=s[i]-'0';
        i++;
    }
    i=i+2;
    int n=s.size();
        
    while(i<n){
        int temp=0;
        while(isdigit(s[i])){
            temp*=10;
            temp+=s[i]-'0';
            i++;
        }
        i++;
        nums.push_back(temp);
    }
    
}

bool isPossible(vector<int>& nums,ll& t,int i,ll sum){
    if(i==nums.size()) return sum==t;
    return isPossible(nums,t,i+1,sum+nums[i]) || isPossible(nums,t,i+1,sum*nums[i]);
}

void solve(){
    ll res=0;
    string s;
    while(getline(cin,s)){
        ll val=0;
        vector<int> nums;
        parseInput(s,nums,val);
        if(isPossible(nums,val,1,nums[0])) res+=val;
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