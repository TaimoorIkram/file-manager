#include "file.hpp"

namespace fs {
	FSFile::FSFile(std::string fileName) {
		this->fileName = fileName;
	}

	FSFile::~FSFile() {

	}

	std::string FSFile::getFileName() {
		return fileName;
	}

	int FSFile::getFileSize() {
		return fileSize;
	}

	int FSFile::getFileStartBlock() {
		return fileStartBlock;
	}

	bool FSFile::setINode(FSIndexNode* iNode) {
		this->iNode = iNode;
		return true;
	}

	FSFile::FSIndexNode* FSFile::getINode() {
		return iNode;
	}

	bool FSFile::setFileStartBlock(int blockId) {
		fileStartBlock = blockId;
		return true;
	}

	bool FSFile::setDateUpdated(std::string dateUpdated) {
		iNode->dateUpdated = dateUpdated.substr(0, dateUpdated.size() - 2);
		return true;
	}
}