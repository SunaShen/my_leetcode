// @File   : 210_findOrder.cpp
// @Source : https://leetcode-cn.com/problems/course-schedule-ii/
// @Title  : 210. 课程表 II
// @Auther : sun_ds
// @Date   : 2020/5/17

/**  题目描述：
    现在你总共有 n 门课需要选，记为 0 到 n-1。

    在选修某些课程之前需要一些先修课程。 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们: [0,1]

    给定课程总量以及它们的先决条件，返回你为了学完所有课程所安排的学习顺序。

    可能会有多个正确的顺序，你只要返回一种就可以了。如果不可能完成所有课程，返回一个空数组。

    示例 1:

    输入: 2, [[1,0]]
    输出: [0,1]
    解释: 总共有 2 门课程。要学习课程 1，你需要先完成课程 0。因此，正确的课程顺序为 [0,1] 。
    示例 2:

    输入: 4, [[1,0],[2,0],[3,1],[3,2]]
    输出: [0,1,2,3] or [0,2,1,3]
    解释: 总共有 4 门课程。要学习课程 3，你应该先完成课程 1 和课程 2。并且课程 1 和课程 2 都应该排在课程 0 之后。
         因此，一个正确的课程顺序是 [0,1,2,3] 。另一个正确的排序是 [0,2,1,3] 。
    说明:

    输入的先决条件是由边缘列表表示的图形，而不是邻接矩阵。详情请参见图的表示法。
    你可以假定输入的先决条件中没有重复的边。
    提示:

    这个问题相当于查找一个循环是否存在于有向图中。如果存在循环，则不存在拓扑排序，因此不可能选取所有课程进行学习。
    通过 DFS 进行拓扑排序 - 一个关于Coursera的精彩视频教程（21分钟），介绍拓扑排序的基本概念。
    拓扑排序也可以通过 BFS 完成。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/course-schedule-ii
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 *
 * 1.bfs 拓扑排序
 *  我们使用一个队列来进行广度优先搜索。初始时，所有入度为 0 的节点都被放入队列中，它们就是可以作为拓扑排序最前面的节点，并且它们之间的相对顺序是无关紧要的。
 *  在广度优先搜索的每一步中，取出队首的节点 u：
 *  将 u 放入答案中；
 *  移除 u 的所有出边，也就是将 u 的所有相邻节点的入度减少 1。如果某个相邻节点 v 的入度变为 0，那么我们就将 v 放入队列中。
 *  在广度优先搜索的过程结束后。如果答案中包含了这 n 个节点，那么我们就找到了一种拓扑排序，否则说明图中存在环，也就不存在拓扑排序了。
 *
 * 时间复杂度 O(M+N)
 * 空间复杂度 O(M+N)
 * N 为课程数，M 为先修课程要求数
 *
 * 2.dfs 有向图是否无环
 * visited记录是否被访问过。
 * 每个节点状态有三种情况
 * 1）未搜索
 * 2）搜索中
 * 3）已完成
 *
 * 起始随机选取一个节点。
 * 若其相邻节点是未搜索就进行递归。
 * 若其相邻节点是搜索中，证明有环。 失败。 搜索中说明这个相邻节点在当前节点前面，而此时当前节点有可以到达这个相邻节点，所以构成了环。
 * 若其相邻接点全是已完成，则表示相邻接点都执行完成，回溯回来了。此时将当前节点置为已完成，并将当前节点存入结果。
 *
 * 使用 vector res 来模拟 stack。
 * 最后得到结果 res，输出他的反序即可。即是满足条件的序列。
 *
 * 时间复杂度 O(M+N)
 * 空间复杂度 O(M+N)
 * N 为课程数，M 为先修课程要求数
 *
 *
 *
 */


//bfs
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> edges(numCourses);//邻接表
        vector<int> indeg(numCourses);//入度
        vector<int> res;
        for(auto i:prerequisites){
            edges[i[1]].push_back(i[0]);
            indeg[i[0]]++;
        }
        queue<int> q;
        for(int i=0;i<numCourses;i++){
            if(indeg[i]==0) q.push(i);
        }
        while(!q.empty()){
            int t = q.front();
            q.pop();
            res.push_back(t);
            for(int k:edges[t]){
                indeg[k]--;
                if(indeg[k]==0) q.push(k);
            }
        }
        //判断是否能构成完整的拓扑排序
        if(res.size() != numCourses) return {};
        return res;
    }
};

//dfs
class Solution {
private:
    vector<vector<int>> edges;
    vector<int> visited;
    vector<int> res;
public:
    bool dfs(int i){
        visited[i] = 1; //正在搜索
        for(int k:edges[i]){
            if(visited[k]==0){
                if(!dfs(k)) return false;
            }else if(visited[k]==1){//有环了
                return false;
            }
        }
        visited[i] = 2; //已完成
        res.push_back(i);
        return true;
    }
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        edges.resize(numCourses);
        visited.resize(numCourses);
        for(auto i:prerequisites){
            edges[i[1]].push_back(i[0]);
        }
        for(int i=0;i<numCourses;i++){
            if(visited[i]==0){
                if(!dfs(i)) return {};
            }
        }
        return vector<int>(res.rbegin(),res.rend());
    }
};