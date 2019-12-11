// @File   : 337_rob.cpp
// @Source : https://leetcode-cn.com/problems/house-robber-iii/
// @Title  : 打家劫舍 III
// @Auther : sun_ds
// @Date   : 2019/12/10

/**  题目描述：
    在上次打劫完一条街道之后和一圈房屋后，小偷又发现了一个新的可行窃的地区。这个地区只有一个入口，我们称之为“根”。 除了“根”之外，每栋房子有且只有一个“父“房子与之相连。一番侦察之后，聪明的小偷意识到“这个地方的所有房屋的排列类似于一棵二叉树”。 如果两个直接相连的房子在同一天晚上被打劫，房屋将自动报警。

    计算在不触动警报的情况下，小偷一晚能够盗取的最高金额。

    示例 1:

    输入: [3,2,3,null,3,null,1]

         3
        / \
       2   3
        \   \
         3   1

    输出: 7
    解释: 小偷一晚能够盗取的最高金额 = 3 + 3 + 1 = 7.
    示例 2:

    输入: [3,4,5,1,3,null,1]

         3
        / \
       4   5
      / \   \
     1   3   1

    输出: 9
    解释: 小偷一晚能够盗取的最高金额 = 4 + 5 = 9.

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/house-robber-iii
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 树状dp
 *
 * 对于每个节点有两种状态，选与不选。
 *  若选择当前节点，则以当前节点为根的子树的最大金额=当前节点的值 + 左节点在不选择自己时最大金额 + 右节点在不选择自己时最大金额
 *  若不选择当前节点，则以当前节点为根的子树的最大金额 = 左节点最大金额(选不选自己都包括) + 右节点最大金额(选不选自己都包括)
 * 所以，当前节点的最大金额=上述两种情况中的最大值
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
    int Max = 0;
    int dfs(TreeNode* root,int &pre){
        if(root == NULL){
            pre = 0;
            return 0;
        }
        int pre_l = 0, pre_r = 0;
        int l = dfs(root->left,pre_l);
        int r = dfs(root->right,pre_r);

        pre = max(l,pre_l)+max(r,pre_r);
        int res = pre_l+pre_r+root->val;
        Max = max(Max,max(pre,res));
        return res;
    }
    int rob(TreeNode* root) {
        int p = 0;
        dfs(root,p);
        return Max;
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
    int rob(TreeNode* root) {
        int temp{};
        return solve(root, temp);
    }
private:
    int solve(TreeNode* p, int& c) {
        if (!p) return 0;
        int l{}, r{};
        c = solve(p->left, l) + solve(p->right, r);
        return max(l + r + p->val, c);
    }
};