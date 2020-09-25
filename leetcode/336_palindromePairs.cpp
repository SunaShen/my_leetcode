// @File   : 336_palindromePairs.cpp
// @Source : https://leetcode-cn.com/problems/palindrome-pairs/
// @Title  : 336. 回文对
// @Auther : sun_ds
// @Date   : 2020/8/6

/**  题目描述：
    给定一组 互不相同 的单词， 找出所有不同 的索引对(i, j)，使得列表中的两个单词， words[i] + words[j] ，可拼接成回文串。

     

    示例 1：

    输入：["abcd","dcba","lls","s","sssll"]
    输出：[[0,1],[1,0],[3,2],[2,4]]
    解释：可拼接成的回文串为 ["dcbaabcd","abcddcba","slls","llssssll"]
    示例 2：

    输入：["bat","tab","cat"]
    输出：[[0,1],[1,0]]
    解释：可拼接成的回文串为 ["battab","tabbat"]

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/palindrome-pairs
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 *
 * 1. 枚举前缀和后缀
 * 假设存在两个字符串 s1 和 s2, s1 + s2 是一个回文串，记这两个字符串的长度分别为 len1 和 len2
 * 我们分三种情况进行讨论：
 *  1) len1 == len2 这种情况下 s1 是 s2 的翻转。
 *  2) len1 > len2 这种情况下我们可以将 s1 拆成左右两部分：t1 和 t2 ，其中 t1 是 s2 的翻转，t2 是一个回文串。
 *  3) len1 < len2 这种情况下我们可以将 s2 拆成左右两部分：t1 和 t2 ，其中 t2 是 s1 的翻转，t1 是一个回文串。
 *
 * 这样，对于每一个字符串，我们令其为 s1 和 s2 中较长的那一个，然后找到可能和它构成回文串的字符串即可。
 *
 * 具体地说，我们枚举每一个字符串 k，令其为 s1 和 s2 中较长的那一个，那么 k 可以被拆分为两部分，t1 和 t2。
 *  当 t1 是回文串时，符合情况 3，我们只需要查询给定的字符串序列中是否包含 t2 的翻转。
 *  当 t2 是回文串时，符合情况 2，我们只需要查询给定的字符串序列中是否包含 t1 的翻转。
 *  也就是说，我们要枚举字符串 k 的每一个前缀和后缀，判断其是否为回文串。如果是回文串，我们就查询其剩余部分的翻转是否在给定的字符串序列中出现即可。
 *  注意到空串也是回文串，所以我们可以将 k 拆解为 k+∅ 或 ∅+k，这样我们就能将情况 1 也解释为特殊的情况 2 或情况 3。
 *
 *
 *  为实现一个能够在一系列字符串中查询「某个字符串的子串的翻转」是否存在的数据结构，可以采用字典树。
 *
 *
 *  时间复杂度 O(N*M^2)
 *  空间复杂度 O(N*M)
 *
 *  作者：LeetCode-Solution
 *  链接：https://leetcode-cn.com/problems/palindrome-pairs/solution/hui-wen-dui-by-leetcode-solution/
 *  来源：力扣（LeetCode）
 *  著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 *
 *
 *
 */

class Solution {
public:
    struct node {
        int ch[26];
        int flag;
        node() {
            flag = -1;
            memset(ch, 0, sizeof(ch));
        }
    };

    // 字典树
    vector<node> tree;

    void insert(string& s, int id) {
        int len = s.length(), add = 0;
        for (int i = 0; i < len; i++) {
            int x = s[i] - 'a';
            if (!tree[add].ch[x]) {
                tree.emplace_back();
                tree[add].ch[x] = tree.size() - 1;
            }
            add = tree[add].ch[x];
        }
        tree[add].flag = id;
    }

    int findWord(string& s, int left, int right) {
        int add = 0;
        // 逆序查找
        for (int i = right; i >= left; i--) {
            int x = s[i] - 'a';
            if (!tree[add].ch[x]) {
                return -1;
            }
            add = tree[add].ch[x];
        }
        return tree[add].flag;
    }

    // 判断是否为回文串
    bool isPalindrome(string& s, int left, int right) {
        int len = right - left + 1;
        for (int i = 0; i < len / 2; i++) {
            if (s[left + i] != s[right - i]) {
                return false;
            }
        }
        return true;
    }

    vector<vector<int>> palindromePairs(vector<string>& words) {
        tree.emplace_back(node());
        int n = words.size();
        for (int i = 0; i < n; i++) {
            insert(words[i], i);
        }
        vector<vector<int>> ret;
        // 遍历每个 word
        for (int i = 0; i < n; i++) {
            int m = words[i].size();
            // 遍历 word 中的每个字符，作为 t1, t2 的切分点
            for (int j = 0; j <= m; j++) {
                // 后半部分回文，需要找前半部分的逆序是否存在
                if (isPalindrome(words[i], j, m - 1)) {
                    int left_id = findWord(words[i], 0, j - 1);
                    if (left_id != -1 && left_id != i) {
                        ret.push_back({i, left_id});
                    }
                }
                // 前半部分回文，需要找后半部分的逆序是否存在
                if (j && isPalindrome(words[i], 0, j - 1)) {
                    int right_id = findWord(words[i], j, m - 1);
                    if (right_id != -1 && right_id != i) {
                        ret.push_back({right_id, i});
                    }
                }
            }
        }
        return ret;
    }
};
