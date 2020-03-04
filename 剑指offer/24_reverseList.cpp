// @File   : 24_reverseList.cpp
// @Source : https://leetcode-cn.com/problems/fan-zhuan-lian-biao-lcof/
// @Title  : 面试题24. 反转链表
// @Auther : sun_ds
// @Date   : 2020/3/4

/**  题目描述：
    定义一个函数，输入一个链表的头节点，反转该链表并输出反转后链表的头节点。

     

    示例:

    输入: 1->2->3->4->5->NULL
    输出: 5->4->3->2->1->NULL
     

    限制：

    0 <= 节点个数 <= 5000

     

    注意：本题与主站 206 题相同：https://leetcode-cn.com/problems/reverse-linked-list/

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/fan-zhuan-lian-biao-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 反转链表
 *
 * 1.双指针
 * 创建指针pre和cur
 * 依次反向cur的next，全部反序。
 * 即得反序链表
 *
 * 其他的见leetcode 206
 *
 *
 *
 *
 */


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
    ListNode* reverseList(ListNode* head) {
        ListNode* pre = NULL;
        ListNode* cur = head;
        while(cur){
            ListNode* temp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = temp;
        }
        return pre;
    }
};