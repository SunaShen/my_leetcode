// @File   : 91_numDecodings.cpp
// @Source : https://leetcode-cn.com/problems/decode-ways/
// @Title  : 解码方法
// @Auther : sun_ds
// @Date   : 2020/1/14

/**  题目描述：
    一条包含字母 A-Z 的消息通过以下方式进行了编码：

    'A' -> 1
    'B' -> 2
    ...
    'Z' -> 26
    给定一个只包含数字的非空字符串，请计算解码方法的总数。

    示例 1:

    输入: "12"
    输出: 2
    解释: 它可以解码为 "AB"（1 2）或者 "L"（12）。
    示例 2:

    输入: "226"
    输出: 3
    解释: 它可以解码为 "BZ" (2 26), "VF" (22 6), 或者 "BBF" (2 2 6) 。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/decode-ways
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 对字符串解码，求解码方法总数
 *
 * 1.dp
 *  设dp[i]为s[0...i-1]这个子串的解码总数
 *  则可以分情况讨论
 *  若s[i-1] == '0'
 *      判断s[i-2] =1或2是否成立，若成立，则dp[i] = dp[i-2];若不成立，则return 0;
 *  若s[i-1] != '0'
 *      判断s[i-2]和s[i-1]组成的数是否在[10,26区间内]，若在区间内则dp[i] = dp[i-1] + dp[i-2] 否则 dp[i] = dp[i-1];
 *
 *  最终得到dp[len]即为最终结果。
 *
 *  算法复杂度O(n) 空间复杂度O(n)
 *
 * 2.dp
 *  dp[i]为s[0...i-1]子串的译码总数
 *  分情况：
 *      若s[i] = '0' 若s[i-1]=1或2 则dp[i] = dp[i-2]; 否则，return 0;
 *          s[i-1] + s[i] 唯一被译码，不增加情况
 *      若s[i-1] = '1' 则dp[i] = dp[i-1] + dp[i-2];
 *          s[i-1]与s[i]分开译码为dp[i-1]，合并译码为dp[i-2]
 *      若s[i-1] = '2'且'1'<=s[i]<='2'，则dp[i] = dp[i-1] + dp[i-2];
 *          s[i-1]与s[i]分开译码为dp[i-1]，合并译码为dp[i-2]
 *
 *   由于dp[i]的值只与前面两个有关。因此使用curr，temp，pre代替dp数组。
 *
 *   时间复杂度O(n) 空间复杂度O(1)
 *
 *
 *
 *
 */

class Solution {
public:
    int numDecodings(string s) {
        int len = s.size();
        if(len == 0) return 0;
        else if(s[0] == '0') return 0;
        int *dp = new int[len+1];
        memset(dp,0,(len+1)*sizeof(int));
        dp[0] = 1;
        dp[1] = 1;
        for(int i=2;i<=len;++i){
            if(s[i-1] == '0'){
                if(s[i-2]>'0'&&s[i-2]<='2') dp[i] = dp[i-2];
                else return 0;
            }else{
                dp[i] = dp[i-1];
                int temp = (s[i-2] - '0') * 10 + (s[i-1] - '0');
                if(temp>=10&&temp<=26) dp[i] += dp[i-2];
            }
        }
        return dp[len];
    }
};

int numDecodings(string s) {
    if (s[0] == '0') return 0;
    int pre = 1, curr = 1;//dp[-1] = dp[0] = 1
    for (int i = 1; i < s.size(); i++) {
        int tmp = curr;
        if (s[i] == '0')
            if (s[i - 1] == '1' || s[i - 1] == '2') curr = pre;
            else return 0;
        else if (s[i - 1] == '1' || (s[i - 1] == '2' && s[i] >= '1' && s[i] <= '6'))
            curr = curr + pre;
        pre = tmp;
    }
    return curr;
}
