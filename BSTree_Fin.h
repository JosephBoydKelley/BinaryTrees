#include <iostream>
#include "QueArr_BST_Fin.h"
/*
 * Joseph Kelley
 * 11/07/2020
 * BSTree_Fin.cpp
 */
using namespace std;

enum OrderType{ Pre_Order, Post_Order, In_Order };

template<class ItemType>
class TreeNode
{
public:
    ItemType data;
    TreeNode* left;
    TreeNode* right;
};

template<class ItemType>
class BSTree
{
public:
    BSTree();	//No arg constructor
    ~BSTree();	// Destructor

    BSTree(const BSTree& origTree);	//Copy Constructor
    void operator = (const BSTree& origTree); // Assignment Operator

    void makeEmpty();
    inline bool isEmpty() const;
    bool isFull() const;
    inline int getLength();

    ItemType getItem(ItemType item, bool& found);

    void addItem(ItemType item);

    void addItemIter(ItemType item);

    void deleteItem(ItemType item);

    void deleteItemIter(ItemType item);

    void printTree();

    void resetTree(OrderType order);

    ItemType getNextItem(OrderType order, bool& finished);

    //added
    void delNodes();
    void swapTree();

    void printTreeR();

    void computeBigO();

private:
    TreeNode<ItemType>* root;

    QueArr<ItemType> preQue;
    QueArr<ItemType> postQue;
    QueArr<ItemType> inQue;

    void destroy(TreeNode<ItemType>*& tree);
    void insert(TreeNode<ItemType>*& tree, ItemType& item);
    int countNodes(TreeNode<ItemType>*& tree);
    void copyTree(TreeNode<ItemType>*& copy, TreeNode<ItemType>*& origTree);
    void retrieve(TreeNode<ItemType>*& tree, ItemType& item, bool& found);
    void del(TreeNode<ItemType>*& tree, ItemType& item);
    void printNode(TreeNode<ItemType>*& tree);
    void deleteNode(TreeNode<ItemType>*& tree);
    void getPredecessor(TreeNode<ItemType>* tree, ItemType& item);
    void findNode(TreeNode<ItemType>* tree, ItemType item,
                  TreeNode<ItemType>*& nodePtr, TreeNode<ItemType>*& parentPtr);

    void preOrder(TreeNode<ItemType>* tree, QueArr<ItemType>& q);
    void postOrder(TreeNode<ItemType>* tree, QueArr<ItemType>& q);
    void inOrder(TreeNode<ItemType>* tree, QueArr<ItemType>& q );
    //added methods
    void deleteAllNodes(TreeNode<ItemType>*& tree);
    void Swap(TreeNode<ItemType>*& tree);

    void printNodeR(TreeNode<ItemType> *&tree);


    int computeBigOH(TreeNode<ItemType> *tree);
};

template <class ItemType>
BSTree<ItemType>::BSTree()
{
    root = NULL;
}

template <class ItemType>
BSTree<ItemType>::~BSTree()
{
    destroy(root);
}

template <class ItemType>
void BSTree<ItemType>::destroy(TreeNode<ItemType>*& tree)
{
    if (tree != NULL)
    {
        destroy(tree->left);
        destroy(tree->right);
        delete tree;
    }
}

template <class ItemType>
BSTree<ItemType>::BSTree(const BSTree& origTree)
{
    copyTree(root, origTree);
}

template<class ItemType>
void BSTree<ItemType>::operator=(const BSTree& origTree)
{
    if (&origTree == this)
        return;
    destroy(root);
    copyTree(root, origTree.root);
}

template<class ItemType>
void BSTree<ItemType>::makeEmpty()
{
    destroy(root);
    root = NULL;
}

template<class ItemType>
inline bool BSTree<ItemType>::isEmpty() const
{

    return root == NULL;
}

template<class ItemType>
bool BSTree<ItemType>::isFull() const
{
    TreeNode<ItemType>* location;
    try
    {
        location = new TreeNode<ItemType>;
        delete location;
        return false;
    }
    catch (std::bad_alloc exception)
    {
        return true;
    }

}

template<class ItemType>
inline int BSTree<ItemType>::getLength()
{
    return countNodes(root);
}

template<class ItemType>
ItemType BSTree<ItemType>::getItem(ItemType item, bool& found)
{
    retrieve(root, item, found);
    return item;
}

