// @File   : 34_pathSum.cpp
// @Source : https://leetcode-cn.com/problems/er-cha-shu-zhong-he-wei-mou-yi-zhi-de-lu-jing-lcof/
// @Title  : 面试题34. 二叉树中和为某一值的路径
// @Auther : sun_ds
// @Date   : 2020/3/27

/**  题目描述：
    输入一棵二叉树和一个整数，打印出二叉树中节点值的和为输入整数的所有路径。从树的根节点开始往下一直到叶节点所经过的节点形成一条路径。

     

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
     

    提示：

    节点总数 <= 10000
    注意：本题与主站 113 题相同：https://leetcode-cn.com/problems/path-sum-ii/

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/er-cha-shu-zhong-he-wei-mou-yi-zhi-de-lu-jing-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 *
 * dfs,回溯
 *
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
    vector<vector<int>> res;
    void dfs(TreeNode* root,int sum,vector<int> temp,int cur_sum){
        if(root->left==NULL&&root->right==NULL){
            temp.push_back(root->val);
            cur_sum += root->val;
            if(cur_sum==sum){
                res.push_back(temp);
            }
            return;
        }
        temp.push_back(root->val);
        cur_sum += root->val;
        if(root->left) dfs(root->left,sum,temp,cur_sum);
        if(root->right) dfs(root->right,sum,temp,cur_sum);
    }
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        if(root==NULL) return {};
        dfs(root,sum,{},0);
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
    vector<vector<int>> res;
    vector<int> temp;
    void dfs(TreeNode* root,int sum){
        if(root==NULL) return;
        sum -= root->val;
        temp.push_back(root->val);
        if(root->left==NULL&&root->right==NULL&&sum==0){
            res.push_back(temp);
            // return;
        }
        dfs(root->left,sum);
        dfs(root->right,sum);
        temp.pop_back();
    }
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        dfs(root,sum);
        return res;
    }
};



