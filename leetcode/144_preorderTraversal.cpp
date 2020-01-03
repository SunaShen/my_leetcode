// @File   : 144_preorderTraversal.cpp
// @Source : https://leetcode-cn.com/problems/binary-tree-preorder-traversal/
// @Title  : 二叉树的前序遍历
// @Auther : sun_ds
// @Date   : 2019/12/26

/**  题目描述：
    给定一个二叉树，返回它的 前序 遍历。

     示例:

    输入: [1,null,2,3]
       1
        \
         2
        /
       3

    输出: [1,2,3]
    进阶: 递归算法很简单，你可以通过迭代算法完成吗？



    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/binary-tree-preorder-traversal
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 前序遍历
 * 中-左-右
 *
 * 1.递归法
 *  中左右
 * 2.迭代法
 *  使用stack保存节点
 *  一路向左，边向左边存储进res。并将每个节点的非空的右节点入栈。
 *  直到遇到空节点，出栈节点作为下一个节点。
 *
 * 3.迭代法
 *  使用stack保存节点
 *  先将root压入stack
 *  每次从栈顶读取节点，将节点值存入res
 *  并将依次将非空右孩子和左孩子入栈
 *
 *  入栈顺序 先右孩子 后左孩子。
 *  出栈顺序 先左孩子 后右孩子。
 *  满足 中-左-右
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
    vector<int> res;
    vector<int> preorderTraversal(TreeNode* root) {
        recursion(root);
        return res;
    }
    void recursion(TreeNode* root){
        if(root == NULL) return;
        res.push_back(root->val);
        recursion(root->left);
        recursion(root->right);
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
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> q;
        TreeNode* temp = root;
        while(!q.empty()||temp!=NULL){
            if(temp!=NULL){
                res.push_back(temp->val);
                if(temp->right != NULL)
                    q.push(temp->right);
                temp = temp->left;
            }else{
                temp = q.top();
                q.pop();
            }
        }
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
    vector<int> preorderTraversal(TreeNode* root) {
        if(root == NULL) return {};
        vector<int> res;
        stack<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            TreeNode* node = q.top();
            q.pop();
            res.push_back(node->val);
            if(node->right)
                q.push(node->right);
            if(node->left)
                q.push(node->left);
        }
        return res;
    }
};

