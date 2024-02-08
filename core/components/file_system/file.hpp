#include<iostream>

namespace fs {
    /**
     * @brief A virtual representation of a system file
     * object.
     *  
     */
    class FSFile {
        public:
        FSFile();
        ~FSFile();

        private:
        std::string fileName;
        int fileSize;
        int fileBlockStart;
    };
}