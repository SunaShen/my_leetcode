// @File   : 394_decodeString.cpp
// @Source : https://leetcode-cn.com/problems/decode-string/
// @Title  : 394. 字符串解码
// @Auther : sun_ds
// @Date   : 2020/5/28

/**  题目描述：
    给定一个经过编码的字符串，返回它解码后的字符串。

    编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。注意 k 保证为正整数。

    你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。

    此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k ，例如不会出现像 3a 或 2[4] 的输入。

    示例:

    s = "3[a]2[bc]", 返回 "aaabcbc".
    s = "3[a2[c]]", 返回 "accaccacc".
    s = "2[abc]3[cd]ef", 返回 "abcabccdcdcdef".

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/decode-string
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 *
 * 1.栈
 * 遍历字符串
 *  1.1 遇到数字 组成数字倍数multi
 *  1.2 遇到[ 存储前面的数字和前面一部分的字符串 res ，并将 res 和 multi 置空重新开始
 *  1.3 遇到] 需要从栈中读取栈顶的 res 和 multi 此时的解码字符串 = 栈顶字符串(前半部分字符串) + 栈顶重复次数multi * 当前 res
 *  1.4 其他，那就是字符串的部分，res += c；
 *
 * 最终得到 res 为最终将结果。
 *
 */


class Solution {
public:
    string decodeString(string s) {
        int multi = 0;
        string res = "";
        stack<int> stack_multi; //倍数
        stack<string> stack_res; //前半段
        for(auto c : s) {
            if(c == '[') {
                stack_multi.push(multi);
                stack_res.push(res);
                multi = 0;
                res = "";
            }
            else if(c == ']') {
                string temp = "";
                int cur_multi = stack_multi.top();
                stack_multi.pop();
                for(int i = 0; i < cur_multi; i++) temp += res;
                res = stack_res.top() + temp;
                stack_res.pop();
            }
            else if(c >= '0' && c <= '9') multi = multi * 10 + c - '0';
            else res += c;
        }
        return res;
    }
};


