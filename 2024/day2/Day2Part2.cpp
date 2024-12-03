#include<iostream>
#include<vector>
#include<math.h>
#include<limits.h>
#include<unordered_set>
#include<unordered_map>
#include<algorithm>
#include<map>
#include <sstream>
/*
If there is no issue no change
if issue found correct it but only once -> need a cnt

for an issue think like <safe seq>issue<unknown>
issue=>for inc seq always choose i-1 because upto now it is safe we can not choose i because it will cause issue with i-2
so i==1 is special case 

*/

using namespace std;
typedef long long ll;
bool canBeIncreasing(vector < int > & nums) {
    int cnt = 0;
    int n=nums.size();
    for (int i = 1; i < n; i++) {
        int dif = nums[i] - nums[i - 1];
        if (dif > 3 || dif <= 0) {
            if (cnt == 1)
                return false;
                
            cnt++;
            if(i==n-1) continue;
            int next=(i<n)?nums[i+1]:INT_MAX;
            
            int dif2=next - nums[i - 1];
            if(i==1){
                int dif3=next-nums[i];
                if(dif3>0 && dif3<=3) continue;
            }
            if(dif2>0 && dif2<=3) nums[i]=nums[i-1];
            else return false;
        }
    }
    return true;
}

void solve() {
    string s;
    int res = 0;
    while (getline(cin, s)) {
        stringstream ss(s);
        string w;
        vector < int > nums;
        while (ss >> w) nums.push_back(stoi(w));
        int n = nums.size();
        vector < int > nums1 = nums;
        reverse(nums1.begin(), nums1.end());
        if (canBeIncreasing(nums) || canBeIncreasing(nums1)) res++;
    }
    cout << res;

}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    while (t != 0) {
        solve();
        t--;
    }
}