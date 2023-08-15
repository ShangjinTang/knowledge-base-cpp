#include <cmath>
#include <cstddef>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

bool is_prime(int n) {
    int limit = static_cast<int>(sqrt(n));
    for (int i = 2; i <= limit; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

std::size_t calc_prime_count(int n, int first, int last) {
    std::vector<std::thread> threads;
    threads.reserve(n);
    int chunk = (last - first + 1) / n;

    std::vector<int> result;
    std::mutex lock;

    for (int i = 0; i < n; i++) {
        int start = first + i * chunk;
        int end = (i == n - 1) ? last : start + chunk - 1;

        std::thread t(
                [&result, &lock](int from, int to) {
                    for (int i = from; i <= to; i++) {
                        if (is_prime(i)) {
                            std::lock_guard locker(lock);
                            result.push_back(i);
                        }
                    }
                },
                start, end);

        threads.push_back(std::move(t));
    }

    for (auto &t : threads) {
        t.join();
    }

    return result.size();
}

int main() {
    const int min = 1;
    const int max = 100;
    const int threads = 8;
    std::cout << "Prime count from " << min << " to " << max << ": " << calc_prime_count(threads, min, max)
              << std::endl;
    return 0;
}
