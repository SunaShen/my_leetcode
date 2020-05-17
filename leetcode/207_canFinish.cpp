// @File   : 207_canFinish.cpp
// @Source : https://leetcode-cn.com/problems/course-schedule/
// @Title  : 207. 课程表
// @Auther : sun_ds
// @Date   : 2020/5/17

/**  题目描述：
    你这个学期必须选修 numCourse 门课程，记为 0 到 numCourse-1 。

    在选修某些课程之前需要一些先修课程。 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们：[0,1]

    给定课程总量以及它们的先决条件，请你判断是否可能完成所有课程的学习？

     

    示例 1:

    输入: 2, [[1,0]]
    输出: true
    解释: 总共有 2 门课程。学习课程 1 之前，你需要完成课程 0。所以这是可能的。
    示例 2:

    输入: 2, [[1,0],[0,1]]
    输出: false
    解释: 总共有 2 门课程。学习课程 1 之前，你需要先完成​课程 0；并且学习课程 0 之前，你还应先完成课程 1。这是不可能的。
     

    提示：

    输入的先决条件是由 边缘列表 表示的图形，而不是 邻接矩阵 。详情请参见图的表示法。
    你可以假定输入的先决条件中没有重复的边。
    1 <= numCourses <= 10^5

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/course-schedule
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.bfs 拓扑排序
 *  我们使用一个队列来进行广度优先搜索。初始时，所有入度为 0 的节点都被放入队列中，它们就是可以作为拓扑排序最前面的节点，并且它们之间的相对顺序是无关紧要的。
 *  在广度优先搜索的每一步中，取出队首的节点 u：
 *  记录值加一。
 *  移除 u 的所有出边，也就是将 u 的所有相邻节点的入度减少 1。如果某个相邻节点 v 的入度变为 0，那么我们就将 v 放入队列中。
 *  在广度优先搜索的过程结束后。如果计数值等于 n ，那么我们就找到了一种拓扑排序，否则说明图中存在环，也就不存在拓扑排序了。
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
 *
 * 时间复杂度 O(M+N)
 * 空间复杂度 O(M+N)
 * N 为课程数，M 为先修课程要求数
 *
 */


//bfs
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> edges(numCourses);//邻接表
        vector<int> indeg(numCourses);//入度
        int res = 0;
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
            res++;
            for(int k:edges[t]){
                indeg[k]--;
                if(indeg[k]==0) q.push(k);
            }
        }
        //判断是否能构成完整的拓扑排序
        return res == numCourses;
    }
};

//dfs
class Solution {
private:
    vector<vector<int>> edges;
    vector<int> visited;
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
        return true;
    }
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        edges.resize(numCourses);
        visited.resize(numCourses);
        for(auto i:prerequisites){
            edges[i[1]].push_back(i[0]);
        }
        for(int i=0;i<numCourses;i++){
            if(visited[i]==0){
                if(!dfs(i)) return false;
            }
        }
        return true;
    }
};

