#include "cli.h"
#include "dbtable.h"
#include "item.h"
#include "loan.h"
#include "loanschema.h"
#include <iostream>

#include <vector>

using namespace std;

int main(int argc, char **argv)
{
    LoanSchema db;
    CLI cli(&db);
    cli.welcome();

    string command = "";

    while (command != "exit")
    {
        while (true)
        {
            command = cli.prompt("\nType a command, and press ENTER.\n > ");
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
