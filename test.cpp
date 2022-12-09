#include <iostream>

using namespace std;

// result = x^y mod N
void expoModN(int &x, int &y, int &N, int &result)
{
    if (y == 0)
    {
        result = 1;
    }
    else
    {
        int temp = y / 2;
        expoModN(x, temp , N, result);

        temp = result * result;

        if (y % 2 != 0)
        {
            temp = temp * x;
        }
        int q, r;
        q = temp / N;
        r = temp % N;
        result = r;
    }
}

int main(){
    int x = 2;
    int y = 15;
    int N = 5;
    int result = 0;
    expoModN(x, y, N, result);
    cout << result << endl;
    unsigned int a = -5;
    unsigned int b = 3;
    //cout << -a % b << endl;
    // print max usigned long long
    unsigned long long c = -1;
    //cout << c << endl;
    return 0;
}