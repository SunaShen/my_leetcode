// @File   : 67_addBinary.cpp
// @Source : https://leetcode-cn.com/problems/add-binary/
// @Title  : 二进制求和
// @Auther : sun_ds
// @Date   : 2019/9/4


/*  题目描述：
    给定两个二进制字符串，返回他们的和（用二进制表示）。

    输入为非空字符串且只包含数字 1 和 0。

    示例 1:

    输入: a = "11", b = "1"
    输出: "100"
    示例 2:

    输入: a = "1010", b = "1011"
    输出: "10101"

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/add-binary
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/*
 *
 * 二进制求和，输入的式string
 * 从后往前，按位加法，当前位值+carry进位，存入string，最终得到string反序
 * 注意判断，a,b长度，以及是否还存在carry，作为*循环*的条件
 * a,b长度不够，用0补，使用条件表达式在*循环中*判断
 *
 * string反序：
 * 1.存入时用insert(string.begin(), string)
 * 2.reverse(string.begin(), string.end())
 *
 *
 */




#include <iostream>
#include <string>

using namespace std;


class Solution {
public:
    string addBinary(string a, string b) {

        string s;
        int c = 0, i = a.size() - 1, j = b.size() - 1;
//      a,b,c-进位,都结束了才结束
//      a,b位数不够使用条件运算符判断补0
        while(i >= 0 || j >= 0 || c == 1)
        {
            c += i >= 0 ? a[i--] - '0' : 0;
            c += j >= 0 ? b[j--] - '0' : 0;
//          放入时就倒序，不用下面reverse
            s.insert(s.begin(), (c & 1) + '0');
            c >>= 1;
        }
//        reverse(s.begin(), s.end());
        return s;
    }
};




int main()
{
    string a = "111", b = "101";
    Solution su;
    auto res = su.addBinary(a, b);

    cout << a << " + " << b << " = ";
    cout << res << endl;


    cout << "finish" << endl;
    return 0;
}