// 给你字符串 s 和整数 k 。

// 请返回字符串 s 中长度为 k 的单个子字符串中可能包含的最大元音字母数。

// 英文中的 元音字母 为（a, e, i, o, u）。

#include <string>
using namespace std;
class Solution {
public:
    bool isVomel(char ch){
        return ch=='a' || ch=='e' ||ch=='i' ||ch=='o' ||ch=='u';
    } 
    int maxVowels(string s, int k) {
        int result=0;
        int l=0,r=0,vomel=0;
        while(r<s.size()){
            vomel+=isVomel(s[r]);
            if(r-l+1>=k){
                result=max(result,vomel);
                vomel-=isVomel(s[l++]);
            }
            r++;
        }
        return result;
    }
};