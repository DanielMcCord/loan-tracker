#include "cli.h"
#include "dbtable.h"
#include "filehandler.h"
#include "item.h"
#include "loan.h"
#include "loanschema.h"
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    LoanSchema db;
    CLI cli(&db);
    filesystem::path loadFilePath;

    // Check for optional command line flag to load a data file
    if (argc >= 3 && strcmp(argv[1], "-f") == 0)
    {
        loadFilePath = argv[2];

        if (loadFilePath.empty())
        {
            cout << "Path empty - file not loaded." << endl;
        }
        else
        {
            string loadData = FileHandler::readTextFile(loadFilePath);
            cout << "Loaded from file: " << loadFilePath << endl;
        }
    }
    else
    {
        // Give the user a hint if they didn't use the feature.
        cli.commandHint();
    }

    cli.welcome();
    string command = "";

    while (command != "exit")
    {
        while (true)
        {
            command = cli.prompt("\n > ");
            bool commandValid = cli.attempt_command(command);

            if (commandValid)
            {
                break;
            }
            else
            {
                cli.on_invalid_command(command);
            }
        }
    }

    return 0;
}
