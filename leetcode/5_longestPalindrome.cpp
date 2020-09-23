// @File   : 5_longestPalindrome.cpp
// @Source : https://leetcode-cn.com/problems/longest-palindromic-substring/
// @Title  : 5. 最长回文子串
// @Auther : sun_ds
// @Date   : 2019/10/21

/**  题目描述：
    给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。

    示例 1：

    输入: "babad"
    输出: "bab"
    注意: "aba" 也是一个有效答案。
    示例 2：

    输入: "cbbd"
    输出: "bb"

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/longest-palindromic-substring
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 最长回文子串
 * 1.中心扩散，遍历每个字符，将该字符当做回文子串中心
 *   两种情况，子串为奇数，子串为偶数。
 *   保存最大的。输出
 *
 *  字符串中从pos起的n个字符，包括pos
 *  str.substr(pos,n)
 *  字符串中从pos起到末尾
 *  str.substr(pos)
 *
 * 2.dp
 *  dp[i][j]代表，s的子串s[i..j]为回文 等于0或1
 *  则有 dp[i][j] = if(s[i]==s[j]) {dp[i+1][j-1]} else {0}
 *  dp初始值,两种,奇数子串中心和偶数子串中心，dp[i][i],dp[i][i+1]
 *
 *  遍历各个子串长度len
 *
 *
 *  3. Manacher 算法
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
 */


//中心扩散
class Solution {
public:
    string longestPalindrome(string s) {
        int n=s.size();
        if(n<=1)
            return s;

        //left和right可以省略，用i(子串中间位置)和len可推出
        int left = 0, right = 0, max_len = INT_MIN;

        //Right 和 Left 记录最长子串的起始位置和结束位置
        int Right = 0,Left = 0;
        //奇数
        for(int i=0;i<n;i++){
            left = i;
            right = i;
            while(left>=0&&right<n&&s[left]==s[right]){
                --left;
                ++right;
            }
            //此时的s[left]==s[right]是不满足的。所以回文子串其实是 [left + 1 , right - 1];
            int len = right - left - 1;
            if(len > max_len){
                max_len = len;
                Right = right - 1;
                Left = left + 1;
            }
        }
        //偶数
        for(int i=0;i<n-1;i++){
            left = i;
            right = i+1;
            while(left>=0&&right<n&&s[left]==s[right]){
                --left;
                ++right;
            }
            int len = right - left - 1;
            if(len > max_len){
                max_len = len;
                Right = right - 1;
                Left = left + 1;
            }
        }
        return s.substr(Left,Right - Left + 1);
    }
};


class Solution {
public:
    string longestPalindrome(string s) {
        if (s.empty()) return "";
        int len = s.size();
        if (len == 1)return s;
        int longest = 1;
        int start = 0;
        vector <vector<int>> dp(len, vector<int>(len));
        for (int i = 0; i < len; i++) {
            //初始化奇数
            dp[i][i] = 1;
            if (i < len - 1) {
                //初始化偶数
                if (s[i] == s[i + 1]) {
                    dp[i][i + 1] = 1;
                    start = i;
                    longest = 2;
                }
            }
        }
        for (int l = 3; l <= len; l++)//子串长度
        {
            for (int i = 0; i + l - 1 < len; i++)//枚举子串的起始点
            {
                int j = l + i - 1;//终点
                if (s[i] == s[j] && dp[i + 1][j - 1] == 1) {
                    dp[i][j] = 1;
                    start = i;
                    longest = l;
                }
            }
        }
        return s.substr(start, longest);
    }
};

// Manacher
class Solution {
public:
    string longestPalindrome(string s) {
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
        int max_p = 1;
        int start = 0;
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
            if(p[i] > max_p){
                max_p = p[i];
                start = (i - max_p) / 2;
            }
        }
        return s.substr(start, max_p);
    }
};
