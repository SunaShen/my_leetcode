// @File   : 214_shortestPalindrome.cpp
// @Source : https://leetcode-cn.com/problems/shortest-palindrome/
// @Title  : 214. 最短回文串
// @Auther : sun_ds
// @Date   : 2020/8/29

/**  题目描述：
    给定一个字符串 s，你可以通过在字符串前面添加字符将其转换为回文串。找到并返回可以用这种方式转换的最短回文串。

    示例 1:

    输入: "aacecaaa"
    输出: "aaacecaaa"
    示例 2:

    输入: "abcd"
    输出: "dcbabcd"

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/shortest-palindrome
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 我们需要在给定的字符串 s 的前面添加字符串 s'，得到最短的回文串。
 * 这里我们用 s'+ s 表示得到的回文串。显然，这等价于找到最短的字符串 s'，使得 s'+ s 是一个回文串。
 *
 * 由于我们一定可以将 s 去除第一个字符后得到的字符串反序地添加在 s 的前面得到一个回文串，因此一定有 ∣s'∣<∣s∣，其中 ∣s∣ 表示字符串 s 的长度。
 *
 * 将 s 分为两部分：
 *  1) 长度为 ∣s∣−∣s'∣ 的前缀 s1;
 *  2) 长度为 ∣s'∣ 的后缀 s2;
 *
 * 由于 s' + s 是一个回文串，那么 s' 的反序就必然与 s2 相同，并且 s1 本身就是一个回文串。
 * 因此，要找到最短的 s' ，等价于找到最长的 s1。
 * 也就是说，我们需要在字符串 s 中超出一个最长的前缀 s1，它是一个回文串。当我们找到 s1 后，剩余的部分即为 s2，其反序即为 s'。
 *
 * 1. 枚举 + 字符串哈希
 *  枚举每个 s1 结束的位置。找到前缀 s1 为回文串的最长的长度。
 *  使用字符串哈希，降低判断 s1 是否为回文串的复杂度。
 *
 *  使用 Rabin-Karp 字符串哈希算法，使得每个字符串对应着唯一的 hash 值(小概率哈希碰撞)。
 *  因此对 s1 和 s1 的反序同时求哈希值，若相等证明当前 s1 为回文串，记录当前长度。
 *
 *  使用 Rabin-Karp 字符串哈希算法可以借助之前的状态在 O(1) 的复杂度下得到新的哈希值。
 *   left = ((long long)left * base + s[i]) % mod;
 *   right = (right + (long long)mul * s[i]) % mod;
 *
 *  时间复杂度 O(|S|)
 *  空间复杂度 O(1)
 *
 *
 * 2. KMP
 * 使用 KMP 字符串匹配算法来找出这个最长的前缀回文串。
 * 具体地，记 s' 为 s 的反序，由于 s1 是 s 的前缀，那么 s1' 就是 s'的后缀。
 * 考虑到 s1 是一个回文串，因此 s1 == s1' ，s1 同样是 s' 的后缀。
 * 这样一来，我们将 s 作为模式串，s' 作为查询串进行匹配。
 * 当遍历到 s' 的末尾时，如果匹配到 s 中的第 i 个字符，那么说明 s 的前 i 个字符与 s' 的后 i 个字符相匹配（即相同），
 * s 的前 i 个字符对应 s1 , s1' 的后 i 个字符对应 s1' ，由于 s1 = s1'，因此 s1 就是一个回文串。
 *
 * 作者：LeetCode-Solution
 * 链接：https://leetcode-cn.com/problems/shortest-palindrome/solution/zui-duan-hui-wen-chuan-by-leetcode-solution/
 * 来源：力扣（LeetCode）
 * 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 *
 *
 * 3. manacher
 *  借助 manacher 找回文串。
 *  https://leetcode-cn.com/problems/shortest-palindrome/solution/shi-jian-fu-za-du-on-jie-fa-la-che-by-time-limit/
 *
 */

