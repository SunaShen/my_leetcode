// @File   : 55-2_isBalanced.cpp
// @Source : https://leetcode-cn.com/problems/ping-heng-er-cha-shu-lcof/
// @Title  : 面试题55 - II. 平衡二叉树
// @Auther : sun_ds
// @Date   : 2020/4/3

/**  题目描述：
    输入一棵二叉树的根节点，判断该树是不是平衡二叉树。如果某二叉树中任意节点的左右子树的深度相差不超过1，那么它就是一棵平衡二叉树。

     

    示例 1:

    给定二叉树 [3,9,20,null,null,15,7]

        3
       / \
      9  20
        /  \
       15   7
    返回 true 。

    示例 2:

    给定二叉树 [1,2,2,3,3,null,null,4,4]

           1
          / \
         2   2
        / \
       3   3
      / \
     4   4
    返回 false 。

     

    限制：

    1 <= 树的结点个数 <= 10000
    注意：本题与主站 110 题相同：https://leetcode-cn.com/problems/balanced-binary-tree/



    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/ping-heng-er-cha-shu-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 后序遍历
 * 不满足平衡条件返回-1.提前结束。
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
    int func(TreeNode* root){
        if(root==nullptr) return 0;
        int l = func(root->left);
        int r = func(root->right);
        return l==-1||r==-1||abs(l-r)>1 ? -1 : max(l,r)+1;
    }
    bool isBalanced(TreeNode* root) {
        return func(root)!=-1;
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
    int func(TreeNode* root){
        if(root==nullptr) return 0;
        int l = func(root->left);
        if(l==-1) return -1; //提前剪枝
        int r = func(root->right);
        if(r==-1) return -1; //提前剪枝
        return abs(l-r)>1 ? -1 : max(l,r)+1;
    }
    bool isBalanced(TreeNode* root) {
        return func(root)!=-1;
    }
};