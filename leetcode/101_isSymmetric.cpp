// @File   : 101_isSymmetric.cpp
// @Source : https://leetcode-cn.com/problems/symmetric-tree/
// @Title  : 101. 对称二叉树
// @Auther : sun_ds
// @Date   : 2020/3/11

/**  题目描述：
    给定一个二叉树，检查它是否是镜像对称的。

    例如，二叉树 [1,2,2,3,4,4,3] 是对称的。

        1
       / \
      2   2
     / \ / \
    3  4 4  3
    但是下面这个 [1,2,2,null,3,null,3] 则不是镜像对称的:

        1
       / \
      2   2
       \   \
       3    3
    说明:

    如果你可以运用递归和迭代两种方法解决这个问题，会很加分。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/symmetric-tree
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 判断是否是镜像二叉树
 *
 * 递归判断，func(n1->left,n2->right)&&func(n1->right,n2->left)
 *
 * 1.递归
 * 2.迭代 使用队列
 */


//递归
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
    bool func(TreeNode* n1,TreeNode* n2){
        if(n1==NULL||n2==NULL){
            if(n1==NULL&&n2==NULL) return true;
            return false;
        }
        if(n1->val==n2->val){
            return func(n1->left,n2->right)&&func(n1->right,n2->left);
        }
        return false;
    }
    bool isSymmetric(TreeNode* root) {
        if(root==NULL) return true;
        return func(root->left,root->right);
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
    bool func(TreeNode* n1,TreeNode* n2){
        if(n1==NULL&&n2==NULL) return true;
        if(n1==NULL||n2==NULL) return false;
        return (n1->val==n2->val)&&func(n1->left,n2->right)&&func(n1->right,n2->left);
    }
    bool isSymmetric(TreeNode* root) {
        return func(root,root);
    }
};

//迭代(队列)
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
    bool isSymmetric(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        q.push(root);
        while(!q.empty()){
            TreeNode* n1 = q.front();q.pop();
            TreeNode* n2 = q.front();q.pop();
            if(n1==NULL&&n2==NULL) continue;
            if(n1==NULL||n2==NULL) return false;
            if(n1->val!=n2->val) return false;
            q.push(n1->left);
            q.push(n2->right);
            q.push(n1->right);
            q.push(n2->left);
        }
        return true;
    }
};