#include "kernel.hpp"

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
        std::cout << "RESETTING MEMORY ";
        if (!fsHandlers.fsDiskHandler->resetDisk("D:\\NUST Semester 6\\Extras\\Side Projects\\file-manager\\core\\memory\\disk.txt"))
        {
            throw FSException("KERNEL_FILE_SYSTEM_ERROR");
        }
        fsHandlers.fsDiskHandler->writeToDisk("It is a beautiful sunny day at Lorkenhorme, Germland. We hope you have a great day today!");
        std::cout << fsHandlers.fsDiskHandler->getDiskSizeRemaining() << " vBytes." << std::endl;
        if (!fsHandlers.fsDiskHandler->saveDisk("D:\\NUST Semester 6\\Extras\\Side Projects\\file-manager\\core\\memory\\disk.txt"))
        {
            throw FSException("KERNEL_FILE_SYSTEM_ERROR");
        }
        return true;
    }
}