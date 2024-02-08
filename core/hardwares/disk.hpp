#include<iostream>

namespace fs {
    /**
     * @brief A virtual representation of physical disk
     * file.
     * 
     */
    class FSDisk {
        public:
        FSDisk();
        ~FSDisk();

        bool write();
        std::string read();
    };
}