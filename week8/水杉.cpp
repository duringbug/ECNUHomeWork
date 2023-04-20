#include <iostream>
#include <string>
#include <cstdlib>
#include <random>
#include <math.h>
#include <vector>
#include <sstream>
using namespace std;

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
        inorderTraversal(node->left);
        if (node->value != 0)
        {
            cout << node->value << " ";
        }
        inorderTraversal(node->right);
    }
    void preorderTraversal(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        if (node->value != 0)
        {
            cout << node->value << " ";
        }
        preorderTraversal(node->left);
        preorderTraversal(node->right);
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
    BST bst;
    string input;
    cin >> input;
    vector<string> arr;
    stringstream ss(input);
    string token;

    while (getline(ss, token, ','))
    {
        arr.push_back(token);
    }

    for (int i = 0; i < arr.size(); i++)
    {
        if (!arr[i].compare("null"))
        {
            bst.insert(0);
        }
        else
        {
            bst.insert(stoi(arr[i]));
        }
    }
    bst.preorderTraversal(bst.root);
    cout << endl
         << bst.getMin(bst.root)->value;
    cout << endl
         << bst.getMax(bst.root)->value << endl;

    int n; // 查询次数
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int in = 0;
        cin >> in;
        Node *r = bst.search(in);
        if (r != nullptr)
        {
            cout << "yes" << endl;
        }
        else
        {
            cout << "no" << endl;
        }
    }
    cin >> n; // 寻找前驱后继次数
    for (int i = 0; i < n; i++)
    {
        int in = 0;
        cin >> in;
        cout << bst.getPre(bst.search(in))->value << endl
             << bst.getSuc(bst.search(in))->value << endl;
    }
    return 0;
}
