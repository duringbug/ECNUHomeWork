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
    Student(int);
    ~Student();
    static long long idInit();
    static long long idInit(int);
};

Student::Student()
{
    this->id = idInit();
    this->hash = abs(this->id) % 100003;
}

Student::Student(int id)
{
    this->id = idInit(id);
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
    ~HashMap();
};

HashMap::HashMap()
{
    this->hashMap = new data[100003];
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
        h = (h + 1) % 100003;
    }
    hashMap[h].value = student.id;
    hashMap[h].filled = true;
}
void HashMap::insert(Student student, int)
{

    int h = student.hash;
    while (hashMap[h].filled)
    {
        h = (h + 1) % 100003;
    }
    hashMap[h].value = student.id;
    hashMap[h].filled = true;
}

bool HashMap::search(Student student)
{
    int i = student.hash;
    while (hashMap[i].filled)
    {
        if (hashMap[i].value == student.id)
        {
            cout << "Yes" << endl;
            return true;
        }
        i = (i + 1) % 100003;
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
    long long N;
    cin >> N;
    clock_t start, end;
    start = clock();
    HashMap map;

    Student student[N];

    for (int i = 0; i < N; i++)
    {
        char method;
        int q;
        cin >> method >> q;
        student[i] = Student(q);
        switch (method)
        {
        case 'I':
            map.insert(student[i]);
            break;
        case 'Q':
            map.search(student[i]);
        default:
            break;
        }
    }
    end = clock();
    cout << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
    return 0;
}