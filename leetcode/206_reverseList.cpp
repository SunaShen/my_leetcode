// @File   : 206_reverseList.cpp
// @Source : https://leetcode-cn.com/problems/reverse-linked-list/
// @Title  : 206. 反转链表
// @Auther : sun_ds
// @Date   : 2020/3/2

/**  题目描述：
    反转一个单链表。

    示例:

    输入: 1->2->3->4->5->NULL
    输出: 5->4->3->2->1->NULL
    进阶:
    你可以迭代或递归地反转链表。你能否用两种方法解决这道题？

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/reverse-linked-list
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 反序链表
 *
 * 自己实现的迭代和递归都很拙劣。
 *
 * 1.迭代
 *  定义pre和cur. while(cur)
 *  将cur的next方向到pre
 * 2.递归
 *  递归下去，直到最后一个节点head->next==null 再返回，组合。
 *  组合时head->next->next = head; 即下一个节点的下一个位置指向自己，直接反向。
 *  注意还要将head->next = NULL。其实不用也可以，因为上一层结合时就会覆盖。但是最顶一层上没有层被覆盖了会出问题。
 * 3.栈
 *  遍历链表，将链表中各节点指针存进栈中。
 *  再从依次出栈，组成新的反序链表。
 *
 *
 *
 */

//迭代
//自己实现
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
        if(head==NULL||head->next==NULL) return head;
        ListNode* p1 = head;
        ListNode* p2 = head->next;
        //循环将当前放到链表头。
        while(p2){
            ListNode* p3 = p2->next;
            p1->next = p3;
            p2->next = head;
            head = p2;
            p2 = p3;
        }
        return head;
    }
};

//优秀解法
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
            //所有元素指向掉头
            cur->next = pre;
            pre = cur;
            cur = temp;
        }
        return pre;
    }
};

//递归

//自己实现很多不合理
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
    ListNode* res = NULL;
    ListNode* func(ListNode* p){
        if(p->next == NULL){
            res = p;
            return p;
        }
        //返回的这个temp一定是p->next..浪费了。应该返回res的。 见下面解法
        ListNode* temp = func(p->next);
        temp->next = p;
        //p->next没有 空。因为下一次递归返回就会被上一次替代。但是最后一次，没有。所以主函数中还要将最后一个返回 t->next = NULL.
        return p;
    }
    ListNode* reverseList(ListNode* head) {
        if(head==NULL) return head;
        ListNode* t = func(head);
        t->next = NULL;
        return res;
    }
};

//优秀解法
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
        //此处head->next==null判断是否为最后一个节点。而head->next==null是防止输入为NULL，后面就用不到了。
        //递归终止条件是当前为空，或者下一个节点为空
        if(head==null || head->next==null) {
            return head;
        }
        //这里的cur就是最后一个节点
        ListNode* cur = reverseList(head.next);
        //这里请配合动画演示理解
        //如果链表是 1->2->3->4->5，那么此时的cur就是5
        //而head是4，head的下一个是5，下下一个是空
        //所以head.next.next 就是5->4
        head->next->next = head;
        //防止链表循环，需要将head.next设置为空
        head->next = null;
        //每层递归函数都返回cur，也就是最后一个节点
        return cur;
    }
};




//栈
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
        if(head == NULL) return head;
        stack<ListNode* > s;
        ListNode* p = head;
        while(p){
            s.push(p);
            p = p->next;
        }
        p = s.top();
        s.pop();
        head = p;
        while(!s.empty()){
            p->next = s.top();
            s.pop();
            p = p->next;
        }
        p->next = NULL;
        return head;
    }
};

