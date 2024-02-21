#include <exception>
#include <iostream>

#define FS_ERROR_DECORATOR "\n==========================================================\n"

namespace fs {
    /**
     * @brief Root file system exception class. 
     *  
     */
    class FSException : public std::runtime_error {
        public:
        FSException(std::string errorMessage);
        ~FSException();

        const char* what() const noexcept override;

        private:
        std::string errorMessage;
    };
}