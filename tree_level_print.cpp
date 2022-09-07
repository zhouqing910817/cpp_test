#include <iostream>
#include <csignal>
#include <unistd.h>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <deque>
 
using namespace std;

bool debug = false;

class TreeNode {
public:
  TreeNode (int val) : val(val) {

  }
  int val;
  TreeNode* left;
  TreeNode* right;
};

void print_tree(TreeNode* root) {
    if (root == nullptr) return;
    deque<TreeNode*> q;
    q.push_back(root);
    deque<TreeNode*> next_level_q;

    
    int level = 0;
    while (q.size() != 0) {
        if (debug) {
            stringstream ss;
            ss << "level: " << level << " -> ";
            for (int i = 0; i < q.size(); ++i) {
                ss << q[i]->val << ",";
            }
            std::cout << ss.str() << std::endl;
        }
        ++level;
        auto right_n = q.front();
        // next_level_q.pop_front();
        std::cout << right_n->val << std::endl;

        // q and next_level_q move to next
        while(q.size() != 0) {
            auto n = q.front();
            q.pop_front();
            if (n->right != nullptr) {
                next_level_q.push_back(n->right);
            }
            if (n->left != nullptr) {
                 next_level_q.push_back(n->left);
            }
        }
        q = std::move(next_level_q);
    }
}

int main() {
    TreeNode* n0 = new TreeNode(0);
    TreeNode* n1 = new TreeNode(1);
    TreeNode* n2 = new TreeNode(2);
    TreeNode* n3 = new TreeNode(3);
    TreeNode* n4 = new TreeNode(4);
    TreeNode* n5 = new TreeNode(5);
    TreeNode* n6 = new TreeNode(6);

    n0->left = n1;
    n0->right = n2;
    n1->left = n3;
    n1->right = n4;
    n2->left = n5;
    n2->right = n6;
    print_tree(n0);
    
    return 0;
}
