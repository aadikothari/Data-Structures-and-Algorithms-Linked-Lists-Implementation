#include "FileAllocManager.hpp"

/** Seed the random number generator
	  and set default values
  */
FileAllocManager::FileAllocManager() {
	srand(time(NULL));
	for (int i = 0; i < MAX_BLOCKS; i++) {
		disk[i].occupied = false;
		disk[i].arr = nullptr;
		disk[i].arrSize = 0;
	}
	occupiedBlocks = 0;
}

/** Clear all files from the directory and
	  deallocate the resources belong to the files
  */
FileAllocManager::~FileAllocManager() {
	clear();
}

/** Clear all files from the directory and
	  deallocate the resources belong to the files
  */
void FileAllocManager::clear() {
	for (int i = 0; i < MAX_BLOCKS; i++) {
		int* array = disk[i].arr;
		disk[i].occupied = false;
		disk[i].arrSize = 0;

		if (array != nullptr) {
			delete[] array;
		}
		else {
			array = nullptr;
		}
	}

	directory.clear();
	occupiedBlocks = 0;
	//struct File f;

	//f.name = "";
	//f.size = 0;
	//f.indexBlock = nullptr;

	//directory.clear();
}

/** Add a new file to the directory and allocate the required number of blocks to the file if
	  the disk has enough unoccupied blocks.
	  @param filename - a filename to add to the directory
	  @param filesize - the size of the file in KiB
	  @return indices of the blocks allocated to the file, starting with the index block, empty vector if unable to add the file
  */
std::vector<unsigned int> FileAllocManager::addFile(std::string filename, int filesize) {
	// if length exceeds max files, return empty vector
	if (directory.getLength() >= MAX_FILES) {
		return std::vector<unsigned int>();
	}

	// if filename doesn't match, or length is more than 0, return empty vector
	if ((findFile(filename) != -1) && (directory.getLength() > 0)) {
		return std::vector<unsigned int>();
	}
	else {
		// create empty vector
		std::vector<unsigned int> indices;

		// if space is still available, length doesn't exceed MAX files, and filesize is lesser or equal to empty blocks.
		if (((MAX_BLOCKS - occupiedBlocks) >= (static_cast<int>(ceil(static_cast<double>(filesize) / static_cast<double>(BLOCK_SIZE_KiB)) + 1.0)))
			&& (directory.getLength() < MAX_FILES)) {

			// the first available block to add the file in
			int index_block = findFirstAvailBlock(rand() % MAX_BLOCKS);

			// push it in vector
			indices.push_back(index_block);

			// set variables
			disk[index_block].occupied = true;
			disk[index_block].arr = new int[static_cast<int>(ceil(static_cast<double>(filesize)
				/ static_cast<double>(BLOCK_SIZE_KiB)))]();
			int* baseAddy = disk[index_block].arr;

			// increment occupied block
			occupiedBlocks++;

			// accompany changes for disk
			for (int i = 0; i < static_cast<int>(ceil(static_cast<double>(filesize) / static_cast<double>(BLOCK_SIZE_KiB))); i++) {
				*disk[index_block].arr = findFirstAvailBlock(rand() % MAX_BLOCKS);
				disk[*disk[index_block].arr].occupied = true;
				disk[index_block].arrSize++;
				indices.push_back(*disk[index_block].arr);
				disk[index_block].arr++;
			}

			// the base address is returned to disk array
			disk[index_block].arr = baseAddy;

			File f{
				filename,
				filesize,
				&disk[index_block]
			};

			// insert this file at the last position
			directory.insert(directory.getLength() + 1, f);

			// occupied blocks are incremented  
			occupiedBlocks += static_cast<int>(ceil(static_cast<double>(filesize) / static_cast<double>(BLOCK_SIZE_KiB)));
			return indices;	// return this vector
		}
		else {
			// otherwise return empty vector
			return std::vector<unsigned int>();
		}
	}
}

