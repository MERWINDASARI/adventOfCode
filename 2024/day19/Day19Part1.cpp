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

struct TrieNode{
    //alphabet to next node map
    unordered_map<char,TrieNode*> children;
    //to mark the end of the word
    bool isEnd;
};

TrieNode* root= new TrieNode();

void parseTowels(vector<string>& t, string& s){
    string temp="";
    int i=0;
    while(i<s.size()){
        if(s[i]==','){
            t.push_back(temp);
            temp="";
            i+=1;
        }else temp+=s[i];
        i++;
    }
    t.push_back(temp);
}

void scanInput(vector<string>& t,vector<string>& d){
    string s="";
    getline(cin,s);
    parseTowels(t,s);
    getline(cin,s);
    while(getline(cin,s)) d.push_back(s);
}

void insert(string word) {
    TrieNode* curr=root;
    for(auto c:word){
        if(!curr->children.count(c)) curr->children[c]=new TrieNode();
        curr=curr->children[c];
    }
    curr->isEnd=true;
}

bool search(int i,string& word,TrieNode* cur) {
    if(!cur->children.count(word[i])) return false;
    if(i==word.size()-1) return cur->children[word[i]]->isEnd;
    
    if(cur->children[word[i]]->isEnd) 
        return search(i+1,word,cur->children[word[i]]) || search(i+1,word,root);
    return search(i+1,word,cur->children[word[i]]);
}

void solve(){
    
    vector<string> towels, designs;
    scanInput(towels,designs);
    for(auto towel:towels) insert(towel);
    
    int res=0;
    for(auto design:designs){
        if(search(0,design,root)){
            cout<<design<<'\n';
            res++;
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