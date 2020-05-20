// @File   : 1371_findTheLongestSubstring.cpp
// @Source : https://leetcode-cn.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/
// @Title  : 1371. 每个元音包含偶数次的最长子字符串
// @Auther : sun_ds
// @Date   : 2020/5/20

/**  题目描述：
    给你一个字符串 s ，请你返回满足以下条件的最长子字符串的长度：每个元音字母，即 'a'，'e'，'i'，'o'，'u' ，在子字符串中都恰好出现了偶数次。

     

    示例 1：

    输入：s = "eleetminicoworoep"
    输出：13
    解释：最长子字符串是 "leetminicowor" ，它包含 e，i，o 各 2 个，以及 0 个 a，u 。
    示例 2：

    输入：s = "leetcodeisgreat"
    输出：5
    解释：最长子字符串是 "leetc" ，其中包含 2 个 e 。
    示例 3：

    输入：s = "bcbcbc"
    输出：6
    解释：这个示例中，字符串 "bcbcbc" 本身就是最长的，因为所有的元音 a，e，i，o，u 都出现了 0 次。
     

    提示：

    1 <= s.length <= 5 x 10^5
    s 只包含小写英文字母。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/find-the-longest-substring-containing-vowels-in-even-counts
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.状态压缩+前缀和
 * 统计 aeiou 每个字符出现的次数的奇偶。
 * 使用二进制位代表，1 为奇数个，0 位偶数个。
 * status 记录当前位置前的奇偶特性。
 * 前缀和思想，当前状态和前面某个状态相同，那么当前位置到前面那个状态之间的字符串肯定是符合条件的，即 status = 0;（每个字符出现偶数次）
 *
 */

class Solution {
public:
    int findTheLongestSubstring(string s) {
        int ans = 0, status = 0, n = s.size();
        //记录当前位置前的奇偶状态
        vector<int> pos(32, -1);
        pos[0] = 0;
        for (int i = 0; i < n; i ++) {
            if (s[i] == 'a') {
                status ^= 1<<0;
            } else if (s[i] == 'e') {
                status ^= 1<<1;
            } else if (s[i] == 'i') {
                status ^= 1<<2;
            } else if (s[i] == 'o') {
                status ^= 1<<3;
            } else if (s[i] == 'u') {
                status ^= 1<<4;
            }
            //判断前面是否有与当前状态相同的位置。
            if (pos[status] != -1) {
                ans = max(ans, i + 1 - pos[status]);
            } else {
                //每次只记录第一次出现该状态的位置，最左边。
                pos[status] = i + 1;
            }
        }
        return ans;
    }
};

