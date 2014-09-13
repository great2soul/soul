#include <iostream>
#include <time.h>

using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node* parent;
    bool visited;
    //Node(){}
    Node(int d);
    Node(int d, Node* l, Node* r);
};

class BinaryTree {
public:
    Node* root;
    BinaryTree(Node* r);
    //递归实现中序遍历
    void recurse_in_order_visit(Node* root);
    //非递归用栈实现中序遍历
    void non_recurse_using_stack_in_order_visit(Node* root);
    //非递归且不用栈实现中序遍历
    void non_recurse_non_stack_in_order_visit(Node* root);
    enum TRAVESAL_STATE {
        LEFT_NOT_TRAVERS,//左子树未遍历
        LEFT_TRAVERSED,//左子树已遍历(包括左子树为空)
        RIGHT_TRAVERSED//右子树已遍历(右子树为空)
    };
};
int main()
{
    Node* node1 =new Node(1, NULL, NULL);
    Node* node2 =new Node(2, node1, NULL);
    Node* node3 =new Node(4, NULL, NULL);
    Node* node4 =new Node(3, node2, node3);
    Node* node5 =new Node(7, NULL, NULL);
    Node* node6 =new Node(6, NULL, node5);
    Node* node7 =new Node(9, NULL, NULL);
    Node* node8 =new Node(8, node6, node7);
    Node* root =new Node(5, node4, node8);
    BinaryTree* binary_tree =new BinaryTree(root);
    cout<<"递归中序遍历的结果："<<endl;
    binary_tree->recurse_in_order_visit(binary_tree->root);
    cout<<endl;
    cout<<"非递归用栈中序遍历的结果："<<endl;
    binary_tree->non_recurse_using_stack_in_order_visit(binary_tree->root);
    cout<<endl;
        //若使用非递归且不用栈来进行中序遍历，则需要parent指针作为辅助
    node1->parent = node2;
    node2->parent = node4;
    node3->parent = node4;
    node5->parent = node6;
    node6->parent = node8;
    node7->parent = node8;
    node4->parent = root;
    node8->parent = root;
    cout<<"非递归且不用栈中序遍历的结果："<<endl;
    binary_tree->non_recurse_non_stack_in_order_visit(binary_tree->root);
    cout<<endl;
    return0;
}

Node::Node(int d)
{
    data = d;
    parent = left = right = NULL;
    visited =false;
}

Node::Node(int d, Node* l, Node* r)
{
    data = d;
    left = l;
    right = r;
    parent = NULL;
    visited =false;
}

BinaryTree::BinaryTree(Node* r)
{
    root = r;
}

//递归实现中序遍历
void BinaryTree::recurse_in_order_visit(Node* root)
{
    if(root != NULL) {
        recurse_in_order_visit(root->left);
        printf("%d\t", root->data);
        recurse_in_order_visit(root->right);
    }
}

//非递归用栈实现中序遍历
void BinaryTree::non_recurse_using_stack_in_order_visit(Node* root)
{
    Node* stack[9];
    int top =-1;
    while(root != NULL || top >-1) {
        while(root != NULL) {
            stack[++top] = root;
            root = root->left;
        }
        if(top >-1) {
            root = stack[top--];
            printf("%d\t", root->data);
            root = root->right;
        }
    }
}

//非递归且不用栈实现中序遍历
void BinaryTree::non_recurse_non_stack_in_order_visit(Node* root)
{
    while ( root != NULL ) {
        while ( root->left != NULL &&!root->left->visited ) {      
            //一路向左
            root = root->left;
        }
        if ( !root->visited ) {                 
            cout<<root->data<<"\t";
            root->visited=true;
        }
        if ( root->right != NULL &&!root->right->visited ) {                  
            //右子树
            root = root->right;
        }
        else {           
            //回溯至parent节点
            root = root->parent;
        }
    }
}