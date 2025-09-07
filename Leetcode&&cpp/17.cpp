#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    const string digital_map[10]={
            "",
            "",
            "abc",
            "def", 
            "ghi", 
            "jkl", 
            "mno", 
            "pqrs", 
            "tuv", 
            "wxyz", 
        };
    vector<string> result;
    string str;
    vector<string> letterCombinations(string digits) {
        if(digits.empty()){
            return result;
        }
        nothing(digits,0);
        return result;
    }
    void nothing(string digits,int i){
        if(i==digits.size()){
            result.push_back(str);
            return;
        }

        int digital_num=digits[i]-'0';
        string letters = digital_map[digital_num];
        for(int j=0;j<letters.size();j++){
            str.push_back(letters[j]);
            nothing(digits,i+1);
            str.pop_back();
        }
    }
};