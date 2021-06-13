#include "filehandler.h"

using namespace std;

string FileHandler::readTextFile(const filesystem::path &source)
{
    // Initialize the streams.
    ifstream input(source);
    //stringstream accumulator(ios_base::app);
    string accumulator = "";

    // Put the input into the accumulator line by line.
    for (string line; getline(input, line);)
    {
        accumulator += line + '\n';
    }

    return accumulator;
}
