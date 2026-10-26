#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;
//给定一个未排序的整数数组 nums ，找出数字连续的最长
//序列（不要求序列元素在原数组中连续）的长度。请你设计并实现
//时间复杂度为 O(n) 的算法解决此问题。

//示例：
//输入：nums = [100,4,200,1,3,2]
//输出：4
//解释：最长数字连续序列是 [1, 2, 3, 4]。它的长度为 4。

//My First Answer:
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        vector<int> lengths{};
        int i = 0,j = 0,num = 0;
        for(i = 0;i < nums.size();i++)
        {
            int length = 1;
            num = nums[i];
            for(j = 0;j < nums.size();j++)
            {
                if(nums[j] == num+1)
                {
                    length++;
                    num += 1;
                    j = -1;
                }
            }
            lengths.push_back(length);
        }
        int max = lengths[0];
        for(const auto& len: lengths)
        {
            if(len >= max)
            {
                max = len;
            }
        }
        return max;
    }
};

//Solution
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> num_set;
        for (const int& num : nums) {
            num_set.insert(num);
        }

        int longestStreak = 0;

        for (const int& num : num_set) {
            if (!num_set.count(num - 1)) {
                int currentNum = num;
                int currentStreak = 1;

                while (num_set.count(currentNum + 1)) {
                    currentNum += 1;
                    currentStreak += 1;
                }

                longestStreak = max(longestStreak, currentStreak);
            }
        }

        return longestStreak;           
    }
};