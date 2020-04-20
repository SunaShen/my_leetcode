// @File   : 179_largestNumber.cpp
// @Source : https://leetcode-cn.com/problems/largest-number/
// @Title  : 179. 最大数
// @Auther : sun_ds
// @Date   : 2020/3/19

/**  题目描述：
    给定一组非负整数，重新排列它们的顺序使之组成一个最大的整数。

    示例 1:

    输入: [10,2]
    输出: 210
    示例 2:

    输入: [3,30,34,5,9]
    输出: 9534330
    说明: 输出结果可能非常大，所以你需要返回一个字符串而不是整数。
*/

/**
 *
 *
 * 数字转成字符串后进行排序
 * 最后组装
 * 考虑多个零要变成"0"
 *
 *
 */

class Solution {
public:
    string largestNumber(vector<int>& nums) {
        int n = nums.size();
        vector<string> s;
        for(auto i:nums){
            s.push_back(to_string(i));
        }
        sort(s.begin(),s.end(),[](const string &s1,const string &s2){return s1+s2>s2+s1;});
        if(s[0]=="0") return "0";//防止多个0
        string res;
        for(auto i:s){
            res += i;
        }
        return res;
    }
};
