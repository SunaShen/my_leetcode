// @File   : 45_minNumber.cpp
// @Source : https://leetcode-cn.com/problems/ba-shu-zu-pai-cheng-zui-xiao-de-shu-lcof/
// @Title  : 面试题45. 把数组排成最小的数
// @Auther : sun_ds
// @Date   : 2020/3/19

/**  题目描述：
    输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。



    示例 1:

    输入: [10,2]
    输出: "102"
    示例 2:

    输入: [3,30,34,5,9]
    输出: "3033459"


    提示:

    0 < nums.length <= 100
    说明:

    输出结果可能非常大，所以你需要返回一个字符串而不是整数
    拼接起来的数字可能会有前导 0，最后结果不需要去掉前导 0
*/

/**
 *
 * 所有整数都转成字符串进行直接比较字符串大小。
 * 按照字符串s1+s2<s2+s1的方式排序。
 * 后组合各字符串即可。
 *
 *
 *
 */



class Solution {
public:
    string minNumber(vector<int>& nums) {
        int n = nums.size();
        vector<string> s;
        for(auto i:nums){
            s.push_back(to_string(i));
        }
        sort(s.begin(),s.end(),[](const string &s1,const string &s2){return s1+s2<s2+s1;});
        string res;
        for(auto i:s){
            res += i;
        }
        return res;
    }
};

