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

ll getDigit(int& i,string& s){
    ll num=0;
    while(i<s.size() && isdigit(s[i])){
        num=num*10;
        num+=s[i]-'0';
        i++;
    }
    return num;
}

//Register B: 0
void parseRegister(string& s,vector<ll>& v){
    int i=12;
    v.push_back(getDigit(i,s));
}

//Program: 0,1,5,4,3,0
void parseInsts(string& s,vector<int>& v){
    int i=9;
    while(i<s.size()){
        v.push_back(getDigit(i,s));
        i++;
    }
    
}

void scanInput(vector<ll>& regs,vector<int>& insts){
    string s;
    while(getline(cin,s)){
        if(s[0]=='R'){
            parseRegister(s,regs);
        }
        if(s[0]=='P'){
            parseInsts(s,insts);
        }
    }
}

int comboVal(int operand,vector<ll>& regs){
    if(operand>=0 && operand<=3) return operand;
    if(operand>=4 && operand<=6) return regs[operand-4];
    cout<<"Invalid operand"<<'\n';
    return operand;
}

ll getMod(ll val,ll m){
    ll res=val%m;
    if(res<0) res=m-res;
    return  res;
}

void execute(vector<ll>& regs,vector<int>& insts, int& ip, string& output){
    int opcode=insts[ip];
    int operand=insts[ip+1];
    
    // cout<<opcode<<" "<<operand<<": ";
    // for(auto r:regs) cout<<r<<" ";
    // cout<<'\n';
    
    switch(opcode){
        case 0:{
            int d=(1<<comboVal(operand,regs));
            regs[0]=regs[0]/d;
            ip+=2;
            break;
        }
        case 1:{
            regs[1]=regs[1]^operand;
            ip+=2;
            break;
        }
        case 2:{
            regs[1]=getMod(comboVal(operand,regs),8);
            ip+=2;
            break;
        }
        case 3:{
            if(regs[0]) ip=operand;
            else ip+=2;
            break;
        }
        case 4:{
            regs[1]=regs[1]^regs[2];
            ip+=2;
            break;
        }
        case 5:{
            
            output+=to_string(getMod(comboVal(operand,regs),8));
            ip+=2;
            break;
        }
        case 6:{
            int d=(1<<comboVal(operand,regs));
            regs[1]=regs[0]/d;
            ip+=2;
            break;
        }
        case 7:{
            int d=(1<<comboVal(operand,regs));
            regs[2]=regs[0]/d;
            ip+=2;
            break;
        }
        default:{
            cout<<"Invalid opcode"<<'\n';
        }
    }
}

string start(vector<ll>& regs,vector<int>& insts){
    int ip=0;
    string output="";
    while(ip<insts.size()-1){
        execute(regs,insts,ip,output);
    }
    return output;
}

void solve(){
    vector<ll> regs;
    vector<int> insts;
    scanInput(regs,insts);
    //regs[0]=202972175280682; part 2
    string res=start(regs,insts);
    cout<<"Part 1: ";
    for(auto num:res) cout<<num<<",";
    
    
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