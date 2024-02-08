#include "directory.hpp"

namespace fs {
    /**
     * @brief A system module that deals with a virtual file tree
     * (VST) data structure as the system file tree.
     * 
     */
    class FSFileTree {
        public:
        FSFileTree();
        ~FSFileTree();

        bool setRootDirectory();
        bool setCurrentDirectory();
        bool setCurrentFile();
        FSDirectory *getRootDirectory();
        FSDirectory *getCurrentDirectory();
        FSFile *getCurrentFile();
        
        private:
        FSDirectory rootDirectory;
        
        FSDirectory *currentDirectory;
        FSFile *currentFile;
    };
}