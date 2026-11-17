#include<iostream>
#include<vector>
#include<set>
using namespace std;

//以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。

//My First Answer
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        set<int> number;

        for(const auto& nums: intervals)
        {
            for(int i = nums[0];i < nums)
        }
    }
};