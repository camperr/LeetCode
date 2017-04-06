class Solution {
public:
    int strongPasswordChecker(string s) {
        int size = s.size();
        int res, res0, res1, res2;

        res1 = 0;
        int no_low = 1, no_up = 1, no_digit = 1;
        for(int i=0; i<size; i++){
            if(s[i] >= 'A' && s[i] <= 'Z') no_up = 0;
            if(s[i] >= 'a' && s[i] <= 'z') no_low = 0;
            if(s[i] >= '0' && s[i] <= '9') no_digit = 0;
        }
        res1 += no_low + no_up + no_digit;

        if(size < 6) {
            res0 = 6 - size;
            res = max(res0, res1);
            int i = 0;
            res2 = 0;
            while(i < size){
                if(i >= 2 && s[i] == s[i-1] && s[i] == s[i-2]){
                    res2++;
                    if(res2 <= res) i += 2;
                    else i += 3;
                }else{
                    i++;
                }
            }
            return max(res, res2);

        }else if(size <= 20) {
            res = res1;
            int i = 0;
            res2 = 0;
            while(i < size){
                if(i >= 2 && s[i] == s[i-1] && s[i] == s[i-2]){
                    res2++;
                    i += 3;
                }else{
                    i++;
                }
            }
        }else{
            res0 = size - 20;
            res = res0 + res1;
            int del_cnt = res0;
            string s2 = find3(s, del_cnt);
            int i = 0;
            res2 = 0;
            size = s2.size();
            while(i < size){
                if(i >= 2 && s2[i] == s2[i-1] && s2[i] == s2[i-2]){
                    res2++;
                    if(res2 <= del_cnt) i += 1;
                    else i += 3;
                }else{
                    i++;
                }
            }
            return max(res, res2 + res0 - del_cnt);
        } 

        return max(res0, max(res1, res2)); 
    }
private:
    int max(int a, int b){
        return a > b ? a : b;
    }
    string find3(string s, int &del_cnt){
        int res = 0;
        string s2 = "";
        for(int i=2, size=s.size(); i<size; i++){
            if(del_cnt > 0 && s[i] == s[i-1] && s[i] == s[i-2] && (i==2 || s[i]!=s[i-3])) {
                del_cnt --;
            }else{
                s2 += s[i];
            }
        }
        return s2;
    }
};

int main(){
    string s = "abcdef";
    Solution* sol = new Solution();
    cout<<sol->strongPasswordChecker(s)<<endl;
}