#include <string>
using namespace std;
class Solution {
public:
    int numberOfSubstrings(string s, int k) {
        int result=0,l=0,cnt[26]{};
        for(char c:s){
            cnt[c-'a']++;
            while(cnt[c-'a']>=k){
                cnt[s[l]-'a']--;
                l++;
            }
            result+=l;//0到最终的l-1都符合,现在加l刚刚好
        }
        return result;
    }
};