// @File   : 32-2_levelOrder.cpp
// @Source : https://leetcode-cn.com/problems/cong-shang-dao-xia-da-yin-er-cha-shu-ii-lcof/
// @Title  : 面试题32 - II. 从上到下打印二叉树 II
// @Auther : sun_ds
// @Date   : 2020/3/14

/**  题目描述：
    从上到下按层打印二叉树，同一层的节点按从左到右的顺序打印，每一层打印到一行。

     

    例如:
    给定二叉树: [3,9,20,null,null,15,7],

        3
       / \
      9  20
        /  \
       15   7
    返回其层次遍历结果：

    [
      [3],
      [9,20],
      [15,7]
    ]
     

    提示：

    节点总数 <= 1000
    注意：本题与主站 102 题相同：https://leetcode-cn.com/problems/binary-tree-level-order-traversal/

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/cong-shang-dao-xia-da-yin-er-cha-shu-ii-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 层序遍历分层输出
 *
 * 使用队列
 * 使用队列的size来控制分层
 *
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
    vector<vector<int>> levelOrder(TreeNode* root) {
        if(root==NULL) return{};
        vector<vector<int>> res;
        vector<int> temp;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            int num = q.size();
            temp.clear();
            for(int i=0;i<num;i++){
                TreeNode* node = q.front();
                q.pop();
                temp.push_back(node->val);
                if(node->left!=NULL) q.push(node->left);
                if(node->right!=NULL) q.push(node->right);
            }
            res.push_back(temp);
        }
        return res;
    }
};


