#include "BigInt.h"
#include "RSA.h"
#include <iostream>
using namespace std;


int main() {
    cout << "RSA Algorithm" << endl;
    RSABigInt rsa(390);
    cout << "Random Prime Number Generation" << endl;

    //struct timespec tstart={0,0}, tend={0,0};
    //clock_gettime(CLOCK_MONOTONIC, &tstart);

    BigInt primeNumberP(390), primeNumberQ(390);
    rsa.primeNumberGeneration(primeNumberP, 1024/32/2);
    cout << "\nprimeNumber, p=\n";
    primeNumberP.showDigits();

    rsa.primeNumberGeneration(primeNumberQ, 1024/32/2);
    cout << "\nprimeNumber, q=\n";
    primeNumberQ.showDigits();

    rsa.init(primeNumberP, primeNumberQ);
    //rsa.printD();
    return 0;
}