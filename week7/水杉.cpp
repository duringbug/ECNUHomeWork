#include <iostream>
#include <cstdlib>
#include <random>
#include <math.h>
using namespace std;

class Student
{
private:
public:
    long long id;
    long long hash;
    Student();
    ~Student();
    static long long idInit();
};

Student::Student()
{
    this->id = idInit();
    this->hash = abs(this->id) % 100003;
}

Student::~Student()
{
}

long long Student::idInit()
{
    long long range = 1000000000;
    std::default_random_engine e;
    std::uniform_int_distribution<int> u(-1 * range, range);
    e.seed(time(nullptr));
    return u(e);
}
template <class T>
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
    void del(Student);
    void search(Student);
    ~HashMap();
};
template <class T>
HashMap<T>::HashMap()
{
    this->hashMap = new data[100003];
    for (int i = 0; i < 0; i++)
    {
        hashMap[i].filled = false;
    }
}
template <class T>
HashMap<T>::HashMap(int hashrange)
{
    this->hashTable = new T[hashrange];
}
template <class T>
void HashMap<T>::insert(Student student)
{
    int h = student.hash;
    while (hashMap[h].filled)
    {
        h++;
    }
    hashMap[h].value = student.id;
    hashMap[h].filled = true;
}
template <class T>
void HashMap<T>::search(Student student)
{
}
template <class T>
void HashMap<T>::del(Student student)
{
}
template <class T>
HashMap<T>::~HashMap()
{
    delete[] hashMap;
}

int main()
{
    clock_t start, end;
    start = clock();

    HashMap<Student> map;

    Student student;

    cout << student.id << " " << student.hash << endl;

    cout << map.hashMap[0].filled << endl;
    map.insert(student);

    end = clock();
    cout << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
    return 0;
}