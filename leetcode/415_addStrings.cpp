// @File   : 415_addStrings.cpp
// @Source : https://leetcode-cn.com/problems/add-strings/
// @Title  : 415. 字符串相加
// @Auther : sun_ds
// @Date   : 2020/8/4

/**  题目描述：
    给定两个字符串形式的非负整数 num1 和num2 ，计算它们的和。

     

    提示：

    num1 和num2 的长度都小于 5100
    num1 和num2 都只包含数字 0-9
    num1 和num2 都不包含任何前导零
    你不能使用任何內建 BigInteger 库， 也不能直接将输入的字符串转换为整数形式


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/add-strings
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.字符串加法
 * 模拟全加器
 * 类似链表相加
 */

class Solution {
public:
    string addStrings(string num1, string num2) {
        int len1 = num1.size(), len2 = num2.size();
        int i = len1 - 1;
        int j = len2 - 1;
        string res = "";
        int c = 0;
        while(i >= 0 || j >= 0 || c > 0){
            int temp = 0;
            if(i >= 0) {
                temp += num1[i] - '0';
                --i;
            }
            if(j >= 0){
                temp += num2[j] - '0';
                --j;
            }
            temp += c;
            res.push_back(temp%10 + '0');
            c = temp/10;
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
