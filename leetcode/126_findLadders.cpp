// @File   : 126_findLadders.cpp
// @Source : https://leetcode-cn.com/problems/word-ladder-ii/
// @Title  : 126. 单词接龙 II
// @Auther : sun_ds
// @Date   : 2020/6/7

/**  题目描述：
    给定两个单词（beginWord 和 endWord）和一个字典 wordList，找出所有从 beginWord 到 endWord 的最短转换序列。转换需遵循如下规则：

    每次转换只能改变一个字母。
    转换过程中的中间单词必须是字典中的单词。
    说明:

    如果不存在这样的转换序列，返回一个空列表。
    所有单词具有相同的长度。
    所有单词只由小写字母组成。
    字典中不存在重复的单词。
    你可以假设 beginWord 和 endWord 是非空的，且二者不相同。
    示例 1:

    输入:
    beginWord = "hit",
    endWord = "cog",
    wordList = ["hot","dot","dog","lot","log","cog"]

    输出:
    [
      ["hit","hot","dot","dog","cog"],
      ["hit","hot","lot","log","cog"]
    ]
    示例 2:

    输入:
    beginWord = "hit"
    endWord = "cog"
    wordList = ["hot","dot","dog","lot","log"]

    输出: []

    解释: endWord "cog" 不在字典中，所以不存在符合要求的转换序列。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/word-ladder-ii
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 *
 * 1.图+bfs
 * 将所有单词当做图的节点，各单词之间是否只差了一个字符作为他们之间是否有边的条件。
 * 实用邻接矩阵记录图。
 * 使用 bfs 搜索路径。queue 中存储的是每一条路径。若到达目标单词，则组合成字符串并存入结果，否则，遍历与最后节点相邻的节点，更新他们的距离。
 * 最终得到所有的能够到达目标单词的最短路径。
 *
 *
 */

const int INF = 1 << 20;

class Solution {
private:
    unordered_map<string, int> wordId;
    vector<string> idWord;
    vector<vector<int>> edges;
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        int id = 0;
        for (const string& word : wordList) {
            // 过滤重复元素
            if (!wordId.count(word)) {
                // word -> id
                wordId[word] = id++;
                // id -> word
                idWord.push_back(word);
            }
        }
        // endWord 不在 wordList 中，肯定无法转换
        if (!wordId.count(endWord)) {
            return {};
        }
        // 将 beginWord 也当做 wordList 中的一员
        if (!wordId.count(beginWord)) {
            wordId[beginWord] = id++;
            idWord.push_back(beginWord);
        }
        // 无向图的邻接矩阵
        edges.resize(idWord.size());
        for (int i = 0; i < idWord.size(); i++) {
            for (int j = i + 1; j < idWord.size(); j++) {
                // 若两单词之间只差一个字符，则添加边，表示可以转换
                if (transformCheck(idWord[i], idWord[j])) {
                    edges[i].push_back(j);
                    edges[j].push_back(i);
                }
            }
        }
        const int dest = wordId[endWord];
        vector<vector<string>> res;
        // 队列中存储着各个路径
        queue<vector<int>> q;
        // 初始各节点与起始节点距离为无穷大
        vector<int> cost(id, INF);
        q.push(vector<int>{wordId[beginWord]});
        cost[wordId[beginWord]] = 0;
        // bfs
        while (!q.empty()) {
            vector<int> now = q.front();
            q.pop();
            // 路径最后一个元素
            int last = now.back();
            if (last == dest) {
                // 若最后元素为目标元素，则构建 string 存入结果。
                vector<string> tmp;
                for (int index : now) {
                    tmp.push_back(idWord[index]);
                }
                res.push_back(tmp);
            } else {
                // 将于最后元素相邻的节点都
                for (int i = 0; i < edges[last].size(); i++) {
                    int to = edges[last][i];
                    // 使用当前路径距离更短
                    // 用此判断保证到达 dest 的都是最短的路径。
                    if (cost[last] + 1 <= cost[to]) {
                        cost[to] = cost[last] + 1;
                        vector<int> tmp(now);
                        tmp.push_back(to);
                        q.push(tmp);
                    }
                }
            }
        }
        return res;
    }

    bool transformCheck(const string& str1, const string& str2) {
        int differences = 0;
        for (int i = 0; i < str1.size() && differences < 2; i++) {
            if (str1[i] != str2[i]) {
                ++differences;
            }
        }
        return differences == 1;
    }
};

