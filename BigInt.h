//#pragma once
//
//#ifndef BIGINT_H
//#define BIGINT_H
//
//class BigInt {
//public:
//    int size;
//    unsigned int* digit;
//    BigInt() {}
//    BigInt(int n);
//    BigInt(const BigInt& obj);
//    ~BigInt();
//
//    BigInt operator+(BigInt const& obj);
//    BigInt operator-(BigInt const& obj);
//    BigInt copy(BigInt const& obj, int index);
//
//    BigInt expoModNBigInt();
//    void showDigits();
//
//};
//
//#endif // BIGINT_H
//


#ifndef BigInt_H
#define BigInt_H


class BigInt
{
public:
    int nSize;
    unsigned int* digit;
    BigInt() {}
    BigInt(int n);
    BigInt(const BigInt& obj);
    ~BigInt();


    void addBigInt(BigInt& a, BigInt& b);
    void subBigInt(BigInt& a, BigInt& b);
    void multBigInt(BigInt& a, BigInt& b);
    void copyBigInt(BigInt& a, int index);
    void expoModNBigInt(BigInt& x, BigInt& y, BigInt& N, BigInt& result);
    void setSize(int n);
    int msbBigInt();
    void clearBigInt();
    void showDigits();
    void setDigits(int index);
};

int Compare(BigInt& first, BigInt& second);
int divBigInt(BigInt& u, BigInt& v, BigInt& q, BigInt& r);
void gcdBigInt(BigInt& a, BigInt& b, BigInt& result);

#endif // BigInt_H
