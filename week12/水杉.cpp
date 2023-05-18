/*
 * @Description: 
 * @Author: 唐健峰
 * @Date: 2023-05-18 14:18:37
 * @LastEditors: ${author}
 * @LastEditTime: 2023-05-18 20:21:20
 */
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
typedef struct HuffmanArray
{
    int huffmanNum;
    char ch;
}HuffmanArray;

struct compare {
    bool operator()(const Huffman* a, const Huffman* b) {
        return a->frequency > b->frequency;
    }
};

struct compare2 {
    bool operator()(const HuffmanArray* a, const HuffmanArray* b) {
        return a->huffmanNum > b->huffmanNum;
    }
};
//Huffman优先级队列类
class HuffmanQueue {
private:
    // 定义节点类型
    struct Node {
        Huffman data;
        Node* next;
        Node(const Huffman& d, Node* n = nullptr) : data(d), next(n) {}
        bool operator<(const Node& rhs) const { return data.frequency > rhs.data.frequency; }
    };
    Node* frontNode; // 队首指针
    int count; // 队列元素个数

public:
    // 构造函数
    HuffmanQueue() : frontNode(nullptr), count(0) {}

    // 插入元素
    void push(const Huffman * value) {
        Node* newNode = new Node(*value);
        if (frontNode == nullptr || value->frequency < frontNode->data.frequency) {
            newNode->next = frontNode;
            frontNode = newNode;
        }
        else {
            Node* current = frontNode;
            while (current->next != nullptr && current->next->data.frequency < value->frequency) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        count++;
    }

    // 删除队首元素
    void pop() {
        if (frontNode == nullptr) {
            return;
        }
        Node* temp = frontNode;
        frontNode = frontNode->next;
        delete temp;
        count--;
    }

    // 访问队首元素
    Huffman* top() {
        return &(frontNode->data);
    }

    // 判断队列是否为空
    bool empty() const {
        return frontNode == nullptr;
    }

    // 获取队列元素个数
    int size() const {
        return count;
    }
};
//哈夫曼表
priority_queue<HuffmanArray*, vector<HuffmanArray*>, compare2> heap2;
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
    priority_queue<Huffman*, vector<Huffman*>, compare> heap;
    HuffmanQueue huffmanQueue;
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
//制作哈夫曼表:
void getHuffmanTreeArray(Huffman *head, string code = ""){
    if (head == nullptr) return;

    if (head->left == nullptr && head->right == nullptr) { // 叶子节点，输出字符和编码
        HuffmanArray* node = new HuffmanArray();
        node->ch=head->ch;
        node->huffmanNum=stoi(code);
        heap2.push(node);
    }

    getHuffmanTreeArray(head->left, code + "0"); // 遍历左子树
    getHuffmanTreeArray(head->right, code + "1"); // 遍历右子树
}

int main(){
    int N;
    cin >> N;
    for(int i=0;i<N;i++)
    {
        char ch='\0';
        cin >> ch;
        int num;
        cin >> num;
        F[ch]=num;
    }
    Huffman *head = creatHuffmanTree();
    getHuffmanTreeArray(head);
    while (!heap2.empty())
    {
        cout<< heap2.top()->ch << ":" << heap2.top()->huffmanNum<<endl;
        heap2.pop();
    }
    return 0;
}