// @File   : 5_replaceSpace.cpp
// @Source : https://leetcode-cn.com/problems/ti-huan-kong-ge-lcof/
// @Title  : 面试题05. 替换空格
// @Auther : sun_ds
// @Date   : 2020/2/19

/**  题目描述：
    请实现一个函数，把字符串 s 中的每个空格替换成"%20"。

     

    示例 1：

    输入：s = "We are happy."
    输出："We%20are%20happy."
     

    限制：

    0 <= s 的长度 <= 10000

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/ti-huan-kong-ge-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 将字符串中的空格替换成"%20"
 *
 *
 */


class Solution {
public:
    string replaceSpace(string s) {
        string ans = "";
        for(int i=0;i<s.size();i++){
            if(s[i] != ' '){
                ans += s[i];
            }else{
                ans += "%20";
            }
        }
        return ans;
    }
};


