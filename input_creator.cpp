#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

  /////////////////////////////////////////
 //      Runner For Red Black BST      //
////////////////////////////////////////

int main() {
    // Seed the random number generator
    std::srand(std::time(0));

    // Open a file in write mode
    std::ofstream outputFile("input.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    // Characters that can be randomly chosen
    char commands[3] = {'I','E'};

    // Generate lines of output
    for (int i = 0; i < 1000; ++i) {
        char command = commands[std::rand() % 3];  // Randomly select 'I', or 'E'
        //char command = commands[0];
        int number = std::rand() % 3000;  // Generate a random number between 0 and 3000

        // Write to the file
        outputFile << command << " " << number << std::endl;
    }

    outputFile.close();


    return 0;
}