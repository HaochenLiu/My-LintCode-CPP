/*
093. Balanced Binary Tree

Given a binary tree, determine if it is height-balanced.
For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.
Have you met this question in a real interview?
Example
Given binary tree A={3,9,20,#,#,15,7}, B={3,#,20,15,7}
A)  3            B)    3 
   / \                  \
  9  20                 20
    /  \                / \
   15   7              15  7


The binary tree A is a height-balanced binary tree, but B is not.
*/

/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 */
class Solution {
private:
    int getHeight(TreeNode* root) {
        if(root == NULL) return 0;
        if(root->left == NULL && root->right == NULL) return 1;
        return 1 + max(getHeight(root->left), getHeight(root->right));
    }
    
public:
    /**
     * @param root: The root of binary tree.
     * @return: True if this Binary tree is Balanced, or false.
     */
    bool isBalanced(TreeNode *root) {
        // write your code here
        if(root == NULL) return true;
        if(root->left == NULL && root->right == NULL) return true;
        if(isBalanced(root->left) && isBalanced(root->right) && abs(getHeight(root->left) - getHeight(root->right)) <= 1) {
            return true;
        }
        return false;
    }
};
