// @File   : 111_minDepth.cpp
// @Source : https://leetcode-cn.com/problems/minimum-depth-of-binary-tree
// @Title  : 二叉树的最小深度
// @Auther : sun_ds
// @Date   : 2019/10/17

/*  题目描述：
    给定一个二叉树，找出其最小深度。

    最小深度是从根节点到最近叶子节点的最短路径上的节点数量。

    说明: 叶子节点是指没有子节点的节点。

    示例:

    给定二叉树 [3,9,20,null,null,15,7],

        3
       / \
      9  20
        /  \
       15   7
    返回它的最小深度  2.



    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/minimum-depth-of-binary-tree
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/*
 * 二叉树的最小深度
 * 1.BFS，找到第一个叶子节点即可返回(队列实现/递归)
 * 2.递归实现，分治思想。
 * 3.深度优先搜索加剪枝
 *
 * 求二叉树最大、最小深度都可使用递归求解
 *
 *
 * 二叉树遍历：https://www.cnblogs.com/llhthinker/p/4747962.html
 * 二叉树遍历三种方法：
 * 1.递归实现(前序遍历)
 *
 * 2.栈和队列实现
 * BFS 宽度优先搜索 层序遍历
 * 使用 queue
 * queue<pair<TreeNode* ,int>> q
 * q.push(make_pair(root,i))
 * q.front().first q.front().second
 *
 * DFS 深度优先搜索 前序遍历
 * 使用 stack
 * stack<pair<TreeNode* ,int>> s
 * s.push(make_pair(root,i))
 * s.top().first s.top().second
 *
 * 3.Morris算法(待)
 *
 */


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */




//class Solution {
//public:
//    int minDepth(TreeNode* root) {
//        if(!root)
//            return 0;
//
//        queue<TreeNode*> q;
//        queue<int> q2;
//        q.push(root);
//        q2.push(1);
//        while(!q.empty()){
//            if((!q.front()->left)&&(!q.front()->right)) return q2.front();
//            if(q.front()->left){
//                q.push(q.front()->left);
//                q2.push(q2.front()+1);
//            }
//            if(q.front()->right){
//                q.push(q.front()->right);
//                q2.push(q2.front()+1);
//            }
//            q.pop();
//            q2.pop();
//        }
//        return 0;
//
//    }
//};



//class Solution {
//public:
//    int minDepth(TreeNode* root) {
//        if(!root)
//            return 0;
//        int left_depth = minDepth(root->left);
//        int right_depth = minDepth(root->right);
//        if(root->left&&root->right)
//            return 1 + min(left_depth,right_depth);
//        else
//            return 1 + left_depth + right_depth;
//    }
//};


class Solution {
public:
    void findMinDepth(TreeNode *root, int cur, int &ans){
        if(ans <= cur) return;
        if(!root->left && !root->right){
            ans = cur;
            return;
        }
        if(root->left)
            findMinDepth(root->left, cur+1, ans);
        if(root->right)
            findMinDepth(root->right, cur+1, ans);
    }
    int minDepth(TreeNode* root) {
        int ans = INT_MAX;
        if(!root) return 0;
        findMinDepth(root, 1, ans);
        return ans;
    }
};
