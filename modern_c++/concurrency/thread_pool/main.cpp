#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool {
public:
    using Task = std::function<void()>;

    explicit ThreadPool(std::size_t numThreads) {
        start(numThreads);
    }

    ThreadPool() = delete;
    ThreadPool(const ThreadPool& other) = delete;
    ThreadPool(ThreadPool&& other) noexcept = delete;
    ThreadPool& operator=(const ThreadPool& other) = delete;
    ThreadPool& operator=(ThreadPool&& other) noexcept = delete;

    ~ThreadPool() {
        stop();
    }

    template <typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
        using ReturnType = decltype(f(args...));
        auto task = std::make_shared<std::packaged_task<ReturnType()>>(
                // NOLINTNEXTLINE(modernize-avoid-bind)
                std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        // or use `lambda` instead of `std::bind`
        // auto task = std::make_shared<std::packaged_task<ReturnType()>>(
        //         [f = std::forward<F>(f), args = std::make_tuple(std::forward<Args>(args)...)]() mutable {
        //             return std::apply(std::move(f), std::move(args));
        //         });
        auto result = task->get_future();
        {
            std::unique_lock<std::mutex> lock{mEventMutex};
            mTasks.emplace([task]() {
                (*task)();
            });
        }
        mEventCV.notify_one();
        return result;
    }

private:
    std::vector<std::thread> mThreads;
    std::condition_variable mEventCV;
    std::mutex mEventMutex;
    std::queue<Task> mTasks;
    bool mStopping = false;

    void start(std::size_t numThreads) {
        for (auto i = 0; i < numThreads; i++) {
            mThreads.emplace_back([this] {
                while (true) {
                    Task task;
                    {
                        std::unique_lock<std::mutex> lock{mEventMutex};
                        mEventCV.wait(lock, [this] {
                            return mStopping || !mTasks.empty();
                        });
                        if (mStopping && mTasks.empty()) {
                            break;
                        }

                        task = std::move(mTasks.front());
                        mTasks.pop();
                    }
                    task();
                }
            });
        }
    }

    void stop() noexcept {
        {
            std::unique_lock<std::mutex> lock{mEventMutex};
            mStopping = true;
        }
        mEventCV.notify_all();

        for (auto& thread : mThreads) {
            thread.join();
        }
    }
};

int main() {
    ThreadPool pool{16};

    auto pow2 = [](int num) {
        return num * num;
    };
    auto multiply = [](int num1, int num2) {
        return num1 * num2;
    };

    int a = 3;
    int b = 2;
    std::cout << "a = " << a << ", b = " << b << std::endl;

    auto f1 = pool.enqueue(pow2, a);
    auto f2 = pool.enqueue(multiply, a, b);
    auto f3 = pool.enqueue(pow2, b);
    std::cout << "a*a + 2*a*b + b*b = " << f1.get() + 2 * f2.get() + f3.get() << std::endl;

    return 0;
}
