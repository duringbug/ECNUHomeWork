#include <iostream>
#include <string>
#include <cstdlib>
#include <random>
#include <math.h>
#include <vector>
#include <sstream>
using namespace std;

enum Color
{
    RED,
    BLACK
};

template <typename K, typename V>
class RedBlackTree
{
private:
    struct Node
    {
        K key;
        V value;
        Color color;
        Node *left, *right;

        Node(K k, V v, Color c)
            : key(k), value(v), color(c), left(nullptr), right(nullptr) {}
    };

    Node *root;
    void destroy(Node *node)
    {
        if (!node)
        {
            return;
        }
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    void rotateLeft(Node *&node)
    {
        Node *right = node->right;  //          /  \                       /
        node->right = right->left;  //         /\  /\                      /
        right->left = node;         //        /\/\/\/\                     /
        right->color = node->color; //
        node->color = RED;          //
        node = right;               //
    }

    void rotateRight(Node *&node)
    {
        Node *left = node->left;
        node->left = left->right;
        left->right = node;
        left->color = node->color;
        node->color = RED;
        node = left;
    }

    void flipColor(Node *&node)
    {
        node->color = RED;
        node->left->color = BLACK;
        node->right->color = BLACK;
    }

    bool isRed(Node *node)
    {
        if (!node)
        {
            return false;
        }
        return (node->color == RED);
    }

    Node *insert(Node *node, K key, V value)
    {
        if (!node)
        {
            return new Node(key, value, RED);
        }

        if (key < node->key)
        {
            node->left = insert(node->left, key, value);
        }
        else if (key > node->key)
        {
            node->right = insert(node->right, key, value);
        }
        else
        {
            node->value = value;
        }

        // 进行颜色变换和旋转操作
        if (isRed(node->right) && !isRed(node->left))
        {
            rotateLeft(node);
        }
        if (isRed(node->left) && isRed(node->left->left))
        {
            rotateRight(node);
        }
        if (isRed(node->left) && isRed(node->right))
        {
            flipColor(node);
        }

        return node;
    }

public:
    RedBlackTree() : root(nullptr) {}

    ~RedBlackTree()
    {
        destroy(root);
    }

    void put(K key, V value)
    {
        root = insert(root, key, value);
        root->color = BLACK;
    }

    V get(K key) const
    {
        Node *node = root;
        while (node)
        {
            if (key < node->key)
            {
                node = node->left;
            }
            else if (key > node->key)
            {
                node = node->right;
            }
            else
            {
                return node->value;
            }
        }
        return V();
    }

    void inorderTraversal(Node *node)
    {
        if (node != nullptr)
        {
            inorderTraversal(node->left);
            switch (node->color)
            {
            case RED:
                cout << "R";
                break;
            case BLACK:
                cout << "B";
                break;
            default:
                break;
            }
            inorderTraversal(node->right);
        }
        return;
    }
    Node *getroot()
    {
        return this->root;
    }
};
int main()
{
    RedBlackTree<int, int> rbt = RedBlackTree<int, int>();
    int n;
    cin >> n;
    clock_t start, end;
    start = clock();
    for (int i = 0; i < n; i++)
    {
        int r = 0;
        cin >> r;
        rbt.put(r, r);
    }
    rbt.inorderTraversal(rbt.getroot());
    end = clock();
    cout << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
    return 0;
}
