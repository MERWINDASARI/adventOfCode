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
typedef vector<vector<int>> vvi;

int getDigit(int& i,string& s){
    bool isNeg=false;
    if(s[i]=='-'){
        isNeg=true;
        i++;
    }
    int num=0;
    while(isdigit(s[i])){
        num=num*10;
        num+=s[i]-'0';
        i++;
    }
    if(isNeg) num=-num;
    return num;
}
//p=6,3 v=-1,-3
vector<int> parse(string& s){
    vector<int> res;
    int i=0;
    i+=2;
    res.push_back(getDigit(i,s));
    i++;
    res.push_back(getDigit(i,s));
    i+=3;
    res.push_back(getDigit(i,s));
    i++;
    res.push_back(getDigit(i,s));
    
    return res;
}

void scanInput(vvi& p,vvi& v){
    string s;
    while(getline(cin,s)){
       vector<int> temp = parse(s);
       p.push_back({temp[0],temp[1]});
       v.push_back({temp[2],temp[3]});
    }
}

int boundIt(ll i,int n){
    i=i%n;
    if(i<0) i=n+i;
    return i;
}

vector<int> countQuad(vvi& g){
    int m=g.size(),n=g[0].size();
    vector<int> q(5,0);
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(i<m/2&&j<n/2) q[0]+=g[i][j];
            if(i<m/2&&j>n/2) q[1]+=g[i][j];
            if(i>m/2&&j<n/2) q[2]+=g[i][j];
            if(i>m/2&&j>n/2) q[3]+=g[i][j];
            if(i==m/2 || j==n/2) q[4]+=g[i][j];
        }
    }
    return q;
}

void getState(vvi& p,vvi& v,vvi& g,long long t){
    int nr=p.size();
    int m=103,n=101;
    int res=0;
    for(int i=0;i<nr;i++){
        vector<ll> newPos={p[i][0]+t*v[i][0],p[i][1]+t*v[i][1]};
        newPos[0]=boundIt(newPos[0],n);
        newPos[1]=boundIt(newPos[1],m);
        g[newPos[1]][newPos[0]]++;
    }
}

void printGrid(vvi& g){
    int m=g.size(),n=g[0].size();
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(g[i][j]) cout<<"#";
            else cout<<".";
        }
        cout<<'\n';
    }
}
//Found horizontal strip at 51,and vertical at 86 =>using Chinese Remainder Theorem
//t ≡ 51 (mod 103)
//t ≡ 86 (mod 101)
void solve(int t){
    vvi p,v;
    scanInput(p,v);

    for(int i=t;i<t+100;i++){
        int m=103,n=101;
        vvi g(m,vector<int>(n,0));
        getState(p,v,g,i);
        vector<int> q=countQuad(g);
        //cout<<q[0]*q[1]*q[2]*q[3]<<'\n';
        cout<<i<<'\n';
        if(check(g)) printGrid(g);
        cout<<"\n";
    }
   
    
}

int main(int argc, char* argv[]){
    
	ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int t=1;
    //cin>>t;
    while(t!=0){
        if(argc>1) solve(atoi(argv[1]));
        else solve(100);
        t--;
    }
}