/***
 *
 * A program to perform the basic operations insertion, deletion, search on a Binary Search Tree
 *
 * For a Binary Search Tree with no duplicates,
 *      the values to the left of any node are less than the value at the current node
 *      the values to the right of any node are greater than the value at the current node
 *
 * Insertion:
 *      In a Binary Search Tree nodes are always inserted at the leaf.
 *      Check the value to be inserted with the value of the current node.
 *
 *      If (value less than current node)
 *          traverse left until a leaf node is found
 *      else
 *          traverse right until a leaf node is found
 *     
 *      create new node with value and return.  
 *
 * Search:
 *      Check the value to be searched with the value of the current node.
 *      If value found return
 *
 *      If (value less than current node)
 *          traverse left until a leaf node is found
 *      else
 *          traverse right until a leaf node is found
 *   
 * Deletion:
 *      1.  If the node to be deleted is a leaf node, delete the node.
 *
 *      2.  If the node to be deleted has an empty left OR right child,
 *          Swap the contents of the root and the child
 *          Delete the child node.
 *
 *      3.  If the node has non-empty left and right nodes.
 *          
 *          Find the node's inorder successor. 
 *          This is the smallest value in the right subtree of the node.
 *
 *          Copy the contents of the inorder successor to the node
 *
 *          Delete the inorder successor  
 *
***/

#include <iostream>
#include <queue>

class BSTNode{
public:
    BSTNode(int value):_data(value){
    }

friend class BinarySearchTree;  /// The BinarySearchTree class needs access to the
                                /// _data, left and right member variables.

protected:
    int _data;
    BSTNode * left, * right;
};

class BinarySearchTree {
public:
    BinarySearchTree():_root(nullptr){
    }

    void insert(int value)  {
        insert(_root, value);
    }

    bool search(int value) {
        bool keyFound = false;

        if(keyFound == ( search(_root, value) != nullptr) )
            std::cout << value << " key found in BST" << std::endl;
        else
            std::cout << value << " key not found in BST" << std::endl;

        return keyFound;
    }

    void deleteNode(int value)    {
        deleteNode(_root, value);
    }

    void print();

protected:
    BSTNode * _root;
    BSTNode * insert(BSTNode* & root, int value);
    BSTNode * search(BSTNode* root, int value);
    BSTNode * deleteNode(BSTNode* & root, int value);
    BSTNode * findSmallest(BSTNode * root);
};

using BST = BinarySearchTree;

BSTNode* BST::insert(BSTNode* & root, int value)
{
    if(root == nullptr)    {
        root = new BSTNode(value);
        return root;
    }

    if(value < root->_data)
        root->left = insert(root->left, value);
    else
        root->right = insert(root->right, value);

    return root;
}

BSTNode* BST::search(BSTNode* root, int value)
{
    if(root == nullptr || root->_data == value)    {
        return root;
    }

    if(value < root->_data)
        return search(root->left, value);
    else
        return search(root->right, value);
}

BSTNode * BST::findSmallest(BSTNode * root)
{
    while(root && root->left != nullptr)
        root = root->left;

    return root;
}

BSTNode* BST::deleteNode(BSTNode* & root, int value)
{
    if(root == nullptr)    {
        return root;
    }

    if(value < root->_data)
       root->left = deleteNode(root->left, value);
    else if(value > root->_data)
       root->right = deleteNode(root->right, value);
    else
    {
       /// This is a leaf node, delete it      
       if(root->left == nullptr && root->right == nullptr)  {
            delete root;
            root = nullptr;
       }
       /// The tree has an empty left subtree, the node's new value would be the right node.
       /// Return the right node to be linked to the previous root. 
       else if (root->left == nullptr)   {
            BSTNode * right = root->right;
            delete root; root = nullptr;
            return right;
       }
       /// The tree has an empty right subtree, the node's new value would be the left node.
       /// Return the left node to be linked to the previous root. 
       else if (root->right == nullptr) {
            BSTNode * left = root->left;
            delete root; root = nullptr;
            return left;
       }
       /// The node has both non-empty right and left subtrees
       /// Find the inorder successor, i.e. the smallest node in the right subtree.
       /// Copy the contents of the inorder successor to the current node
       /// delete the inorder successor
       else {
           BSTNode * inorderSucc = findSmallest(root->right);
           root->_data = inorderSucc->_data;
           root->right = deleteNode(root->right, inorderSucc->_data);
       }
    }

    return root;
}

void BST::print()
{
    if(_root == nullptr)
        return;

    std::queue<BSTNode *> bstNodes;

    /// The preOrder traversal will print the nodes in the ascending order;
    bstNodes.push(_root);

    while(!bstNodes.empty())
    {
        std::cout << bstNodes.front()->_data << " ";

        if( (bstNodes.front())->left != nullptr )
            bstNodes.push(bstNodes.front()->left);

        if( (bstNodes.front())->right != nullptr )
            bstNodes.push(bstNodes.front()->right);

        bstNodes.pop(); /// Pop the front, i.e the root node;
    }
    std::cout << std::endl;
}


int main()
{
    BinarySearchTree bst1;

 /// Insert values in the new list   
    bst1.insert(5);
    bst1.insert(3);
    bst1.insert(4);
    bst1.insert(2);
    bst1.insert(7);
    bst1.insert(6);
    bst1.insert(9);

    bst1.print();

    bst1.search(10);
    bst1.search(5);
    bst1.search(2);
    bst1.search(9);

    std::cout << "After deleting 5" << std::endl;
    bst1.deleteNode(5);
    bst1.print();

    std::cout << "After deleting 9" << std::endl;
    bst1.deleteNode(9);
    bst1.print();

    return 0;
}


