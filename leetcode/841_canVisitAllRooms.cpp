// @File   : 841_canVisitAllRooms.cpp
// @Source : https://leetcode-cn.com/problems/keys-and-rooms/
// @Title  : 841. 钥匙和房间
// @Auther : sun_ds
// @Date   : 2020/9/1

/**  题目描述：
    有 N 个房间，开始时你位于 0 号房间。每个房间有不同的号码：0，1，2，...，N-1，并且房间里可能有一些钥匙能使你进入下一个房间。

    在形式上，对于每个房间 i 都有一个钥匙列表 rooms[i]，每个钥匙 rooms[i][j] 由 [0,1，...，N-1] 中的一个整数表示，其中 N = rooms.length。 钥匙 rooms[i][j] = v 可以打开编号为 v 的房间。

    最初，除 0 号房间外的其余所有房间都被锁住。

    你可以自由地在房间之间来回走动。

    如果能进入每个房间返回 true，否则返回 false。

    示例 1：

    输入: [[1],[2],[3],[]]
    输出: true
    解释:
    我们从 0 号房间开始，拿到钥匙 1。
    之后我们去 1 号房间，拿到钥匙 2。
    然后我们去 2 号房间，拿到钥匙 3。
    最后我们去了 3 号房间。
    由于我们能够进入每个房间，我们返回 true。
    示例 2：

    输入：[[1,3],[3,0,1],[2],[0]]
    输出：false
    解释：我们不能进入 2 号房间。
    提示：

    1 <= rooms.length <= 1000
    0 <= rooms[i].length <= 1000
    所有房间中的钥匙数量总计不超过 3000。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/keys-and-rooms
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.dfs
 *  从 0 开始遍历整张图，记录到达的节点个数。
 *  其中，使用 vis 记录节点是否被访问过，防止重复记录。
 *  最后判断访问的节点个数是否等于 n
 *
 *  时间复杂度 O(M+N)
 *  空间复杂度 O(N)
 *
 * 2.并查集
 *  dfs + 并查集
 *  dfs 遍历，使用并查集记录各个节点的连通性。
 *  最后判断联通分量个数。
 *
 */

class Solution {
public:
    vector<int> vis;
    int num;

    void dfs(vector<vector<int>>& rooms, int x) {
        vis[x] = true;
        num++;
        for (auto& it : rooms[x]) {
            if (!vis[it]) {
                dfs(rooms, it);
            }
        }
    }

    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int n = rooms.size();
        num = 0;
        vis.resize(n);
        dfs(rooms, 0);
        return num == n;
    }
};

// dfs + 并查集
class Solution {
private:
    struct UnionFind{
        int count;
        vector<int> parent;

        UnionFind(int n){
            parent.resize(n);
            count = n;
            for(int i=0;i<n;i++){
                parent[i] = i;
            }
        }
        int findParent(int i){
            if(parent[i] == i) return i;
            return parent[i] = findParent(parent[i]);
        }
        void connect(int x, int y){
            int x_p = findParent(x);
            int y_p = findParent(y);
            if(x_p == y_p) return;
            parent[x_p] = y_p;
            count--;
        }
    };
public:
    vector<int> vis;

    void dfs(vector<vector<int>>& rooms, int x, UnionFind& uf) {
        if(vis[x]) return;
        vis[x] = true;
        for (auto& it : rooms[x]) {
            uf.connect(x, it);
            dfs(rooms, it, uf);
        }
    }

    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int n = rooms.size();
        UnionFind uf(n);
        vis.resize(n);
        dfs(rooms, 0, uf);
        return uf.count == 1;
    }
};