#include <chrono>
#include <future>
#include <iostream>
#include <thread>

bool buffer_file_loading() {
    size_t bytes_loaded = 0;
    while (bytes_loaded < 20000) {
        std::cout << "Loading file" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        bytes_loaded += 1000;
    }
    return true;
}

int main() {
    std::future<bool> background_thread = std::async(std::launch::async, buffer_file_loading);
    std::future_status status;

    while (true) {
        std::cout << "Main thread running..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        status = background_thread.wait_for(std::chrono::milliseconds(1));

        if (status == std::future_status::ready) {
            std::cout << "data ready..." << std::endl;
            break;
        }
    }

    return 0;
}
