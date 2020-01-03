// @File   : 129_sumNumbers.cpp
// @Source : https://leetcode-cn.com/problems/sum-root-to-leaf-numbers/
// @Title  : 求根到叶子节点数字之和
// @Auther : sun_ds
// @Date   : 2019/12/23

/**  题目描述：
    给定一个二叉树，它的每个结点都存放一个 0-9 的数字，每条从根到叶子节点的路径都代表一个数字。

    例如，从根到叶子节点路径 1->2->3 代表数字 123。

    计算从根到叶子节点生成的所有数字之和。

    说明: 叶子节点是指没有子节点的节点。

    示例 1:

    输入: [1,2,3]
        1
       / \
      2   3
    输出: 25
    解释:
    从根到叶子节点路径 1->2 代表数字 12.
    从根到叶子节点路径 1->3 代表数字 13.
    因此，数字总和 = 12 + 13 = 25.
    示例 2:

    输入: [4,9,0,5,1]
        4
       / \
      9   0
     / \
    5   1
    输出: 1026
    解释:
    从根到叶子节点路径 4->9->5 代表数字 495.
    从根到叶子节点路径 4->9->1 代表数字 491.
    从根到叶子节点路径 4->0 代表数字 40.
    因此，数字总和 = 495 + 491 + 40 = 1026.

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/sum-root-to-leaf-numbers
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 给定一个二叉树，它的每个结点都存放一个 0-9 的数字，每条从根到叶子节点的路径都代表一个数字。
 * 求所有数字之和
 *
 * 1.dfs
 *  叶子节点记录当前数字num并加到结果res上
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
    int res = 0;
    int sumNumbers(TreeNode* root) {
        if(root == NULL) return 0;
        dfs(root,0);
        return res;
    }
    void dfs(TreeNode* root, int num){
        if(root->left == NULL && root->right == NULL){   //叶子节点
            num += root->val;
            res += num;
            return;
        }
        num += root->val;
        if(root->left != NULL){
            dfs(root->left, num*10);
        }
        if(root->right != NULL){
            dfs(root->right, num*10);
        }
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
    int sumNumbers(TreeNode* root) {
        int res = 0;
        dfs(root,0,res);
        return res;
    }
    void dfs(TreeNode* root, int num, int &res){
        if(root == NULL) return;
        num = num*10 + root->val;
        if(root->left == NULL && root->right == NULL){   //叶子节点
            res += num;
            return;
        }
        dfs(root->left, num, res);
        dfs(root->right, num, res);
    }
};

