#include "directory.hpp"

namespace fs {
    /**
     * @brief A system module that deals with a virtual file tree
     * (VFT) data structure as the system file tree.
     * 
     */
    class FSFileTree {
        public:
        FSFileTree();
        ~FSFileTree();

        bool setCurrentDirectory(FSDirectory *directory);
        bool setCurrentFile(FSFile *file);
        FSDirectory *getRootDirectory();
        FSDirectory *getCurrentDirectory();
        FSFile *getCurrentFile();

        FSFile* createFile(std::string filePath);
        FSDirectory* createDirectory(std::string directoryPath);
        std::string getDirectoryTree(FSDirectory *directory, int level = 0);
        bool deleteFile(std::string filePath);
        bool deleteDirectory(std::string directoryPath);
        FSFile* findFile(std::string filePath);
        FSDirectory* findDirectory(std::string directoryPath);

        private:
        FSDirectory *rootDirectory = nullptr;
        
        FSDirectory *currentDirectory;
        FSFile *currentFile;
    };
}