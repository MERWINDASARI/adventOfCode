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

int getDigit(int& i,string& s){
    int num=0;
    while(isdigit(s[i])){
        num=num*10;
        num+=s[i]-'0';
        i++;
    }
    return num;
}

void parseButton(string& s,vector<ll>& v){
    int i=12;
    v.push_back(getDigit(i,s));
    i+=4;
    v.push_back(getDigit(i,s));
}

void parsePrize(string& s,vector<ll>& v){
    int i=9;
    v.push_back(getDigit(i,s));
    i+=4;
    v.push_back(getDigit(i,s));
}

void scanInput(vector<ll>& a,vector<ll>& b,vector<ll>& c){
    string s;
    while(getline(cin,s)){
        if(s[0]=='B'){
            if(s[7]=='A') parseButton(s,a);
            else parseButton(s,b);
        }else if(s[0]=='P'){
            parsePrize(s,c);
        }
    }
}

ll getDet(ll& a,ll& b,ll& c,ll& d){
    return abs((a*d)-(b*c));
}

ll getmin(ll& a,ll& b,ll& c, ll& costa,ll& costb){
    ll res=LLONG_MAX;
    //m=100 for part 1
    int m=max(ceil((double)c/a),ceil((double)c/b));
    for(ll i=1;i<=m;i++){
        for(ll j=1;j<=m;j++){
            if(i*a+j*b==c) res=min(res,costa*i+costb*j);
        }
    }
    //NO integral solution
    if(res==INT_MAX) res=0;
    return res;
}

void solve(){
    ll costa=3, costb=1;
    vector<ll> a,b,c;
    scanInput(a,b,c);
    ll res=0;
    ll inc=10000000000000;//inc=0 for part 1
    for(ll i=0;i<a.size();i+=2){
        ll a1=a[i],b1=b[i],c1=c[i]+inc,a2=a[i+1],b2=b[i+1],c2=c[i+1]+inc;
        ll det=getDet(a1,b1,a2,b2);
        if(det!=0){
            ll detx=getDet(c1,b1,c2,b2);
            ll dety=getDet(a1,c1,a2,c2);
            if(detx%det==0&& dety%det==0){
                
                res+=costa*(detx/det);
                res+=costb*(dety/det);
            }
            
        }else{
            //parallel or coincident
            double m=(double)a1/a2;
            double n=(double)c1/c2;
            if(abs(m - n) < 1e-9){
                //many solutions
                res+=getmin(a1,b1,c1,costa,costb);
            }
        }
    }
    cout<< res;
    
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