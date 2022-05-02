class Solution {
public:
    void swap(vector<int>& nums, int u, int v){
        int t = nums[u];
        nums[u] = nums[v];
        nums[v] = t;
    }
    void sortColors(vector<int>& nums) {
        int p = 0, q = nums.size()-1;
        for(int i=0; i<=q;){
            if (nums[i] == 0){
                swap(nums, i, p);
                p++;
                i++;
            }
            else if (nums[i] == 2){
                swap(nums, i, q);
                q--;
            }else{
                i++;
            }
        }
    }
};
