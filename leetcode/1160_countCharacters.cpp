// @File   : 1160_countCharacters.cpp
// @Source : https://leetcode-cn.com/problems/find-words-that-can-be-formed-by-characters/
// @Title  : 1160. 拼写单词
// @Auther : sun_ds
// @Date   : 2020/3/17

/**  题目描述：
    给你一份『词汇表』（字符串数组） words 和一张『字母表』（字符串） chars。

    假如你可以用 chars 中的『字母』（字符）拼写出 words 中的某个『单词』（字符串），那么我们就认为你掌握了这个单词。

    注意：每次拼写时，chars 中的每个字母都只能用一次。

    返回词汇表 words 中你掌握的所有单词的 长度之和。

     

    示例 1：

    输入：words = ["cat","bt","hat","tree"], chars = "atach"
    输出：6
    解释：
    可以形成字符串 "cat" 和 "hat"，所以答案是 3 + 3 = 6。
    示例 2：

    输入：words = ["hello","world","leetcode"], chars = "welldonehoneyr"
    输出：10
    解释：
    可以形成字符串 "hello" 和 "world"，所以答案是 5 + 5 = 10。
     

    提示：

    1 <= words.length <= 1000
    1 <= words[i].length, chars.length <= 100
    所有字符串中都仅包含小写英文字母

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/find-words-that-can-be-formed-by-characters
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 *
 * 1.map
 *  使用map分别记录单词和字母表的字符数，对比，如果单词中某字符数超过字符表中字符数，则不成功，否则将单词长度加入结果。
 * 2.vector
 *  由于对字母进行操作，所以可以使用长度26的vector，以字母顺序为下标，统计各字符出现次数。
 *
 */

//使用map
class Solution {
public:
    int countCharacters(vector<string>& words, string chars) {
        int n = words.size();
        map<char,int> m;
        m.clear();
        int res = 0;
        for(auto i:chars) m[i]++;
        for(int i=0;i<words.size();i++){
            map<char,int> temp = m;
            bool flag = true;
            for(auto k:words[i]){
                temp[k]--;
                if(temp[k]<0){
                    flag = false;
                    break;
                }
            }
            if(flag){
                res += words[i].size();
            }
        }
        return res;
    }
};

//使用vector
class Solution {
public:
    int countCharacters(vector<string>& words, string chars) {
        int n = words.size();
        int res = 0;
        vector<int> cha(26,0);
        for(auto c:chars) cha[c-'a']++;
        for(int i=0;i<words.size();i++){
            vector<int> temp(26,0);
            for(auto c:words[i]) temp[c-'a']++;
            bool flag = true;
            for(int j=0;j<26;j++){
                if(temp[j]>cha[j]){
                    flag = false;
                    break;
                }
            }
            if(flag) res += words[i].size();
        }
        return res;
    }
};

