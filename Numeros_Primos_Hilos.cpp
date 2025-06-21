#include <iostream>
#include <thread>
#include <vector>
#include <cmath>
#include <atomic>
#include <chrono>

bool isPrime(long n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (long i = 3; i <= std::sqrt(n); i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

void findPrimeParallel(std::atomic<long>& counter, std::atomic<int>& primeCount, long limit) {
    while (true) {
        long i = counter.fetch_add(1);
        if (i >= limit) break;
        if (isPrime(i)) {
            primeCount.fetch_add(1);
        }
    }
}

int main() {
    const long limit = 1000000;
    //const int threadCount = 2;
    //const int threadCount = 4;
    //const int threadCount = 8;
    const int threadCount = std::thread::hardware_concurrency(); //Limite de 16

    std::atomic<long> counter(0);
    std::atomic<int> primeCount(0);
    std::vector<std::thread> threads;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < threadCount; ++i) {
        threads.emplace_back(findPrimeParallel, std::ref(counter), std::ref(primeCount), limit);
    }

    for (auto& t : threads) {
        t.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Tiempo de ejecucion: " << elapsed.count() << " segundos" << std::endl;

    std::cout << "Usando " << threadCount << " hilos" << std::endl;

    std::cout << "Total de primos (paralelo): " << primeCount << std::endl;
}