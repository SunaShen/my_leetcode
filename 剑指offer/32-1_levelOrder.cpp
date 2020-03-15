// @File   : 32-1_levelOrder.cpp
// @Source : https://leetcode-cn.com/problems/cong-shang-dao-xia-da-yin-er-cha-shu-lcof/
// @Title  : 面试题32 - I. 从上到下打印二叉树
// @Auther : sun_ds
// @Date   : 2020/3/14

/**  题目描述：
    从上到下打印出二叉树的每个节点，同一层的节点按照从左到右的顺序打印。

     

    例如:
    给定二叉树: [3,9,20,null,null,15,7],

        3
       / \
      9  20
        /  \
       15   7
    返回：

    [3,9,20,15,7]
     

    提示：

    节点总数 <= 1000


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/cong-shang-dao-xia-da-yin-er-cha-shu-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 层序遍历
 * 使用队列迭代实现
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
    vector<int> levelOrder(TreeNode* root) {
        if(root==NULL) return {};
        vector<int> res;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            TreeNode* temp = q.front();
            q.pop();
            res.push_back(temp->val);
            if(temp->left!=NULL) q.push(temp->left);
            if(temp->right!=NULL) q.push(temp->right);
        }
        return res;
    }
};

