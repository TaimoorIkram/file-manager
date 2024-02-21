#include<iostream>

namespace fs {
    /**
     * @brief A virtual representation of a system file
     * object.
     *  
     */
    class FSFile {
        public:
        /**
        * @brief Logical representation of the file system index nodes.
        * Used to index file and directory objects; contains metadata
        * such as creation date, created by. More parameters to be added.
        *
        * @param dateCreated The date of creation of the file or directory.
        * @param dateUpdated The date of the updation of the file or directory.
        * @param createdBy A pointer to a user object that created the file.
        */
        struct FSIndexNode {
            std::string dateCreated;
            std::string dateUpdated;
            std::string createdBy = "tammy";
        };

        FSFile(std::string fileName);
        ~FSFile();

        std::string getFileName();
        int getFileSize();
        int getFileStartBlock();
        FSFile::FSIndexNode* getINode();

        bool setINode(FSIndexNode* iNode);
        bool setFileStartBlock(int blockId);
        bool setDateUpdated(std::string dateUpdated);

        private:
        std::string fileName;
        int fileSize;
        int fileStartBlock;
        FSIndexNode *iNode;
    };
}