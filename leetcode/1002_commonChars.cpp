// @File   : 1002_commonChars.cpp
// @Source : https://leetcode-cn.com/problems/find-common-characters/
// @Title  : 1002. 查找常用字符
// @Auther : sun_ds
// @Date   : 2020/10/14

/**  题目描述：
    给定仅有小写字母组成的字符串数组 A，返回列表中的每个字符串中都显示的全部字符（包括重复字符）组成的列表。例如，如果一个字符在每个字符串中出现 3 次，但不是 4 次，则需要在最终答案中包含该字符 3 次。

    你可以按任意顺序返回答案。

     

    示例 1：

    输入：["bella","label","roller"]
    输出：["e","l","l"]
    示例 2：

    输入：["cool","lock","cook"]
    输出：["c","o"]
     

    提示：

    1 <= A.length <= 100
    1 <= A[i].length <= 100
    A[i][j] 是小写字母

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/find-common-characters
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1. 计数
 *  分别使用两个 vector<int>(26,0) 计数 count 和 mincount
 *  遍历各个单词，使用 count 统计单词中各个字符出现次数。
 *  使用全局 mincount 记录每个 count 中字符出现的最小值
 *
 */

class Solution {
public:
    vector<string> commonChars(vector<string>& A) {
        vector<int> count(26, 0);
        vector<int> mincount(26, INT_MAX);
        for(const auto& word:A){
            fill(count.begin(), count.end(), 0);
            for(auto c:word){
                count[c - 'a']++;
            }
            for(int i=0;i<26;i++){
                mincount[i] = min(mincount[i], count[i]);
            }
        }
        vector<string> res;
        for(int i=0;i<26;i++){
            for(int k=0;k<mincount[i];k++){
                // emplace_back
                res.emplace_back(1, 'a' + i);
            }
        }
        return res;
    }
};
