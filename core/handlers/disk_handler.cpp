#include "disk_handler.hpp"
#include <fstream>
#include <string>

namespace fs {
    FSDiskHandler::FSDiskHandler() {
        FSDisk::FSDiskMemoryDataNode newNode{};
        this->fsDisk = new FSDisk();
    }

    bool FSDiskHandler::resetDisk(std::string diskFilePath) {
        std::ofstream diskFile;
        diskFile.open(diskFilePath);
        if(diskFile.is_open()){
            for (int id = 0; id < FS_DISK_MAX_BLOCK_COUNT; id++)
            {
                diskFile << id << " ........ -1 false \n";
                fsDisk->addDiskMemoryDataNode("........");
            }
            
            diskFile.close();
            return true;
        }
        else return false;
    }

    bool FSDiskHandler::loadDisk(std::string diskFilePath) {
        std::ifstream diskFile;
        std::string diskLine;
        diskFile.open(diskFilePath);
        if (diskFile.is_open()) {
            while (std::getline(diskFile, diskLine)) {
                std::cout << diskLine << std::endl;
            }
            diskFile.close();
            return true;
        }
        else return false;
    }

    bool FSDiskHandler::saveDisk(std::string diskFilePath) {
        std::ofstream diskFile;
        diskFile.open(diskFilePath);
        if(diskFile.is_open()){
            diskFile << "0 012345678 1 true \n";
            diskFile.close();
            return true;
        }
        else return false;
    }

    bool FSDiskHandler::writeToDisk(std::string) {
        // TODO: 
        // 1. Divide the string into byte length parts and store in a buffer. 
        // 2. Write them one by one from buffer to memory by first requesting 
        // the required blocks.
        // 3. Raise a DISK_MEMORY_OVERFLOW_EXCEPTION if the requsted 
        // blocks are more than left.
        // 4. Start writing the bytes one by one to the disk by requesting the 
        // next available non-empty block.
        //
    }
    
    bool FSDiskHandler::writeToDisk(int blockId, std::string) {
        // TODO: 
        // 1. Divide the string into byte length parts and store in a buffer. 
        // 2. Write them one by one from buffer to memory by first requesting 
        // the required blocks.
        // 3. Raise a DISK_MEMORY_OVERFLOW_EXCEPTION if the requsted 
        // blocks are more than one plus the blocks left.
        // 4. Start writing the data one byte by the other by first writing to 
        // the byte blockId of the virtual disk (fsDisk) object.
        //
    }

    int FSDiskHandler::getDiskSize() {
        return fsDisk->getNodeCount();
    }
}