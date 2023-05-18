/*
 * @Description: 
 * @Author: 唐健峰
 * @Date: 2023-05-18 19:11:26
 * @LastEditors: ${author}
 * @LastEditTime: 2023-05-18 20:19:08
 */
// 定义HuffmanArray类型
#include <iostream>
using namespace std;
int F[128];//Ascall表
typedef struct HuffmanArray
{
    int huffmanNum;
    char ch;
}HuffmanArray;

typedef struct Huffman
{
    Huffman *parent;
    Huffman *left;
    Huffman *right;
    int frequency;
    char ch;
} Huffman;
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
// HuffmanArray优先级队列类
class PriorityQueue {
private:
    // 定义节点类型
    struct Node {
        HuffmanArray data;
        Node* next;
        Node(const HuffmanArray& d, Node* n = nullptr) : data(d), next(n) {}
        bool operator<(const Node& rhs) const { return data.huffmanNum > rhs.data.huffmanNum; }
    };
    Node* frontNode; // 队首指针
    int count; // 队列元素个数

public:
    // 构造函数
    PriorityQueue() : frontNode(nullptr), count(0) {}

    // 插入元素
    void push(const HuffmanArray& value) {
        Node* newNode = new Node(value);
        if (frontNode == nullptr || value.huffmanNum < frontNode->data.huffmanNum) {
            newNode->next = frontNode;
            frontNode = newNode;
        }
        else {
            Node* current = frontNode;
            while (current->next != nullptr && current->next->data.huffmanNum < value.huffmanNum) {
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
    HuffmanArray& top() {
        return frontNode->data;
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
int main() {
    // // 创建对象
    // PriorityQueue queue;

    // // 创建测试数组
    // HuffmanArray test[] = { {4, 'a'}, {1, 'b'}, {7, 'c'}, {2, 'd'}, {5, 'e'} };

    // // 将测试数组元素插入到队列中
    // for (int i = 0; i < 5; i++) {
    //     queue.push(test[i]);
    // }

    // // 输出队列中的元素
    // while (!queue.empty()) {
    //     cout << queue.top().huffmanNum << " " << queue.top().ch << endl;
    //     queue.pop();
    // }
    Huffman h1 = {nullptr, nullptr, nullptr, 5, 'a'};
    Huffman h2 = {nullptr, nullptr, nullptr, 3, 'b'};
    Huffman h3 = {nullptr, nullptr, nullptr, 9, 'c'};
    Huffman h4 = {nullptr, nullptr, nullptr, 7, 'd'};

    HuffmanQueue queue;
    queue.push(&h1);
    queue.push(&h2);
    queue.push(&h3);
    queue.push(&h4);

    cout << "队列是否为空：" << (queue.empty() ? "是" : "否") << endl;
    cout << "队列元素个数：" << queue.size() << endl;

    cout << "访问队首元素：" << queue.top()->ch << endl;

    queue.pop();
    cout << "删除队首元素后，队首元素为：" << queue.top()->ch << endl;

    queue.pop();
    cout << "删除队首元素后，队首元素为：" << queue.top()->ch << endl;

    cout << "队列元素个数：" << queue.size() << endl;

    return 0;
}

