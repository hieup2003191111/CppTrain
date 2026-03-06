#include "my_library/version.h"

const std::string get_version() {
    return "1.0.0";
}

const std::string get_build_metadata() {
    return "Built on " __DATE__ " at " __TIME__;
}