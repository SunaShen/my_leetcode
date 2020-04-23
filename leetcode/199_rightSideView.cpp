// @File   : 199_rightSideView.cpp
// @Source : https://leetcode-cn.com/problems/binary-tree-right-side-view/
// @Title  : 199. 二叉树的右视图
// @Auther : sun_ds
// @Date   : 2020/4/22

/**  题目描述：
    给定一棵二叉树，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。

    示例:

    输入: [1,2,3,null,5,null,4]
    输出: [1, 3, 4]
    解释:

       1            <---
     /   \
    2     3         <---
     \     \
      5     4       <---

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/binary-tree-right-side-view
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 1.层序遍历
 * 取每一次的最后一个放入vector即是右视图
 * 2.dfs
 * 使用stack，先入栈左节点后入栈右节点，则对应先出栈右节点，后出栈左节点
 * 记录使用map统计各个深度的第一个访问到的节点即为每一层的最右边节点
 * 3.bfs
 * 使用queue，先入队左节点后入队右节点，则对应先出队左节点，后出队右节点
 * 记录使用map统计各个深度的最后一个访问到的节点即为每一层的最右边节点
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
    vector<int> rightSideView(TreeNode* root) {
        if(root==nullptr) return {};
        vector<int> res;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            int len = q.size();
            for(int i=0;i<len;i++){
                TreeNode* temp = q.front();
                q.pop();
                if(i!=len-1){
                    if(temp->left) q.push(temp->left);
                    if(temp->right) q.push(temp->right);
                }else{//每一层的最后一个
                    res.push_back(temp->val);
                    if(temp->left) q.push(temp->left);
                    if(temp->right) q.push(temp->right);
                }
            }
        }
        return res;
    }
};

