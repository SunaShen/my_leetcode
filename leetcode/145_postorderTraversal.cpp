// @File   : 145_postorderTraversal.cpp
// @Source : https://leetcode-cn.com/problems/binary-tree-postorder-traversal/
// @Title  : 145. 二叉树的后序遍历
// @Auther : sun_ds
// @Date   : 2020/3/14

/**  题目描述：
    给定一个二叉树，返回它的 后序 遍历。

    示例:

    输入: [1,null,2,3]
       1
        \
         2
        /
       3

    输出: [3,2,1]
    进阶: 递归算法很简单，你可以通过迭代算法完成吗？

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/binary-tree-postorder-traversal
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 后序遍历
 * 1.递归
 *
 * 2.迭代
 * 使用栈
 * 入栈顺序 先左后右
 * 效果 根-右-左
 * 反序结果 即 左-右-根 后序遍历
 *
 *
 *
 *
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
    vector<int> res;
public:
    void func(TreeNode* root){
        if(root==NULL) return;
        func(root->left);
        func(root->right);
        res.push_back(root->val);
    }
    vector<int> postorderTraversal(TreeNode* root) {
        func(root);
        return res;
    }
};

//迭代
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
    vector<int> postorderTraversal(TreeNode* root) {
        if(root==NULL) return {};
        vector<int> res;
        stack<TreeNode*> s;
        s.push(root);
        //根-右-左的反序  即 左-右-根
        while(!s.empty()){
            TreeNode* node = s.top();
            s.pop();
            res.push_back(node->val);
            if(node->left!=NULL) s.push(node->left);
            if(node->right!=NULL) s.push(node->right);
        }
        reverse(res.begin(),res.end());
        return res;
    }
};