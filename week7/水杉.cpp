#include <iostream>
#include <cstdlib>
#include <random>
#include <math.h>
using namespace std;

int main()
{
    long long hashMap[100000];
    long long status[100000];
    for (long long i = 0; i < 100000; i++)
    {
        status[i] = 0;
    }
    long long N;
    cin >> N;
    for (long long i = 0; i < N; i++)
    {
        char method;
        long long q;
        cin >> method >> q;

        if (method == 'I')
        {
            long long p = abs(q) % 100000;
            while (status[p] == 1)
            {
                p = (p + 1) % 100000;
            }
            hashMap[p] = q;
            status[p] = 1;
        }
        else if (method == 'Q')
        {
            long long s = 0;
            long long p = abs(q) % 100000;
            while (status[p] == 1)
            {
                if (hashMap[p] == q)
                {
                    cout << "Yes" << endl;
                    s++;
                    break;
                }
                p = (p + 1) % 100000;
            }
            if (s == 0)
            {
                cout << "No" << endl;
            }
        }
    }
    return 0;
}