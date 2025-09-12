#include <string>
#include <algorithm>
using namespace std;
class Solution {
public:
    int minFlips(string s) {
        int n=s.size();
        int result=n;
        int cnt=0;

        for(int i=0;i<n*2-1;i++){
            if(s[i%n]%2 != i%2){
                cnt++;
            }
            int left=i-n+1;
            if(left<0){
                continue;
            }
            result=min({result,cnt,n-cnt});
            if(s[left]%2 != left%2){
                cnt--;
            }
        }
        return result;
    }
};