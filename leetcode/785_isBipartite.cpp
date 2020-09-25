// @File   : 785_isBipartite.cpp
// @Source : https://leetcode-cn.com/problems/is-graph-bipartite/
// @Title  : 785. 判断二分图
// @Auther : sun_ds
// @Date   : 2020/7/16

/**  题目描述：
    给定一个无向图graph，当这个图为二分图时返回true。

    如果我们能将一个图的节点集合分割成两个独立的子集A和B，并使图中的每一条边的两个节点一个来自A集合，一个来自B集合，我们就将这个图称为二分图。

    graph将会以邻接表方式给出，graph[i]表示图中与节点i相连的所有节点。每个节点都是一个在0到graph.length-1之间的整数。这图中没有自环和平行边： graph[i] 中不存在i，并且graph[i]中没有重复的值。


    示例 1:
    输入: [[1,3], [0,2], [1,3], [0,2]]
    输出: true
    解释:
    无向图如下:
    0----1
    |    |
    |    |
    3----2
    我们可以将节点分成两组: {0, 2} 和 {1, 3}。

    示例 2:
    输入: [[1,2,3], [0,2], [0,1,3], [0,2]]
    输出: false
    解释:
    无向图如下:
    0----1
    | \  |
    |  \ |
    3----2
    我们不能将节点分割成两个独立的子集。
    注意:

    graph 的长度范围为 [1, 100]。
    graph[i] 中的元素的范围为 [0, graph.length - 1]。
    graph[i] 不会包含 i 或者有重复的值。
    图是无向的: 如果j 在 graph[i]里边, 那么 i 也会在 graph[j]里边。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/is-graph-bipartite
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1. bfs
 *  使用 color 记录染色 -1，1， 0 表示未染色
 *  从第一个点扩散，不断扩展，并且每一层颜色取反，若已被染色且颜色相同，直接返回 false；
 *
 *  时间复杂度 O(M+N)
 *  空间复杂度 O(N)
 *  其中 N 和 M 分别是无向图中的点数和边数。
 *
 *
 * 2. 并查集
 *  分成两类，相连的两个节点必定不属于同一类。
 *
 */

class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> color(n,0);
        for(int i=0;i<n;i++){
            if(color[i] == 0){
                queue<int> q;
                q.push(i);
                color[i] = 1;
                while(!q.empty()){
                    int temp = q.front();
                    q.pop();
                    for(auto j:graph[temp]){
                        if(color[j] == color[temp]){
                            return false;
                        }
                        if(color[j] == 0){
                            color[j] = -color[temp];
                            q.push(j);
                        }
                    }
                }
            }
        }
        return true;
    }
};


class Solution {
public:
    struct unionFind{
        int count;
        vector<int> parent;
        unionFind(int n){
            count = n;
            parent.resize(n);
            for(int i=0;i<n;i++){
                parent[i] = i;
            }
        }
        int findParent(int index){
            if(parent[index] == index) return index;
            return parent[index] = findParent(parent[index]);
        }
        void connect(int x, int y){
            int xp = findParent(x);
            int yp = findParent(y);
            if(xp == yp) return;
            parent[xp] = yp;
            count--;
        }
        bool isConnect(int x, int y){
            return findParent(x) == findParent(y);
        }
    };
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        unionFind uf(n);
        for(int i=0;i<graph.size();i++){
            for(auto p : graph[i]){
                if(uf.isConnect(i, p)){
                    return false;
                }
                uf.connect(graph[i][0], p);
            }
        }
        return true;
    }
};
