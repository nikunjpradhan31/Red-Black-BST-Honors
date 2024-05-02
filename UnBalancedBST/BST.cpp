
#include "MyMap.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

int getRandomNumber() {
    std::srand(200);
    // Generate a random number in the range 0 to 400 (inclusive)
    int random_number = std::rand() % 401;
    // Adjust the range to -200 to 200
    random_number -= 200;
    return random_number;
}

int main() {
    // Loop through each file in the TestFiles directory
    std::ofstream outputFile("results_BST.txt");
    for (const auto& entry : fs::directory_iterator("TestFiles")) {
        if (entry.path().extension() == ".txt") { // Check if the file is a .txt file
            std::ifstream file(entry.path());
            std::string line;
            MyMap<int, int> map;

            while (getline(file, line)) {
                std::istringstream iss(line);
                char operation;
                int key;

                if (!(iss >> operation >> key)) {
                    continue;
                }
                if (operation == 'I') {
                    map.insert(key, getRandomNumber());
                } else if (operation == 'E') {
                    map.erase(key);
                }
            }

            //map.printTree();
            outputFile << "Normal Height of the tree for file " << entry.path().filename() << ": " << map.getHeight(map.begin()) <<" with " << map.size()<< " nodes"<< std::endl;

            file.close();
        }
    }
    return 0;
}