template<class ItemType>
void BSTree<ItemType>::addItem(ItemType item)
{
    insert(root, item);
}

template<class ItemType>
void BSTree<ItemType>::addItemIter(ItemType item)
{
    TreeNode<ItemType>* newNode;
    TreeNode<ItemType>* nodePtr;
    TreeNode<ItemType>* parentPtr;

    newNode = new TreeNode<ItemType>;
    newNode->data = item;
    newNode->left = NULL;
    newNode->right = NULL;

    findNode(root, item, nodePtr, parentPtr);

    if (parentPtr == NULL)
        root = newNode;
    else if (item < parentPtr->data)
        parentPtr->left = newNode;
    else
        parentPtr->right = newNode;

}

template<class ItemType>
inline void BSTree<ItemType>::deleteItem(ItemType item)
{
    del(root, item);
}

template<class ItemType>
void BSTree<ItemType>::deleteItemIter(ItemType item)
{
    TreeNode<ItemType>* nodePtr;
    TreeNode<ItemType>* parentPtr;
    findNode(root, item, nodePtr, parentPtr);
    if (nodePtr == root)
        deleteNode(root);
    else
    {
        if (parentPtr->left == nodePtr)
            deleteNode(parentPtr->left);
        else
            deleteNode(parentPtr->right);
    }
}

template<class ItemType>
inline void BSTree<ItemType>::printTree()

{
    printNode(root);
    cout << endl;
}

//Added
template<class ItemType>
inline void BSTree<ItemType>::computeBigO()
{
    int BigO = computeBigOH(root);
    cout << "The Big O is" << BigO;
}

//Added
template<class ItemType>
int BSTree<ItemType>::computeBigOH(TreeNode<ItemType>* tree){
    if (tree == NULL)
        return 0;
    else
    {
        int lSide = computeBigOH(tree->left);
        int rSide = computeBigOH(tree->right);
        /* use the larger one */
        if (lSide > rSide)
            return (lSide+1);
        else
            return (rSide+1);
    }
}
//Added
template<class ItemType>
inline void BSTree<ItemType>::printTreeR()

{
    printNodeR(root);
    cout << endl;
}

template<class ItemType>
void BSTree<ItemType>::resetTree(OrderType order)
{
    switch (order)
    {
        case Pre_Order: preOrder(root, preQue);
            break;
        case Post_Order: postOrder(root, postQue);
            break;
        case In_Order: inOrder(root, inQue);
            break;

    }
}

template<class ItemType>
ItemType BSTree<ItemType>::getNextItem(OrderType order, bool& finished)
{
    ItemType item;
    finished = false;
    switch (order)
    {
        case Pre_Order: preQue.dequeue(item);
            if (preQue.isEmpty())
                finished = true;
            break;
        case Post_Order: postQue.dequeue(item);
            if (postQue.isEmpty())
                finished = true;
            break;
        case In_Order: inQue.dequeue(item);
            if (inQue.isEmpty())
                finished = true;
            break;

    }

    return item;
}

template<class ItemType>
int BSTree<ItemType>::countNodes(TreeNode<ItemType>*& tree)
{
    if (tree == NULL)
        return 0;
    else
        return (countNodes(tree->left) + countNodes(tree->right)) + 1;
}

template<class ItemType>
void BSTree<ItemType>::copyTree(TreeNode<ItemType>*& copy, TreeNode<ItemType>*& origTree)
{
    if (origTree == NULL)
        copy = NULL;

    else
    {
        copy = new TreeNode<ItemType>;
        copy->data = origTree->data;

        copyTree(copy->left, origTree->left);
        copyTree(copy->right, origTree->right);
    }
}

template<class ItemType>
void BSTree<ItemType>::retrieve(TreeNode<ItemType>*& tree, ItemType& item, bool& found)
{
    if (tree == NULL)
    {
        found = false;
    }
    else if (item < tree->data)
    {
        retrieve(tree->left, item, found);
    }
    else if (item > tree->data)
    {
        retrieve(tree->right, item, found);
    }
    else
    {
        item = tree->data;
        found = true;
    }
}

template<class ItemType>
void BSTree<ItemType>::del(TreeNode<ItemType>*& tree, ItemType& item)
{
    if (item < tree->data)
        del(tree->left, item);
    else if (item > tree->data)
        del(tree->right, item);
    else
        deleteNode(tree);
}

