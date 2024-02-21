#include "file_tree.hpp"
#include "../../utils/utils.hpp"

#include <sstream>

namespace fs {
	FSFileTree::FSFileTree() {
		rootDirectory = new FSDirectory("root");
		FSFile::FSIndexNode* iNode = new FSFile::FSIndexNode;

		time_t timeNow = time(0);
		std::string directoryCreatedOn = ctime(&timeNow);
		iNode->dateCreated = directoryCreatedOn.substr(0, directoryCreatedOn.size() - 1);
		iNode->dateUpdated = directoryCreatedOn.substr(0, directoryCreatedOn.size() - 1);

		rootDirectory->setINode(iNode);

		setCurrentDirectory(getRootDirectory());
	}

	FSFile* FSFileTree::createFile(std::string filePath) {
		std::vector<std::string> pathParameters = FSUtils::splitString(filePath, "/");
		FSDirectory* startDirectory = getCurrentDirectory();
		FSFile* file = new FSFile(pathParameters.back());
		FSFile::FSIndexNode* iNode = new FSFile::FSIndexNode;

		time_t timeNow = time(0);
		std::string fileCreatedOn = ctime(&timeNow);
		iNode->dateCreated = fileCreatedOn.substr(0, fileCreatedOn.size() - 1);
		iNode->dateUpdated = fileCreatedOn.substr(0, fileCreatedOn.size() - 1);

		file->setINode(iNode);

		if (pathParameters.size() == 1) {
			if (currentDirectory->addFile(file)) return file;
			else return nullptr;
		}
		else if (pathParameters.at(0) != ".") {
			startDirectory = currentDirectory->findDirectory(pathParameters.front());
			if (startDirectory == nullptr) return nullptr;
		}

		for (int iterator = 1; iterator < pathParameters.size() - 1; iterator++) {
			startDirectory = startDirectory->findDirectory(pathParameters.at(iterator));
			if (startDirectory == nullptr) return nullptr;
		}
		startDirectory->addFile(file);
		return file;
	}
	
	FSDirectory* FSFileTree::createDirectory(std::string directoryPath) {
		std::vector<std::string> pathParameters = FSUtils::splitString(directoryPath, "/");
		FSDirectory* startDirectory = getCurrentDirectory();
		FSDirectory* directory = new FSDirectory(pathParameters.back());
		FSFile::FSIndexNode* iNode = new FSFile::FSIndexNode;

		time_t timeNow = time(0);
		std::string directoryCreatedOn = ctime(&timeNow);
		iNode->dateCreated = directoryCreatedOn.substr(0, directoryCreatedOn.size() - 1);
		iNode->dateUpdated = directoryCreatedOn.substr(0, directoryCreatedOn.size() - 1);

		directory->setINode(iNode);

		if (pathParameters.size() == 1) {
			if (currentDirectory->addDirectory(directory)) return directory;
			else return nullptr;
		}
		else if (pathParameters.at(0) != ".") {
			startDirectory = currentDirectory->findDirectory(pathParameters.front());
			if (startDirectory == nullptr) return nullptr;
		}

		for (int iterator = 1; iterator < pathParameters.size() - 1; iterator++) {
			startDirectory = startDirectory->findDirectory(pathParameters.at(iterator));
			if (startDirectory == nullptr) return nullptr;
		}
		startDirectory->addDirectory(directory);
		
		return directory;
	}

	bool FSFileTree::setCurrentDirectory(FSDirectory *directory) {
		currentDirectory = directory;
		return true;
	}

	bool FSFileTree::setCurrentFile(FSFile *file) {
		currentFile = file;
		return true;
	}

	FSDirectory* FSFileTree::getRootDirectory() {
		return rootDirectory;
	}

	FSDirectory* FSFileTree::getCurrentDirectory() {
		return currentDirectory;
	}

	FSFile* FSFileTree::getCurrentFile() {
		return currentFile;
	}

	std::string FSFileTree::getDirectoryTree(FSDirectory *directory, int level) {
		std::ostringstream treeString;
		std::string spaceCharacter = "";
		FSFile::FSIndexNode* directoryINode = directory->getINode();

		treeString << directory->getDirectoryName();
		treeString << "  -c " << directoryINode->dateCreated;
		treeString << "  -lu " << directoryINode->dateUpdated;
		treeString << "  -u " << directoryINode->createdBy << '\n';

		for (int iterator = 0; iterator < level; iterator++) {
			spaceCharacter += "  ";
		}

		if (directory->getSubdirectoriesCount() > 0) {
			for each (FSDirectory *subdirectory in directory->getSubdirectories()) {
				treeString << spaceCharacter << "D " << getDirectoryTree(subdirectory, level + 1);
			}
		}

		if (directory->getFilesCount() > 0) {
			for each (FSFile *file in directory->getFiles()) {
				FSFile::FSIndexNode *fileINode = file->getINode();

				treeString << spaceCharacter << "F " << file->getFileName();
				treeString << "  -c " << fileINode->dateCreated;
				treeString << "  -lu " << fileINode->dateUpdated;
				treeString << "  -u " << fileINode->createdBy << '\n';
			}
		}


		return treeString.str();
	}
	
