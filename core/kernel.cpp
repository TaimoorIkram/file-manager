#include "kernel.hpp"

namespace fs {
    FSKernel::FSKernel() {
        fsHandlers.fsDiskHandler = new FSDiskHandler();
    }

    FSKernel::~FSKernel() {

    }

    bool FSKernel::startKernel() {
        if (!fsHandlers.fsDiskHandler->resetDisk("D:\\NUST Semester 6\\Extras\\Side Projects\\file-manager\\core\\memory\\disk.txt"))
        {
            throw FSException("KERNEL_FILE_SYSTEM_ERROR");
        }
        std::cout << fsHandlers.fsDiskHandler->getDiskSize() << " vBytes." << std::endl;
    }
}