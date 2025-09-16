#include <string>
#include <algorithm>
using namespace std;
class Solution {
public:
    int maxConsecutiveAnswers(string answerKey, int k) {
        int result=0,left=0,cnt[2]{};
        for(int right=0;right<answerKey.length();right++){
            cnt[answerKey[right]>>1&1]++;
            while(cnt[0]>k&&cnt[1]>k){
                cnt[answerKey[left]>>1&1]--;
                left++;
            }
            result=max(result,right-left+1);
        }
        return result;
    }

};