#pragma once
#ifndef RSABigInt_H
#define RSABigInt_H
#include "BigInt.h"

class RSABigInt
{
public:
    RSABigInt(int nSize);
    virtual ~RSABigInt();

    void CalculateD(BigInt& e, BigInt& phi, BigInt& d);
    void init(BigInt& p, BigInt& q);
    void eGeneration(BigInt& phi, BigInt& result);
    void encryption(BigInt& msg, BigInt& code);
    void decryption(BigInt& code, BigInt& msg);
    void randomNGeneration(BigInt& randResult, int n);
    void primeNumberGeneration(BigInt& randPrime, int n);
    void printN() {
        N.showDigits();
    }
    void printD() {
        d.showDigits();
    }
private:
    int SIZE;
    BigInt N;
    BigInt d;
    BigInt e;
};

#endif // RSABigInt_H


