// @File   : 104_maxDepth.cpp
// @Source : https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/
// @Title  : 二叉树的最大深度
// @Auther : sun_ds
// @Date   : 2019/10/17

/*  题目描述：
    给定一个二叉树，找出其最大深度。

    二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。

    说明: 叶子节点是指没有子节点的节点。

    示例：
    给定二叉树 [3,9,20,null,null,15,7]，

        3
       / \
      9  20
        /  \
       15   7
    返回它的最大深度 3 。



    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/maximum-depth-of-binary-tree
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/*
 * 二叉树最大深度
 * 1.递归实现
 * 2.通过堆栈来实现(dfs，bfs)
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
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(root==nullptr)
            return 0;
        return 1 + max(maxDepth(root->left),maxDepth(root->right));
    }
};

//迭代
//stack dfs
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
    int maxDepth(TreeNode* root) {
        stack<pair<TreeNode*,int>> s;
        int res = 0;
        if(root) s.push(make_pair(root,1));
        while(!s.empty()){
            auto temp = s.top(); s.pop();
            auto node = temp.first;
            int dep = temp.second;
            res = max(res,dep);
            if(node->right){
                s.push(make_pair(node->right,dep+1));
            }
            if(node->left){
                s.push(make_pair(node->left,dep+1));
            }
        }
        return res;
    }
};
//queue bfs
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
    int maxDepth(TreeNode* root) {
        queue<pair<TreeNode*,int>> q;
        int res = 0;
        if(root) q.push(make_pair(root,1));
        while(!q.empty()){
            auto temp = q.front(); q.pop();
            auto node = temp.first;
            int dep = temp.second;
            res = max(res,dep);
            if(node->left){
                q.push(make_pair(node->left,dep+1));
            }
            if(node->right){
                q.push(make_pair(node->right,dep+1));
            }
        }
        return res;
    }
};
//queue 层序遍历
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
    int maxDepth(TreeNode* root) {
        queue<TreeNode*> q;
        int res = 0;
        if(root) q.push(root);
        TreeNode* temp;
        while(!q.empty()){
            res++;
            int len = q.size();
            for(int i=0;i<len;i++){
                temp = q.front(); q.pop();
                if(temp->left) q.push(temp->left);
                if(temp->right) q.push(temp->right);
            }
        }
        return res;
    }
};