#include <iostream>
#include <csignal>
#include <unistd.h>
#include <string>
#include <sstream>
#include <vector>
 
using namespace std;

bool debug = false;

class ListNode {
  public:
    int val;
    ListNode* next = nullptr;
};

ListNode* reverse_between_impl(ListNode* pre_start, ListNode* start, ListNode* end) {
    auto end_next = end->next;
    auto pre = start;
    auto p = start->next;
    while (p != nullptr && p != end_next) {
        auto r = p->next;
        p->next = pre;
        pre = p;
        p = r;
    }
    if (pre_start == nullptr) {
        start->next = end_next;
        return pre;
    } else {
        pre_start->next = end;
        start->next = end_next;
        return nullptr;
    }
}

ListNode* reverse_between(ListNode* head, int m, int n) {
    if (m == n) return head;
    int index = 1;
    auto p = head;
    ListNode* pre = nullptr;
    ListNode* pre_start = nullptr;
    ListNode* start = nullptr;
    ListNode* end = nullptr;
    while(p != nullptr) {
        if (index == m) {
            start = p;
            pre_start = pre;
        }
        if (index == n) {
            end = p;
        }

        if (start != nullptr && end != nullptr) {
            if (debug) std::cout << "start: " << start->val << " end:" << end->val << std::endl;
            auto ret = reverse_between_impl(pre_start, start, end);
            if (pre_start != nullptr) {
                return head;
            } else {
                return ret;
            }
        }

        pre = p;
        p = p->next;
        ++index;
    }
    return nullptr;
}

ListNode* build_list(std::vector<int>& vec) {
    ListNode* pre = nullptr;
    ListNode* head = nullptr;
    for (auto & v : vec) {
        auto p = new ListNode();
        p->val = v;
        if (pre != nullptr) {
            pre->next = p;
        } else {
            head = p;
        }
        pre = p;
    }
    return head;
}

void print_list(ListNode* head) {
    std::stringstream ss;
    ss << "{";
    while (head != nullptr) {
        ss << head->val;
        if (head->next != nullptr) {
            ss << ", ";
        }
        head = head->next;
    }
    ss << "}";
    std::cout << ss.str() << std::endl;
}

int main() {
    std::vector<int> vec = {1,2,3,4,5,6};
    auto head = build_list(vec);
    std::cout << "list:";
    print_list(head);
    auto rev_head = reverse_between(head, 1, 6);   
    std::cout << "reverse list:";
    print_list(rev_head);
    return 0;
}
