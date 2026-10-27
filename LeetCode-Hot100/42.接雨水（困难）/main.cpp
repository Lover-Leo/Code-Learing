#include<iostream>
#include<vector>
using namespace std;
//题目:给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
//示例:
//输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
//输出：6
//解释：上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，
//在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。 

//My First Answer:
class Solution {
public:
    int trap(vector<int>& height) {
        int area = 0;
        int i = 0;
        int end = static_cast<int>(height.size()) - 1;
        while(i < end)
        {
            int r = i + 1;
            int pre = height[i];
            while(pre > height[r] && r <= end)
            {
                r++;
            }
            if(r > end)
            {
                i++;
                continue;
            }
            while(i < r)
            {
                area += (pre - height[i]);
                i++;
            }
        }
        return area;
    }
};
//错误点：会漏右墙低于左墙但仍然可以接水的情况

//Solution 1:动态规划
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if (n == 0) {
            return 0;
        }
        vector<int> leftMax(n);
        leftMax[0] = height[0];
        for (int i = 1; i < n; ++i) {
            leftMax[i] = max(leftMax[i - 1], height[i]);
        }

        vector<int> rightMax(n);
        rightMax[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            rightMax[i] = max(rightMax[i + 1], height[i]);
        }

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans += min(leftMax[i], rightMax[i]) - height[i];
        }
        return ans;
    }
};

//Solution 2:单调栈
class Solution {
public:
    int trap(vector<int>& height) {
        int ans = 0;
        stack<int> stk;
        int n = height.size();
        for (int i = 0; i < n; ++i) {
            while (!stk.empty() && height[i] > height[stk.top()]) {
                int top = stk.top();
                stk.pop();
                if (stk.empty()) {
                    break;
                }
                int left = stk.top();
                int currWidth = i - left - 1;
                int currHeight = min(height[left], height[i]) - height[top];
                ans += currWidth * currHeight;
            }
            stk.push(i);
        }
        return ans;
    }
};