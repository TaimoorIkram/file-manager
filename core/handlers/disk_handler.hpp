#include "../hardwares/disk.hpp"

#define FS_DISK_DELIMITER "]+{=}+["
#define FS_DISK_NO_DATA "........"

namespace fs {
    /**
     * @brief System handler for the disk virtual objects. Performs
     * the operations on the virtual disk as an intermediary. 
     *  
     */
    class FSDiskHandler {
        public:
        FSDiskHandler();
        ~FSDiskHandler();

        bool loadDisk(std::string diskFilePath);
        bool saveDisk(std::string diskFilePath);
        bool resetDisk(std::string diskFilePath);
        bool writeToDisk(std::string data);
        bool writeToDisk(int blockId, std::string data);
        bool clearDisk(int blockId, bool clearLinked);
        std::string readFromDisk(int blockId, bool linkedNodes = false);
        int getDiskSize();
        int getDiskSizeRemaining();

        private:
        FSDisk *fsDisk;
    };
}