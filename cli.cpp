#include "cli.h"

using namespace std;

//clang-format off
// If I was on ClangFormat 11, I'd probably use the BeforeLambdaBody rule.
CLI::CLI() : validCommands({
    {
        "create item", []
        {
        }
    },
    {
        "create loan", []
        {
        }
    },
    {
        "list items", []
        {
        }
    },
    {
        "list loans", []
        {
        }
    },
    {
        "delete item", []
        {
        }
    },
    {
        "save", []
        {
        }
    },
    {
        "exit", []
        {
        }
    }
})
{
}
// clang-format on

CLI::CLI(const map<string, function<void()>> &validCommands)
{
    this->validCommands = validCommands;
}

void CLI::welcome() const
{
    cout << "LoanIt - an item lending tracker." << endl;
    cout << "For help, type 'help' (without quotes) and press enter." << endl;
    list_valid_commands();
}

bool CLI::attempt_command(const string &command)
{
    if (validCommands.count(command) == 1)
    {
        validCommands.at(command)();
        return true;
    }
    else
    {
        on_invalid_command(command);
        return false;
    }
}

void CLI::on_invalid_command(const string &command) const
{
    cout << "Unrecognized command '" << command << "'." << endl;
    list_valid_commands();
}

void CLI::list_valid_commands() const
{
    cout << "The following commands are available:" << endl;

    for (const auto &command : validCommands)
    {
        cout << command.first << endl;
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
