#include <exception>
#include <iostream>

namespace fs {
    /**
     * @brief Root file system exception class. 
     *  
     */
    class FSException : std::exception {
        public:
        FSException(std::string errorMessage);
        ~FSException();

        private:
        std::string errorMessage;
    };
}