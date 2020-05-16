// @File   : 662_widthOfBinaryTree.cpp
// @Source : https://leetcode-cn.com/problems/maximum-width-of-binary-tree/
// @Title  : 662. 二叉树最大宽度
// @Auther : sun_ds
// @Date   : 2020/5/16

/**  题目描述：
    给定一个二叉树，编写一个函数来获取这个树的最大宽度。树的宽度是所有层中的最大宽度。这个二叉树与满二叉树（full binary tree）结构相同，但一些节点为空。

    每一层的宽度被定义为两个端点（该层最左和最右的非空节点，两端点间的null节点也计入长度）之间的长度。

    示例 1:

    输入:

               1
             /   \
            3     2
           / \     \
          5   3     9

    输出: 4
    解释: 最大值出现在树的第 3 层，宽度为 4 (5,3,null,9)。
    示例 2:

    输入:

              1
             /
            3
           / \
          5   3

    输出: 2
    解释: 最大值出现在树的第 3 层，宽度为 2 (5,3)。
    示例 3:

    输入:

              1
             / \
            3   2
           /
          5

    输出: 2
    解释: 最大值出现在树的第 2 层，宽度为 2 (3,2)。
    示例 4:

    输入:

              1
             / \
            3   2
           /     \
          5       9
         /         \
        6           7
    输出: 8
    解释: 最大值出现在树的第 4 层，宽度为 8 (6,null,null,null,null,null,null,7)。
    注意: 答案在32位有符号整数的表示范围内。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/maximum-width-of-binary-tree
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.bfs
 * 构建成完全二叉树的形式。
 * 层序遍历，记录每层最左端的节点位置，当前层所有节点位置与该位置相减，即为当前层的最大宽度。
 * 定义三元组，保存节点、深度和位置。
 * 深度可以省略，使用层序遍历中，一层一个 for 循环即可。
 *
 * 本题数据有毒，完全二叉树位置可能会爆，必须有 unsigned long long 才行。
 *
 * 2.dfs
 * dfs 先序遍历。每次第一个到达新层的节点就是当前层的最左端节点。
 * 使用 map 存储每一个层的最左端节点的索引。
 * 遍历，得到最大的宽度。
 *
 *
 */


//bfs
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
struct struct_node{
    TreeNode *node;
    unsigned long long depth,pos;
    struct_node (TreeNode *_node,unsigned long long _depth,unsigned long long _pos):node(_node),depth(_depth),pos(_pos){}
};
class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        if(root==nullptr) return 0;
        queue<struct_node> q;
        q.push(struct_node(root,0,0));
        int cur_depth = -1;
        unsigned long long cur_left = 0;
        unsigned long long res = 0;
        while(!q.empty()){
            auto temp = q.front();
            q.pop();
            if(temp.depth != cur_depth){
                cur_depth = temp.depth;
                cur_left = temp.pos;
            }
            res = max(temp.pos - cur_left + 1,res);
            if(temp.node->left!=nullptr){
                //由于 pos 是从 0 开始的，pos 是标准的完全二叉树索引
                q.push(struct_node(temp.node->left,temp.depth+1,temp.pos*2+1));
                //由于 pos 是从 0 开始的，pos 是每一层都从 0 开始的。由于是一层一层遍历的，所以也不会有影响。反而是 pos 不那么容易越界。
//                q.push(struct_node(temp.node->left,temp.depth+1,temp.pos*2));
            }

            if(temp.node->right!=nullptr){
                q.push(struct_node(temp.node->right,temp.depth+1,temp.pos*2+2));
//                q.push(struct_node(temp.node->left,temp.depth+1,temp.pos*2+1));
            }
        }
        return res;
    }
};

//dfs
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    unsigned long long res = 0;
    map<int,unsigned long long> m;
    void dfs(TreeNode* root,int depth,unsigned long long pos){
        if(root==nullptr) return;
        if(m.count(depth)==0){
            m[depth] = pos;
        }
        res = max(res,pos - m[depth] + 1);
        dfs(root->left,depth+1,pos*2+1);
        dfs(root->right,depth+1,pos*2+2);
    }
    int widthOfBinaryTree(TreeNode* root) {
        dfs(root,0,0);
        return res;
    }
};