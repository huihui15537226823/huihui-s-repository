class Solution {
public:
    int maximumLengthSubstring(string s) {
        int ans = 0, left = 0, cnt[26]{};
        for(int i=0;i<s.length();i++){
            int b=s[i]-'a';
            cnt[b]++;

            while(cnt[b]>2){
                cnt[s[left]-'a']--;
                left++;
            }
            ans=max(ans,i-left+1);
        }
        return ans;
    }
};