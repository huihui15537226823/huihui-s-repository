#include <string>
using namespace std;
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int is=0;
        if(s.size()==0&&t.size()==0){
                return true;
            }
        for(int it=0;it<t.size();it++){
            if(is<s.size() && s[is]==t[it]){
                is++;
            }
            if(is==s.size()){
                return true;
            }
        }
        return false;
    }
};