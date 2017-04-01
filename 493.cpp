#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;
struct Node{
    long long v;
    bool single;
};

class Solution {
public:
    int reversePairs(vector<int>& nums) {
        int size = nums.size();
        init(nums, size);
        int res = countPairs(sortList, size*2);
        for(int i=0; i<size; i++){
            if(nums[i] < 0) res--;
        }
        destroy();
        return res;
    }
private:
    void init(vector<int>& nums, int size){
        sortList = new Node[size*2];
        for(int i=0; i<size; i++){
            sortList[i*2] = (Node){nums[i], true};
            sortList[i*2+1] = (Node){nums[i]*2, false};
        }
        tmp = new Node[size*2];
    }
    void destroy(){
        delete sortList;
        delete tmp;
    }
    int countPairs(Node* nums, int size){
        if(size <= 1) return 0;

        int lcnt = countPairs(nums, size/2);
        int rcnt = countPairs(nums + size/2, size - size/2);
        int cross_cnt = merge(nums, size/2, size);
        copy_to(nums, size);

        return lcnt + rcnt + cross_cnt;
    }
    int merge(Node* nums, int lend, int rend){
        int i, j, k, dcnt, pcnt;
        k = dcnt = pcnt = 0;
        i = 0;
        j = lend;

        while(i<lend || j<rend){
            if(j>=rend || (i<lend && nums[i].v <= nums[j].v)){
                tmp[k++] = nums[i];
                if(nums[i].single) pcnt += dcnt;
                i++;
            }else{
                tmp[k++] = nums[j];
                if(!nums[j].single) dcnt += 1;
                j++;
            }
        }
        return pcnt;
    }
    void copy_to(Node* nums, int size){
        for(int i=0; i<size; i++){
            nums[i] = tmp[i];
        }
    }
    Node* sortList;
    Node* tmp;
};

int main(){
    int arr[10] = {100,49,24,11,5,2,0};
    vector<int> nums;
    for(int i=0;i<7;i++) nums.push_back(arr[i]);
    Solution* sol = new Solution();
    cout<<sol->reversePairs(nums)<<endl;
}