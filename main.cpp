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
        else if (!filesystem::exists(loadFilePath))
        {
            cout << "File " << loadFilePath << " does not exist." << endl;
        }
        else
        {
            string loadData = FileHandler::readTextFile(loadFilePath);

            if (loadData.empty())
            {
                cout << "No data found. File may be empty, or you may lack sufficient permissions."
                     << endl;
            }
            else
            {
                db = LoanSchema(loadData);

                if (db.empty())
                {
                    cout << "Failed to load data. File may be corrupted or improperly formatted."
                         << endl;
                }
                else
                {
                    cout << "Loaded from file: " << loadFilePath << endl;
                }
            }
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
            bool commandValid = cli.attemptCommand(command);

            if (commandValid)
            {
                break;
            }
        }
    }

    return 0;
}
