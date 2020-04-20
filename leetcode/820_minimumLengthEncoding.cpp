// @File   : 820_minimumLengthEncoding.cpp
// @Source : https://leetcode-cn.com/problems/short-encoding-of-words/
// @Title  : 820. 单词的压缩编码
// @Auther : sun_ds
// @Date   : 2020/3/28

/**  题目描述：
    给定一个单词列表，我们将这个列表编码成一个索引字符串 S 与一个索引列表 A。

    例如，如果这个列表是 ["time", "me", "bell"]，我们就可以将其表示为 S = "time#bell#" 和 indexes = [0, 2, 5]。

    对于每一个索引，我们可以通过从字符串 S 中索引的位置开始读取字符串，直到 "#" 结束，来恢复我们之前的单词列表。

    那么成功对给定单词列表进行编码的最小字符串长度是多少呢？

     

    示例：

    输入: words = ["time", "me", "bell"]
    输出: 10
    说明: S = "time#bell#" ， indexes = [0, 2, 5] 。
     

    提示：

    1 <= words.length <= 2000
    1 <= words[i].length <= 7
    每个单词都是小写字母 。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/short-encoding-of-words
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.字典树 找后缀
 * 先将word按照长度降序排序
 * 构建字典树，将每个word倒序插入。
 * 如果遇到nullptr说明是新单词。结果加上word.size()+1
 * 否则结果不变。
 *
 * 注意字典树结构。
 *
 * 2.逆字典序排序
 *  后缀相同的排在一起。前面的可以被后面包含。
 *
 *
 */

class TrieNode{
public:
    char val;
    TrieNode* child[26];
    TrieNode(){
        for(int i=0;i<26;i++) child[i] = nullptr;
    }
};
class Trie{
    TrieNode* root;
public:
    Trie(){
        root = new TrieNode();
    }
    int insert(string word){
        TrieNode* cur = root;
        bool flag = false;
        for(int i=word.size()-1;i>=0;i--){
            int c = word[i] - 'a';
            if(cur->child[c]==nullptr){
                flag = true;
                cur->child[c] = new TrieNode();
            }
            cur = cur->child[c];
        }
        return flag ? word.size()+1 : 0;
    }
};
class Solution {
public:
    int minimumLengthEncoding(vector<string>& words) {
        vector<string> list;
        //先排序
        sort(words.begin(),words.end(),[](const string & a, const string & b){
            return a.size()>b.size();
        });
        int res = 0;
        Trie *trie = new Trie();
        for(int i=0;i<words.size();i++){
            res += trie->insert(words[i]);
        }
        return res;
    }
};

class Solution {
public:
    //排序 每个单词倒序字典序
    static bool compare(string& s1, string& s2) {
        int N1 = s1.length();
        int N2 = s2.length();
        for (int i = 0; i < min(N1, N2); i++) {
            char c1 = s1[N1-1-i];
            char c2 = s2[N2-1-i];
            if (c1 != c2) {
                return c1 < c2;
            }
        }
        return N1 < N2;
    }
    int minimumLengthEncoding(vector<string>& words) {
        int N = words.size();
        // 逆序字典序排序
        sort(words.begin(), words.end(), compare);

        int res = 0;
        for (int i = 0; i < N; i++) {
            if (i+1 < N && endsWith(words[i+1], words[i])) {
                // 当前单词是下一个单词的后缀，丢弃
            } else {
                res += words[i].length() + 1;
            }
        }
        return res;
    }

    bool endsWith(string& s, string& t) {
        int N1 = s.length();
        int N2 = t.length();
        if (N1 < N2) {
            return false;
        }
        for (int i = 0; i < N2; i++) {
            //比较后缀是否相同
            if (s[N1-N2+i] != t[i]) {
                return false;
            }
        }
        return true;
    }
};


