#include "../hardwares/memory.hpp"

namespace fs {
    /**
     * @brief System handler for the memory virtual objects. Performs
     * the operations on the virtual memory as an intermediary. 
     *  
     */
    class FSMemoryHandler {
        public:
        FSMemoryHandler();
        ~FSMemoryHandler();

        bool writeToMemory();
        std::string readFromMemory();

        private:
        FSMemory *fsMemory;
    };
}