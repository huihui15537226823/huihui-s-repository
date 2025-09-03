#include <unordered_map>
#include <string>
using namespace std;
class Solution {
public:
    unordered_map<char,int> cTov={
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000},
    };

    int romanToInt(string s) {
        int result=0;
        for(int i=0;i<s.length();++i){
            int value=cTov[s[i]];
            if(i<s.length()-1 && value<cTov[s[i+1]]){
                result-=value;
            }else{
                result+=value;
            }
        }
        return result;
    }
};