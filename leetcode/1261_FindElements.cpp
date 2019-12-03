// @File   : 1261_FindElements.cpp
// @Source : https://leetcode-cn.com/problems/find-elements-in-a-contaminated-binary-tree/
// @Title  : 在受污染的二叉树中查找元素
// @Auther : sun_ds
// @Date   : 2019/11/29

/**  题目描述：
    给出一个满足下述规则的二叉树：

    root.val == 0
    如果 treeNode.val == x 且 treeNode.left != null，那么 treeNode.left.val == 2 * x + 1
    如果 treeNode.val == x 且 treeNode.right != null，那么 treeNode.right.val == 2 * x + 2
    现在这个二叉树受到「污染」，所有的 treeNode.val 都变成了 -1。

    请你先还原二叉树，然后实现 FindElements 类：

    FindElements(TreeNode* root) 用受污染的二叉树初始化对象，你需要先把它还原。
    bool find(int target) 判断目标值 target 是否存在于还原后的二叉树中并返回结果。
     

    示例 1：



    输入：
    ["FindElements","find","find"]
    [[[-1,null,-1]],[1],[2]]
    输出：
    [null,false,true]
    解释：
    FindElements findElements = new FindElements([-1,null,-1]);
    findElements.find(1); // return False
    findElements.find(2); // return True
    示例 2：



    输入：
    ["FindElements","find","find","find"]
    [[[-1,-1,-1,-1,-1]],[1],[3],[5]]
    输出：
    [null,true,true,false]
    解释：
    FindElements findElements = new FindElements([-1,-1,-1,-1,-1]);
    findElements.find(1); // return True
    findElements.find(3); // return True
    findElements.find(5); // return False
    示例 3：



    输入：
    ["FindElements","find","find","find","find"]
    [[[-1,null,-1,-1,null,-1]],[2],[3],[4],[5]]
    输出：
    [null,true,false,false,true]
    解释：
    FindElements findElements = new FindElements([-1,null,-1,-1,null,-1]);
    findElements.find(2); // return True
    findElements.find(3); // return False
    findElements.find(4); // return False
    findElements.find(5); // return True
     

    提示：

    TreeNode.val == -1
    二叉树的高度不超过 20
    节点的总数在 [1, 10^4] 之间
    调用 find() 的总次数在 [1, 10^4] 之间
    0 <= target <= 10^6

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/find-elements-in-a-contaminated-binary-tree
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 遍历二叉树,填充值
 *
 * 二叉树查找值
 * 1.用set作弊
 * 2.可以利用填充数值规则，二分快速定位？
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
class FindElements {
public:
    TreeNode* class_root;
    int tar;
    void traversal(TreeNode* root){
        if(root==NULL) return;
        if(root->left!=NULL) {
            root->left->val = 2*root->val + 1;
            traversal(root->left);
        }
        if(root->right!=NULL){
            root->right->val = 2*root->val + 2;
            traversal(root->right);
        }
    }
    FindElements(TreeNode* root) {
        class_root = root;
        root->val = 0;
        traversal(root);
    }
    bool find_tar(TreeNode* root){
        if(root==NULL) return false;
        if(root->val==tar){
            return true;
        }
        if(find_tar(root->left))
            return true;
        if(find_tar(root->right))
            return true;
        return false;
    }
    bool find(int target) {
        tar = target;
        return find_tar(class_root);
    }

};

/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
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
class FindElements {
public:
    unordered_set<int> s;
    void recover(TreeNode* root,int val){
        if(root==NULL) return;
        root->val = val;
        s.insert(val);
        recover(root->left,2*val+1);
        recover(root->right,2*val+2);
    }
    FindElements(TreeNode* root) {
        recover(root,0);
    }
    bool find(int target) {
        return s.find(target)!=s.end();
    }

};

/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */


