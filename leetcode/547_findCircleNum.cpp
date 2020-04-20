// @File   : 547_findCircleNum.cpp
// @Source : https://leetcode-cn.com/problems/friend-circles/
// @Title  : 547. 朋友圈
// @Auther : sun_ds
// @Date   : 2020/4/12

/**  题目描述：
    班上有 N 名学生。其中有些人是朋友，有些则不是。他们的友谊具有是传递性。如果已知 A 是 B 的朋友，B 是 C 的朋友，那么我们可以认为 A 也是 C 的朋友。所谓的朋友圈，是指所有朋友的集合。

    给定一个 N * N 的矩阵 M，表示班级中学生之间的朋友关系。如果M[i][j] = 1，表示已知第 i 个和 j 个学生互为朋友关系，否则为不知道。你必须输出所有学生中的已知的朋友圈总数。

    示例 1:

    输入:
    [[1,1,0],
     [1,1,0],
     [0,0,1]]
    输出: 2
    说明：已知学生0和学生1互为朋友，他们在一个朋友圈。
    第2个学生自己在一个朋友圈。所以返回2。
    示例 2:

    输入:
    [[1,1,0],
     [1,1,1],
     [0,1,1]]
    输出: 1
    说明：已知学生0和学生1互为朋友，学生1和学生2互为朋友，所以学生0和学生2也是朋友，所以他们三个在一个朋友圈，返回1。
    注意：

    N 在[1,200]的范围内。
    对于所有学生，有M[i][i] = 1。
    如果有M[i][j] = 1，则有M[j][i] = 1。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/friend-circles
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.并查集
 *
 * 并查集包含 1.初始化 2.查找祖宗节点(递归) 3.合并
 *
 * 统计集合个数，遍历使用set统计祖宗节点。返回set的大小即为集合个数
 *
 */

class Solution {
public:
    int getp(vector<int> &set,int index){
        if(set[index]==index){
            return index;
        }else{
            set[index] = getp(set,set[index]);  //路径压缩
            return set[index];
        }
    }
    void merge(vector<int> &set,int index1,int index2){
        int i1 = getp(set,index1);
        int i2 = getp(set,index2);
        if(i1!=i2){
            set[i2] = i1;
        }
    }
    int findCircleNum(vector<vector<int>>& M) {
        int n = M.size();
        vector<int> set(n);
        for(int i=0;i<n;i++){
            set[i] = i;
        }
        for(int i=0;i<n;i++){
            for(int j=i;j<n;j++){
                if(M[i][j]==1){
                    merge(set,i,j);
                }
            }
        }
        unordered_set<int> count;
        for(int i=0;i<n;i++){
            count.insert(getp(set,i));
        }
        return count.size();
    }
};

class Solution {
public:
    int getp(vector<int> &set,int index){
        if(set[index]==index){
            return index;
        }else{
            set[index] = getp(set,set[index]);
            return set[index];
        }
    }
    void merge(vector<int> &set,int index1,int index2,int &count){
        int i1 = getp(set,index1);
        int i2 = getp(set,index2);
        if(i1!=i2){
            set[i2] = i1;
            count--;
        }
    }
    int findCircleNum(vector<vector<int>>& M) {
        int n = M.size();
        int count = n;
        vector<int> set(n);
        for(int i=0;i<n;i++){
            set[i] = i;
        }
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(M[i][j]==1){
                    merge(set,i,j,count);
                }
            }
        }
        return count;
    }
};


//java版并查集
//使用size记录当前集合节点数，使树尽量平衡
//使用路径压缩

//class UF {
//    // 连通分量个数
//private int count;
//    // 存储一棵树
//private int[] parent;
//    // 记录树的“重量”
//private int[] size;
//
//public UF(int n) {
//        this.count = n;
//        parent = new int[n];
//        size = new int[n];
//        for (int i = 0; i < n; i++) {
//            parent[i] = i;
//            size[i] = 1;
//        }
//    }
//
//public void union(int p, int q) {
//        int rootP = find(p);
//        int rootQ = find(q);
//        if (rootP == rootQ)
//            return;
//
//        // 小树接到大树下面，较平衡
//        if (size[rootP] > size[rootQ]) {
//            parent[rootQ] = rootP;
//            size[rootP] += size[rootQ];
//        } else {
//            parent[rootP] = rootQ;
//            size[rootQ] += size[rootP];
//        }
//        count--;
//    }
//
//public boolean connected(int p, int q) {
//        int rootP = find(p);
//        int rootQ = find(q);
//        return rootP == rootQ;
//    }
//
//private int find(int x) { //使用递归可以直接压缩到祖宗节点
//        while (parent[x] != x) {
//            // 进行路径压缩
//            parent[x] = parent[parent[x]];
//            x = parent[x];
//        }
//        return x;
//    }
//
//public int count() {
//        return count;
//    }
//}





