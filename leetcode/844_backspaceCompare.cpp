// @File   : 844_backspaceCompare.cpp
// @Source : https://leetcode-cn.com/problems/backspace-string-compare/
// @Title  : 844. 比较含退格的字符串
// @Auther : sun_ds
// @Date   : 2020/10/19

/**  题目描述：
    给定 S 和 T 两个字符串，当它们分别被输入到空白的文本编辑器后，判断二者是否相等，并返回结果。 # 代表退格字符。

    注意：如果对空文本输入退格字符，文本继续为空。

     

    示例 1：

    输入：S = "ab#c", T = "ad#c"
    输出：true
    解释：S 和 T 都会变成 “ac”。
    示例 2：

    输入：S = "ab##", T = "c#d#"
    输出：true
    解释：S 和 T 都会变成 “”。
    示例 3：

    输入：S = "a##c", T = "#a#c"
    输出：true
    解释：S 和 T 都会变成 “c”。
    示例 4：

    输入：S = "a#c", T = "b"
    输出：false
    解释：S 会变成 “c”，但 T 仍然是 “b”。
     

    提示：

    1 <= S.length <= 200
    1 <= T.length <= 200
    S 和 T 只含有小写字母以及字符 '#'。
     

    进阶：

    你可以用 O(N) 的时间复杂度和 O(1) 的空间复杂度解决该问题吗？

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/backspace-string-compare
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1. 逆序双指针
 *  当前字符只受它后面的退格符'#'影响。
 *  因此，逆序遍历，并记录当前遇到的'#'数量，跳过对应的字符。
 *  剩下的是剩下的字符。
 *  两个字符串同时执行，比较剩下部分是否相等，若不等直接返回 false
 *
 *  时间复杂度 O(M+N)
 *  空间复杂度 O(1)
 *
 */

class Solution {
public:
    bool backspaceCompare(string S, string T) {
        int i = S.length() - 1, j = T.length() - 1;
        int skipS = 0, skipT = 0;

        while (i >= 0 || j >= 0) {
            while (i >= 0) {
                if (S[i] == '#') {
                    skipS++, i--;
                } else if (skipS > 0) {
                    skipS--, i--;
                } else {
                    break;
                }
            }
            while (j >= 0) {
                if (T[j] == '#') {
                    skipT++, j--;
                } else if (skipT > 0) {
                    skipT--, j--;
                } else {
                    break;
                }
            }
            if (i >= 0 && j >= 0) {
                if (S[i] != T[j]) {
                    return false;
                }
            } else {
                if (i >= 0 || j >= 0) {
                    return false;
                }
            }
            i--, j--;
        }
        return true;
    }
};

