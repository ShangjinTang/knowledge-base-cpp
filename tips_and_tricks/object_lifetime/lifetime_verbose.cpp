#include <fmt/format.h>

#include <algorithm>
#include <utility>
#include <vector>

struct Lifetime {
    void print_moved_from() const noexcept {
        if (moved_from_) {
            fmt::print("[moved from] ");
        }

        if (copy_) {
            fmt::print("[copy] ");
        }
    }

    auto operator<=>(const Lifetime &other) const {
        ++comparisons;
        print_moved_from();
        fmt::print("operator<=>(const Lifetime &) {{{} <=> {}}} [three-way comparison]\n", id_, other.id_);
        return id_ - other.id_;
    }

    explicit Lifetime(int id_) noexcept : id_{id_} {
        ++objects;
        fmt::print("Lifetime(int) {{{}}} [int constructor]\n", id_);
    }
    Lifetime() noexcept {
        ++objects;
        fmt::print("Lifetime() {{{}}} [default constructor]\n", id_);
    }
    ~Lifetime() noexcept {
        ++destructions;
        print_moved_from();
        fmt::print("~Lifetime() {{{}}} [destructor]\n", id_);
    }
    Lifetime(const Lifetime &other) noexcept : id_{other.id_}, moved_from_{other.moved_from_}, copy_{true} {
        ++copies;
        ++objects;
        print_moved_from();
        fmt::print("Lifetime(const Lifetime &) {{{}}} [copy constructor]\n", id_);
    }
    Lifetime(Lifetime &&other) noexcept
            : id_{other.id_}, moved_from_{std::exchange(other.moved_from_, true)}, copy_{other.copy_} {
        ++moves;
        ++objects;
        print_moved_from();
        fmt::print("Lifetime(Lifetime &&) {{{}}} [move constructor]\n", id_);
    }

    Lifetime &operator=(const Lifetime &other) noexcept {
        print_moved_from();
        if (&other == this) {
            fmt::print("[self assignment]");
            ++self_assignments;
        } else {
            ++copy_assignments;
        }
        fmt::print("operator=(const Lifetime &) {{{} = {}}} [copy assignment operator]\n", id_, other.id_);
        id_ = other.id_;
        moved_from_ = other.moved_from_;
        copy_ = true;
        return *this;
    }
    Lifetime &operator=(Lifetime &&other) noexcept {
        print_moved_from();
        if (&other == this) {
            fmt::print("[self assignment]");
            ++self_assignments;
        } else {
            ++move_assignments;
        }

        fmt::print("operator=(Lifetime &&) {{{} = {}}} [move assignment operator]\n", id_, other.id_);
        id_ = other.id_;
        moved_from_ = std::exchange(other.moved_from_, true);
        copy_ = other.copy_;
        return *this;
    }

    static inline std::size_t objects{0};           // NOLINT
    static inline std::size_t moves{0};             // NOLINT
    static inline std::size_t copies{0};            // NOLINT
    static inline std::size_t move_assignments{0};  // NOLINT
    static inline std::size_t copy_assignments{0};  // NOLINT
    static inline std::size_t destructions{0};      // NOLINT
    static inline std::size_t self_assignments{0};  // NOLINT
    static inline std::size_t comparisons{0};       // NOLINT

private:
    int id_ = -1;
    bool moved_from_ = false;
    bool copy_ = false;
};

void dump_counters() {
    fmt::print("\n\n******\n");
    fmt::print("* Total Objects:     {}\n", Lifetime::objects);
    fmt::print("* Move Constructors: {}\n", Lifetime::moves);
    fmt::print("* Copy Constructors: {}\n", Lifetime::copies);
    fmt::print("* Move Assignments:  {}\n", Lifetime::move_assignments);
    fmt::print("* Copy Assignments:  {}\n", Lifetime::copy_assignments);
    fmt::print("* Destructors:       {}\n", Lifetime::destructions);
    fmt::print("* Self Assignments:  {}\n", Lifetime::self_assignments);
    fmt::print("* Comparisons:       {}\n", Lifetime::comparisons);
};

struct DumpCounters {
    DumpCounters() = default;
    DumpCounters(const DumpCounters &) = delete;
    DumpCounters(DumpCounters &&) = delete;
    DumpCounters &operator=(const DumpCounters &) = delete;
    DumpCounters &operator=(DumpCounters &&) = delete;

    ~DumpCounters() {
        dump_counters();
    }
};

// a static global to dump all the counts as the program
// shuts down
[[maybe_unused]] DumpCounters LTCD;  // NOLINT

int main() {
    fmt::print("Before lambda construction\n");
    auto lambda = [lft = Lifetime{1}]() mutable {
        lft = Lifetime{2};
    };

    fmt::print("Before lambda call\n");
    lambda();
    fmt::print("After lambda call\n");

    std::vector<Lifetime> vec{};
    vec.emplace_back(6);
    vec.emplace_back(4);
    vec.emplace_back(5);
    vec.emplace_back(3);

    fmt::print("Starting sort\n");
    std::sort(vec.begin(), vec.end());
    fmt::print("Ending sort\n");

    auto vec2 = std::move(vec);
}
