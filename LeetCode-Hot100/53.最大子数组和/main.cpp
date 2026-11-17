#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//My First Answer
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int pre = 0,ans = 0;
        int n = static_cast<int>(nums.size());

        for(const auto num: nums)
        {
            pre = max(pre + num,num);
            ans = max(ans,pre);
        }

        return ans;
    }
};