// @File   : 43_multiply.cpp
// @Source : https://leetcode-cn.com/problems/multiply-strings/
// @Title  : 43. 字符串相乘
// @Auther : sun_ds
// @Date   : 2020/8/13

/**  题目描述：
    给定两个以字符串形式表示的非负整数 num1 和 num2，返回 num1 和 num2 的乘积，它们的乘积也表示为字符串形式。

    示例 1:

    输入: num1 = "2", num2 = "3"
    输出: "6"
    示例 2:

    输入: num1 = "123", num2 = "456"
    输出: "56088"
    说明：

    num1 和 num2 的长度小于110。
    num1 和 num2 只包含数字 0-9。
    num1 和 num2 均不以零开头，除非是数字 0 本身。
    不能使用任何标准库的大数类型（比如 BigInteger）或直接将输入转换为整数来处理。


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/multiply-strings
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1. 模拟竖式乘法
 *  num2 的每一位与 num1 相乘，最后相加。
 *  整个过程使用字符串表示，需要字符串加法
 *
 *  时间复杂度 O(MN+N^2) 字符相乘 M*N 字符相加 N*(N+M)  最长字符串长度为(M+N) 因此 M*N + N*(N+M) = O(MN+N^2)
 *  空间复杂度 O(M+N)
 *
 * 2. 直接使用数组存储中间计算结果(提前确定乘积结果的位置)
 *  前提，明确乘法结果对应数组位置
 *
 *  两个数组长度 m 和 n，则乘积的长度必为 m+n-1 或 m+n ！
 *  创建数组 ansArr[m+n]
 *  则 num[i] 和 num[j] 的乘积 位于 ansArr[i+j+1], 若 ansArr[i+j+1] >= 10, 将进位加到 ansArr[i+j]。
 *
 *  时间复杂度 O(MN)
 *  空间复杂度 O(M+N)
 *
 */

class Solution {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") {
            return "0";
        }
        string ans = "0";
        int m = num1.size(), n = num2.size();
        for (int i = n - 1; i >= 0; i--) {
            string curr;
            int add = 0;
            // 补零
            for (int j = n - 1; j > i; j--) {
                curr.push_back(0);
            }
            int y = num2.at(i) - '0';
            // num1 与 y 乘法
            for (int j = m - 1; j >= 0; j--) {
                int x = num1.at(j) - '0';
                int product = x * y + add;
                curr.push_back(product % 10);
                add = product / 10;
            }
            // 后处理
            while (add != 0) {
                curr.push_back(add % 10);
                add /= 10;
            }
            reverse(curr.begin(), curr.end());
            for (auto &c : curr) {
                c += '0';
            }
            // 结果相加
            ans = addStrings(ans, curr);
        }
        return ans;
    }

    string addStrings(string &num1, string &num2) {
        int i = num1.size() - 1, j = num2.size() - 1, add = 0;
        string ans;
        while (i >= 0 || j >= 0 || add != 0) {
            int x = i >= 0 ? num1.at(i) - '0' : 0;
            int y = j >= 0 ? num2.at(j) - '0' : 0;
            int result = x + y + add;
            ans.push_back(result % 10);
            add = result / 10;
            i--;
            j--;
        }
        reverse(ans.begin(), ans.end());
        for (auto &c: ans) {
            c += '0';
        }
        return ans;
    }
};


class Solution {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") {
            return "0";
        }
        int m = num1.size(), n = num2.size();
        auto ansArr = vector<int>(m + n);
        for (int i = m - 1; i >= 0; i--) {
            int x = num1.at(i) - '0';
            for (int j = n - 1; j >= 0; j--) {
                int y = num2.at(j) - '0';
                // 每个数字的乘积的位置都是确定的
                ansArr[i + j + 1] += x * y;
            }
        }
        // 从低位到高位，处理进位
        for (int i = m + n - 1; i > 0; i--) {
            ansArr[i - 1] += ansArr[i] / 10;
            ansArr[i] %= 10;
        }
        // 处理前导零。 由乘积的长度可知，只能有一个零或没有
        int index = ansArr[0] == 0 ? 1 : 0;
        string ans;
        while (index < m + n) {
            ans.push_back(ansArr[index]);
            index++;
        }
        for (auto &c: ans) {
            c += '0';
        }
        return ans;
    }
};

