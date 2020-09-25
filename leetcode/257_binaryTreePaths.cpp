// @File   : 257_binaryTreePaths.cpp
// @Source : https://leetcode-cn.com/problems/binary-tree-paths/
// @Title  : 257. 二叉树的所有路径
// @Auther : sun_ds
// @Date   : 2020/9/4

/**  题目描述：
    给定一个二叉树，返回所有从根节点到叶子节点的路径。

    说明: 叶子节点是指没有子节点的节点。

    示例:

    输入:

       1
     /   \
    2     3
     \
      5

    输出: ["1->2->5", "1->3"]

    解释: 所有根节点到叶子节点的路径为: 1->2->5, 1->3

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/binary-tree-paths
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.dfs
 * 递归
 * 时间复杂度 O(N^2)
 * 空间复杂度 O(N^2)
 *
 * 2.bfs
 * 两个队列，分别存储节点和 path
 * 时间复杂度 O(N^2)
 * 空间复杂度 O(N^2)
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
    vector<string> res;
public:
    void func(TreeNode* root, string temp){
        if(root->left == nullptr && root->right == nullptr){
            res.push_back(temp);
        }
        if (root->left != nullptr)
            func(root->left, temp + "->" + to_string(root->left->val));
        if (root->right != nullptr)
            func(root->right, temp + "->" + to_string(root->right->val));
    }
    vector<string> binaryTreePaths(TreeNode* root) {
        if (root == nullptr) return {};
        func(root, to_string(root->val));
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
    vector<string> binaryTreePaths(TreeNode* root) {
        if (root == nullptr) return {};
        vector<string> res;
        queue<TreeNode*> q;
        queue<string> path;
        q.push(root);
        path.push(to_string(root->val));
        while (!q.empty()) {
            TreeNode* node = q.front();
            string temp = path.front();
            q.pop();
            path.pop();
            if (node->left == nullptr && node->right == nullptr) {
                res.push_back(temp);
            } else {
                if (node->left != nullptr) {
                    q.push(node->left);
                    path.push(temp + "->" + to_string(node->left->val));
                }
                if (node->right != nullptr) {
                    q.push(node->right);
                    path.push(temp + "->" + to_string(node->right->val));
                }
            }
        }
        return res;
    }
};

