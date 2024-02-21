#include "exception.hpp"

#include <sstream>

namespace fs {
    FSException::FSException(std::string errorMessage) : std::runtime_error(errorMessage) {
        std::ostringstream error;
        error << FS_ERROR_DECORATOR << ":/ \nSystem encountered a fatal error. \nFor more details: " << errorMessage << FS_ERROR_DECORATOR;
        this->errorMessage = error.str();
    }

    FSException::~FSException() {

    }

    const char* FSException::what() const noexcept {
        
        return errorMessage.c_str();
    }
}