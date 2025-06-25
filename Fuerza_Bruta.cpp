#include <iostream>
#include <cmath>
#include <chrono>

bool isPrime(long n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

void findPrime() {
    int primeNumbers = 0;
    long limit = 1000000;

    auto start = std::chrono::high_resolution_clock::now();
    for (long i = 0; i < limit; ++i) {
        if (isPrime(i)) {
            primeNumbers++;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Total de primos (secuencial): " << primeNumbers << std::endl;
    std::cout << "Tiempo de ejecución: " << elapsed.count() << " segundos" << std::endl;
}

int main() {
    findPrime();
    return 0;
}
