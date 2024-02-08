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

        bool writeToDisk();
        std::string readFromDisk();

        private:
        FSDisk *fsDisk;
    };
}