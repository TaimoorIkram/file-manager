#include "kernel.hpp"

#define FS_KERNEL_DISK_FILE_PATH "C:\\Users\\HP\\Desktop\\File System\\file-manager\\core\\memory\\disk.txt"

namespace fs {
    FSKernel::FSKernel() {
        fsHandlers.fsDiskHandler = new FSDiskHandler();
    }

    FSKernel::~FSKernel() {

    }

    bool FSKernel::startKernel() {
        // TODO:
        // 1. Kernel loads the physical disk file into the 
        // virtual memory using the disk handler.
        // 2. Kernel sets up the memory module by loading 
        // any backup dumps from the memory dump file into
        // the virtual memory using the memory handler.
        // 3. Kernel reconstructs the saved file tree from 
        // the separate file map, into the system memory.
        // 4. When implemented, the kernel will load the 
        // programs in applications folder into the system's 
        // processes list.
        // 5. Kernel will load the system environment variables
        // when the external programs feature is implemented.
        //
        std::cout << "Preparing Disk ... ";
        if (!fsHandlers.fsDiskHandler->resetDisk(FS_KERNEL_DISK_FILE_PATH))
        {
            throw FSException("KERNEL_FILE_SYSTEM_ERROR");
        }
        std::cout << "Done" << std::endl;

        std::cout << "Saving Initial Disk State ... ";
        if (!fsHandlers.fsDiskHandler->saveDisk(FS_KERNEL_DISK_FILE_PATH))
        {
            throw FSException("KERNEL_FILE_SYSTEM_ERROR");
        }
        std::cout << "Done" << std::endl;

        std::cout << "Loading Saved Disk State ... ";
        if (!fsHandlers.fsDiskHandler->loadDisk(FS_KERNEL_DISK_FILE_PATH))
        {
            throw FSException("KERNEL_FILE_SYSTEM_ERROR");
        }
        std::cout << "Done" << std::endl;

        fsHandlers.fsDiskHandler->writeToDisk(5, "Christiano Ronaldo and Lionel Messi are the best players in the world!");
        std::cout << fsHandlers.fsDiskHandler->getDiskSizeRemaining() << " vBytes free." << std::endl;

        std::cout << "Saving Modified Disk State ... ";
        if (!fsHandlers.fsDiskHandler->saveDisk(FS_KERNEL_DISK_FILE_PATH))
        {
            throw FSException("KERNEL_FILE_SYSTEM_ERROR");
        }
        std::cout << "Done" << std::endl;

        return true;
    }
}