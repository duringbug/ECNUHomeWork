#include <iostream>
using namespace std;

// 红黑树节点
template <typename T>
class RBNode
{
public:
    enum Color
    {
        RED,
        BLACK
    };

    // 构造函数
    RBNode(const T &data)
        : data_(data), color_(RED), parent_(nullptr),
          left_(nullptr), right_(nullptr) {}

    T data_;         // 节点数据
    Color color_;    // 节点颜色
    RBNode *parent_; // 父节点
    RBNode *left_;   // 左儿子
    RBNode *right_;  // 右儿子
};

// 红黑树
template <typename T>
class RBTree
{
public:
    // 构造函数
    RBTree() : root_(nullptr) {}

    // 插入节点
    void Insert(const T &data)
    {
        // 创建一个新节点
        RBNode<T> *node = new RBNode<T>(data);
        // 将新节点插入到红黑树中
        Insert(node);
    }

    // 中序遍历
    void InOrderWalk()
    {
        InOrderWalk(root_);
        cout << endl;
    }

private:
    // 插入节点
    void Insert(RBNode<T> *node)
    {
        // 找到节点要插入的位置
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
            root_ = node; // 空树
        }
        else if (node->data_ < parent->data_)
        {
            parent->left_ = node;
        }
        else
        {
            parent->right_ = node;
        }

        // 对新节点进行调整，使其符合红黑树的性质
        InsertFixup(node);
    }

    // 对插入节点进行调整
    void InsertFixup(RBNode<T> *node)
    {
        while (node->parent_ != nullptr && node->parent_->color_ == RBNode<T>::RED)
        {
            // case 1: 父亲是祖父的左儿子
            if (node->parent_ == node->parent_->parent_->left_)
            {
                RBNode<T> *uncle = node->parent_->parent_->right_;
                // case 1.1: 叔叔节点是红色的
                if (uncle != nullptr && uncle->color_ == RBNode<T>::RED)
                {
                    node->parent_->color_ = RBNode<T>::BLACK;
                    uncle->color_ = RBNode<T>::BLACK;
                    node->parent_->parent_->color_ = RBNode<T>::RED;
                    node = node->parent_->parent_;
                    // case 1.2: 叔叔节点是黑色的，且新节点是右儿子
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
                // case 2: 父亲是祖父的右儿子
            }
            else
            {
                RBNode<T> *uncle = node->parent_->parent_->left_;
                // case 2.1: 叔叔节点是红色的
                if (uncle != nullptr && uncle->color_ == RBNode<T>::RED)
                {
                    node->parent_->color_ = RBNode<T>::BLACK;
                    uncle->color_ = RBNode<T>::BLACK;
                    node->parent_->parent_->color_ = RBNode<T>::RED;
                    node = node->parent_->parent_;
                    // case 2.2: 叔叔节点是黑色的，且新节点是左儿子
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
        root_->color_ = RBNode<T>::BLACK; // 根节点一定是黑色的
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
        cout << (node->color_ == RBNode<T>::BLACK ? 'B' : 'R');
        InOrderWalk(node->right_);
    }

private:
    RBNode<T> *root_;
};

int main()
{
    RBTree<int> tree;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int r = 0;
        cin >> r;
        tree.Insert(r);
    }
    tree.InOrderWalk();
    return 0;
}
