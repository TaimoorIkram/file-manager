#include "directory.hpp"

namespace fs {
	FSDirectory::FSDirectory(std::string directoryName) {
		this->directoryName = directoryName;
	}

	FSDirectory::~FSDirectory() {

	}

	FSFile* FSDirectory::findFile(std::string fileName) {
		if (files.size() == 0) return nullptr;
		
		for each (FSFile *file in files) {
			if (file->getFileName() == fileName) return file;
		}
		return nullptr;
	}

	FSDirectory* FSDirectory::findDirectory(std::string directoryName) {
		if (directories.size() == 0) return nullptr;

		for each (FSDirectory* directory in directories) {
			if (directory->getDirectoryName() == directoryName) return directory;
		}
		return nullptr;
	}

	std::vector<FSDirectory*> FSDirectory::getSubdirectories() {
		return directories;
	}

	std::vector<FSFile*> FSDirectory::getFiles() {
		return files;
	}

	int FSDirectory::getSubdirectoriesCount() {
		return directories.size();
	}

	int FSDirectory::getFilesCount() {
		return files.size();
	}

	bool FSDirectory::addFile(FSFile *file) {
		files.push_back(file);
		return true;
	}

	bool FSDirectory::setINode(FSFile::FSIndexNode *iNode) {
		this->iNode = iNode;
		return true;
	}

	FSFile::FSIndexNode* FSDirectory::getINode() {
		return iNode;
	}

	bool FSDirectory::setDateUpdated(std::string dateUpdated) {
		iNode->dateUpdated = dateUpdated.substr(0, dateUpdated.size() - 2);
		return true;
	}

	bool FSDirectory::addDirectory(FSDirectory *directory) {
		directories.push_back(directory);
		return true;
	}

	std::string FSDirectory::getDirectoryName() {
		return directoryName;
	}

	bool FSDirectory::deleteFile(std::string fileName) {
		for (int iterator = 0; iterator < files.size(); iterator++) {
			if (files.at(iterator)->getFileName() == fileName) {
				files.erase(files.begin() + iterator);
				return true;
			}
		}

		return false;
	}

	bool FSDirectory::hasDirectory(std::string directoryName) {
		for each (FSDirectory *directory in directories) {
			if (directory->getDirectoryName() == directoryName) return true;
		}
		return false;
	}

	bool FSDirectory::deleteDirectory(std::string directoryName) {
		if (hasDirectory(directoryName)) {
			for (int iterator = 0; iterator < directories.size(); iterator++) {
				FSDirectory* directory = directories.at(iterator);
				if (directory->getDirectoryName() == directoryName) {
					directories.erase(directories.begin() + iterator);
					delete directory;
					return true;
				}
			}
		}

		return false;
	}
	
	bool FSDirectory::hasFile(std::string fileName) {
		for each (FSFile *file in files) {
			if (file->getFileName() == fileName) return true;
		}
		return false;
	}
}