#include <iostream>
#include <string>
#include <cstdlib>
#include <random>
#include <math.h>
#include <vector>
#include <sstream>
using namespace std;
#define RANGE 1000000 // 数字范围
#define INSERT 10     // 插入值得个数
#define TIMES 1       // 寻找次数

class Node
{
public:
    int value;
    Node *left;
    Node *right;
    Node *parent;

    Node(int v)
    {
        value = v;
        left = nullptr;
        right = nullptr;
    }
};

class BST
{
public:
    Node *root;

    BST()
    {
        root = nullptr;
    }

    void insert(int v)
    {
        Node *newNode = new Node(v);
        if (root == nullptr)
        {
            root = newNode;
            return;
        }
        Node *cur = root;
        while (true)
        {
            if (v < cur->value)
            {
                if (cur->left == nullptr)
                {
                    if (v != 0)
                    {
                        cur->left = newNode;
                        newNode->parent = cur;
                    }
                    break;
                }
                cur = cur->left;
            }
            else
            {
                if (cur->right == nullptr)
                {
                    if (v != 0)
                    {
                        cur->right = newNode;
                        newNode->parent = cur;
                    }
                    break;
                }
                cur = cur->right;
            }
        }
    }

    Node *search(int v)
    {
        Node *cur = root;
        while (cur != nullptr)
        {
            if (v == cur->value)
            {
                return cur;
            }
            else if (v < cur->value)
            {
                cur = cur->left;
            }
            else
            {
                cur = cur->right;
            }
        }
        return nullptr;
    }

    void inorderTraversal(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        if (node->value != 0)
        {
            cout << node->value << " ";
        }
        inorderTraversal(node->left);
        inorderTraversal(node->right);
    }
    void preorderTraversal(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        preorderTraversal(node->left);
        if (node->value != 0)
        {
            cout << node->value << " ";
        }
        preorderTraversal(node->right);
    }
    void sucorderTraversal(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        sucorderTraversal(node->right);
        if (node->value != 0)
        {
            cout << node->value << " ";
        }
        sucorderTraversal(node->left);
    }
    Node *getMin(Node *node)
    {
        if (node->left == nullptr || node->left->value == 0)
        {
            return node;
        }
        return getMin(node->left);
    }
    Node *getMax(Node *node)
    {
        if (node->right == nullptr || node->right->value == 0)
        {
            return node;
        }
        return getMax(node->right);
    }
    Node *getPre(Node *p)
    {
        if (p == nullptr || p->value == 0)
        {
            return nullptr;
        }
        if (p->left != nullptr)
        {
            return getMax(p->left);
        }
        Node *cur = p;
        Node *parent = cur->parent;
        while (parent != nullptr && cur == parent->left)
        {
            cur = parent;
            parent = cur->parent;
        }
        return parent;
    }

    Node *getSuc(Node *p)
    {
        if (p == nullptr || p->value == 0)
        {
            return nullptr;
        }
        if (p->right != nullptr)
        {
            return getMin(p->right);
        }
        Node *cur = p;
        Node *parent = cur->parent;
        while (parent != nullptr && cur == parent->right)
        {
            cur = parent;
            parent = cur->parent;
        }
        return parent;
    }
};

int main()
{
    std::default_random_engine e;
    std::uniform_int_distribution<int> u(-1 * RANGE, RANGE);
    e.seed(time(nullptr));
    BST bst;
    for (int i = 0; i < INSERT; i++)
    {
        bst.insert(u(e));
    }
    clock_t start, end;
    start = clock();
    for (int n = 0; n < TIMES; n++)
    {
        bst.search(u(e));
    }
    end = clock();
    cout << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
    cout << bst.search(1) << endl;
    bst.inorderTraversal(bst.root);
    cout << endl;
    bst.preorderTraversal(bst.root);
    cout << endl;
    bst.sucorderTraversal(bst.root);
    return 0;
}
