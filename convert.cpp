#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    vector<char> buffer(37837, 0);
    int length = 0;
    ifstream myfile("input.bin", ios::binary | ios::ate);
    if (myfile.is_open())
    {
        myfile.seekg(0, myfile.end);
        length = myfile.tellg();
        myfile.seekg(0, myfile.beg);

        cout << "Reading " << length << " characters... ";
        // read data as a block:
        myfile.read(&buffer[0], length);

        if (myfile)
            cout << "all characters read successfully." << endl;
        else
            cout << "error: only " << myfile.gcount() << " could be read";
        myfile.close();
    }
    else
        cout << "Unable to open file";

    ofstream outfile("out.inc");
    for (auto val = buffer.begin(); val != buffer.end(); ++val)
    {
        unsigned int num = (unsigned char)(*val);
        outfile << num << '\n';
    }
    outfile.close();
    return 0;
}