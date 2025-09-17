#include <string>
using namespace std;
class Solution {
public:
    int longestSemiRepetitiveSubstring(string s) {
        int result=1,same=0,left=0;
        for(int right=1;right<s.length();right++){
            if(s[right]==s[right-1]){
                same++;
            }
            if(same>1){
                left++;
                while(s[left]!=s[left-1]){
                    left++;
                }
                same=1;
            }
            result=max(result,right-left+1);
        }
        return result;
    }
};