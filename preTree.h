/*
 * Joseph Kelley
 * 11/07/2020
 * preeTree.h
 */
#include <iostream>
using namespace std;
class node {
public:
    char data;
    node *left;
    node *right;
    node(char data) {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};
class StackNode {
public:
    node *treeNode;
    StackNode *next;
    StackNode(node *treeNode) {
        this->treeNode = treeNode;
        next = NULL;
    }
};
class preTree {
private:
    StackNode *top;
public:
    preTree() {
        top = NULL;
    }
    void push(node *ptr) {
        if (top == NULL)
            top = new StackNode(ptr);
        else {
            StackNode *temp = new StackNode(ptr);
            temp->next = top;
            top = temp;
        }
    }
    node *pop() {
        if (top == NULL) {
            cout << "Empty" << endl;
            return NULL;
        }
        else {
            node *ptr = top->treeNode;
            top = top->next;
            return ptr;
        }
    }
    node *Top() {
        return top->treeNode;
    }

    void insert(char val) {
        if (isalpha(val)) {
            node *temp = new node(val);
            push(temp);
        }
        else if (isoperator(val)) {
            node *temp = new node(val);
            temp->left = pop();
            temp->right = pop();
            push(temp);
        }
        else {
            cout<<"Try Again"<<endl;
            return;
        }
    }
    static bool isalpha(char c) {
        return (c >= 'A' && c <= 'Z');
    }
    static bool isoperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }
    void make(string pre) {
        for (int i = pre.length() - 1; i >= 0; i--)
            insert(pre[i]);
        cout<< endl <<"Prefix: ";
        prefix();
        cout<< endl <<"Infix: ";
        infix();
        cout<< endl <<"Postfix: ";
        postfix();
    }
    void postfix() {
        postOrder(Top());
    }
    void postOrder(node *ptr) {
        if (ptr != NULL) {
            postOrder(ptr->left);
            postOrder(ptr->right);
            cout<<ptr->data;
        }
    }
    void infix() {
        inOrder(Top());
    }
    void inOrder(node *ptr) {
        if (ptr != NULL) {
            cout << "(";
            inOrder(ptr->left);
            cout<<ptr->data;
            inOrder(ptr->right);
            cout << ")";
        }
    }
    void prefix() {
        preOrder(Top());
    }
    void preOrder(node *ptr) {
        if (ptr != NULL) {
            cout<<ptr->data;
            preOrder(ptr->left);
            preOrder(ptr->right);
        }
    }
};