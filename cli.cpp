#include "cli.h"
#include <cctype>

using namespace std;

// If I was on clang-format 11, I'd probably use the BeforeLambdaBody rule.
const map<string, function<void(CLI *)>> CLI::validCommands = {
    {"create item",
     [](CLI *self) {
         string itemName = "";
         while (true)
         {
             itemName = self->prompt("Please enter a name for the new item\n > ");
             if (itemName != "")
             {
                 break;
             }
             else
             {
                 cout << "Item name cannot be empty.\n";
             }
         }

         string itemDescription = self->prompt("Enter a description (optional).\n > ");
         Item toAdd(itemName, itemDescription);
         self->db->items.add(toAdd);
     }},
    {"create loan", [](CLI *self) {}},
    {"list items",
     [](CLI *self) {
         for (const auto &[key, record] : self->db->items.records)
         {
             cout << record.toString() << endl;
         }
     }},
    {"list loans", [](CLI *self) {}},
    {"delete item", [](CLI *self) {}},
    {"save", [](CLI *self) {}},
    {"exit", [](CLI *self) { self->onExit(); }},
    {"help", [](CLI *self) {}}};

CLI::CLI(LoanSchema *db)
{
    this->db = db;
}

void CLI::welcome() const
{
    cout << "LoanIt - an item lending tracker." << endl;
    cout << "For help, type 'help' (without quotes) and press enter." << endl;
    list_valid_commands();
}

void CLI::ioLoop()
{
}

bool CLI::attempt_command(const string &command)
{
    if (validCommands.count(command) == 1)
    {
        validCommands.at(command)(this);
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

void CLI::onExit()
{
    unsigned char shouldSave = prompt("\nSave changes? (y/N)\n > ").at(0);
    if (shouldSave == 'y' || shouldSave == 'Y')
    {
    }
}
