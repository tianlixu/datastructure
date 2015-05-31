#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <cstdlib>

using namespace std;

//#define CRLF cout << endl;

// Definition for a binary tree node.
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };


class BinaryTree
{
public:
    /// in level order
    std::string levelOrderSerialize(TreeNode* root) {
        if (root == nullptr)
            return "#";
        
        string s;
        std::queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* node = q.front();
            if (node == nullptr) {
                s += "# ";
            } else {
                s += std::to_string(node->val) + " ";
                q.push(node->left);
                q.push(node->right);
            }

            q.pop();
        }

        return s;
    }
    
    TreeNode* levelOrderDeserialize(const char* src[], int m) {
        if (m == 0)
            return nullptr;

        int index = 0;
        TreeNode* root = new TreeNode(atoi(src[index]));
        index ++;
        std::queue<TreeNode*> q;
        q.push(root);
        
        while (index < m) {
            TreeNode* node = q.front();
            
            if (strcmp(src[index], "#") != 0) {
                node->left = new TreeNode(atoi(src[index]));
                q.push(node->left);
            }
            index ++;

            if (strcmp(src[index], "#") != 0) {
                node->right = new TreeNode(atoi(src[index]));
                q.push(node->right);
            }
            index ++;

            q.pop();
        }

        return root;
    }


    /// Traversal: preorder, inorder, postorder, level order, zigzag order

    void preorderTraversal(TreeNode *root) {
        if (root == nullptr)
            return;

        cout << root->val << " ";
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }

    void levelOrderTraversal(TreeNode *root) {
        if (root == nullptr)
            return;
        
        std::queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* node = q.front();

            cout << node->val << " ";
            
            if (node->left != nullptr)
                q.push(node->left);
            if (node->right != nullptr)
                q.push(node->right);
            
            q.pop();
        }
    }

    /*
     * zigzag: solution 1 with 2 stacks
     */
    void zigzagOrderTraversal(TreeNode *root) {
        if (root == nullptr)
            return;

        bool isLeftToRight = true;
        std::stack<TreeNode*> thisLevel;
        std::stack<TreeNode*> nextLevel;

        thisLevel.push(root);
        while (!thisLevel.empty()) {
            TreeNode* node = thisLevel.top();
            // visit node
            cout << node->val << " ";

            if (isLeftToRight) {
                if (node->left != nullptr)
                    nextLevel.push(node->left);
                if (node->right != nullptr)
                    nextLevel.push(node->right);
            } else {
                if (node->right != nullptr)
                    nextLevel.push(node->right);
                if (node->left != nullptr)
                    nextLevel.push(node->left);
            }

            thisLevel.pop();
            if (thisLevel.empty()) {
                isLeftToRight = !isLeftToRight;
                std::swap(thisLevel, nextLevel);
                cout << endl;
            }
        }
    }

    /*
     * zigzag traversal, solution 2 with 2 stacks and recursion
     */
    void zigzagOrderTraversal2(TreeNode* root) {
        if (root == nullptr)
            return;
        
        std::stack<TreeNode*> thisLevel;
        std::stack<TreeNode*> nextLevel;

        thisLevel.push(root);
        zigzagOrderTraversal2Recursive(thisLevel, nextLevel, true);
    }
    
    void zigzagOrderTraversal2Recursive(std::stack<TreeNode*> thisLevel, std::stack<TreeNode*> nextLevel, bool isLeftToRight) {
        while (!thisLevel.empty()) {
            TreeNode* node = thisLevel.top();
            // visit node
            cout << node->val << " ";

            if (isLeftToRight) {
                if (node->left != nullptr)
                    nextLevel.push(node->left);
                if (node->right != nullptr)
                    nextLevel.push(node->right);
            } else {
                if (node->right != nullptr)
                    nextLevel.push(node->right);
                if (node->left != nullptr)
                    nextLevel.push(node->left);
            }

            thisLevel.pop();
        }

        if (!nextLevel.empty())
            zigzagOrderTraversal2Recursive(nextLevel, thisLevel, !isLeftToRight);
    }
    
public:
    /*
     * zigzag traversal, solution 2(recursive), Time: O(n^2)
     */
    void zigzagOrderTraversal3(TreeNode* root) {
        int height = this->height(root);
        for (int i=0; i<= height; i++) {
            printLevel(root, i, i%2 == 0);
        }
    }
private:
    void printLevel(TreeNode* root, int height, bool isLeftToRight) {
        if (root == nullptr)
            return;

        if (height == 0)
            cout << root->val << " ";

        if (height > 0) {
            if (isLeftToRight) {
                printLevel(root->left, height-1, isLeftToRight);
                printLevel(root->right, height-1, isLeftToRight);                
            } else {
                printLevel(root->right, height-1, isLeftToRight);
                printLevel(root->left, height-1, isLeftToRight);
            }
        }
    }


public:    
    /*
     * height: Number of edges in longest path from root to a leaf node
     */
    int height(TreeNode* root) {
        if (root == nullptr)
            return -1;
        else
            return std::max(height(root->left), height(root->right)) + 1;
    }

    /*
     * To free the memory in a tree using postOrder traversal
     */
    void release(TreeNode* root) {
        if (root == nullptr)
            return;

        release(root->left);
        release(root->right);
        delete(root);
    }
};

int main()
{
    //const char* src[] = {"1", "2", "3", "4", "5", "6", "7"};
    const char* src[] = {"1", "2", "3", "#", "#", "6", "7", "#", "#", "#", "#"};

    BinaryTree bt;
    TreeNode* root = bt.levelOrderDeserialize(src, 7);
    bt.preorderTraversal(root);
    cout << endl;

    bt.levelOrderTraversal(root);
    cout << endl;

    cout << bt.levelOrderSerialize(root) << endl;


    /// test zigzag
    cout << "zigzag with 2 stacks: " << endl;
    bt.zigzagOrderTraversal(root);

    cout << "zigzag with 2 stacks and recursion:" << endl;
    bt.zigzagOrderTraversal2(root);
    cout << endl;

    cout << "zigzag with recursive: " << endl;
    bt.zigzagOrderTraversal3(root);
    cout << endl;
    

    /// height
    cout << "height=" << bt.height(root) << endl;

    bt.release(root);
    
    return 0;
}


