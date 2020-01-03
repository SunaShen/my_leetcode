// @File   : 107_levelOrderBottom.cpp
// @Source : https://leetcode-cn.com/problems/binary-tree-level-order-traversal-ii/
// @Title  : 二叉树的层次遍历 II
// @Auther : sun_ds
// @Date   : 2020/1/3

/**  题目描述：
    给定一个二叉树，返回其节点值自底向上的层次遍历。 （即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历）

    例如：
    给定二叉树 [3,9,20,null,null,15,7],

        3
       / \
      9  20
        /  \
       15   7
    返回其自底向上的层次遍历为：

    [
      [15,7],
      [9,20],
      [3]
    ]


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/binary-tree-level-order-traversal-ii
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 自底向上层次遍历
 *
 * 使用102的层次遍历
 * 将结果reverse
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
public:
    vector<vector<int>> res;
    void dfs(TreeNode* root, int level){
        if(res.size() < level){
            res.push_back({});
        }
        res[level - 1].push_back(root->val);
        if(root->left != NULL)
            dfs(root->left, level + 1);
        if(root->right != NULL)
            dfs(root->right, level + 1);
    }
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        if(root == NULL) return {};
        dfs(root,1);
        reverse(res.begin(),res.end());
        return res;
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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        if(root == NULL) return {};
        vector<vector<int>> res;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            vector<int> t;
            int num = q.size();
            for(int i=0;i<num;++i){
                TreeNode* temp = q.front();
                t.push_back(temp->val);
                q.pop();
                if(temp->left != NULL)
                    q.push(temp->left);
                if(temp->right != NULL)
                    q.push(temp->right);
            }
            res.push_back(t);
        }
        reverse(res.begin(),res.end());
        return res;
    }
};


