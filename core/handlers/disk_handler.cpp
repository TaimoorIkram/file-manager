#include "disk_handler.hpp"
#include "../utils/utils.hpp"
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

    bool FSDiskHandler::loadDisk(std::string diskFilePath) {
        std::ifstream diskFile;
        std::string diskLine;
        diskFile.open(diskFilePath);
        if (diskFile.is_open()) {
            while (std::getline(diskFile, diskLine)) {
                std::vector<std::string> diskLineTokens = FSUtils::splitString(diskLine, FS_DISK_DELIMITER);

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

        // Check if the blockId is valid
        if (blockId < 0 || blockId >= fsDisk->getNodeCount()) {
            // Invalid blockId
            return false;
        }
        // checking blocks needed
        int blockDataSize = blockData.size();
        int blocksNeeded = ceil((double)blockDataSize / FS_DISK_BLOCK_SIZE);
        if (fsDisk->getFreeNodeCount() < blocksNeeded) return false; // need to raise the DISK_MEMORY_OVERFLOW_EXCEPTION
        // storing into a  buffer
        int startPos = 0;
        std::vector<std::string> blocks;
        while (startPos < blockData.length()) {
            blocks.push_back(blockData.substr(startPos, FS_DISK_BLOCK_SIZE));
            startPos += FS_DISK_BLOCK_SIZE;
        }

        // wrting 
        FSDisk::FSDiskMemoryDataNode* prevNode = nullptr, * currentNode = nullptr;

        for (int index = 0; index < blocks.size(); index++) {
            prevNode = currentNode;
            currentNode = fsDisk->writeToBlock(blockId, blocks[index], true);
            if (fsDisk->getNode(blockId)->toRead != -1)
            {
                blockId = fsDisk->getNode(blockId)->toRead;
            }
            else {
                blockId = fsDisk->getNextEmptyDataNode();
            }
            if (prevNode != nullptr) fsDisk->linkNodes(prevNode->id, currentNode->id);

        }

        return true;
    }

    bool FSDiskHandler::clearDisk(int blockId, bool clearLinked = false) {
        FSDisk::FSDiskMemoryDataNode* tempNode = fsDisk->getNode(blockId);

        if (clearLinked == true) {
            int nextNodeId = -1;
            while (true) {
                nextNodeId = tempNode->toRead;
                fsDisk->freeBlock(tempNode->id);

                if (nextNodeId == -1) break;
                tempNode = fsDisk->getNode(nextNodeId);
            }
        }

        return true;
    }

    int FSDiskHandler::getDiskSize() {
        return fsDisk->getNodeCount();
    }
    
    int FSDiskHandler::getDiskSizeRemaining() {
        return fsDisk->getFreeNodeCount();
    }
}