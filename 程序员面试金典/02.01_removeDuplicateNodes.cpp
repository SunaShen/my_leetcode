// @File   : 02.01_removeDuplicateNodes.cpp
// @Source : https://leetcode-cn.com/problems/remove-duplicate-node-lcci/
// @Title  : 面试题 02.01. 移除重复节点
// @Auther : sun_ds
// @Date   : 2020/6/26

/**  题目描述：
    编写代码，移除未排序链表中的重复节点。保留最开始出现的节点。

    示例1:

     输入：[1, 2, 3, 3, 2, 1]
     输出：[1, 2, 3]
    示例2:

     输入：[1, 1, 1, 1, 2]
     输出：[1, 2]
    提示：

    链表长度在[0, 20000]范围内。
    链表元素在[0, 20000]范围内。
    进阶：

    如果不得使用临时缓冲区，该怎么解决？

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/remove-duplicate-node-lcci
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 *
 * 1. 使用 hash 存储出现过的元素
 *  跳过链表中重复出现的元素
 *  时间复杂度 O(N)
 *  空间复杂度 O(N)
 *
 * 2. 不用额外空间
 *  时间换空间。两层循环
 *  时间复杂度 O(N^2)
 *  空间复杂度 O(1)
 *
 */



//使用额外空间
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* removeDuplicateNodes(ListNode* head) {
        unordered_set<int> s;
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* curr = dummy->next;
        ListNode* pre = dummy;
        while(curr != nullptr){
            if(s.count(curr->val) == 0){
                s.insert(curr->val);
                pre->next = curr;
                pre = curr;
                curr = curr->next;
            }else{
                curr = curr->next;
            }
        }
        pre->next = nullptr;
        return dummy->next;
    }
};

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* removeDuplicateNodes(ListNode* head) {
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* curr = dummy->next;
        while(curr != nullptr){
            ListNode* temp = curr;
            while(temp->next != nullptr){
                if(temp->next->val == curr->val){
                    temp->next = temp->next->next;
                }else{
                    temp = temp->next;
                }
            }
            curr = curr->next;
        }
        return dummy->next;
    }
};
