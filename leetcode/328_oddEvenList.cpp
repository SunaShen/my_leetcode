// @File   : 328_oddEvenList.cpp
// @Source : https://leetcode-cn.com/problems/odd-even-linked-list/
// @Title  : 328. 奇偶链表
// @Auther : sun_ds
// @Date   : 2020/7/5

/**  题目描述：
    给定一个单链表，把所有的奇数节点和偶数节点分别排在一起。请注意，这里的奇数节点和偶数节点指的是节点编号的奇偶性，而不是节点的值的奇偶性。

    请尝试使用原地算法完成。你的算法的空间复杂度应为 O(1)，时间复杂度应为 O(nodes)，nodes 为节点总数。

    示例 1:

    输入: 1->2->3->4->5->NULL
    输出: 1->3->5->2->4->NULL
    示例 2:

    输入: 2->1->3->5->6->4->7->NULL
    输出: 2->3->6->7->1->5->4->NULL
    说明:

    应当保持奇数节点和偶数节点的相对顺序。
    链表的第一个节点视为奇数节点，第二个节点视为偶数节点，以此类推。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/odd-even-linked-list
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 奇数在前，偶数在后
 * 分成两个链表最后拼接。
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if(head == nullptr || head->next == nullptr) return head;
        ListNode* t1 = head;
        ListNode* t2 = head->next;
        ListNode* head2 = head->next;
        while(t2 != nullptr && t2->next != nullptr){
            t1->next = t2->next;
            t1 = t1->next;
            t2->next = t2->next->next;
            t2 = t2->next;
        }
        t1->next = head2;
        return head;
    }
};
