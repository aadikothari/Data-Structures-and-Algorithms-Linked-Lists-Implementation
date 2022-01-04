#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "FileAllocManager.hpp"

using namespace std;

int main(int argc, char* argv[]) {
	bool condition = true;
	// Interactive mode
	if (argc == 1) {
		while (condition) {
			std::string line;
			// I ran out of ideas for variable naming LOL
			std::vector<string> lol;
			std::vector<unsigned int> addFile_outs;
			int start_pos = 0;
			FileAllocManager f;
			std::cout << ">>> ";

			// continue while exit isn't encountered
			while (line != "exit") {
				// reading lines
				getline(std::cin, line);

				// break if empty bit encountered
				if (line == "") {
					break;
				}
				std::string placeHolder;
				cout << ">>> " << line << endl;

				// traverse thru lines
				for (int i = 0; i < line.size(); i++) {
					// when a blank is encountered
					if (line[i] == ' ') {
						lol.push_back(placeHolder);
						placeHolder = "";
					}
					else
						placeHolder.push_back(line[i]);

				}

				// push the placeholder string into lol
				lol.push_back(placeHolder);

				// IF ADD
				if (lol[0] == "add") {
					int filesize = stoi(lol[2]);
					addFile_outs = f.addFile(lol[1], filesize);
					if (addFile_outs.size() > 0) {
						std::cout << "Index block at position " << addFile_outs[0] << endl;
						int i = 0;
						while (i < addFile_outs.size() - 1) {
							std::cout << "Block " << i << " is at position " << addFile_outs[i + 1] << "." << endl;
							i++;
						}
						std::cout << "\n";
					}
					else
						std::cout << "Invalid command or parameter" << endl;
				}

				// IF DELETE
				else if (lol[0] == "del") {
					if (f.deleteFile(lol[1])) {
						cout << lol[1] << " is deleted successfully!" << endl;
					}
					else
						std::cout << "Invalid command or parameter" << endl;
					cout << endl;
				}

				// IF SEEK
				else if (lol[0] == "seek") {
					int india = f.seekFile(lol[1], stoi(lol[2]));
					if (india < 0)
						std::cout << "Invalid command or parameter" << endl;
					else
						cout << lol[1] << ": Block number " << lol[2] << " on disk is " << india << "." << endl;
					cout << "\n";
				}
				else if (lol[0] == "list") {
					std::vector<string> list_h;
					list_h = f.listFiles();
					int i = 0;
					while (i < list_h.size()) {
						std::cout << list_h[i] << endl;
						i++;
					}
					std::cout << endl;
				}

				// IF DISK
				else if (lol[0] == "disk") {
					vector<unsigned int> disk_h = f.printDisk();
					std::cout << "Out of " << MAX_BLOCKS << " blocks, following blocks are occupied:" << endl;
					if (disk_h.size() != 0) {
						int i = 0;
						while (i < disk_h.size()) {
							cout << disk_h[i] << " ";
							i++;
						}
						cout << endl;
						disk_h.clear();
					}
					cout << "\n";
				}

				// IF NOTHING; INVALID
				else
					std::cout << "Invalid command or parameter" << endl;
				// clear the vector
				lol.clear();
			}
		}
	}

	// USING command prompt
	else if (argc == 3) {
		ifstream inf(argv[2]);
		string funcCode = argv[1];
		std::string line;
		std::vector<string> lol;
		std::vector<unsigned int> addFile_outs;
		int start_pos = 0;
		FileAllocManager f;

		if (funcCode == "-f") {
			// While end of file hasn't been reached, keep going
			while (!inf.eof()) {
				getline(inf, line);
				if (line == "") {
					break;
				}
				std::string placeHolder;
				cout << ">>> " << line << endl;

				//traverse. thesame comments can be found in interactive mode
				for (int i = 0; i < line.size(); i++) {
					if (line[i] == ' ') {
						lol.push_back(placeHolder);
						placeHolder = "";
					}
					else
						placeHolder.push_back(line[i]);

				}
				lol.push_back(placeHolder);

				// Add
				if (lol[0] == "add") {
					int filesize = stoi(lol[2]);
					addFile_outs = f.addFile(lol[1], filesize);
					if (addFile_outs.size() > 0) {
						std::cout << "Index block at position " << addFile_outs[0] << endl;
						int i = 0;
						while (i < addFile_outs.size() - 1) {
							std::cout << "Block " << i << " is at position " << addFile_outs[i + 1] << "." << endl;
							i++;
						}
						std::cout << "\n";
					}
					else
						std::cout << "Invalid command or parameter" << endl;
				}

				// Delete
				else if (lol[0] == "del") {
					if (f.deleteFile(lol[1])) {
						cout << lol[1] << " is deleted successfully!" << endl;
					}
					else
						std::cout << "Invalid command or parameter" << endl;
					cout << endl;
				}

				// Seek
				else if (lol[0] == "seek") {
					int ctr = f.seekFile(lol[1], stoi(lol[2]));
					if (ctr < 0)
						std::cout << "Invalid command or parameter" << endl;
					else
						cout << lol[1] << ": Block number " << lol[2] << " on disk is " << ctr << "." << endl;
					cout << "\n";
				}

				// List
				else if (lol[0] == "list") {
					std::vector<string> list_h;
					list_h = f.listFiles();
					int i = 0;
					while (i < list_h.size()) {
						std::cout << list_h[i] << endl;
						i++;
					}
					std::cout << endl;
				}

				// Disk
				else if (lol[0] == "disk") {
					vector<unsigned int> disk_h = f.printDisk();
					std::cout << "Out of " << MAX_BLOCKS << " blocks, following blocks are occupied:" << endl;
					if (disk_h.size() != 0) {
						int i = 0;
						while (i < disk_h.size()) {
							cout << disk_h[i] << " ";
							i++;
						}
						cout << endl;
						disk_h.clear();
						cout << "\n";
					}
				}

				// OTHERWISE INVALID
				else
					std::cout << "Invalid command or parameter" << endl;
				lol.clear();

			}
		}
	}
}