#include "filehandler.h"

using namespace std;

string FileHandler::readTextFile(const filesystem::path &source)
{
    // Initialize the streams.
    ifstream input(source);
    string accumulator = "";

    // Put the input into the accumulator line by line.
    for (string line; getline(input, line);)
    {
        accumulator += line + '\n';
    }

    return accumulator;
}

void FileHandler::writeTextFile(
    const string &content, const filesystem::path &destination, bool clobber)
{
    ofstream output;

    if (!clobber)
    {
        output = ofstream(destination, ios_base::app);
    }
    else
    {
        output = ofstream(destination);
    }

    output << content;
}
