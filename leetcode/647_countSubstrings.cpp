// @File   : 647_countSubstrings.cpp
// @Source : https://leetcode-cn.com/problems/palindromic-substrings/
// @Title  : 647. 回文子串
// @Auther : sun_ds
// @Date   : 2020/8/19

/**  题目描述：
    给定一个字符串，你的任务是计算这个字符串中有多少个回文子串。

    具有不同开始位置或结束位置的子串，即使是由相同的字符组成，也会被视作不同的子串。

     

    示例 1：

    输入："abc"
    输出：3
    解释：三个回文子串: "a", "b", "c"
    示例 2：

    输入："aaa"
    输出：6
    解释：6个回文子串: "a", "a", "a", "aa", "aa", "aaa"
     

    提示：

    输入的字符串长度不会超过 1000 。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/palindromic-substrings
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 *
 * 1. 中心扩散
 *  以每一个位置为中心(考虑奇偶回文)，向两边扩散，并统计子串的个数。
 *
 *  时间复杂度 O(N^2)
 *  空间复杂度 O(1)
 *
 *
 * 2. Manacher 算法
 *  https://www.cxyxiaowu.com/2665.html
 *
 *  添加分隔符'#',使得奇偶情况合并
 *  维护 p 矩阵，值为当前字符为中心的回文半径，不包含本字符。
 *  如：
 *      #b#a#b# 的 以 a 为中心 p[3] = 3;     p[3]的值即为原字符串 "bab"中 a 为中心的最大回文长度
 *      #b#b# 的 以 # 为中心 p[2] = 2;       p[2]的值即为原字符串 "bb"中 bb 中间为中心的最大回文长度
 *
 *  遍历构造 p 矩阵，过程中维护 maxRight 和 maxRight 对应的中心 center。
 *  maxRight 记录当前向右扩展的最远边界; center 为 maxRight 对应的回文中心
 *
 *  遍历过程中，借助前面已经填充好的 p。
 *  i >= maxRight 时，无法借助之前的 p，只能使用中心扩散扫描。
 *  i < maxRight 时，需要关注 i 关于 center 对称的位置 mirror 处的 p[mirror] 的值
 *   1) p[mirror] < maxRight - i
 *      p[i] = p[mirror];
 *   2) p[mirror] == maxRight - i
 *      p[i] >= p[mirror]; 还需要继续扩散
 *   3）p[mirror] > maxRight - i
 *      p[i] = maxRight - i;
 *
 *  结合上述几种情况，当 i < maxRight 时，p[i] = min(maxRight - i, p[mirror]); 然后在此基础继续中心扩散。
 *
 *  时间复杂度 O(N)
 *  空间复杂度 O(N)
 *
 *
 *
 */

class Solution {
public:
    int countSubstrings(string s) {
        int n = s.size(), ans = 0;
        // 合并两种情况到一个 for 循环 即奇数回文和偶数回文
        for (int i = 0; i < 2 * n - 1; ++i) {
            int l = i / 2, r = i / 2 + i % 2;
            while (l >= 0 && r < n && s[l] == s[r]) {
                --l;
                ++r;
                ++ans;
            }
        }
        return ans;
    }
};

class Solution {
public:
    int countSubstrings(string s) {
        int n = s.size();
        string t = "#";
        for(auto c:s){
            t += c;
            t += '#';
        }
        n = t.size();
        int res = 0;
        vector<int> p(n,0);
        int maxR = 0;
        int center = 0;
        for(int i=0;i<n;i++){
            if(i < maxR){
                p[i] = min(maxR - i, p[2 * center - i]);
            }
            int left = i - (1 + p[i]);
            int right = i + (1 + p[i]);
            while(left >= 0 && right < n && t[left] == t[right]){
                left--;
                right++;
                p[i]++;
            }
            if(i + p[i] > maxR){
                maxR = i + p[i];
                center = i;
            }
            res += (p[i] + 1) / 2;
        }
        return res;
    }
};
