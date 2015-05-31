#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <cstdlib>

using namespace std;

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
    bt.zigzagOrderTraversal(root);


    bt.release(root);
    
    return 0;
}


