// @File   : 17_letterCombinations.cpp
// @Source : https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number/
// @Title  : 电话号码的字母组合
// @Auther : sun_ds
// @Date   : 2019/11/9

/*  题目描述：
    给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。

    给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。



    示例:

    输入："23"
    输出：["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
    说明:
    尽管上面的答案是按字典序排列的，但是你可以任意选择答案输出的顺序。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/*
 * 给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。
 * 九宫格打字？
 *
 * 回溯法
 *
 * 1.递归 dfs
 * 2.循环 bfs
 *
 *
 * 注意循环方法的实现。
 * 递归变循环，主要注意如何保存中间结果。以及怎么拼接结果。
 *
 *
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>



using namespace std;

//循环
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> ans;
        if (digits.size() == 0) return ans;
        ans.push_back("");
        vector<string> key = { {"abc"}, {"def"}, {"ghi"}, {"jkl"}, {"mno"}, {"pqrs"}, {"tuv"}, {"wxyz"} };
        for (auto it = digits.begin(); it != digits.end(); ++it) {
            vector<string> tmp;
            int num = *it - '2';
            if (num < 0) continue;
            for (auto i = key[num].begin(); i != key[num].end(); ++i)
                for (auto j = ans.begin(); j != ans.end(); ++j)
                    // 存储新结果需要用到老的结果。
                    tmp.push_back(*j + *i);
            ans = tmp;
        }
        return ans;
    }
};

//递归
class Solution {
public:
    vector<string> ans;
    vector<vector<char>> index{{'a','b','c'},{'d','e','f'},{'g','h','i'},{'j','k','l'},{'m','n','o'},{'p','q','r','s'},{'t','u','v'},{'w','x','y','z'}};
    string dig;
    void func(int cnt, string temp){
        if(cnt == dig.size()){
            ans.push_back(temp);
            return;
        }
        vector<char> t = index[dig[cnt] - '2'];
        for(auto i:t){
            func(cnt+1,temp+i);
        }
    }
    vector<string> letterCombinations(string digits) {
        dig = digits;
        func(0,{});
        return ans;
    }
};


int main(int argc, char * argv[])
{
    string s="23";
    Solution su;
    auto res = su.letterCombinations(s);
    for(auto k : res){
        cout << k << endl;
    }
    return 0;
}


