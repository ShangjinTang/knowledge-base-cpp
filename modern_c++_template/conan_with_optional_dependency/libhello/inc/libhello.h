#include <string>

#include "libhello_export.h"

namespace hello {
class LIBHELLO_EXPORT libhello {
public:
    [[nodiscard]] int32_t saySomething(const std::string &something) const noexcept;
#ifdef WITH_OPENSSL
    [[nodiscard]] int32_t saySomethingHashed(const std::string &something) const noexcept;
#endif
};
}  // namespace hello
