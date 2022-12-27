#include <iostream>
#include <map>
#include <shared_mutex>
#include <string>
#include <thread>

std::map<std::string, int> tele_book{{"Dijkstra", 1972}, {"Scott", 1976}, {"Ritchie", 1983}};

std::shared_timed_mutex tele_book_mutex;

void addToTeleBook(const std::string& na, int tele) {
    std::lock_guard<std::shared_timed_mutex> writer_lock(tele_book_mutex);
    std::cout << "\nSTARTING UPDATE " << na;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    tele_book[na] = tele;
    std::cout << " ... ENDING UPDATE " << na << std::endl;
}

void printNumber(const std::string& na) {
    std::shared_lock<std::shared_timed_mutex> reader_lock(tele_book_mutex);
    auto search_entry = tele_book.find(na);
    if (search_entry != tele_book.end()) {
        std::cout << search_entry->first << ": " << search_entry->second << std::endl;
    } else {
        std::cout << na << " not found!" << std::endl;
    }
}

int main() {
    std::cout << std::endl;

    std::thread reader8([] {
        printNumber("Bjarne");
    });
    std::thread reader1([] {
        printNumber("Scott");
    });
    std::thread reader2([] {
        printNumber("Ritchie");
    });
    std::thread w1([] {
        addToTeleBook("Scott", 1968);
    });
    std::thread reader3([] {
        printNumber("Dijkstra");
    });
    std::thread reader4([] {
        printNumber("Scott");
    });
    std::thread w2([] {
        addToTeleBook("Bjarne", 1965);
    });
    std::thread reader5([] {
        printNumber("Scott");
    });
    std::thread reader6([] {
        printNumber("Ritchie");
    });
    std::thread reader7([] {
        printNumber("Scott");
    });

    reader1.join();
    reader2.join();
    reader3.join();
    reader4.join();
    reader5.join();
    reader6.join();
    reader7.join();
    reader8.join();
    w1.join();
    w2.join();

    std::cout << std::endl;

    std::cout << "\nThe new telephone book" << std::endl;
    for (const auto& tele_it : tele_book) {
        std::cout << tele_it.first << ": " << tele_it.second << std::endl;
    }

    std::cout << std::endl;
}
