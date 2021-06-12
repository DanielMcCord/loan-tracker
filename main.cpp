#include "cli.h"
#include "dbtable.h"
#include "item.h"
#include "loan.h"
#include "loanschema.h"
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    string loadFileName = "";

    // If the user does not load a file, tell them how to do it.
    if (argc >= 3 && strcmp(argv[1], "-f") == 0)
    {
        loadFileName = argv[2];
        cout << "Loaded from file: " << loadFileName << endl;
    }
    else
    {
        string commandName(argv[0]);

        cout << "Use `" << argv[0] << ' '
             << "-f FILENAME` to load records from a file." << endl;
    }

    LoanSchema db;
    CLI cli(&db);
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
