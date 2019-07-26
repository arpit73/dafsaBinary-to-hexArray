#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

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

vector<char> readDafsaBinary(string fileName) {
    unsigned int length = entriesCount(fileName);
    vector<char> buffer(length, 0);
    ifstream myFile(fileName, ios::binary);
    if (myFile.is_open()) {
        myFile.read(&buffer[0], length);

    } else {
        cout << "Unable to open file";
    }
    myFile.close();
    return buffer;
}

void makeHexArray(vector<char> buffer) {
    ofstream outfile("out.inc");
    vector<unsigned int> nums;

    for (auto buf : buffer) {
        unsigned int num = (unsigned char)(buf);
        nums.push_back(num);
    }

    string text = "/* This file is generated. DO NOT EDIT!\n\n";
    text += "The byte array encodes a dictionary of strings and values. See ";
    text += "make_dafsa.py for documentation.";
    text += "*/\n\n";
    text += "const unsigned char kDafsa[" + to_string(nums.size()) + "] = {\n";

    int formatCount = 1;
    for (auto num : nums) {
        text += "  ";
        stringstream stream;
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

int main() {
    vector<char> buffer = readDafsaBinary("input.bin");
    makeHexArray(buffer);
    return 0;
}