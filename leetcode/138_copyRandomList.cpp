// @File   : 138_copyRandomList.cpp
// @Source : https://leetcode-cn.com/problems/copy-list-with-random-pointer/
// @Title  : 138. 复制带随机指针的链表
// @Auther : sun_ds
// @Date   : 2020/3/26

/**  题目描述：
    给定一个链表，每个节点包含一个额外增加的随机指针，该指针可以指向链表中的任何节点或空节点。

    要求返回这个链表的 深拷贝。 

    我们用一个由 n 个节点组成的链表来表示输入/输出中的链表。每个节点用一个 [val, random_index] 表示：

    val：一个表示 Node.val 的整数。
    random_index：随机指针指向的节点索引（范围从 0 到 n-1）；如果不指向任何节点，则为  null 。
     

    示例 1：



    输入：head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
    输出：[[7,null],[13,0],[11,4],[10,2],[1,0]]
    示例 2：



    输入：head = [[1,1],[2,1]]
    输出：[[1,1],[2,1]]
    示例 3：



    输入：head = [[3,null],[3,0],[3,null]]
    输出：[[3,null],[3,0],[3,null]]
    示例 4：

    输入：head = []
    输出：[]
    解释：给定的链表为空（空指针），因此返回 null。
     

    提示：

    -10000 <= Node.val <= 10000
    Node.random 为空（null）或指向链表中的节点。
    节点数目不超过 1000 。


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/copy-list-with-random-pointer
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.使用map迭代
 * 第一次遍历创建新节点并存储当前节点与新建节点的对应关系
 * 第二次遍历，更新新建节点的next和random
 * 2.dfs
 * 存储老节点和新节点对应的map
 * 从头开始递归构建。
 * 如果当前老节点在map中，说明他对应的新节点已经创建，直接返回。
 * 否则，为当前节点创建新节点，并添加他的next和random
 * 3.bfs
 * 使用队列
 *
 */

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;

        unordered_map<Node*, Node*> mp;
        for (Node *it = head; it; it = it->next) {
            mp[it] = new Node(it->val);
        }
        for (Node *it = head; it; it = it->next) {
            if (it->next) mp[it]->next = mp[it->next];
            if (it->random) mp[it]->random = mp[it->random];
        }
        return mp[head];
    }
};



