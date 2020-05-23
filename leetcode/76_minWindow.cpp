// @File   : 76_minWindow.cpp
// @Source : https://leetcode-cn.com/problems/minimum-window-substring/
// @Title  : 76. 最小覆盖子串
// @Auther : sun_ds
// @Date   : 2020/5/23

/**  题目描述：
    给你一个字符串 S、一个字符串 T，请在字符串 S 里面找出：包含 T 所有字符的最小子串。

    示例：

    输入: S = "ADOBECODEBANC", T = "ABC"
    输出: "BANC"
    说明：

    如果 S 中不存这样的子串，则返回空字符串 ""。
    如果 S 中存在这样的子串，我们保证它是唯一的答案。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/minimum-window-substring
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.map + 滑动窗口
 * 使用 map 统计 t 中各个元素出现的个数。
 * 即此时 map 表示当前需要的元素。
 * 使用双指针，滑动窗口的思想。
 * 右指针从左往右遍历，每次执行m[s[r]]--;若 m[s[r]] >= 0 还成立，证明是s[r]是 t 中还缺少的的元素。此时 len++；
 * len 记录 t 中已经匹配上的个数。若 len==t.size(). 表示当前区间[l,r]包含了 t 所需的所有元素
 * 此时，记录当前窗口大小，并收缩左指针。
 * 执行 m[s[l]]++; 若m[s[l]] > 0成立了，表示 s[l]是 t 中需要的元素，现在将他移出滑动窗口，len 需要减减，跳出循环。
 *
 * 最终得到的min_len就是能够覆盖 t 的最短的子串的长度。
 *
 * 对于其他不相关的元素，m 中初始值就是 0，减减之后就是负值。一直不会对程序有影响。
 *
 */

class Solution {
public:
    string minWindow(string s, string t) {
        //m 存储 t 中需要的元素。
        map<char,int> m;
        for(auto c:t) m[c]++;
        int l = 0,r = 0;
        int L=0;
        int min_len = INT_MAX;
        int len = 0;
        while(r<s.size()){
            m[s[r]]--;
            //减减之后， m[s[r]] >= 0 还成立，证明是s[r]是 t 中还缺少的的元素。
            if(m[s[r]] >= 0) len++;
            //len 记录 t 中已经匹配上的个数。若 len==t.size(). 表示当前区间[l,r]包含了 t 所需的所有元素
            //记录当前长度，左指针收缩右移。
            while(len == t.size()){
                if(min_len > r-l+1){
                    min_len = r-l+1;
                    L = l;
                }
                m[s[l]]++;
                // 若m[s[l]] > 0成立了，表示 s[l]是 t 中需要的元素，现在将他移出滑动窗口，len 需要减减，跳出循环。
                if(m[s[l]] > 0) len--;
                //左指针收缩右移。
                l++;
            }
            //r 循环后移。直到[l,r]区间包含 t，收缩左指针。
            r++;
        }
        if(min_len == INT_MAX) return "";
        return s.substr(L,min_len);
    }
};

