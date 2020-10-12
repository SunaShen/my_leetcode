// @File   : 530_getMinimumDifference.cpp
// @Source : https://leetcode-cn.com/problems/minimum-absolute-difference-in-bst/
// @Title  : 530. 二叉搜索树的最小绝对差
// @Auther : sun_ds
// @Date   : 2020/10/12

/**  题目描述：
    给你一棵所有节点为非负值的二叉搜索树，请你计算树中任意两节点的差的绝对值的最小值。

     

    示例：

    输入：

       1
        \
         3
        /
       2

    输出：
    1

    解释：
    最小绝对差为 1，其中 2 和 1 的差的绝对值为 1（或者 2 和 3）。
     

    提示：

    树中至少有 2 个节点。
    本题与 783 https://leetcode-cn.com/problems/minimum-distance-between-bst-nodes/ 相同

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/minimum-absolute-difference-in-bst
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1. 中序遍历
 *  中序遍历 pre 保存前一个节点的值
 *  由于中序遍历的节点升序排列，得到中序遍历相邻节点之间的最小差值即为结果
 *
 *  时间复杂度 O(N)
 *  空间复杂度 O(N)
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
    int res = INT_MAX;
    int pre = -1;
public:
    int abs(int a, int b){
        return a > b ? a - b : b - a;
    }
    void dfs(TreeNode* root){
        if(root == nullptr) return;
        dfs(root->left);
        if(pre != -1){
            if(res > abs(root->val, pre)){
                res = abs(root->val, pre);
            }
        }
        pre = root->val;
        dfs(root->right);
    }
    int getMinimumDifference(TreeNode* root) {
        dfs(root);
        return res;
    }
};