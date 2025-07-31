// Hello, Roy
// Hello, Stepan

// Given a binary tree with a character in each node. The characters are Latin
// lowercase letters. The set of a node is defined as the character of this node
// and the characters of all its descendants. Leaf nodes does not have sets.
//
// Find the first two nodes in the tree such that their sets are equal.
// 
// Example:
//         a (abc)
//        /       \
//       b (bc)    c (cb)
//      / \       / \
//     b   c     c   b
//
// Result:
//     b (bc) and c (cb) have the same set {b, c}

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>

struct Node {
    char data;
    Node* left;
    Node* right;

    Node(char val) : data(val), left(nullptr), right(nullptr) {}
};

// This function performs a depth-first traversal to gather all characters in the subtree rooted at 'node'
std::set<char> CalculateNodeSet(Node* node) {
    std::set<char> nodeSet;
    if (node == nullptr) {
        return nodeSet;
    }

    nodeSet.insert(node->data);

    // Recursively add characters from left and right subtrees
    std::set<char> leftSubtreeSet = CalculateNodeSet(node->left);
    nodeSet.insert(leftSubtreeSet.begin(), leftSubtreeSet.end());

    std::set<char> rightSubtreeSet = CalculateNodeSet(node->right);
    nodeSet.insert(rightSubtreeSet.begin(), rightSubtreeSet.end());

    return nodeSet;
}

std::pair<Node*, Node*> FindEqualSets(Node* root) {
    std::map<std::set<char>, std::vector<Node*>> setNodeMap; // Stores sets and the nodes having those sets

    // Perform a level-order (or pre-order) traversal to process nodes in the order they appear
    // We'll use a queue for a breadth-first traversal
    std::vector<Node*> queue;
    if (root != nullptr) {
        queue.push_back(root);
    }

    int head = 0;
    while (head < queue.size()) {
        Node* currentNode = queue[head++];

        std::set<char> currentSet = CalculateNodeSet(currentNode);

        // Skip leaf nodes (as they don't have sets according to the problem)
        if (currentNode->left == nullptr && currentNode->right == nullptr) {
            // Leaf node, skip
        }
		else {
            // Check if this set has been seen before
            if (setNodeMap.count(currentSet)) {
                // We found a node with an equal set.
                // The first node with this set is already stored in setNodeMap[currentSet][0]
                return {setNodeMap[currentSet][0], currentNode}; 
            } else {
                // Add the current set and node to the map
                setNodeMap[currentSet].push_back(currentNode);
            }
        }

        // Add children to the queue for processing
        if (currentNode->left != nullptr) {
            queue.push_back(currentNode->left);
        }
        if (currentNode->right != nullptr) {
            queue.push_back(currentNode->right);
        }
    }

    // No two nodes with equal sets found
    return {nullptr, nullptr};
}

int main() {
    Node* root = new Node('a');
    root->left = new Node('b');
    root->right = new Node('c');
    root->left->left = new Node('b');
    root->left->right = new Node('c');
    root->right->left = new Node('c');
    root->right->right = new Node('b');

    std::pair<Node*, Node*> result = FindEqualSets(root);
    if (result.first != nullptr && result.second != nullptr) {
        std::cout << "First node with equal set: " << result.first->data << std::endl;
        std::cout << "Second node with equal set: " << result.second->data << std::endl;
    } else {
        std::cout << "No two nodes with equal sets found." << std::endl;
    }

	// Can use shared_ptr or other memory management structure to avoid cleanup
    delete root->right->right;
    delete root->right->left;
    delete root->left->right;
    delete root->left->left;
    delete root->right;
    delete root->left;
    delete root;

    return 0;
}
