// @File   : 133_cloneGraph.cpp
// @Source : https://leetcode-cn.com/problems/clone-graph/
// @Title  : 133. 克隆图
// @Auther : sun_ds
// @Date   : 2020/8/12

/**  题目描述：
    给你无向 连通 图中一个节点的引用，请你返回该图的 深拷贝（克隆）。

    图中的每个节点都包含它的值 val（int） 和其邻居的列表（list[Node]）。

    class Node {
        public int val;
        public List<Node> neighbors;
    }
     

    测试用例格式：

    简单起见，每个节点的值都和它的索引相同。例如，第一个节点值为 1（val = 1），第二个节点值为 2（val = 2），以此类推。该图在测试用例中使用邻接列表表示。

    邻接列表 是用于表示有限图的无序列表的集合。每个列表都描述了图中节点的邻居集。

    给定节点将始终是图中的第一个节点（值为 1）。你必须将 给定节点的拷贝 作为对克隆图的引用返回。

     

    示例 1：



    输入：adjList = [[2,4],[1,3],[2,4],[1,3]]
    输出：[[2,4],[1,3],[2,4],[1,3]]
    解释：
    图中有 4 个节点。
    节点 1 的值是 1，它有两个邻居：节点 2 和 4 。
    节点 2 的值是 2，它有两个邻居：节点 1 和 3 。
    节点 3 的值是 3，它有两个邻居：节点 2 和 4 。
    节点 4 的值是 4，它有两个邻居：节点 1 和 3 。
    示例 2：



    输入：adjList = [[]]
    输出：[[]]
    解释：输入包含一个空列表。该图仅仅只有一个值为 1 的节点，它没有任何邻居。
    示例 3：

    输入：adjList = []
    输出：[]
    解释：这个图是空的，它不含任何节点。
    示例 4：



    输入：adjList = [[2],[1]]
    输出：[[2],[1]]
     

    提示：

    节点数不超过 100 。
    每个节点值 Node.val 都是唯一的，1 <= Node.val <= 100。
    无向图是一个简单图，这意味着图中没有重复的边，也没有自环。
    由于图是无向的，如果节点 p 是节点 q 的邻居，那么节点 q 也必须是节点 p 的邻居。
    图是连通图，你可以从给定节点访问到所有节点。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/clone-graph
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1. dfs + 哈希
 *  深拷贝需要重新创建新的节点。
 *  使用 dfs 遍历整个图。
 *  并使用哈希unordered_map<Node*, Node*> visited 记录老节点与新节点的对应关系(可作为终止条件，防止死循环)
 *
 *  遇到新节点就创建节点，并填充每个新节点的邻接表。遇到老节点直接返回，
 *
 *  dfs 创建节点和节点相邻的节点一直递归下去
 *
 *  最终，整个图中每个节点被遍历一次，得到深拷贝。
 *
 *  时间复杂度 O(N)
 *  空间复杂度 O(N)
 *
 *
 * 2. bfs + 哈希
 *  使用 bfs 的遍历结构遍历整张图。
 *  使用 unordered_map<Node*, Node*> visited 记录已经创建过的节点。
 *
 *  bfs 创建当前节点当如队列中，轮到自己时再创建他相邻的节点
 *
 *  时间复杂度 O(N)
 *  空间复杂度 O(N)
 *
 */

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;

    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }

    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }

    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    // 全局
    unordered_map<Node*, Node*> visited;
    Node* cloneGraph(Node* node) {
        if (node == nullptr) {
            return node;
        }

        // 如果该节点已经被访问过了，则直接从哈希表中取出对应的克隆节点返回
        if (visited.find(node) != visited.end()) {
            return visited[node];
        }

        // 克隆节点，注意到为了深拷贝我们不会克隆它的邻居的列表
        Node* cloneNode = new Node(node->val);
        // 哈希表存储
        visited[node] = cloneNode;

        // 遍历该节点的邻居并更新克隆节点的邻居列表
        for (auto& neighbor: node->neighbors) {
            cloneNode->neighbors.emplace_back(cloneGraph(neighbor));
        }
        return cloneNode;
    }
};

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;

    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }

    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }

    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (node == nullptr) {
            return node;
        }

        unordered_map<Node*, Node*> visited;

        // 将题目给定的节点添加到队列
        queue<Node*> Q;
        Q.push(node);
        // 克隆第一个节点并存储到哈希表中
        visited[node] = new Node(node->val);

        // 广度优先搜索
        while (!Q.empty()) {
            // 取出队列的头节点
            auto n = Q.front();
            Q.pop();
            // 遍历该节点的邻居
            for (auto& neighbor: n->neighbors) {
                if (visited.find(neighbor) == visited.end()) {
                    // 如果没有被访问过，就克隆并存储在哈希表中
                    visited[neighbor] = new Node(neighbor->val);
                    // 将邻居节点加入队列中
                    Q.push(neighbor);
                }
                // 更新当前节点的邻居列表
                visited[n]->neighbors.emplace_back(visited[neighbor]);
            }
        }

        return visited[node];
    }
};
