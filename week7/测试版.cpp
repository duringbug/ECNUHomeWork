#include <iostream>
#include <cstdlib>
#include <random>
#include <math.h>
using namespace std;

#define RANGE 1000000 // 数字范围
#define HASH 100003   // 数组长度，即hash值
#define CIRCLE 2      // 循环取平均值

class Student
{
private:
public:
    long long id;
    long long hash;
    Student();
    Student(int);
    ~Student();
    static long long idInit();
    static long long idInit(int);
};

Student::Student()
{
    this->id = idInit();
    this->hash = abs(this->id) % HASH;
}

Student::Student(int id)
{
    this->id = idInit(id);
    this->hash = abs(this->id) % HASH;
}

Student::~Student()
{
}

long long Student::idInit()
{
    long long range = RANGE;
    std::default_random_engine e;
    std::uniform_int_distribution<int> u(-1 * range, range);
    e.seed(time(nullptr));
    return u(e);
}
long long Student::idInit(int id)
{
    return id;
}

class HashMap
{
    typedef struct data
    {
        bool filled;
        long long value;
    } data;

private:
public:
    data *hashMap;
    HashMap();
    HashMap(int);
    void insert(Student);
    void insert(Student, int);
    bool search(Student);
    bool simpleSearch(Student);
    ~HashMap();
};

HashMap::HashMap()
{
    this->hashMap = new data[HASH];
    for (int i = 0; i < 0; i++)
    {
        hashMap[i].filled = false;
    }
}

HashMap::HashMap(int hashrange)
{
    data a[hashrange];
    this->hashMap = a;
}

void HashMap::insert(Student student)
{
    int h = student.hash;
    while (hashMap[h].filled)
    {
        h = (h + 1) % HASH;
    }
    hashMap[h].value = student.id;
    hashMap[h].filled = true;
}
void HashMap::insert(Student student, int)
{

    int h = student.hash;
    while (hashMap[h].filled)
    {
        h = (h + 1) % HASH;
    }
    hashMap[h].value = student.id;
    hashMap[h].filled = true;
}

bool HashMap::search(Student student) // hash查找
{
    int i = student.hash;
    while (hashMap[i].filled)
    {
        if (hashMap[i].value == student.id)
        {
            cout << "Yes" << endl;
            return true;
        }
        i = (i + 1) % HASH;
    }
    cout << "No" << endl;
    return false;
}
bool HashMap::simpleSearch(Student student) // 循序查找
{
    int i = 0;
    while (i < HASH)
    {
        if (hashMap[i].filled)
        {
            if (hashMap->value == student.id)
            {
                cout << "Yes" << endl;
                return true;
            }
        }
        i++;
    }
    cout << "No" << endl;
    return false;
}

HashMap::~HashMap()
{
    delete[] hashMap;
}

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    std::default_random_engine e;
    std::uniform_int_distribution<int> u(-1 * RANGE, RANGE);
    e.seed(time(nullptr));

    long long N;
    cout << "生成多少个数:";
    cin >> N;
    double circle = 0;
    for (int i = 0; i < CIRCLE; i++)
    {
        clock_t start, end;
        start = clock();
        HashMap map;

        Student *student[N];

        for (int i = 0; i < N; i++)
        {
            student[i] = new Student(u(e)); // 数据生成器
            cout << dis(gen) << " " << student[i]->id << " ";
            switch (dis(gen))
            {
            case 0:
                map.insert(*student[i]);
                cout << endl;
                break;
            case 1:
                map.simpleSearch(*student[i]);
            default:
                break;
            }
        }
        end = clock();
        cout << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
        circle = (double)(end - start) / CLOCKS_PER_SEC * 1000 + circle;
        for (int i = 0; i < HASH; i++)
        {
            map.hashMap[i].filled = false;
        }
    }
    cout << "平均耗时:" << (circle / CIRCLE) << "ms" << endl;
    return 0;
}