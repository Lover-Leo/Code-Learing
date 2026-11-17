#include<iostream>
#include<vector>
#include<map>
using namespace std;

//My First Answer
//void

//枚举
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        const int n = nums.size();
        int count = 0;
        int arr[n];
        for (int i = 0; i < n; i++) {
            arr[i] = nums[i];
        }
        for (int start = 0; start < nums.size(); ++start) {
            int sum = 0;
            for (int end = start; end >= 0; --end) {
                sum += arr[end];
                if (sum == k) {
                    count++;
                }
            }
        }
        return count;
    }
};

//哈希表+前缀和
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        mp[0] = 1;
        int count = 0, pre = 0;
        for (auto& x:nums) {
            pre += x;
            if (mp.find(pre - k) != mp.end()) {
                count += mp[pre - k];
            }
            mp[pre]++;
        }
        return count;
    }
};