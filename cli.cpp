#include "cli.h"

using namespace std;

CLI::CLI()
    : validCommands({"create item", "create loan", "list items", "list loans", "delete item",
                     "save", "exit", "help"})
{
}

CLI::CLI(const vector<string> &validCommands)
{
    this->validCommands = validCommands;
}

void CLI::welcome() const
{
    cout << "LoanIt - an item lending tracker." << endl;
    cout << "For help, type 'help' (without quotes) and press enter." << endl;
    list_valid_commands();
}

void CLI::on_invalid_command(const string &command) const
{
    cout << "Unrecognized command '" << command << "'." << endl;
    list_valid_commands();
}

void CLI::list_valid_commands() const
{
    cout << "The following commands are supported:" << endl;

    for (const string &command : validCommands)
    {
        cout << command << endl;
    }
}

string CLI::prompt(const string &message) const
{
    cout << message << flush;
    string input;
    // Using std::ws to discard whitespace.
    getline(cin >> ws, input);
    return input;
}
