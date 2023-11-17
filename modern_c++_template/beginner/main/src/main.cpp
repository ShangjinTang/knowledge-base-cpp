#include "fmt/core.h"
#include "mymath.h"
#include "spdlog/spdlog.h"

int main() {
    spdlog::info("Welcome to spdlog!");

    int a = 2;
    int b = 3;
    fmt::print("Hello fmt! {} + {} = {}.\n", a, b, mymath::add(a, b));
}
