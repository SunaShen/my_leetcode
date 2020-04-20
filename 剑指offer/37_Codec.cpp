// @File   : 37_Codec.cpp
// @Source : https://leetcode-cn.com/problems/xu-lie-hua-er-cha-shu-lcof/
// @Title  : 面试题37. 序列化二叉树
// @Auther : sun_ds
// @Date   : 2020/4/13

/**  题目描述：
    请实现两个函数，分别用来序列化和反序列化二叉树。

    示例: 

    你可以将以下二叉树：

        1
       / \
      2   3
         / \
        4   5

    序列化为 "[1,2,3,null,null,4,5]"
    注意：本题与主站 297 题相同：https://leetcode-cn.com/problems/serialize-and-deserialize-binary-tree/

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/xu-lie-hua-er-cha-shu-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 *
 *
 * 使用queue层序遍历
 * 序列化：使用queue层序遍历二叉树。左右孩子为null也要输出
 * 反序列化：对应的也是层序的构建，使用queue，并用i表示输入中的第i个节点。如果当前节点不为null就new新节点，否则就跳过。
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
class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(root==nullptr) return "[]";
        string res;
        queue<TreeNode*> q;
        q.push(root);
        //使用队列层序遍历
        while(!q.empty()){
            TreeNode* node = q.front();
            q.pop();
            if(node!=nullptr){
                res += to_string(node->val);
                res += ",";
                //左右孩子，就算是null也放进去
                q.push(node->left);
                q.push(node->right);
            }else{
                res += "null,";
            }
        }
        res[res.size()-1] = ']';//把最后一个","改成"]"
        res.insert(0,"[");//在最前面插入"["
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if(data=="[]") return nullptr;
        string s = data.substr(1,data.size()-2);    //去掉中括号"[","]".
        //使用stringstream 以 ","分割字符
        istringstream ss(s);
        string t;
        vector<string> num;
        while(getline(ss,t,',')){
            num.push_back(t);
        }

        //构造二叉树
        int i=0;    //使用i定位在string中的位置
        //使用queue 层序构建，跟上面保持一致
        queue<TreeNode*> q;
        TreeNode* root = new TreeNode(atoi(num[i++].c_str()));
        q.push(root);

        while(!q.empty()){
            TreeNode* temp = q.front();
            q.pop();
            //构建左孩子 如果为null就不构建了，下面直接i++跳过
            if(num[i]!="null"){
                temp->left = new TreeNode(atoi(num[i].c_str()));
                q.push(temp->left);
            }
            i++; //后移一位
            //构建右孩子 如果为null就不构建了，下面直接i++跳过
            if(num[i]!="null"){
                temp->right = new TreeNode(atoi(num[i].c_str()));
                q.push(temp->right);
            }
            i++; //后移一位
        }
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));

