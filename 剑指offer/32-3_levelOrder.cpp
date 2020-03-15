// @File   : 32-3_levelOrder.cpp
// @Source : https://leetcode-cn.com/problems/cong-shang-dao-xia-da-yin-er-cha-shu-iii-lcof/
// @Title  : 面试题32 - III. 从上到下打印二叉树 III
// @Auther : sun_ds
// @Date   : 2020/3/14

/**  题目描述：
    请实现一个函数按照之字形顺序打印二叉树，即第一行按照从左到右的顺序打印，第二层按照从右到左的顺序打印，第三行再按照从左到右的顺序打印，其他行以此类推。

     

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
      [20,9],
      [15,7]
    ]
     

    提示：

    节点总数 <= 1000


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/cong-shang-dao-xia-da-yin-er-cha-shu-iii-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 层序遍历
 * 1.队列
 * 奇数层从左往右，偶数层从右往左
 * 借助上面基础，判断奇偶，偶数将temp反转后再加入res
 * reverse操作比较慢
 *
 *
 * 2.双端队列
 * 奇数 前取后放 先放左再放右
 * 偶数 后取前放 先放右再放左
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
        bool flag = false;
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
            if(flag) reverse(temp.begin(),temp.end());
            flag = !flag;
            res.push_back(temp);
        }
        return res;
    }
};

//双端队列
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
        deque<TreeNode*> q;
        q.push_back(root);
        bool flag = false;
        TreeNode* node;
        while(!q.empty()){
            int num = q.size();
            temp.clear();
            for(int i=0;i<num;i++){
                if(flag){
                    node = q.back();
                    q.pop_back();
                    if(node->right!=NULL) q.push_front(node->right);
                    if(node->left!=NULL) q.push_front(node->left);
                }else{
                    node = q.front();
                    q.pop_front();
                    if(node->left!=NULL) q.push_back(node->left);
                    if(node->right!=NULL) q.push_back(node->right);
                }
                temp.push_back(node->val);
            }
            flag = !flag;
            res.push_back(temp);
        }
        return res;
    }
};