// Rabin-Karp
class Solution {
public:
    string shortestPalindrome(string s) {
        int n = s.size();
        int base = 131, mod = 1000000007;
        int left = 0, right = 0, mul = 1;
        int best = -1;
        for (int i = 0; i < n; ++i) {
            left = ((long long)left * base + s[i]) % mod;
            right = (right + (long long)mul * s[i]) % mod;
            if (left == right) {
                best = i;
            }
            mul = (long long)mul * base % mod;
        }
        string add = (best == n - 1 ? "" : s.substr(best + 1, n));
        reverse(add.begin(), add.end());
        return add + s;
    }
};


// KMP
class Solution {
public:
    string shortestPalindrome(string s) {

        string sr(s.rbegin(), s.rend());

        int n = s.size();
        vector<int> next(n + 1, -1);
        int i = 0, j = -1;

        while(i < n){
            while(j >= 0 && s[i] != s[j]) j = next[j];
            i++;
            j++;
            next[i] = j;
        }

        i = 0, j = 0;
        while(i < n){
            while(j >= 0 && sr[i] != s[j]) j = next[j];
            i++;
            j++;
        }

        string add = (j == n ? "" : s.substr(j, n));
        reverse(add.begin(), add.end());
        return add + s;
    }
};



// 借助Manacher
class Manacher {
public:
    Manacher(const std::string &s) {
        construct(s);
    };

    void getLongestPalindromeString(int &position, int &length) {
        // 找到最长的回文子串的位置与长度。
        position = -1, length = -1;
        for(int i = 0; i < len.size(); i++) {
            if(len[i] > length) {
                length = len[i];
                position = i;
            }
        }
        // 映射到原始字符串中的位置。
        position = position/2 - length/4;
        length = length/2;
        return;
    }

    // s[L:R] 是否是回文的
    //// 根据 len 判断
    bool isPalindrome(int L, int R) {
        //// 转换到加上分割符的坐标
        L = L*2 + 1;
        R = R*2 + 1;
        //// center
        int mid = (L+R)/2;
        if(0 <= mid && mid < len.size() && R-L+1 <= len[mid]) {
            return true;
        }
        return false;
    }

private:
    //// 存储的当前的回文串的长度 不是回文半径。 长度 = 回文半径 * 2 + 1
    vector<int> len;

    void construct(const std::string &s) {
        vector<char> vec;
        // 用 0 作为分隔符
        vec.resize(s.size()*2+1);
        for(int i = 0; i < s.size(); i++) {
            vec[i<<1|1] = s[i];
        }

        //// 使用 L,R 记录 不是 maxRight 和 center。
        int L = 0, R = -1;
        len.resize(vec.size());

        for(int i = 0, n = vec.size(); i < n; i++) {
            if(i <= R) { // 被覆盖了，尝试加速
                //// p[i] = min(maxR - i, p[2 * center - i]);
                len[i] = min((R-i)*2+1, len[L+R-i]);
            } else { // 未被覆盖，那就没办法加速了，从 1 开始。
                len[i] = 1;
            }
            // 尝试继续探测
            int l = i - len[i]/2 - 1;
            int r = i + len[i]/2 + 1;
            while(0 <= l && r < vec.size() && vec[l] == vec[r]) {
                --l;
                ++r;
            }
            // 更新
            len[i] = r-l-1;
            if(r > R) {
                L = l+1;
                R = r-1;
            }
        }
    }
};

class Solution {
public:
    string shortestPalindrome(string s) {
        if(s.size() <= 0) {
            return s;
        }
        Manacher manacher(s);
        for(int i = s.size()-1; i >= 0; i--) {
            //// 逆序遍历，找到第一个回文的前缀即是最长的回文前缀
            if(manacher.isPalindrome(0, i)) {
                auto str = s.substr(i+1);
                reverse(str.begin(), str.end());
                return str + s;
            }
        }
        // s[0:0] 只有一个字符，所以必为回文，所以永远不会执行这个 return。
        return "";
    }
};