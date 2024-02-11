#include "disk_handler.hpp"
#include <fstream>
#include <string>

namespace fs {
    bool FSDiskHandler::resetDisk(std::string diskFilePath) {
        std::ofstream diskFile;
        diskFile.open(diskFilePath);
        if(diskFile.is_open()){
            for (int id = 0; id < FS_DISK_MAX_BLOCK_COUNT; id++)
            {
                diskFile << id << " ........ -1 false \n";
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
}