	FSFile* FSFileTree::findFile(std::string filePath) {
		std::vector<std::string> pathParameters = FSUtils::splitString(filePath, "/");
		FSDirectory* startDirectory = getCurrentDirectory();
		FSFile* file;

		if (pathParameters.size() == 1) {
			file = currentDirectory->findFile(pathParameters.back());
			;			if (file != nullptr) return file;
			else return nullptr;
		}
		else if (pathParameters.at(0) != ".") {
			startDirectory = currentDirectory->findDirectory(pathParameters.front());
			if (startDirectory == nullptr) return nullptr;
		}

		for (int iterator = 1; iterator < pathParameters.size() - 1; iterator++) {
			startDirectory = startDirectory->findDirectory(pathParameters.at(iterator));
		}
		file = currentDirectory->findFile(pathParameters.back());

		return file;
	}

	bool FSFileTree::deleteDirectory(std::string directoryPath) {
		std::vector<std::string> pathParameters = FSUtils::splitString(directoryPath, "/");
		FSDirectory* startDirectory = getCurrentDirectory();
		std::string targetDirectoryName = pathParameters.back();

		if (pathParameters.size() == 1) {
			if (currentDirectory->hasDirectory(targetDirectoryName)) {
				currentDirectory->deleteDirectory(targetDirectoryName);
				return true;
			}
			else return false;
		}
		else if (pathParameters.at(0) != ".") {
			startDirectory = currentDirectory->findDirectory(pathParameters.front());
			if (startDirectory == nullptr) return false;
		}

		for (int iterator = 1; iterator < pathParameters.size() - 1; iterator++) {
			startDirectory = startDirectory->findDirectory(pathParameters.at(iterator));
			if (startDirectory == nullptr) return false;
		}

		if (startDirectory->hasDirectory(targetDirectoryName)) {
			startDirectory->deleteDirectory(targetDirectoryName);
			return true;
		}
		else return false;
	}


	FSDirectory* FSFileTree::findDirectory(std::string directoryPath) {
		std::vector<std::string> pathParameters = FSUtils::splitString(directoryPath, "/");
		FSDirectory* startDirectory = getCurrentDirectory();
		std::string targetDirectoryName = pathParameters.back();

		if (pathParameters.size() == 1) {
			if (currentDirectory->hasDirectory(targetDirectoryName)) {
				startDirectory = currentDirectory->findDirectory(targetDirectoryName);
				return startDirectory;
			}
			else return nullptr;
		}
		else if (pathParameters.at(0) != ".") {
			startDirectory = currentDirectory->findDirectory(pathParameters.front());
			if (startDirectory == nullptr) return nullptr;
		}

		for (int iterator = 1; iterator < pathParameters.size(); iterator++) {
			startDirectory = startDirectory->findDirectory(pathParameters.at(iterator));
			if (startDirectory == nullptr) return nullptr;
		}

		return startDirectory;
	}

	bool FSFileTree::deleteFile(std::string filePath) {
		std::vector<std::string> pathParameters = FSUtils::splitString(filePath, "/");
		FSDirectory* startDirectory = getCurrentDirectory();
		std::string targetFileName = pathParameters.back();

		if (pathParameters.size() == 1) {
			if (currentDirectory->hasFile(targetFileName)) {
				currentDirectory->deleteFile(targetFileName);
				return true;
			}
			else return false;
		}
		else if (pathParameters.at(0) != ".") {
			startDirectory = currentDirectory->findDirectory(pathParameters.front());
			if (startDirectory == nullptr) return false;
		}

		for (int iterator = 1; iterator < pathParameters.size() - 1; iterator++) {
			startDirectory = startDirectory->findDirectory(pathParameters.at(iterator));
			if (startDirectory == nullptr) return false;
		}

		if (startDirectory->hasFile(targetFileName)) {
			startDirectory->deleteFile(targetFileName);
			return true;
		}
		else return false;
	}
}