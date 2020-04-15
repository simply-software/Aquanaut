#pragma once

#include <cerrno>
#include <stdexcept>
#include <cstdlib>
#include <string>

namespace aqua {

    inline void convert_from_string(std::string& to, const std::string& from) {
        to = from;
    }

    inline void convert_from_string(double& to, const std::string& from) {
        char* endp = nullptr;

        // The following assumes that .c_str() is idempotent, which is not technically guaranteed by
        // the standard, but in practice is always the case.
        to = strtod(from.c_str(), &endp);
        if (*endp != '\0') {
            throw std::runtime_error("'" + from + "' is not a valid double format");                
        }

        if (errno == ERANGE) {
            throw std::range_error("'" + from + "' is too large to store in a double");
        }
    }
    
} // namespace aqua