#include "RSA.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

RSABigInt::RSABigInt(int nSize)
{
    SIZE = nSize;
    N.setSize(nSize);
    d.setSize(nSize);
    e.setSize(nSize);
}

RSABigInt::~RSABigInt()
{

}

void RSABigInt::init(BigInt& p, BigInt& q)
{
    N.multBigInt(p, q);
    BigInt one(p.nSize);
    one.digit[0] = 1;
    BigInt phi(p.nSize);

    BigInt tempP(p.nSize), tempQ(p.nSize);

    tempP.subBigInt(p, one);
    tempQ.subBigInt(q, one);

    phi.multBigInt(tempP, tempQ);
    cout << "\nGenerated 'phi' :" << endl;
    phi.showDigits();
    eGeneration(phi, e);
    cout << "\nGenerated 'e' :" << endl;
    e.showDigits();
    CalculateD(e, phi, d);
    cout << "\nGenerated 'd' :" << endl;
    d.showDigits();
}

void RSABigInt::eGeneration(BigInt& phi, BigInt& result)
{
    BigInt temp(phi.nSize);
    temp.digit[0] = 3;
    BigInt value2(phi.nSize);
    value2.digit[0] = 2;
    BigInt temp2(phi.nSize);

    while (1)
    {
        BigInt gcdValue(phi.nSize);
        gcdBigInt(phi, temp, gcdValue);

        if (gcdValue.msbBigInt() == 0 && gcdValue.digit[0] == 1)
        {
            break;
        }
        temp2.addBigInt(temp, value2);
        temp.copyBigInt(temp2, 0);
    }
    result.copyBigInt(temp, 0);

}

void RSABigInt::encryption(BigInt& msg, BigInt& code)
{
    BigInt temp(SIZE);
    temp.expoModNBigInt(msg, e, N, code);

}

void RSABigInt::decryption(BigInt& code, BigInt& msg)
{
    BigInt temp(SIZE);
    temp.expoModNBigInt(code, d, N, msg);

}

void RSABigInt::primeNumberGeneration(BigInt& randPrime, int n)
{
    BigInt valueOne(randPrime.nSize);
    valueOne.digit[0] = 1;
    BigInt valueTwo(randPrime.nSize);
    valueTwo.digit[0] = 2;
    BigInt valueThree(randPrime.nSize);
    valueThree.digit[0] = 3;

    BigInt tempPrime(randPrime.nSize);
    BigInt tempExpoDummy(randPrime.nSize);
    BigInt ExpoDummy(randPrime.nSize);

    BigInt tempRemainder(randPrime.nSize);
    BigInt tempPrimeMinusOne(randPrime.nSize);
    randomNGeneration(tempPrime, n);

    while (1)
    {
        tempPrimeMinusOne.clearBigInt();
        tempRemainder.clearBigInt();
        ExpoDummy.clearBigInt();
        tempExpoDummy.clearBigInt();
        tempPrimeMinusOne.subBigInt(tempPrime, valueOne);

        ExpoDummy.expoModNBigInt(valueTwo, tempPrimeMinusOne, tempPrime, tempRemainder);

        if (tempRemainder.msbBigInt() == 0 && tempRemainder.digit[0] == 1)
        {
            cout << "Prime Number Generating ... Wait a little bit\n";
            tempRemainder.clearBigInt();
            tempExpoDummy.expoModNBigInt(valueThree, tempPrimeMinusOne, tempPrime, tempRemainder);
            if (tempRemainder.msbBigInt() == 0 && tempRemainder.digit[0] == 1)
            {
                break;
            }
        }
        tempPrime.clearBigInt();
        randomNGeneration(tempPrime, n);
    }
    randPrime.copyBigInt(tempPrime, 0);
}

void RSABigInt::randomNGeneration(BigInt& randResult, int n)
{
    for (int i = 0;i < n;i++)
    {
        unsigned int rnd = rand();
        randResult.digit[i] = randResult.digit[i] | rnd << 16;
        rnd = rand();
        randResult.digit[i] = randResult.digit[i] | rnd << 1;
    }
    randResult.digit[0] = randResult.digit[0] | 1;
    randResult.digit[n - 1] = randResult.digit[n - 1] | 1 << 30;
}

void RSABigInt::CalculateD(BigInt& e, BigInt& phi, BigInt& d)
{
    int i = 0;
    BigInt temp1(phi.nSize), temp2(phi.nSize), quotient(phi.nSize), remainder(phi.nSize);
    BigInt one(phi.nSize);
    one.digit[0] = 1;
    BigInt k(phi.nSize);
    while (true)
    {
        i++;
        k.digit[0] = i;
        temp1.multBigInt(k, phi);
        temp2.addBigInt(temp1, one);
        divBigInt(temp2, e, quotient, remainder);
        if (remainder.msbBigInt() == 0 && remainder.digit[0] == 0)
        {
            d.copyBigInt(quotient, 0);
            break;
        }
    }
}
