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
        

        FSDiskMemoryDataNode* writeToBlock(int id, std::string data, bool markRead = false);
        std::string readFromBlock(int id);
        FSDiskMemoryDataNode* addDiskMemoryDataNode(std::string data);
        bool linkNodes(int fromId, int toId);
        FSDiskMemoryDataNode* getHeadNode();
        FSDiskMemoryDataNode* getNode(int id);
        int getFreeNodeCount();
        int getNodeCount();
        FSDiskMemoryDataNode* getLinkedNodes(int id);
        int getNextEmptyDataNode();
        bool isFull() { return globalBlockId < FS_DISK_MAX_BLOCK_COUNT; }
        bool freeBlock(int blockId);

    private:
        int globalBlockId = 0;
        int freeNodeCount = FS_DISK_MAX_BLOCK_COUNT;
        FSDiskMemoryDataNode *fsDiskMemoryDataHeadNode = nullptr;
    };
}