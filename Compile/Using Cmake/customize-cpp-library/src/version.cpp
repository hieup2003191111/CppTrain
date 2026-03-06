#include "my_library/version.h"
#include <string>

namespace my_library {

std::string getVersion() {
    return "1.0.0"; // Keep in sync with tests/docs
}

} // namespace my_library