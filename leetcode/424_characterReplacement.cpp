// @File   : 424_characterReplacement.cpp
// @Source : https://leetcode-cn.com/problems/longest-repeating-character-replacement/
// @Title  : 424. 替换后的最长重复字符
// @Auther : sun_ds
// @Date   : 2020/4/21

/**  题目描述：
    给你一个仅由大写英文字母组成的字符串，你可以将任意位置上的字符替换成另外的字符，总共可最多替换 k 次。在执行上述操作后，找到包含重复字母的最长子串的长度。

    注意:
    字符串长度 和 k 不会超过 10^4。

    示例 1:

    输入:
    s = "ABAB", k = 2

    输出:
    4

    解释:
    用两个'A'替换为两个'B',反之亦然。
    示例 2:

    输入:
    s = "AABABBA", k = 1

    输出:
    4

    解释:
    将中间的一个'A'替换为'B',字符串变为 "AABBBBA"。
    子串 "BBBB" 有最长重复字母, 答案为 4。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/longest-repeating-character-replacement
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 1.滑动窗口
 * 使用count统计窗口内各个字符出现的次数。
 * 设定窗口大小为win
 * 取区间中字符出现次数最多的字符为主字符，则包含的其他字符个数为win - count[max]
 * 当win - count[max]<=k时都是满足条件的，记录窗口的最大长度。
 * 并在窗口末尾加入新的元素。
 * 若win - count[max]>k，则需要收缩窗口。
 *
 * 最终得到最大的窗口值
 *
 *
 *
 */

class Solution {
public:
    int get_max(vector<int>& count){
        int val = 0;
        int index = 0;
        for(int i=0;i<26;i++){
            if(count[i]>val){
                val = count[i];
                index = i;
            }
        }
        return index;
    }
    int characterReplacement(string s, int k) {
        if(s.size()==0) return 0;
        int n = s.size();
        int res = k;
        int win = k+1;
        vector<int> count(26,0);
        for(int i=0;i<=k;i++){
            count[s[i] - 'A']++;
        }
        int i=0;
        while(1){
            if(win - count[get_max(count)]<=k){
                res = max(res,win);
                if(i+win<n){
                    count[s[i+win] - 'A']++;
                    win++;
                }else{
                    break;
                }
            }else{
                count[s[i] - 'A']--;
                win--;
                i++;
            }
        }
        return res;
    }
};

