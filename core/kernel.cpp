#include "kernel.hpp"

namespace fs {
    FSKernel::FSKernel() {
    }

    FSKernel::~FSKernel() {

    }

    bool FSKernel::startKernel() {
        if (!fsHandlers.fsDiskHandler->resetDisk("D:\\NUST Semester 6\\Extras\\Side Projects\\file-manager\\core\\memory\\disk.txt"))
        {
            throw FSException("KERNEL_FILE_SYSTEM_ERROR");
        }
        std::cout << "All systems check." << std::endl;
    }
}