template<class ItemType>
void BSTree<ItemType>::printNode(TreeNode<ItemType>*& tree)
{

    {
        if (tree == root)
        {
            cout << "Root's data: " << root->data << endl;
        }
        if (tree != NULL)
        {
            printNode(tree->left);
            cout << tree->data << " ";
            printNode(tree->right);
        }

    }
}

//Added
template<class ItemType>
void BSTree<ItemType>::printNodeR(TreeNode<ItemType>*& tree)
{

    {
        if (tree == root)
        {
            cout << "Root's data: " << root->data << endl;
        }
        if (tree != NULL)
        {
            printNodeR(tree->right);
            cout << tree->data << " ";
            printNodeR(tree->left);
        }

    }
}
template<class ItemType>
void BSTree<ItemType>::deleteNode(TreeNode<ItemType>*& tree)
{
    ItemType item;
    TreeNode<ItemType>* tempPtr;
    tempPtr = tree;
    if (tree->left == NULL)
    {
        tree = tree->right;
        delete tempPtr;
    }
    else if (tree->right == NULL)
    {
        tree = tree->left;
        delete tempPtr;
    }
    else
    {
        getPredecessor(tree->left, item);
        tree->data = item;
        del(tree->left, item);
    }

}

template<class ItemType>
void BSTree<ItemType>::getPredecessor(TreeNode<ItemType>* tree, ItemType& item)
{
    while (tree->right != NULL)
        tree = tree->right;

    item = tree->data;
}

template<class ItemType>
void BSTree<ItemType>::findNode(TreeNode<ItemType>* tree, ItemType item,
                                TreeNode<ItemType>*& nodePtr, TreeNode<ItemType>*& parentPtr)
{
    nodePtr = tree;
    parentPtr = NULL;
    bool found = false;
    while (nodePtr != NULL && !found)
    {
        if (item < nodePtr->data)
        {
            parentPtr = nodePtr;
            nodePtr = nodePtr->left;
        }
        else if (item > nodePtr->data)
        {
            parentPtr = nodePtr;
            nodePtr = nodePtr->right;
        }
        else
        {
            found = true;
        }
    }

}

template<class ItemType>
void BSTree<ItemType>::preOrder(TreeNode<ItemType>* tree, QueArr<ItemType>& preQue)
{
    if (tree != NULL)
    {
        preQue.enqueue(tree->data);
        preOrder(tree->left, preQue);
        preOrder(tree->right, preQue);
    }

}
template<class ItemType>
void BSTree<ItemType>::postOrder(TreeNode<ItemType>* tree, QueArr<ItemType>& postQue)
{
    if (tree != NULL)
    {
        postOrder(tree->left, postQue);
        postOrder(tree->right, postQue);
        postQue.enqueue(tree->data);

    }

}

template<class ItemType>
void BSTree<ItemType>::inOrder(TreeNode<ItemType>* tree, QueArr<ItemType>& inQue)
{
    if (tree != NULL)
    {
        inOrder(tree->left, inQue);
        inQue.enqueue(tree->data);
        inOrder(tree->right, inQue);
    }

}
template<class ItemType>
void BSTree<ItemType>::insert(TreeNode<ItemType>*& tree, ItemType& item)
{
    if (tree == NULL)
    {
        tree = new TreeNode<ItemType>;
        tree->data = item;
        tree->right = NULL;
        tree->left = NULL;
    }
    else if (item < tree->data)
    {
        insert(tree->left, item);
    }
    else
    {
        insert(tree->right, item);
    }
}
template<class ItemType>
void BSTree<ItemType>::delNodes(){
    deleteAllNodes(root);
}
template<class ItemType>
void BSTree<ItemType>::deleteAllNodes(TreeNode<ItemType>*& tree) {
    if (tree== NULL)
        return;
    else {
        deleteAllNodes(tree->left);
        deleteAllNodes(tree->right);
    }
    deleteNode(tree);
}
template<class ItemType>
void BSTree<ItemType>::swapTree(){
    Swap(root);
}

template<class ItemType>
void BSTree<ItemType>::Swap(TreeNode<ItemType>*& tree) {
    if (tree== NULL)
        return;
    else {
        TreeNode<ItemType> *temp= tree->left;
        tree->left=tree->right;
        tree->right= temp;
        Swap(tree->left);
        Swap(tree->right);
    }
}
