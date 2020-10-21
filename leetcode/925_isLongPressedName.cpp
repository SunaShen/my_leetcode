// @File   : 925_isLongPressedName.cpp
// @Source : https://leetcode-cn.com/problems/long-pressed-name/
// @Title  : 925. 长按键入
// @Auther : sun_ds
// @Date   : 2020/10/21

/**  题目描述：
    你的朋友正在使用键盘输入他的名字 name。偶尔，在键入字符 c 时，按键可能会被长按，而字符可能被输入 1 次或多次。

    你将会检查键盘输入的字符 typed。如果它对应的可能是你的朋友的名字（其中一些字符可能被长按），那么就返回 True。

     

    示例 1：

    输入：name = "alex", typed = "aaleex"
    输出：true
    解释：'alex' 中的 'a' 和 'e' 被长按。
    示例 2：

    输入：name = "saeed", typed = "ssaaedd"
    输出：false
    解释：'e' 一定需要被键入两次，但在 typed 的输出中不是这样。
    示例 3：

    输入：name = "leelee", typed = "lleeelee"
    输出：true
    示例 4：

    输入：name = "laiden", typed = "laiden"
    输出：true
    解释：长按名字中的字符并不是必要的。
     

    提示：

    name.length <= 1000
    typed.length <= 1000
    name 和 typed 的字符都是小写字母。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/long-pressed-name
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1. 双指针
 *  当 name[i] == typed[j] 时，字符匹配 i++,j++
 *  否则，typed[j-1] == typed[j]时，为连按状态，j++
 *  否则，返回 false。
 *
 *  时间复杂度 O(M+N)
 *  空间复杂度 O(1)
 *
 */

class Solution {
public:
    bool isLongPressedName(string name, string typed) {
        int i = 0, j = 0;
        while (j < typed.length()) {
            if (i < name.length() && name[i] == typed[j]) {
                i++;
                j++;
            } else if (j > 0 && typed[j] == typed[j - 1]) {
                j++;
            } else {
                return false;
            }
        }
        return i == name.length();
    }
};
