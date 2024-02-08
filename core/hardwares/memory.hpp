#include<iostream>

namespace fs {
    /**
     * @brief A virtual representation of physical primary
     * memory file.
     * 
     */
    class FSMemory {
        public:
        FSMemory();
        ~FSMemory();

        bool write();
        std::string read();
    };
}