/** Delete a file from the directory and deallocate all the blocks belong to this file
	  @param filename - a file of filename to delete from the directory
	  @return whether the file could be deleted or not
  */
bool FileAllocManager::deleteFile(std::string filename) {
	//int decision = findFile(filename);

	// if file cannot be found
	if (findFile(filename) == -1) {
		return false;
	}

	// otherwise, continue:
	else {
		// store the directory
		File f = directory.getEntry(findFile(filename));

		// clear out the file
		for (int i = 0; i < f.indexBlock->arrSize; i++) {
			int index = f.indexBlock->arr[i];
			occupiedBlocks--;
			disk[index].occupied = false;
		}

		// set the File struct variables to 0, false and null wherever needed
		f.indexBlock->arrSize = 0;
		f.indexBlock->occupied = false;
		delete[] f.indexBlock->arr;
		f.indexBlock->arr = NULL;

		// occupied blocks should be decremented
		occupiedBlocks--;

		// remove the file as needed
		directory.remove(findFile(filename));
		return true;
	}
}

/** Read file name and the index to storage block to seek and print out which block number that corresponds to on the disk
	  @param filename - a filename to seek on disk
	  @param blocknumber - a block index of the file to seek its position on disk
	  @return index of the storage block on the disk corresponding to block number for the given file, -1 if invalid input
  */
int FileAllocManager::seekFile(std::string filename, int blocknumber) const {

	// if unable to find file, return -1
	if (findFile(filename) == -1) {
		return -1;
	}
	
	// if the block index of the file is out of bounds (more than the indexblock)
	if (blocknumber >= directory.getEntry(findFile(filename)).indexBlock->arrSize) {
		// return -1
		return -1;
	}

	// otherwise, for loop to traverse through the directory
	for (int i = 1; i <= directory.getLength(); i++) {
		// if filename matches
		if (filename == directory.getEntry(i).name) {
			// return the specified index
			return directory.getEntry(i).indexBlock->arr[blocknumber];
		}
	}
	return -1;
}

/** List all the file names in the directory
	  @return list of filenames in the directory, in reverse order of when they were added
  */
std::vector<std::string> FileAllocManager::listFiles() const {
	std::vector<std::string> answer;
	
	// traverse and push file from directory in the vector
	for (int i = directory.getLength(); i >= 1; i--) {
		std::string val = directory.getEntry(i).name;
		answer.push_back(val);
	}

	return answer;
}

/** Returns the list of all occupied blocks on disk
	  @return indices of allocated blocks, in ascending order
  */
std::vector<unsigned int> FileAllocManager::printDisk() const {
	std::vector<unsigned int> answer;

	for (int i = 0; i < MAX_BLOCKS; i++) {
		// if disk is fully occupied
		if (!disk[i].occupied) {
			//std::cout << "cannot add";
		}
		// if disk isn't fully occupied
		else {
			// push the index iof allocated blocks
			answer.push_back(i);
		}
	}

	return answer;
}

/** Find the file in the directory using file name
	  @param filename - the name of the file to find in the directory
	  @return the position of the file in the directory list, -1 if the file could not be found
  */
int FileAllocManager::findFile(std::string filename) const {
	for (int i = 1; i <= directory.getLength(); i++) {
		std::string val = directory.getEntry(i).name;
		if (filename == val) {
			return i;
		}
	}
	return -1;
}

/** Search will start at `start` position and go ahead till the last position. if all of these blocks are occupied, then search will continue from the first position to `start` - 1 position in the linked list
	  @param start - the start position to search for the first unoccupied block in the disk,
	  @return the position of the first unoccupied block in the disk
  */
int FileAllocManager::findFirstAvailBlock(int start) const {
	
	for (int i = start; i < MAX_BLOCKS; i++) {
		bool isItOccupied = disk[i].occupied;
		if (isItOccupied == false) {
			return i;
		}
	}

	for (int i = 0; i < start; i++) {
		bool isItOccupied = disk[i].occupied;
		if (isItOccupied == false) {
			return i;
		}
	}
}