// @File   : 01.06_compressString.cpp
// @Source : https://leetcode-cn.com/problems/compress-string-lcci/
// @Title  : 面试题 01.06. 字符串压缩
// @Auther : sun_ds
// @Date   : 2020/3/16

/**  题目描述：
    字符串压缩。利用字符重复出现的次数，编写一种方法，实现基本的字符串压缩功能。比如，字符串aabcccccaaa会变为a2b1c5a3。若“压缩”后的字符串没有变短，则返回原先的字符串。你可以假设字符串中只包含大小写英文字母（a至z）。

    示例1:

     输入："aabcccccaaa"
     输出："a2b1c5a3"
    示例2:

     输入："abbccd"
     输出："abbccd"
     解释："abbccd"压缩后为"a1b2c2d1"，比原字符串长度更长。
    提示：

    字符串长度在[0, 50000]范围内。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/compress-string-lcci
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * count统计元素重复出现的次数
 * 拼接在temp上 temp += 元素 + to_string(count);
 * 最后比较temp和S的size，输出小的
 *
 *
 */

class Solution {
public:
    string compressString(string S) {
        string temp;
        int count = 1;
        for(int i=1;i<S.size();i++){
            if(S[i]==S[i-1]) count++;
            else{
                temp += S[i-1];
                temp += to_string(count);
                count = 1;
            }
        }
        temp += S[S.size()-1];
        temp += to_string(count);
        return temp.size()<S.size() ? temp : S;
    }
};