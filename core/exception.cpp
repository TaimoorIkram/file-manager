#include "exception.hpp"

namespace fs {
    FSException::FSException(std::string errorMessage) {
        this->errorMessage = errorMessage;
    }

    FSException::~FSException() {

    }
    
}