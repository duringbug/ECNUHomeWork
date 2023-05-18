#include <iostream>
#include <random>
using namespace std;
#define RANGE 1000000

template <typename T>
class RBNode
{
public:
    enum Color
    {
        RED,
        BLACK
    };

    RBNode(const T &data)
        : data_(data), color_(RED), parent_(nullptr),
          left_(nullptr), right_(nullptr) {}

    T data_;
    Color color_;
    RBNode *parent_;
    RBNode *left_;
    RBNode *right_;
};

template <typename T>
class RBTree
{
public:
    RBTree() : root_(nullptr) {}

    void Insert(const T &data)
    {
        RBNode<T> *node = new RBNode<T>(data);
        Insert(node);
    }

    void InOrderWalk()
    {
        InOrderWalk(root_);
        cout << endl;
    }

private:
    void Insert(RBNode<T> *node)
    {
        RBNode<T> *parent = nullptr;
        RBNode<T> *current = root_;
        while (current != nullptr)
        {
            parent = current;
            if (node->data_ < current->data_)
            {
                current = current->left_;
            }
            else
            {
                current = current->right_;
            }
        }
        node->parent_ = parent;
        if (parent == nullptr)
        {
            root_ = node;
        }
        else if (node->data_ < parent->data_)
        {
            parent->left_ = node;
        }
        else
        {
            parent->right_ = node;
        }
        InsertFixup(node);
    }

    void InsertFixup(RBNode<T> *node)
    {
        while (node->parent_ != nullptr && node->parent_->color_ == RBNode<T>::RED)
        {
            if (node->parent_ == node->parent_->parent_->left_)
            {
                RBNode<T> *uncle = node->parent_->parent_->right_;
                if (uncle != nullptr && uncle->color_ == RBNode<T>::RED)
                {
                    node->parent_->color_ = RBNode<T>::BLACK;
                    uncle->color_ = RBNode<T>::BLACK;
                    node->parent_->parent_->color_ = RBNode<T>::RED;
                    node = node->parent_->parent_;
                }
                else
                {
                    if (node == node->parent_->right_)
                    {
                        node = node->parent_;
                        LeftRotate(node);
                    }
                    node->parent_->color_ = RBNode<T>::BLACK;
                    node->parent_->parent_->color_ = RBNode<T>::RED;
                    RightRotate(node->parent_->parent_);
                }
            }
            else
            {
                RBNode<T> *uncle = node->parent_->parent_->left_;
                if (uncle != nullptr && uncle->color_ == RBNode<T>::RED)
                {
                    node->parent_->color_ = RBNode<T>::BLACK;
                    uncle->color_ = RBNode<T>::BLACK;
                    node->parent_->parent_->color_ = RBNode<T>::RED;
                    node = node->parent_->parent_;
                }
                else
                {
                    if (node == node->parent_->left_)
                    {
                        node = node->parent_;
                        RightRotate(node);
                    }
                    node->parent_->color_ = RBNode<T>::BLACK;
                    node->parent_->parent_->color_ = RBNode<T>::RED;
                    LeftRotate(node->parent_->parent_);
                }
            }
        }
        root_->color_ = RBNode<T>::BLACK;
    }

    // 左旋
    void LeftRotate(RBNode<T> *node)
    {
        RBNode<T> *right = node->right_;
        node->right_ = right->left_;
        if (right->left_ != nullptr)
        {
            right->left_->parent_ = node;
        }
        right->parent_ = node->parent_;
        if (node->parent_ == nullptr)
        {
            root_ = right;
        }
        else if (node == node->parent_->left_)
        {
            node->parent_->left_ = right;
        }
        else
        {
            node->parent_->right_ = right;
        }
        right->left_ = node;
        node->parent_ = right;
    }
    // 右旋
    void RightRotate(RBNode<T> *node)
    {
        RBNode<T> *left = node->left_;
        node->left_ = left->right_;
        if (left->right_ != nullptr)
        {
            left->right_->parent_ = node;
        }
        left->parent_ = node->parent_;
        if (node->parent_ == nullptr)
        {
            root_ = left;
        }
        else if (node == node->parent_->left_)
        {
            node->parent_->left_ = left;
        }
        else
        {
            node->parent_->right_ = left;
        }
        left->right_ = node;
        node->parent_ = left;
    }

    void InOrderWalk(RBNode<T> *node)
    {
        if (node == nullptr)
        {
            return;
        }
        InOrderWalk(node->left_);
        cout << node->data_ << " ";
        cout << (node->color_ == RBNode<T>::BLACK ? 'B' : 'R') << endl;
        InOrderWalk(node->right_);
    }

private:
    RBNode<T> *root_;
};

int main()
{
    std::default_random_engine e;
    std::uniform_int_distribution<int> u(-1 * RANGE, RANGE);
    e.seed(time(nullptr));
    RBTree<int> tree;
    int n;
    cin >> n;
    clock_t start, end;
    start = clock();
    for (int i = 0; i < n; i++)
    {
        tree.Insert(u(e));
    }
    tree.InOrderWalk();
    end = clock();
    cout << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
    return 0;
}