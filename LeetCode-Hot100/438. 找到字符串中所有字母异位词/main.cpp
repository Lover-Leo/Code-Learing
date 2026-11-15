#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;


//给定两个字符串 s 和 p，找到 s 中所有 p 的 异位词 的子串，返回这些子串的起始索引。
//不考虑答案输出的顺序。

//My Answer
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        string finding = p;
        sort(finding.begin(),finding.end());

        int left = 0;
        vector<int> ans;
        int n = static_cast<int>(s.size());
        int m = static_cast<int>(p.size());

        for (int left = 0; left <= n - m; ++left) 
        {
            string mp = s.substr(left, m);
            sort(mp.begin(), mp.end());

            if (mp == finding) {
                ans.push_back(left);
            }
        }

        return ans;
    }
};
