// @File   : 1170_numSmallerByFrequency.cpp
// @Source : https://leetcode-cn.com/problems/compare-strings-by-frequency-of-the-smallest-character/
// @Title  : 比较字符串最小字母出现频次
// @Auther : sun_ds
// @Date   : 2019/10/7

/*  题目描述：
    我们来定义一个函数 f(s)，其中传入参数 s 是一个非空字符串；该函数的功能是统计 s  中（按字典序比较）最小字母的出现频次。

    例如，若 s = "dcce"，那么 f(s) = 2，因为最小的字母是 "c"，它出现了 2 次。

    现在，给你两个字符串数组待查表 queries 和词汇表 words，请你返回一个整数数组 answer 作为答案，其中每个 answer[i] 是满足 f(queries[i]) < f(W) 的词的数目，W 是词汇表 words 中的词。

     

    示例 1：

    输入：queries = ["cbd"], words = ["zaaaz"]
    输出：[1]
    解释：查询 f("cbd") = 1，而 f("zaaaz") = 3 所以 f("cbd") < f("zaaaz")。
    示例 2：

    输入：queries = ["bbb","cc"], words = ["a","aa","aaa","aaaa"]
    输出：[1,2]
    解释：第一个查询 f("bbb") < f("aaaa")，第二个查询 f("aaa") 和 f("aaaa") 都 > f("cc")。
     

    提示：

    1 <= queries.length <= 2000
    1 <= words.length <= 2000
    1 <= queries[i].length, words[i].length <= 10
    queries[i][j], words[i][j] 都是小写英文字母

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/compare-strings-by-frequency-of-the-smallest-character
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
 *
 * 1.首先实现f(x)函数功能，即统计字符串中最小字符(字典序)出现的次数。
 * 使用数组保存不同字符出现的次数，得到字典序最小字符出现的次数。
 * 2.对word中多有字符串执行f(x)并保存
 * 3.循环遍历queries中每一个字符串对应的f(x)，并统计小于word中各字符串的f(x)的次数
 * 4.输出结果
 *
 */




#include <iostream>
#include <vector>
#include <string>

using namespace std;


class Solution {
public:
    int getf(string s){
        int n=s.length();
        int count[30] = {0};
        for(int i=0; i<n; i++) count[s[i] - 'a']++;
        for(int i=0; i<26; i++) if(count[i]>0) return count[i];
        return 0;
    }

    vector<int> numSmallerByFrequency(vector<string>& queries, vector<string>& words) {
        int m=queries.size(), n=words.size();
        vector<int> w_count;
        vector<int> res;
        for(int i=0; i<n; i++)w_count.push_back(getf(words[i]));
        for(int i=0; i<m; i++){
            int c = getf(queries[i]);
            int r = 0;
            for(int j=0; j<n; j++){
                if(c<w_count[j]) r++;
            }
            res.push_back(r);
        }
        return res;
    }
};

int main()
{

    vector<string> queries = {"bbb","cc"};
    vector<string> words = {"a","aa","aaa","aaaa"};
    Solution su;
    auto res = su.numSmallerByFrequency(queries,words);

    cout << "[";
    for(auto i:res)
        cout << i << ",";
    cout << "]" << endl;
    cout << "finish" << endl;
    return 0;
}