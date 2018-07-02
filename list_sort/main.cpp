#include <iostream>
#include <vector>
#include <limits>

struct ListNode {
    ListNode *next;
    int value;
    ListNode(int v) : next(nullptr), value(v) {};
};

void find_max_and_max_prev(ListNode* head, ListNode **max, ListNode **max_prev)
{
    ListNode *p = head;
    ListNode *p_max = head;
    ListNode *p_max_prev = head;
    ListNode *p_prev = head;

    while (p->next) {
        p_prev = p;
        p = p->next;
        if(p->value > p_max->value)
        {
            p_max = p;
            p_max_prev = p_prev;
        }
    }

    *max = p_max;
    *max_prev = p_max_prev;
}

ListNode* delete_node(ListNode *head, ListNode *max, ListNode *max_prev)
{
    if(max == max_prev)
    {
        return max->next;
    }
    else {
        max_prev->next = max->next;
        // delete(max);

        return head;
    }
}

ListNode* connect_max_to_list(ListNode *head, ListNode **last, const int v)
{
    if(head == nullptr)
    {
       *last = new ListNode(v); 
       return *last;
    }
    else{
        (*last)->next = new ListNode(v);
        *last = (*last)->next;
        return head;
    }
}

ListNode* select_sort_list(ListNode *head)
{
    if(head == nullptr)
        return head;
    if(head->next == nullptr)
        return head;

    ListNode *last = nullptr;
    ListNode *new_list = nullptr;
    while(head)
    {
        ListNode *max; 
        ListNode *prev;

        find_max_and_max_prev(head, &max, &prev);

        // printf("%d\n", max->value);

        new_list = connect_max_to_list(new_list, &last, max->value);

        head = delete_node(head, max, prev);
    }

    return new_list;
}

ListNode* make_list(std::vector<int>& nums)
{
    if(nums.empty())
        return nullptr;

    ListNode *pLast = new ListNode(nums[0]);
    ListNode *pHead = pLast;

    for (int i = 1; i < (int)nums.size(); i++) {
        pLast->next = new ListNode(nums[i]);
        pLast = pLast->next;
    }

    return pHead; 
}

void print_list(ListNode *head) {
    ListNode *p = head;
    while (p)
    {
        printf("%d", p->value);
        if(p->next)
        {
            printf("->");
        }
        else {
            printf("\n");
        }
        p = p->next;
    }
}

int main(int, char**) {
   std::cout << "Hello, world!\n";

   std::vector<int> nums({1,3,5,7,9,2,4,6,8,0});

   ListNode *l = make_list(nums);

   printf("before sorted:\n");
   print_list(l);

   ListNode *sorted = select_sort_list(l);

   printf("after sorted:\n");
   print_list(sorted);

   return 0;

}
