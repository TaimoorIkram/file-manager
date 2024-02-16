#include "disk_handler.hpp"
#include <fstream>
#include <string>
#include <vector>

namespace fs {
    FSDiskHandler::FSDiskHandler() {
        FSDisk::FSDiskMemoryDataNode newNode{};
        this->fsDisk = new FSDisk();
    }

    bool FSDiskHandler::resetDisk(std::string diskFilePath) {
        for (int id = 0; id < FS_DISK_MAX_BLOCK_COUNT; id++)
        {
            fsDisk->addDiskMemoryDataNode(FS_DISK_NO_DATA);
        }
        return true;
    }

    std::vector<std::string> splitString(std::string& str, std::string delimiter) {
        std::vector<std::string> tokens;
        size_t pos = 0;
        size_t delimiterLength = delimiter.length();

        while ((pos = str.find(delimiter)) != std::string::npos) {
            tokens.push_back(str.substr(0, pos));
            str.erase(0, pos + delimiterLength);
        }
        tokens.push_back(str); // Push the remaining part of the string after the last delimiter
        return tokens;
    }

    bool FSDiskHandler::loadDisk(std::string diskFilePath) {
        std::ifstream diskFile;
        std::string diskLine;
        diskFile.open(diskFilePath);
        if (diskFile.is_open()) {
            while (std::getline(diskFile, diskLine)) {
                std::vector<std::string> diskLineTokens = splitString(diskLine, FS_DISK_DELIMITER);

                int blockId = std::stoi(diskLineTokens.at(0));
                std::string blockData = diskLineTokens.at(1);
                int blockLinkedToId = std::stoi(diskLineTokens.at(0));
                
                if (blockData == FS_DISK_NO_DATA) continue;
                
                fsDisk->writeToBlock(blockId, blockData, true);
                fsDisk->linkNodes(blockId, blockLinkedToId);
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
            FSDisk::FSDiskMemoryDataNode *diskMemoryNode = fsDisk->getHeadNode();
            while (diskMemoryNode != nullptr) {
                diskFile << diskMemoryNode->id << FS_DISK_DELIMITER << diskMemoryNode->data  << FS_DISK_DELIMITER << diskMemoryNode->toRead << "\n";
                diskMemoryNode = diskMemoryNode->next;
            }
            diskFile.close();
            return true;
        }
        else return false;
    }

    bool FSDiskHandler::writeToDisk(std::string data) {
        // TODO: 
        // 1. Divide the string into byte length parts and store in a buffer. 
        // 2. Write them one by one from buffer to memory by first requesting 
        // the required blocks.
        // 3. Raise a DISK_MEMORY_OVERFLOW_EXCEPTION if the requsted 
        // blocks are more than left.
        // 4. Start writing the bytes one by one to the disk by requesting the 
        // next available non-empty block.
        //
        int blockDataSize = data.size();
        int blocksNeeded = ceil((double) blockDataSize / FS_DISK_BLOCK_SIZE);
        if (fsDisk->getFreeNodeCount() < blocksNeeded) return false;
        FSDisk::FSDiskMemoryDataNode *prevNode = nullptr, *currentNode = nullptr;

        for (int index = 0; index < blocksNeeded; index++) {
            int blockDataStartIndex = index * FS_DISK_BLOCK_SIZE;
            std::string blockData = data.substr(blockDataStartIndex, FS_DISK_BLOCK_SIZE);
            prevNode = currentNode;
            currentNode = fsDisk->writeToBlock(fsDisk->getNextEmptyDataNode(), blockData, true);
            
            if (prevNode != nullptr) fsDisk->linkNodes(prevNode->id, currentNode->id);
        }

        return true;
    }
    
    bool FSDiskHandler::writeToDisk(int blockId, std::string blockData) {
        // TODO: 
        // 1. Divide the string into byte length parts and store in a buffer. 
        // 2. Write them one by one from buffer to memory by first requesting 
        // the required blocks.
        // 3. Raise a DISK_MEMORY_OVERFLOW_EXCEPTION if the requsted 
        // blocks are more than one plus the blocks left.
        // 4. Start writing the data one byte by the other by first writing to 
        // the byte blockId of the virtual disk (fsDisk) object.
        //

        return false;
    }

    int FSDiskHandler::getDiskSize() {
        return fsDisk->getNodeCount();
    }
    
    int FSDiskHandler::getDiskSizeRemaining() {
        return fsDisk->getFreeNodeCount();
    }
}