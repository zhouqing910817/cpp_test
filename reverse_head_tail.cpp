#include <iostream>
#include <csignal>
#include <unistd.h>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
 
using namespace std;

bool debug = false;

class TreeNode {
  public:
    TreeNode(int data = 0) : data(data), next(nullptr) {
    }
    TreeNode* next;
    int data;
};
void print(TreeNode* head) {
    if (head == nullptr) return;
    auto cur = head;
    std::stringstream ss;
    while(cur != nullptr) {
        ss << cur->data << ", ";
        cur = cur->next;
    }
    std::cout << ss.str() << std::endl;
}
TreeNode* reverse(TreeNode* head) {
    if (head == nullptr || head->next == nullptr) return head;
    TreeNode *pre = nullptr, *cur = head;
    while(cur != nullptr) {
        auto r = cur->next;
        cur->next = pre;

        pre = cur;
        cur = r;
    }
    return pre;
}
void merge_interleave(TreeNode* head, TreeNode* reverse_head) {
    auto p = head;
    auto reverse_p = reverse_head;
    TreeNode* pre_reverse_p = nullptr;
    while(p != nullptr && reverse_p != nullptr) {
        auto p_next = p->next;
        auto reverse_p_next = reverse_p->next;
        p->next = reverse_p;
        reverse_p->next = p_next;

        p = p_next;
        pre_reverse_p = reverse_p;
        reverse_p = reverse_p_next;
    }
    std::cout << "pre_reverse_p: " << pre_reverse_p->data << std::endl;
    
    if (reverse_p != nullptr) {
        pre_reverse_p->next = reverse_p;
    }
    
}
/*
1 2 3 4 5 6
*/
void reverse_head_tail(TreeNode* head) {
    if (head == nullptr || head->next == nullptr) return;
    auto p = head;
    int count = 0;
    while(p != nullptr) {
        ++count;
        p = p->next;
    }
    std::cout << "list count: " << count << std::endl;
    p = head;
    TreeNode* pre = nullptr;
    for (int i = 0; i < count / 2; ++i) {
        pre = p;
        p = p->next;
    }
    auto pre_next = pre->next;
    pre->next = nullptr;
    auto reverse_head = reverse(pre_next);
    std::cout << "list : ";
    print(head);
    std::cout << "reverse list : ";
    print(reverse_head);
    merge_interleave(head, reverse_head);
}

int main() {
    auto n0 = new TreeNode(0);
    auto n1 = new TreeNode(1);
    auto n2 = new TreeNode(2);
    auto n3 = new TreeNode(3);
    auto n4 = new TreeNode(4);
    auto n5 = new TreeNode(5);
    auto n6 = new TreeNode(6);

    n0->next = n1;
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;
    // n5->next = n6;


    reverse_head_tail(n0);
    std::cout << "ret list: ";
    print(n0);
    return 0;
}