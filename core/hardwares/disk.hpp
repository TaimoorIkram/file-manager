#include <iostream>

#define FS_DISK_BLOCK_SIZE 8
#define FS_DISK_MAX_BLOCK_COUNT 2048

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
        FSDisk();
        ~FSDisk();

        bool writeToBlock(int id, std::string data);
        std::string readFromBlock(int id);
        bool isFull() { return globalBlockId < FS_DISK_MAX_BLOCK_COUNT; }

    private:
        int globalBlockId;
        /**
         * @brief Disk memory's virtual unit, represents a single
         * block of storage of a particular block size.
         *
         */
        struct FSDiskMemoryDataNode
        {
            int id;
            std::string data;
            FSDiskMemoryDataNode *next;
            int sizeRemaining = FS_DISK_BLOCK_SIZE;
            int toRead;
        };

        FSDiskMemoryDataNode *fsDiskMemoryDataHeadNode = nullptr;
    };
}