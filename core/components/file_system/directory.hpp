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
        FSDirectory(std::string directoryName);
        ~FSDirectory();

        bool addFile(FSFile *file);
        bool addDirectory(FSDirectory *directory);
        FSFile* findFile(std::string fileName);
        FSDirectory* findDirectory(std::string directoryName);
        bool deleteFile(std::string fileName);
        bool deleteDirectory(std::string directoryName);

        int getFilesCount();
        int getSubdirectoriesCount();
        std::string getDirectoryName();
        std::vector<FSDirectory*> getSubdirectories();
        std::vector<FSFile*> getFiles();
        bool setINode(FSFile::FSIndexNode *iNode);
        FSFile::FSIndexNode* getINode();
        bool hasDirectory(std::string directoryName);
        bool hasFile(std::string fileName);

        bool setDateUpdated(std::string dateUpdated);

        private:
        std::string directoryName;
        std::vector<FSFile*> files;
        std::vector<FSDirectory*> directories;
        FSFile::FSIndexNode *iNode;
    };
}