// @File   : 125_isPalindrome.cpp
// @Source : https://leetcode-cn.com/problems/valid-palindrome/
// @Title  : 125. 验证回文串
// @Auther : sun_ds
// @Date   : 2020/6/19

/**  题目描述：
    给定一个字符串，验证它是否是回文串，只考虑字母和数字字符，可以忽略字母的大小写。

    说明：本题中，我们将空字符串定义为有效的回文串。

    示例 1:

    输入: "A man, a plan, a canal: Panama"
    输出: true
    示例 2:

    输入: "race a car"
    输出: false

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/valid-palindrome
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.双指针
 * 双指针比较，跳过数字字母以外的字符。
 *
 * 内置函数
 * isalpha()
 * isdigit()
 * tolower()
 *
 * isalnum()
 *
 *
 *
 */

class Solution {
public:
    bool isPalindrome(string s) {
        int n = s.size();
        int l = 0, r = n-1;
        while(l<r){
            while(l < r && !(isalpha(s[l])||isdigit(s[l]))) ++l;
            while(l < r && !(isalpha(s[r])||isdigit(s[r]))) --r;
            if( l > r || tolower(s[l]) != tolower(s[r])) return false;
            ++l;
            --r;
        }
        return true;
    }
};


class Solution {
public:
    bool isPalindrome(string s) {
        int i = 0;
        int j = s.size() - 1;
        while( i < j)
        {
            while(i < j && !isalnum(s[i]))
                i++;
            while(i  < j && !isalnum(s[j]))
                j--;
            if(tolower(s[i++]) != tolower(s[j--]))
                return false;
        }
        return true;
    }
};

