#include "fmt/core.h"
#include "spdlog/spdlog.h"

int main() {
    spdlog::info("Welcome to spdlog!");
    fmt::print("Hello fmt {}.\n", 2023);
}
