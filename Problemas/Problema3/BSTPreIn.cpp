#include <algorithm>
#include <vector>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)

    {
        if (preorder.empty() || inorder.empty()){
            return nullptr;
        }

        int rootVal = preorder[0];
        TreeNode* root = new TreeNode(rootVal);
        auto it = std::find(inorder.begin(), inorder.end(), rootVal);
        int index = std::distance(inorder.begin(), it);

        std::vector<int> leftIn(inorder.begin(), inorder.begin() + index);
        std::vector<int> rightIn(inorder.begin() + index + 1, inorder.end());

        std::vector<int> leftPre(preorder.begin() + 1, preorder.begin() + 1 + leftIn.size());
        std::vector<int> rightPre(preorder.begin() + 1 + leftIn.size(), preorder.end());

        root->left = buildTree(leftPre, leftIn);
        root->right = buildTree(rightPre, rightIn);

        return root;
    }
};