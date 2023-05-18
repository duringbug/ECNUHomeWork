/*
 * @Description: 
 * @Author: 唐健峰
 * @Date: 2023-05-18 14:18:37
 * @LastEditors: ${author}
 * @LastEditTime: 2023-05-18 19:29:22
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

//优先队列:128
template <typename T>
class PriorityQueue {
public:
    explicit PriorityQueue(int capacity = 128): size_(0), capacity_(capacity) {
        data_ = new T[capacity_];
    }

    ~PriorityQueue() {
        delete [] data_;
    }

    bool empty() const {
        return size_ == 0;
    }

    int size() const {
        return size_;
    }

    const T& top() const {
        if (empty()) {
            throw std::out_of_range("PriorityQueue is empty");
        }
        return data_[0];
    }

    void push(const T& value) {
        if (size_ == capacity_) {
            throw std::overflow_error("PriorityQueue is full");
        }
        // 插入到最后一个位置
        data_[size_] = value;
        ++size_;

        // 从下往上堆化
        int i = size_ - 1;
        while (i != 0 && data_[(i - 1) / 2] > data_[i]) {
            std::swap(data_[i], data_[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void pop() {
        if (empty()) {
            throw std::out_of_range("PriorityQueue is empty");
        }
        // 将末尾元素替换到头部，并从上往下堆化
        data_[0] = data_[size_ - 1];
        --size_;

        int i = 0;
        while (true) {
            int left = i * 2 + 1;
            int right = i * 2 + 2;
            int smallest = i;

            if (left < size_ && data_[left] < data_[smallest]) {
                smallest = left;
            }
            if (right < size_ && data_[right] < data_[smallest]) {
                smallest = right;
            }

            if (smallest == i) {
                break;
            }

            std::swap(data_[i], data_[smallest]);
            i = smallest;
        }
    }

private:
    T* data_;
    int size_;
    int capacity_;
};

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