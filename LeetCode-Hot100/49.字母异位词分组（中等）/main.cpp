#include<iostream>
#include<map>
#include<vector>
#include<numeric>
using namespace std;

//题目:给你一个字符串数组，
//请你将 字母异位词 组合在一起。可以按任意顺序返回结果列表。
//示例:
//输入: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
//输出: [["bat"],["nat","tan"],["ate","eat","tea"]]
//解释:
//在 strs 中没有字符串可以通过重新排列来形成 "bat"。
//字符串 "nat" 和 "tan" 是字母异位词，因为它们可以重新排列以形成彼此。
//字符串 "ate" ，"eat" 和 "tea" 是字母异位词，因为它们可以重新排列以形成彼此。

//My First Answer
//未解决

//Solution 1:排序
//由于互为字母异位词的两个字符串包含的字母相同，因此对两个字符串分别
//进行排序之后得到的字符串一定是相同的，故可以将排序之后的字符串作为哈希表的键。
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> mp;
        for (string& str: strs) {
            string key = str;
            sort(key.begin(), key.end());
            mp[key].emplace_back(str);
        }
        vector<vector<string>> ans;
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            ans.emplace_back(it->second);
        }
        return ans;
    }
};
//Solution 2:计数
//由于互为字母异位词的两个字符串包含的字母相同，因此两个字符串中的
//相同字母出现的次数一定是相同的，故可以将每个字母出现的次数使用字符串表示，
//作为哈希表的键。

//由于字符串只包含小写字母，因此对于每个字符串，可以使用长度为 26 的数组
//记录每个字母出现的次数。需要注意的是，在使用数组作为哈希表的键时，不同语言的
//支持程度不同，因此不同语言的实现方式也不同。
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // 自定义对 array<int, 26> 类型的哈希函数
        auto arrayHash = [fn = hash<int>{}] (const array<int, 26>& arr) -> size_t {
            return accumulate(arr.begin(), arr.end(), 0u, [&](size_t acc, int num) {
                return (acc << 1) ^ fn(num);
            });
        };

        unordered_map<array<int, 26>, vector<string>, decltype(arrayHash)> mp(0, arrayHash);
        for (string& str: strs) {
            array<int, 26> counts{};
            int length = str.length();
            for (int i = 0; i < length; ++i) {
                counts[str[i] - 'a'] ++;
            }
            mp[counts].emplace_back(str);
        }
        vector<vector<string>> ans;
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            ans.emplace_back(it->second);
        }
        return ans;
    }
};