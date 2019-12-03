// @File   : 14_longestCommonPrefix.cpp
// @Source : https://leetcode-cn.com/problems/longest-common-prefix/
// @Title  : 最长公共前缀
// @Auther : sun_ds
// @Date   : 2019/9/26

/*  题目描述：
    编写一个函数来查找字符串数组中的最长公共前缀。

    如果不存在公共前缀，返回空字符串 ""。

    示例 1:

    输入: ["flower","flow","flight"]
    输出: "fl"
    示例 2:

    输入: ["dog","racecar","car"]
    输出: ""
    解释: 输入不存在公共前缀。
    说明:

    所有输入只包含小写字母 a-z 。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/longest-common-prefix
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/*
 * 最长公共前缀
 *
 * 限制条件---前缀
 * 1.找出最短的字符(只需搜索这么多)
 * 2.比较各个字符串对应位置字符是否相等，相等加入结果并继续，不相等直接return
 * 复杂的O(N^2)?
 *
 */



#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.size()==0)
            return {};
        int min_l = INT_MAX;
        for(int i=0;i<strs.size();i++){
            if(strs[i].size() < min_l)
                min_l = strs[i].size();
        }
        if(min_l==0)
            return {};
        string res;
        for (int j = 0; j < min_l; j++) {
            char temp = strs[0][j];
            for(int i=1;i<strs.size();i++) {
                if(strs[i][j]!=temp)
                    return res;
            }
            res = res + temp;
        }
        return res;
    }
};

int main()
{
    vector<string> s={"flower","flow","flight"};

    Solution su;
    auto res = su.longestCommonPrefix(s);

    cout << res << endl;

    cout << "finish" << endl;
    return 0;
}