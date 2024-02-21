#include "disk.hpp"

namespace fs {
    FSDisk::FSDisk() {
        
    }

    FSDisk::~FSDisk() {

    }

    FSDisk::FSDiskMemoryDataNode* FSDisk::getHeadNode() {
        return fsDiskMemoryDataHeadNode;
    }

    FSDisk::FSDiskMemoryDataNode* FSDisk::getNode(int id) {
        FSDisk::FSDiskMemoryDataNode *tempNode = getHeadNode();
        while (tempNode->next != nullptr)
        {
            if (tempNode->id == id) return tempNode;
            tempNode = tempNode->next;
        }

        return nullptr;
    }

    FSDisk::FSDiskMemoryDataNode* FSDisk::writeToBlock(int id, std::string data, bool markRead) {
        FSDisk::FSDiskMemoryDataNode* tempNode = getNode(id);
        std::string oldDiskData = tempNode->data;
        tempNode->data = data;
        if (markRead == true) {
            tempNode->empty = false;
            freeNodeCount--;
        }
        return tempNode;
    }

    std::string FSDisk::readFromBlock(int id) {
        FSDisk::FSDiskMemoryDataNode* tempNode = getNode(id);
        std::string diskData = tempNode->data;
        return diskData;
    }

    FSDisk::FSDiskMemoryDataNode* FSDisk::addDiskMemoryDataNode(std::string data) {
        FSDisk::FSDiskMemoryDataNode* tempNode = getHeadNode();
        FSDisk::FSDiskMemoryDataNode *newNode = new FSDisk::FSDiskMemoryDataNode;
        newNode->id = globalBlockId++;
        newNode->data = data;
        newNode->next = nullptr;
        newNode->sizeRemaining = FS_DISK_BLOCK_SIZE;
        newNode->toRead = -1;

        if (fsDiskMemoryDataHeadNode == nullptr) {
            fsDiskMemoryDataHeadNode = newNode;
            return tempNode;
        }
        while (tempNode->next != nullptr) {
            tempNode = tempNode->next;
        }
        tempNode->next = newNode;
        return tempNode->next;
    }
    
    bool FSDisk::linkNodes(int fromId, int toId) {
        FSDisk::FSDiskMemoryDataNode* tempNodeFrom = getNode(fromId);
        FSDisk::FSDiskMemoryDataNode* tempNodeTo = getNode(toId);
        tempNodeFrom->toRead = tempNodeTo->id;
        return true;
    }

    FSDisk::FSDiskMemoryDataNode* FSDisk::getLinkedNodes(int id) {
        FSDisk::FSDiskMemoryDataNode *tempNode = getNode(id);
        FSDisk::FSDiskMemoryDataNode* tempRootNode = tempNode;
        while (tempNode->toRead != -1) {
            FSDisk::FSDiskMemoryDataNode* otherNode = getNode(tempNode->toRead);
            tempRootNode->next = otherNode;
            tempNode = tempNode->next;
        }
        return tempRootNode;
    }

    int FSDisk::getNextEmptyDataNode() {
        FSDisk::FSDiskMemoryDataNode *tempNode = getHeadNode();
        while (tempNode != nullptr) {
            if (tempNode->empty) return tempNode->id;
            tempNode = tempNode->next;
        }
        return -1;
    }

    bool FSDisk::freeBlock(int blockId) {
        FSDisk::FSDiskMemoryDataNode* tempNode = getNode(blockId);
        tempNode->data = "........";
        tempNode->sizeRemaining = FS_DISK_BLOCK_SIZE;
        tempNode->toRead = -1;
        freeNodeCount++;

        return true;
    }

    int FSDisk::getNodeCount() {
        return globalBlockId;
    }
    
    int FSDisk::getFreeNodeCount() {
        return freeNodeCount;
    }
}