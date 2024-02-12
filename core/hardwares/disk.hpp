#include <iostream>

#define FS_DISK_BLOCK_SIZE 8
#define FS_DISK_MAX_BLOCK_COUNT 1024

namespace fs
{
    /**
     * @brief A virtual representation of physical disk
     * file.
     *
     */
    class FSDisk
    {
    public:
        /**
         * @brief Disk memory's virtual unit, represents a single
         * block of storage of a particular block size.
         *
         */
        struct FSDiskMemoryDataNode
        {
            int id = 0;
            std::string data = "........";
            FSDiskMemoryDataNode *next = nullptr;
            int sizeRemaining = FS_DISK_BLOCK_SIZE;
            int toRead = -1;
            bool empty = true;
        };

        FSDisk();
        ~FSDisk();
        

        std::string writeToBlock(int id, std::string data);
        std::string readFromBlock(int id);
        FSDiskMemoryDataNode* addDiskMemoryDataNode(std::string data);
        bool linkNodes(int fromId, int toId);
        FSDiskMemoryDataNode* getHeadNode();
        FSDiskMemoryDataNode* getNode(int id);
        int getNodeCount();
        FSDiskMemoryDataNode* getLinkedNodes(int id);
        FSDiskMemoryDataNode* getNextEmptyDataNode();
        bool isFull() { return globalBlockId < FS_DISK_MAX_BLOCK_COUNT; }

    private:
        int globalBlockId = 0;
        FSDiskMemoryDataNode *fsDiskMemoryDataHeadNode = nullptr;
    };
}