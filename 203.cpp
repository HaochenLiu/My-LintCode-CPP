/*
203. Segment Tree Modify

For a Maximum Segment Tree, which each node has an extra value max to store the maximum value in this node's interval.
Implement a modify function with three parameter root, index and value to change the node's value with [start, end] = [index, index] to the new given value. Make sure after this change, every node in segment tree still has the max attribute with the correct value.
Have you met this question in a real interview?
Example
For segment tree:
                     [1, 4, max=3]
                    /                \
        [1, 2, max=2]                [3, 4, max=3]
       /              \             /             \
[1, 1, max=2], [2, 2, max=1], [3, 3, max=0], [4, 4, max=3]


if call modify(root, 2, 4), we can get:
                     [1, 4, max=4]
                    /                \
        [1, 2, max=4]                [3, 4, max=3]
       /              \             /             \
[1, 1, max=2], [2, 2, max=4], [3, 3, max=0], [4, 4, max=3]


or call modify(root, 4, 0), we can get:
                     [1, 4, max=2]
                    /                \
        [1, 2, max=2]                [3, 4, max=0]
       /              \             /             \
[1, 1, max=2], [2, 2, max=1], [3, 3, max=0], [4, 4, max=0]


Note
We suggest you finish problem Segment Tree Build and Segment Tree Query first.
Challenge
Do it in O(h) time, h is the height of the segment tree.
*/

/**
 * Definition of SegmentTreeNode:
 * class SegmentTreeNode {
 * public:
 *     int start, end, max;
 *     SegmentTreeNode *left, *right;
 *     SegmentTreeNode(int start, int end, int max) {
 *         this->start = start;
 *         this->end = end;
 *         this->max = max;
 *         this->left = this->right = NULL;
 *     }
 * }
 */
class Solution {
public:
    /**
     *@param root, index, value: The root of segment tree and
     *@ change the node's value with [index, index] to the new given value
     *@return: void
     */
    void modify(SegmentTreeNode *root, int index, int value) {
        if (root->start == root->end) {
            root->max = value;
            return;
        }
        int mid = root->start + (root->end - root->start) / 2;
        if (index <= mid) {
            modify(root->left, index, value);
        } else {
            modify(root->right, index, value);
        }
        root->max = max(root->left->max, root->right->max);
    }
};
