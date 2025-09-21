#include <vector>
#include <unordered_map>
using namespace std;
class Solution {
public:
    int beautifulBouquet(vector<int>& flowers, int cnt) {
        long long result=0;
        unordered_map<int,int> c;
        int l=0;
        for(int r=0;r<flowers.size();r++){
            int x=flowers[r];
            c[x]++;
            while(c[x]>cnt){
                c[flowers[l]]--;
                l++;
            }
            result+=r-l+1;
        }
        return result%1000000007;
    }
};