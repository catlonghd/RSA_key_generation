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

void RSABigInt::init(BigInt &p, BigInt &q)
{
    N.multiply(p, q);
    BigInt one(p.nSize);
    one.digit[0] = 1;
    BigInt phi(p.nSize);

    BigInt tempP(p.nSize), tempQ(p.nSize);

    tempP.subtract(p, one);
    tempQ.subtract(q, one);

    phi.multiply(tempP, tempQ);
    cout << "\nGenerated 'phi' :" << endl;
    phi.showDigits();
    eCalculate(phi, e);
    cout << "\nPublic key (n, e) :" << endl;
    cout << "(";
    N.showDigits();
    cout << ", ";
    e.showDigits();
    cout << ")\n";
    
    
    CalculateD(e, phi, d);
    cout << "\nPrivate key (n, d) :" << endl;
    cout << "("; 
    N.showDigits();
    cout << ", ";
    d.showDigits();
    cout << ")\n";
}

void RSABigInt::eCalculate(BigInt &phi, BigInt &result)
{
    BigInt temp(phi.nSize);
    temp.digit[0] = 3;
    BigInt value2(phi.nSize);
    value2.digit[0] = 2;
    BigInt temp2(phi.nSize);

    while (1)
    {
        BigInt gcdValue(phi.nSize);
        gcd(phi, temp, gcdValue);

        if (gcdValue.msb() == 0 && gcdValue.digit[0] == 1)
        {
            break;
        }
        temp2.add(temp, value2);
        temp.copyTo(temp2, 0);
    }
    result.copyTo(temp, 0);
}

// Generate a random number and prime number
void RSABigInt::primeGeneration(BigInt& randPrime, int n)
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
        tempPrimeMinusOne.clearBit();
        tempRemainder.clearBit();
        ExpoDummy.clearBit();
        tempExpoDummy.clearBit();
        tempPrimeMinusOne.subtract(tempPrime, valueOne);

        ExpoDummy.expoModNBigInt(valueTwo, tempPrimeMinusOne, tempPrime, tempRemainder);

        if (tempRemainder.msb() == 0 && tempRemainder.digit[0] == 1)
        {
            cout << "Prime Number Generating ... Wait a little bit\n";
            tempRemainder.clearBit();
            tempExpoDummy.expoModNBigInt(valueThree, tempPrimeMinusOne, tempPrime, tempRemainder);
            if (tempRemainder.msb() == 0 && tempRemainder.digit[0] == 1)
            {
                break;
            }
        }
        tempPrime.clearBit();
        randomNGeneration(tempPrime, n);
    }
    randPrime.copyTo(tempPrime, 0);
}

void RSABigInt::randomNGeneration(BigInt &randResult, int n)
{
    for (int i = 0; i < n; i++)
    {
        unsigned int rnd = rand();
        randResult.digit[i] = randResult.digit[i] | rnd << 16;
        rnd = rand();
        randResult.digit[i] = randResult.digit[i] | rnd << 1;
    }
    randResult.digit[0] = randResult.digit[0] | 1;
    randResult.digit[n - 1] = randResult.digit[n - 1] | 1 << 30;
}

void RSABigInt::CalculateD(BigInt &e, BigInt &phi, BigInt &d)
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
        temp1.multiply(k, phi);
        temp2.add(temp1, one);
        divideAndRemainder(temp2, e, quotient, remainder);
        if (remainder.msb() == 0 && remainder.digit[0] == 0)
        {
            d.copyTo(quotient, 0);
            break;
        }
    }
}
