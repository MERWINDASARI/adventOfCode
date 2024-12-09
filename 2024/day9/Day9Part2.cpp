#include<iostream>
#include<vector>
#include<math.h>
#include<limits.h>
#include<unordered_set>
#include<unordered_map>
#include<algorithm>
#include<map>
#include<list>


using namespace std;
typedef long long ll;

vector<int> scanInput(){
    vector<int> res;
    string s;
    cin>>s;
    for(auto c:s) res.push_back(c-'0');
    return res;
}

vector<int> getBlocks(vector<int>& input,int& limit){
    vector<int> res;
    int sum=0;
    int i=0;
    while(sum+input[i]<=limit){
        res.push_back(input[i]);
        sum+=input[i];
        i++;
    }
    res.push_back(limit-sum);
    return res;
}

//lenidxlenidxlenidx...
vector<vector<int>> getAssignment(vector<int>&blks,vector<int> files){
    bool isFile=true;
    vector<vector<int>> res;
    int i=0,j=files.size()-1;
    for(auto b:blks){
        if(isFile){
            res.push_back({b,i});
            i++;
        }else{
            while(b>=files[j]){
                res.push_back({files[j],j});
                b-=files[j];
                j--;
            }
            if(b>0) res.push_back({b,j});
            files[j]-=b;
        }
        isFile=!isFile;
    }
    return res;
}

ll getAPSUM(int a,int n){
    return (2*a+n-1)*n/2;
}

ll getCheckSum(list<vector<int>>& assignment){
    int i=0;
    ll sum=0;
    for(auto a:assignment){
        if(a[1]) sum+=(a[2]*getAPSUM(i,a[0]));
        i+=a[0];
    }
    return sum;
}

void compaction(list<vector<int>>& blks,vector<int> files){
    int n=files.size();
    for(int i=n-1;i>=0;i--){
        list<vector<int>>::iterator itr=blks.begin();
        bool isfound=true;
        //untill end && (smaller than req or fileblk)
        while(itr!=blks.end() && ((*itr)[0]<files[i] || (*itr)[1])){

            //not cross current blk
            if((*itr)[2]==i){
                isfound=false;
                break;
            }
            itr++;
        }
        if(isfound){
            //found space to move
            if((*itr)[0]==files[i]){
                //same size no need of insert
                (*itr)[1]=1;
                (*itr)[2]=i;
            }else{
                //insert free space of size itr->[0]-files[i] after itr
                int r=(*itr)[0]-files[i];
                (*itr)[0]=files[i];
                (*itr)[1]=1;
                (*itr)[2]=i;
                
                itr++;
                blks.insert(itr, {r,0,-1});
                
            }
        }
    }
    cout<<'\n';
}

// Mark moved files as free block
void garbageCollect(list<vector<int>>& blks){
    unordered_set<int> h;
    list<vector<int>>::iterator itr=blks.begin();
    for(itr=blks.begin();itr!=blks.end();itr++){
        if(h.count((*itr)[2]) && (*itr)[1]){
            (*itr)[1]=0;
            (*itr)[2]=-1;
        }
        h.insert((*itr)[2]);
    }
}

void solve(){
    vector<int> input=scanInput();
    
    vector<int> files;
    bool isFile=true;
    int usedBlocks=0;
    //<blkSize,isFile,fileIdx>
    list<vector<int>> blks;
    for(auto b:input){
        if(isFile){
            blks.push_back({b,1,files.size()});
            files.push_back(b);
            usedBlocks+=b;
        }else{
            blks.push_back({b,0,-1});
        }
        isFile=!isFile;
    }
    compaction(blks,files);
    garbageCollect(blks);
    
    cout<<getCheckSum(blks);
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