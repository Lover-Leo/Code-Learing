#include<iostream>
#include<vector>
#include<unordered_map>
#include<queue>
#include<set>
#include<algorithm>
using namespace std;
//题目:给你一个整数数组 nums ，判断是否存在三元组 
//[nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k ，
//同时还满足 nums[i] + nums[j] + nums[k] == 0 。请你返回所有和为 0 且不重复的三元组。
//注意：答案中不可以包含重复的三元组。

//示例:
//输入：nums = [-1,0,1,2,-1,-4]
//输出：[[-1,-1,2],[-1,0,1]]
//解释：
//nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0 。
//nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0 。
//nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0 。
//不同的三元组是 [-1,0,1] 和 [-1,-1,2] 。
//注意，输出的顺序和三元组的顺序并不重要。

//My First Answer:
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int i,j,k;
        vector<vector<int>> anses;
        set<vector<int>> preanses;
        for(i = 0;i < nums.size();i++)
        {
            for(j = i + 1;j < nums.size();j++)
            {
                for(k = j + 1;k < nums.size();k++)
                {
                    if(nums[j] + nums[k] == -nums[i])
                    {
                        priority_queue<int,vector<int>,greater<int>> preans;
                        preans.push(nums[i]);
                        preans.push(nums[j]);
                        preans.push(nums[k]);
                        vector<int> ans;
                        ans.push_back(preans.top());
                        preans.pop();
                        ans.push_back(preans.top());
                        preans.pop();
                        ans.push_back(preans.top());
                        preans.pop();
                        preanses.insert(ans);
                    }
                }
            }
        }
        for(const auto& an: preanses)
        {
            anses.push_back(an);
        }
        return anses;
    }
};

//Solution:双指针
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());  // 先排序
        vector<vector<int>> res;
        int n = static_cast<int>(nums.size());

        for (int i = 0; i < n; i++) {
            // 跳过重复的第一个数
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }

            // 双指针，寻找 nums[l] + nums[r] == -nums[i]
            int l = i + 1;
            int r = n - 1;
            int target = -nums[i];

            while (l < r) {
                int sum = nums[l] + nums[r];

                if (sum == target) {
                    res.push_back({nums[i], nums[l], nums[r]});
                    l++;
                    r--;

                    // 跳过重复的第二个数
                    while (l < r && nums[l] == nums[l - 1]) {
                        l++;
                    }

                    // 跳过重复的第三个数
                    while (l < r && nums[r] == nums[r + 1]) {
                        r--;
                    }
                } else if (sum < target) {
                    l++;  // 和偏小，尝试更大的数
                } else {
                    r--;  // 和偏大，尝试更小的数
                }
            }
        }

        return res;
    }
};