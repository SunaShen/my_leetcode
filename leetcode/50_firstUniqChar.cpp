// @File   : 50_firstUniqChar.cpp
// @Source : https://leetcode-cn.com/problems/di-yi-ge-zhi-chu-xian-yi-ci-de-zi-fu-lcof/
// @Title  : 面试题50. 第一个只出现一次的字符
// @Auther : sun_ds
// @Date   : 2020/3/29

/**  题目描述：
    在字符串 s 中找出第一个只出现一次的字符。如果没有，返回一个单空格。

    示例:

    s = "abaccdeff"
    返回 "b"

    s = ""
    返回 " "
     

    限制：

    0 <= s 的长度 <= 50000



    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/di-yi-ge-zhi-chu-xian-yi-ci-de-zi-fu-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.统计
 * 首先遍历字符串，统计各字符出现的次数
 * 再次遍历字符串，若当前字符统计次数为1，则返回。保证时第一个出现一次的字符
 *
 *
 */


class Solution {
public:
    char firstUniqChar(string s) {
        int n = s.size();
        vector<int> map(256,0);
        for(int i=0;i<n;i++){
            map[s[i]]++;
        }
        //还是沿着输入字符串遍历，这样才能返回第一个出现次数为1的字符
        for(int i=0;i<n;i++){
            if(map[s[i]]==1) return s[i];
        }
        return ' ';
    }
};


