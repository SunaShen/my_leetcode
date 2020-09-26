// @File   : 113_pathSum.cpp
// @Source : https://leetcode-cn.com/problems/path-sum-ii/
// @Title  : 113. 路径总和 II
// @Auther : sun_ds
// @Date   : 2020/9/26

/**  题目描述：
    给定一个二叉树和一个目标和，找到所有从根节点到叶子节点路径总和等于给定目标和的路径。

    说明: 叶子节点是指没有子节点的节点。

    示例:
    给定如下二叉树，以及目标和 sum = 22，

                  5
                 / \
                4   8
               /   / \
              11  13  4
             /  \    / \
            7    2  5   1
    返回:

    [
       [5,4,11,2],
       [5,8,4,5]
    ]

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/path-sum-ii
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1. dfs
 *  递归，使用 temp 记录路径，遍历至叶子节点并且 temp 之和等于 sum 则记录 temp
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
    vector<vector<int>> res;
    vector<int> temp;
public:
    void func(TreeNode* root, int sum){
        if(root->left == nullptr && root->right == nullptr){
            if (sum == root->val) {
                temp.push_back(root->val);
                res.push_back(temp);
                temp.pop_back();
            }
            return;
        }
        temp.push_back(root->val);
        sum -= root->val;
        if (root->left != nullptr) func(root->left, sum);
        if (root->right != nullptr) func(root->right, sum);
        temp.pop_back();
    }
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        if(root == nullptr) return {};
        func(root, sum);
        return res;
    }
};


class Solution {
public:
    vector<vector<int>> ret;
    vector<int> path;

    void dfs(TreeNode* root, int sum) {
        if (root == nullptr) {
            return;
        }
        path.emplace_back(root->val);
        sum -= root->val;
        if (root->left == nullptr && root->right == nullptr && sum == 0) {
            ret.emplace_back(path);
        }
        dfs(root->left, sum);
        dfs(root->right, sum);
        path.pop_back();
    }

    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        dfs(root, sum);
        return ret;
    }
};
