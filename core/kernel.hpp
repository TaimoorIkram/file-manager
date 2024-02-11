#include "handlers/disk_handler.hpp"
#include "handlers/memory_handler.hpp"

#include "components/file_system/file_tree.hpp"

#include "exception.hpp"

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

        bool startKernel();
        bool stopKernel();

        bool createDirectory();
        bool createFile();
        bool writeToFile();
        bool openFile();
        bool closeFile();
        bool deleteFile();
        bool deleteDirectory();
        bool getPrograms();
        bool installProgram();


        private:
        struct FSHandlers {
            FSMemoryHandler *fsMemoryHandler;
            FSDiskHandler *fsDiskHandler;
            FSFileTree *fsFileTree;
        };

        FSHandlers fsHandlers{};
        FSFileTree *fsFileTree;
    };
}