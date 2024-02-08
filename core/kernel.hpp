#include "handlers/disk_handler.hpp"
#include "handlers/memory_handler.hpp"

namespace fs {
    /**
     * @brief Loads and controls the main functions to be performed on the
     * system including the memory reads, writes, disk loads, stores and 
     * file system operations. 
     *  
     */
    class FSKernel {
        public:
        FSKernel();
        ~FSKernel();

        private:
        struct FSMemoryHandlers {
            FSMemoryHandler *fsMemoryHandler;
            FSDiskHandler *fsDiskHandler;
        };
    };
}