// @File   : 6_convert.cpp
// @Source : https://leetcode-cn.com/problems/zigzag-conversion/
// @Title  : Z 字形变换
// @Auther : sun_ds
// @Date   : 2019/10/21

/*  题目描述：
    将一个给定字符串根据给定的行数，以从上往下、从左到右进行 Z 字形排列。

    比如输入字符串为 "LEETCODEISHIRING" 行数为 3 时，排列如下：

    L   C   I   R
    E T O E S I I G
    E   D   H   N
    之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如："LCIRETOESIIGEDHN"。

    请你实现这个将字符串进行指定行数变换的函数：

    string convert(string s, int numRows);
    示例 1:

    输入: s = "LEETCODEISHIRING", numRows = 3
    输出: "LCIRETOESIIGEDHN"
    示例 2:

    输入: s = "LEETCODEISHIRING", numRows = 4
    输出: "LDREOEIIECIHNTSG"
    解释:

    L     D     R
    E   O E   I I
    E C   I H   N
    T     S     G

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/zigzag-conversion
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/*
 * Z字形变换，N字形变换?
 *
 * 一行拆分成n行，并逐行输出。
 *
 * 找规律？。
 *
 * 1.找规律，定义numRows个string存储，numRows + numRows - 2一个循环。对该值取模。
 *   使用模后的值k和numRows的大小判断是向上还是向下。
 *   算法复杂度O(n)
 *
 * 2.简化版，更易理解。 上下穿梭，遇到最上和最下变相。(精巧)
 *   算法复杂度O(n)
 *
 * 3.直接读取，不用创建多个string保存每行。
 *   首末行每次写入1个字符，其他每次写如两个。即每次循环中的第前i个和第后i个。
 */


class Solution {
public:
    string convert(string s, int numRows) {
        if(numRows <= 1)
            return s;
        int n = s.size();
        vector<string> res(min(n,numRows));
//        vector<string> res(numRows);
        int mod = 2*numRows - 2;
        for(int i=0;i<n;i++){
            int k = i%mod;
            if(k>=numRows)
                k = (numRows - 1) - (k - numRows + 1);
            res[k] += s[i];
        }
        string ans;
        for(auto i:res){
            ans += i;
        }
        return ans;
    }
};





class Solution {
public:
    string convert(string s, int numRows) {

        if (numRows == 1) return s;

        vector<string> rows(min(numRows, int(s.size())));
        int curRow = 0;
        bool goingDown = false;

        for (char c : s) {
            rows[curRow] += c;
            if (curRow == 0 || curRow == numRows - 1) goingDown = !goingDown;
            curRow += goingDown ? 1 : -1;
        }

        string ret;
        for (string row : rows) ret += row;
        return ret;
    }
};


class Solution {
public:
    string convert(string s, int numRows) {

        if (numRows == 1) return s;

        string ret;
        int n = s.size();
        int cycleLen = 2 * numRows - 2;

        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j + i < n; j += cycleLen) {
                ret += s[j + i];
                // 排除首位两行
                if (i != 0 && i != numRows - 1 && j + cycleLen - i < n)
                    ret += s[j + cycleLen - i];
            }
        }
        return ret;
    }
};