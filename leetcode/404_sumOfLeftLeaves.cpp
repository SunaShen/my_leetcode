// @File   : 404_sumOfLeftLeaves.cpp
// @Source : https://leetcode-cn.com/problems/sum-of-left-leaves/
// @Title  : 404. 左叶子之和
// @Auther : sun_ds
// @Date   : 2020/9/19

/**  题目描述：
    计算给定二叉树的所有左叶子之和。

    示例：

        3
       / \
      9  20
        /  \
       15   7

    在这个二叉树中，有两个左叶子，分别是 9 和 15，所以返回 24

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/sum-of-left-leaves
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1. 递归
 *  使用 flag 记录当前节点是父节点的左孩子还是右孩子
 *  当 flag 显示是左孩子，且当前节点为叶子节点，则加上当前的值。
 *
 *  时间复杂度 O(N) N为节点个数
 *  空间复杂度 O(N) 递归栈空间，最坏情况下链式结构
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
private:
    int res;
public:
    void dfs(TreeNode* root, bool flag){
        if(root->left == nullptr && root->right == nullptr && flag){
            res += root->val;
            return;
        }
        if(root->left != nullptr){
            dfs(root->left, true);
        }
        if(root->right != nullptr){
            dfs(root->right, false);
        }
    }
    int sumOfLeftLeaves(TreeNode* root) {
        if(root == nullptr) return 0;
        dfs(root, false);
        return res;
    }
};

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
    int sumOfLeftLeaves(TreeNode* root) {
        if(root == nullptr) return 0;
        int l = 0;
        if(root->left != nullptr && root->left->left == nullptr && root->left->right == nullptr){
            l += root->left->val;
        }
        return l + sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);
    }
};
