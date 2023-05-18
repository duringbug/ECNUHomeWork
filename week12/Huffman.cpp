#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;
int F[128];
typedef struct Huffman
{
    Huffman *parent;
    Huffman *left;
    Huffman *right;
    int frequency;
    char ch;
} Huffman;
void initF()
{
    for (int i = 0; i < 128; i++)
    {
        F[i] = 0;
    }
}
void prasePassage(std::string str)
{
    initF();
    for (int i = 0; i < str.length(); i++)
    {
        F[str[i]]++;
    }
}
Huffman *creatHuffmanTree()
{
    struct compare {
        bool operator()(const Huffman* a, const Huffman* b) {
            return a->frequency > b->frequency;
        }
    };
    priority_queue<Huffman*, vector<Huffman*>, compare> heap;
    // 将字符频率存储到节点中
    for (int i = 0; i < 128; i++) {
        if (F[i] == 0) continue; // 跳过未出现的字符
        Huffman* node = new Huffman();
        node->ch = i;
        node->frequency = F[i];
        node->left = nullptr;
        node->right = nullptr;
        node->parent = nullptr;
        heap.push(node);
    }

    // 构造哈夫曼树
    while (heap.size() > 1) {
        Huffman* a = heap.top();
        heap.pop();
        Huffman* b = heap.top();
        heap.pop();
        Huffman* parent = new Huffman();
        parent->ch = '\0';
        parent->frequency = a->frequency + b->frequency;
        parent->left = a;
        parent->right = b;
        a->parent = parent;
        b->parent = parent;
        heap.push(parent);
    }

    return heap.top();
}
void printHuffmanTree(Huffman *head, string code = "") {
    if (head == nullptr) return;

    if (head->left == nullptr && head->right == nullptr) { // 叶子节点，输出字符和编码
        cout << head->ch << ":" << code << endl;
    }

    printHuffmanTree(head->left, code + "0"); // 遍历左子树
    printHuffmanTree(head->right, code + "1"); // 遍历右子树
}
int main()
{
    std::string str = "a;akfw.fi";
    prasePassage(str);
    Huffman *head = creatHuffmanTree();
    printHuffmanTree(head);
    return 0;
}