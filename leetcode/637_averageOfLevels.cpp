// @File   : 637_averageOfLevels.cpp
// @Source : https://leetcode-cn.com/problems/average-of-levels-in-binary-tree/
// @Title  : 637. 二叉树的层平均值
// @Auther : sun_ds
// @Date   : 2020/9/12

/**  题目描述：
    给定一个非空二叉树, 返回一个由每层节点平均值组成的数组。

     

    示例 1：

    输入：
        3
       / \
      9  20
        /  \
       15   7
    输出：[3, 14.5, 11]
    解释：
    第 0 层的平均值是 3 ,  第1层是 14.5 , 第2层是 11 。因此返回 [3, 14.5, 11] 。
     

    提示：

    节点值的范围在32位有符号整数范围内。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/average-of-levels-in-binary-tree
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.层序遍历(bfs)
 * 层序遍历
 * 统计每一层的平均值
 *
 * 时间复杂度 O(N)
 * 空间复杂度 O(N)
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
    vector<double> averageOfLevels(TreeNode* root) {
        if(root == nullptr) return {};
        vector<double> res;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            int n = q.size();
            long long count = 0;
            for(int i=0;i<n;i++){
                auto node = q.front();
                q.pop();
                count += node->val;
                if(node->left != nullptr){
                    q.push(node->left);
                }
                if(node->right != nullptr){
                    q.push(node->right);
                }
            }
            res.push_back(count/(double)n);
        }
        return res;
    }
};