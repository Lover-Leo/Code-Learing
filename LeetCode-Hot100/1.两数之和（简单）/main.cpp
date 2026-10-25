#include<iostream>
#include<vector>
#include<map>
using namespace std;

//题目:给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值
// target 的那 两个 整数，并返回它们的数组下标。
//你可以假设每种输入只会对应一个答案，并且你不能使用两次相同的元素。
//你可以按任意顺序返回答案。
//示例:
//输入：nums = [2,7,11,15], target = 9
//输出：[0,1]
//解释：因为 nums[0] + nums[1] == 9 ，返回 [0, 1] 。

//My  First Answer
class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        int i = 0,j = 0;
        for(i = 0;i < nums.size();i++)
        {
            for(j = i+1;j < nums.size();j++)
            {
                if(nums.at(i) + nums.at(j) == target)
                {         std::vector<int> answer{i,j};
                    return answer;
                }
            }
        }
        return std::vector<int> {};
    };           
};

//Solution:哈希表
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hashtable;
        for (int i = 0; i < nums.size(); ++i) {
            auto it = hashtable.find(target - nums[i]);
            if (it != hashtable.end()) {
                return {it->second, i};
            }
            hashtable[nums[i]] = i;
        }
        return {};
    }
};