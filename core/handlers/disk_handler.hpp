#include "../hardwares/disk.hpp"

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
        bool writeToDisk(std::string);
        bool writeToDisk(int blockId, std::string);
        std::string readFromDisk(int blockId, bool linkedNodes = false);
        int getDiskSize();

        private:
        FSDisk *fsDisk;
    };
}