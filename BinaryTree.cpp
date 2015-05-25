#include <iostream>
#include <queue>
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
    TreeNode* levelOrderDeserialize(const char* src[], int m) {
        if (m == 0)
            return nullptr;

        int index = 0;
        TreeNode* root = new TreeNode(atoi(src[index]));
        index ++;
        std::queue<TreeNode*> q;
        q.push(root);
        
//        while (!q.empty()) {
        while (index < m) {
            TreeNode* node = q.front();
            if (strcmp(src[index], "#") != 0) {
                node->left = new TreeNode(atoi(src[index]));
                q.push(node->left);
                index ++;
            }
            if (strcmp(src[index], "#") != 0) {
                node->right = new TreeNode(atoi(src[index]));
                q.push(node->right);
                index ++;
            }
            q.pop();
        }

        return root;
    }

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
};

int main()
{
    const char* src[] = {"1", "2", "3", "4", "5", "6", "7"};

    BinaryTree bt;
    TreeNode* root = bt.levelOrderDeserialize(src, 7);
    bt.preorderTraversal(root);
    cout << endl;

    bt.levelOrderTraversal(root);
    cout << endl;

    return 0;
}


