#include <iostream>
#include <string>

class Node {
  public:
    Node* left = nullptr;
    Node* right = nullptr;
    int data;
    int id;
};

void num_path_impl(Node* tree, int m, int sum, int* result) {
        std::cout << "visit node data: " << tree->id << " sum:" << sum << std::endl;
	if (sum > m) {
	    return;
	}
	sum += tree->data;
	if (tree->left == nullptr && tree->right == nullptr) {
            std::cout << "visit node : " << tree->id << " new_sum:" << sum << std::endl;
	    if (sum == m) {
	        *result += 1;
                std::cout << "visit node: " << tree->id << " new_sum:" << sum << " equals m:" << m << std::endl;
	        return;
	    }
	}
	if (tree->left != nullptr) {
	    num_path_impl(tree->left, m, sum,result);
	}
        if (tree->right != nullptr) {
	    num_path_impl(tree->right, m, sum,result);
	}
}

int num_path(Node* tree, int m) {
    if (tree == nullptr) {
	    return 0;
    }
    int result = 0;
    int sum = 0;
    num_path_impl(tree, m, sum,&result);
    return result;
}



int main()
{
    /*
    auto node1 = new Node();
    node1->data = 1;
    node1->id = 1;
    
    auto node2 = new Node();
    node2->data = 1;
    node2->id = 2;

    auto node3 = new Node();
    node3->data = 1;
    node3->id = 3;

    auto node4 = new Node();
    node4->data = 1;
    node4->id = 4;

    auto node5 = new Node();
    node5->data = 1;
    node5->id = 5;

    auto node6 = new Node();
    node6->data = 1;
    node6->id = 6;

    node1->left = node2;
    node1->right = node3;

    node2->left = node4;
    node2->right = node5;

    node3->left = node6;

    int sum = 3;
    auto path = num_path(node1, sum);
    std::cout << "sum = " << sum << " has path: " << path;
    */

    std::string output_file = "./request_" + std::to_string(1) + ".json";
    FILE * p_file;
    p_file = fopen (output_file.c_str(), "a+");

    fputs ("abcd1", p_file);
    fputs ("\n", p_file);
    fputs ("abcd2", p_file);
    fputs ("\n", p_file);
    fclose(p_file);
}
