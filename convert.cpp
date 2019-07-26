#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Find the number of entries to be created in the array
unsigned int entriesCount(string fileName) {
    unsigned int size = 0;
    ifstream myFile(fileName, ios::binary);

    if (myFile.is_open()) {
        // Find the number of values in the file
        myFile.seekg(0, myFile.end);
        size = myFile.tellg();
        myFile.seekg(0, myFile.beg);
    } else {
        cout << "Unable to open file";
    }
    myFile.close();
    return size;
}

// Reads the binary file and returns a vector of numbers that are evaluated
// by casting the character to unsigned int as the data originally was
vector<unsigned int> readDafsaBinary(string fileName) {
    unsigned int length = entriesCount(fileName);
    vector<char> buffer(length, 0);
    ifstream myFile(fileName, ios::binary);
    if (myFile.is_open()) {
        myFile.read(&buffer[0], length);

    } else {
        cout << "Unable to open file";
    }

    // Casting characters to unsigned int as observed in make_dafsa.py
    vector<unsigned int> numbers;
    for (auto buf : buffer) {
        unsigned int num = (unsigned char)(buf);
        numbers.push_back(num);
    }

    myFile.close();
    return numbers;
}

// Converts the numbers to hex and formats them to follow C++ array syntax as
// created by make_dafsa.py
void makeHexArray(string filename, vector<unsigned int> numbers) {
    ofstream outfile(filename);

    string text = "/* This file is generated. DO NOT EDIT!\n\n";
    text += "The byte array encodes a dictionary of strings and values. See ";
    text += "convert.cpp/make_dafsa.py for documentation.";
    text += "*/\n\n";
    text +=
        "const unsigned char kDafsa[" + to_string(numbers.size()) + "] = {\n";

    // Used for simple formatting for readability of output
    int formatCount = 1;

    for (auto num : numbers) {
        text += "  ";
        stringstream stream;  // called inside thee loop to reset its value
        // same thing as '0x%02x', formats to get atleast two digits after hex
        // conversion
        stream << setfill('0') << setw(2) << hex << num;
        text += "0x" + stream.str();
        if (formatCount % 12 == 0) {
            text += ",\n";
        } else {
            text += ",";
        }
        ++formatCount;
    }
    text += "\n";
    text += "};\n";

    outfile << text;
    outfile.close();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Enter the correct number of arguments." << endl;
        return -1;
    }
    vector<unsigned int> numbers = readDafsaBinary(argv[1]);
    makeHexArray(argv[2], numbers);
    return 0;
}