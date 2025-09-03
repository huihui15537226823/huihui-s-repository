#include <string>
#include <vector>
using namespace std;
class Solution {
    public:
        string common(const string& str1,const string& str2){
            int length=min(str1.size(),str2.size());
            int i=0;
            while(i<length&& str1[i]==str2[i]){
                ++i;
            }
            return str1.substr(0,i);
        }
        string longestCommonPrefix(vector<string>& strs) {
            if(!strs.size()){
                return "";
            }
            string a=strs[0];
            int count=strs.size();
    
            for(int I=1;I<count;++I){
                a=common(a,strs[I]);
                if(!a.size()){
                    break;
                }
            }
            return a;
        }
    };