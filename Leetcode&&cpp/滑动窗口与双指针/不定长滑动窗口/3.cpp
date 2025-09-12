#include <string>
#include <unordered_set>
#include <algorithm>
#
using namespace std;
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n=s.size();
        int result=0;
        int left=0;

        unordered_set<char> window;

        for(int r=0;r<n;r++){
            char c=s[r];
            while(window.contains(c)){//window.find(c) != window.end()
                window.erase(s[left]);
                left++;
            }
            window.insert(c);
            result=max(result,r-left+1);
        }
        return result;
    }
};