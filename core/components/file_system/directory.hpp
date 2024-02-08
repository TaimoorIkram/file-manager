#include "file.hpp"
#include<vector>

namespace fs {
    /**
     * @brief A virtual representation of a system file
     * object.
     *  
     */
    class FSDirectory {
        public:
        FSDirectory();
        ~FSDirectory();

        bool addFile();
        bool addDirectory();
        FSFile* findFile();
        FSDirectory* findDirectory();

        private:
        std::string directoryName;
        std::vector<FSFile*> files;
        std::vector<FSDirectory*> directories;
    };
}