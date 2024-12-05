#include<iostream>
#include<vector>
#include<math.h>
#include<limits.h>
#include<unordered_set>
#include<unordered_map>
#include<algorithm>
#include<map>
#include <sstream>


using namespace std;
typedef long long ll;

string scanRules(vector<vector<int>>& rules){
    
    string s;
    string updates="";
    bool isRule=true;
    while (getline(cin, s)) {
        if(isRule){
            if(s==""){
                isRule=!isRule;
                continue;
            }
            stringstream ss(s);
            string w;
            vector<int> rule;
            while(getline(ss, w, '|')){
                rule.push_back(stoi(w));
            }
            rules.push_back(rule);
        }
        else updates+=s+" ";
    }
    return updates;
}

vector<int> parse(string& s){
    stringstream ss(s);
    string w;
    vector<int> temp;
    char del = ',';
    while(getline(ss, w, del)){
        int num=stoi(w);
        temp.push_back(num);
    }
    return temp;
}

bool isCorrectUpdate(vector<vector<int>>& rules,unordered_map<int,int>& m){
    for(auto r:rules){
        if(m.count(r[0]) && m.count(r[1]) && m[r[0]]>=m[r[1]]){
            return false;
        }
    }
    return true;
}

int getMiddle(string update,vector<vector<int>>& rules){
    unordered_map<int,int> m;
    vector<int> temp=parse(update);
    for(int i=0;i<temp.size();i++) m[temp[i]]=i;
    if(isCorrectUpdate(rules,m)){
        return temp[temp.size()/2];
    }
    return 0;
}

void solve(){
    vector<vector<int>> rules;
    string updates=scanRules(rules);
    stringstream ss(updates);
    string s;
    int sum=0;
    while(ss >> s){
        //cout<<s<<'\n';
        sum+=getMiddle(s,rules);
    }
    cout<<sum;
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