#include<iostream>
#include<vector>
#include<string>
using namespace std;
//题目:给定一个字符串 s ，请你找出其中不含有重复字符的 最长 子串 的长度。
//示例:输入: s = "abcabcbb"
//输出: 3 
//解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。注意 "bca" 和 "cab" 也是正确答案。

//My First Answer:
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = static_cast<int>(s.size());
        int left = 0;
        int max_num = 0;

        for (int right = 0; right < n; right++) {
            for (int i = left; i < right; i++) {
                if (s[i] == s[right]) {
                    left = i + 1;  // 跳过旧的重复字符
                    break;
                }
            }

            // 此时窗口包含 left 和 right 两端
            max_num = std::max(max_num, right - left + 1);
        }

        return max_num;
    }
};

// a  b  c  a  b  a
//          r
//    l
// i