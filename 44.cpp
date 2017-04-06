#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
class Solution {
public:
    bool isMatch(string s, string p) {
        string p2 = "";
        int i=0, j=0;
        int s_size = s.size();
        int p_size = p.size();
        while(i < p_size){
            while(i > 0 && i < p_size && p[i] == '*' && p[i-1] == '*') i++;
            if(i < p_size) p2 += p[i++];
        }
        p_size = p2.size();

        int length = (s_size + 1) * (p_size + 1);
        bool* arr = new bool[length];
        bool* arr2 = new bool[length];
        bool** t = new bool*[p_size + 1];
        bool** d = new bool*[p_size + 1];
        for(i=0; i<= p_size; i++){
            t[i] = arr + (s_size + 1) * i;
            d[i] = arr2 + (s_size + 1) * i;

            if((i == 0) || (i == 1 && p2[0] == '*')){
                d[i][0] = true;
            }else{
                d[i][0] = false;
            }

            t[i][0] = d[i][0];
        }

        for(j=1; j<=s_size; j++){
            d[0][j] = false;
            t[0][j] = true;
        } 

        for(i=1; i<=p_size; i++){
            for(j=1; j<=s_size; j++){
                if (p2[i-1] == '*'){
                    d[i][j] = t[i-1][j];
                }else if(p2[i-1] == '?'){
                    d[i][j] = d[i-1][j-1];
                }else{
                    d[i][j] = d[i-1][j-1] & (p2[i-1] == s[j-1]);
                }

                t[i][j] = t[i][j-1] | d[i][j];
            }

        }

        bool ans = d[p_size][s_size];
        delete[] arr;
        delete[] arr2;
        delete[] t;
        delete[] d;
        return ans;
    }
};

int main(){
    string s = "ab";
    string p = "c*";
    Solution* sol = new Solution();
    cout<<sol->isMatch(s, p)<<endl;
    delete sol;
}