//
// Created by DELL on 5/3/2023.
//
#include <iostream>

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

void insert(TreeNode* node, int value) {
    if (value < node->value) {
        if (node->left == nullptr) {
            node->left = new TreeNode(value);
        } else {
            insert(node->left, value);
        }
    } else {
        if (node->right == nullptr) {
            node->right = new TreeNode(value);
        } else {
            insert(node->right, value);
        }
    }
}

void inorder_traversal(TreeNode* node) {
    if (node->left) {
        inorder_traversal(node->left);
    }
    std::cout << node->value << " ";
    if (node->right) {
        inorder_traversal(node->right);
    }
}

int main() {
    // Create the root node with a value of 500
    TreeNode* root = new TreeNode(500);

    // Insert numbers from 1 to 1000 into the tree
    for (int i = 1; i <= 1000; ++i) {
        if (i != 500) {
            insert(root, i);
        }
    }

    // Perform an inorder traversal to display the sorted data
    inorder_traversal(root);


    return 0;
}
