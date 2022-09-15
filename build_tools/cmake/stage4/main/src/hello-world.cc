#include <iostream>
#include <string>

#include "hello-greet.h"
#include "hello-time.h"

int main(int argc, char** argv) {
    std::string who = "world";
    if (argc > 1) {
        who = argv[1];
    }
    std::cout << get_greet(who) << std::endl;
    print_localtime();
    return 0;
}
