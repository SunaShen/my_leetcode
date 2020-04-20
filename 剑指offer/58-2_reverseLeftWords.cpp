// @File   : 58-2_reverseLeftWords.cpp
// @Source : https://leetcode-cn.com/problems/zuo-xuan-zhuan-zi-fu-chuan-lcof/
// @Title  : 面试题58 - II. 左旋转字符串
// @Auther : sun_ds
// @Date   : 2020/3/29

/**  题目描述：
    字符串的左旋转操作是把字符串前面的若干个字符转移到字符串的尾部。请定义一个函数实现字符串左旋转操作的功能。比如，输入字符串"abcdefg"和数字2，该函数将返回左旋转两位得到的结果"cdefgab"。

     

    示例 1：

    输入: s = "abcdefg", k = 2
    输出: "cdefgab"
    示例 2：

    输入: s = "lrloseumgh", k = 6
    输出: "umghlrlose"
     

    限制：

    1 <= k < s.length <= 10000


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/zuo-xuan-zhuan-zi-fu-chuan-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 旋转字符串
 *
 *
 */

class Solution {
public:
    string reverseLeftWords(string s, int n) {
        return (s+s).substr(n,s.size());
    }
};

//额外空间
class Solution {
public:
    string reverseLeftWords(string s, int n) {
        string res;
        for(int i = 0; i<s.size(); i++)
        {
            int x = (i + n) % s.size();
            res += s[x];
        }
        return res;
    }
};


class Solution {
public:
    string reverseLeftWords(string s, int n) {
        std::rotate(s.begin(),s.begin()+n,s.end());
        return s;
    }
};