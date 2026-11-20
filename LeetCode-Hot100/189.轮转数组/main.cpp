#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>
using namespace std;

//题目:给定一个整数数组 nums，将数组中的元素向右轮转 k 个位置，其中 k 是非负数

//My First Answer
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();

        for(int i = 0;i < k;i++)
        {
            int a = nums[n - 1];

            for(int i = n - 2;i >= 0;i--)
            {
                nums[i + 1] = nums[i];
            }

            nums[0] = a;
        }
    }
};

//解法一：额外数组
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> newArr(n);
        for (int i = 0; i < n; ++i) {
            newArr[(i + k) % n] = nums[i];
        }
        nums.assign(newArr.begin(), newArr.end());
    }
};

//解法2:环状替代
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = k % n;
        int count = gcd(k, n);
        for (int start = 0; start < count; ++start) {
            int current = start;
            int prev = nums[start];
            do {
                int next = (current + k) % n;
                swap(nums[next], prev);
                current = next;
            } while (start != current);
        }
    }
};