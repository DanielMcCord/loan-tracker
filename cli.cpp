#include "cli.h"

using namespace std;

// If I was on clang-format 11, I'd probably use the BeforeLambdaBody rule.
// Empty comments are to help clang-format do what I meant it to,
// without having to turn it off or on.
const map<string, function<void(CLI *)>> CLI::validCommands = {
    {
        // All of the lambdas below use self as a pointer to a CLI object.
        "create item",
        [](CLI *self) // Interactively adds an item to the database.
        {
            string itemName = "";
            while (true)
            {
                itemName = self->prompt("Please enter a name for the new item.\n > ");

                if (itemName == "")
                {
                    cout << "Item name cannot be empty." << endl;
                }
                else if (!self->db->items.findByName(itemName).isEmpty())
                {
                    cout << "An item with that name already exists. Choose a different name."
                         << endl;
                }
                else
                {
                    break;
                }
            }

            string itemDescription;
            while (true)
            {
                itemDescription = self->prompt("Enter a description.\n > ");

                if (itemDescription != "")
                {
                    break;
                }
                else
                {
                    cout << "Please add a one-line description of the item.\n";
                }
            }

            Item toAdd(itemName, itemDescription);
            bool added = self->db->items.add(toAdd);
            self->unsavedChanges = self->unsavedChanges || added;
        } // end of "create item"
    },
    {
        "create loan",
        [](CLI *self) // Interactively adds a loan to the database.
        {
            if (self->db->items.records.empty())
            {
            }
            else
            {
                string borrowerName = "";

                while (true)
                {
                    borrowerName = self->prompt("Please enter the name of the borrower.\n > ");
                    if (borrowerName != "")
                    {
                        break;
                    }
                    else
                    {
                        cout << "Borrower name cannot be empty.\n";
                    }
                }

                Item::key_t itemID = 0;

                while (true)
                {
                    string itemName = self->prompt("What is being lent to them?\n > ");
                    Item toLoan = self->db->items.findByName(itemName);

                    // Make sure the item actually exists.
                    if (!toLoan.isEmpty())
                    {
                        itemID = toLoan.primaryKey;
                        break;
                    }
                    else
                    {
                        cout << "Item not found. Please choose one of the following:" << endl;
                        CLI::validCommands.at("list items");
                    }
                }

                Loan toAdd(itemID, borrowerName);
                bool added = self->db->loans.add(toAdd);
                self->unsavedChanges = self->unsavedChanges || added;
            }
        } // end of "create loan"
    },
    {
        "list items",
        [](CLI *self) // Shows a list of all the items.
        {
            cout << self->db->items.toString() << endl; //
        } // end of "list items"
    },
    {
        "list loans",
        [](CLI *self) // Shows a list of all the loans.
        {
            cout << self->db->loans.toString() << endl; //
        } // end of "list loans"
    },
    {
        "delete item",
        [](CLI *self) // Interactively deletes an item from the database.
        {
            // Prompt user for item to delete.
            string toDelete = "";
            size_t itemID = 0;

            // This loop goes until the item to delete is a valid one.
            while (true)
            {
                toDelete = self->prompt("Choose an item to delete.\n > ");
                // Check that the item exists.
                size_t itemFound = 0;

                // Need the ID for later.
                itemID = 0;

                for (const auto &itemRecord : self->db->items.records)
                {
                    ++itemFound;
                }

                if (itemFound < 1)
                {
                    cout << "There is no item with that name to delete." << endl;
                    continue;
                }

                // Make sure no one is using it.
                size_t inUse = 0;

                for (const auto &loanRecord : self->db->loans.records)
                {
                    if (loanRecord.second.itemID == itemID)
                    {
                        ++inUse;
                    }
                }

                if (inUse)
                {
                    cout << "Can't delete: would orphan " << inUse << " loan records." << endl;
                    continue;
                }

                // We can delete it.
                break;
            }

            DBTable<Item>::size_type removed = (self->db->items.remove(itemID));

            // Tell the user what happened.
            switch (removed)
            {
            case 0:
                cout << "Failed to delete '" << toDelete << "' for an unknown reason." << endl;
                break;
            case 1:
                cout << "Deletion completed successfuly." << endl;
                break;
            default:
                // The most likely reason for this would be if a multimap was used.
                cout << "Unknown error. Hic sunt dracones." << endl;
                break;
            }

            self->unsavedChanges = self->unsavedChanges || removed != 0;
        } // end of "delete item"
    },
    {
        "delete loan",
        [](CLI *self) // Interactively deletes a loan from the database.
        {
            Loan::key_t toDelete = 0;
            std::istringstream input("");

            while (true)
            {
                std::istringstream input(self->prompt("Enter the ID of the loan to delete.\n > "));
                input >> toDelete;
                if (input.fail())
                {
                    cout << "Failed to get valid number from input. Try again." << endl;
                }
                else
                {
                    // Make sure the number is valid.
                    if (toDelete < 0)
                    {
                        cout << "Number must be positive." << endl;
                    }
                    else if (self->db->loans.records.count(toDelete) < 1)
                    {
                        cout << "Loan ID not found." << endl;
                    }
                    else
                    {
                        break;
                    }
                }
            }

            // Give the user a chance to change their mind.
            cout << "You are about to delete the following loan:" << endl;
            cout << "(Loan ID / Item ID / Borrower)" << endl;
            cout << self->db->loans.at(toDelete).toString() << endl;
            cout << "Are you sure you wish to proceed? (y/N)";
            string confirmationAnswer = self->prompt();

            if (confirmationAnswer.at(0) == 'y' || confirmationAnswer.at(0) == 'Y')
            {
                DBTable<Loan>::size_type removed(self->db->loans.remove(toDelete));
                cout << (removed > 0 ? "Loan deleted." : "Delete failed.") << endl;

                self->unsavedChanges = self->unsavedChanges || removed != 0;
            }
        } // end of "delete loan"
    },
    {
        "save",
        [](CLI *self) // Save changes to a file.
        {
            bool saved = false;
            self->unsavedChanges = self->unsavedChanges && !saved;
        } // end of "save"
    },
    {
        "exit",
        [](CLI *self) // Exit the application.
        {
            self->onExit(); //
        } // end of "exit"
    },
    {
        "help",
        [](CLI *self) // Display help information.
        {
            self->list_valid_commands(); //
        } // end of "help"
    } //
};

CLI::CLI(LoanSchema *db) : unsavedChanges(false)
{
    this->db = db;
}

void CLI::welcome() const
{
    cout << "LoanIt - an item lending tracker." << endl;
    cout << "For help, type 'help' (without quotes) and press enter." << endl;
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
    if (unsavedChanges)
    {
        unsigned char shouldSave = prompt("\nSave changes? (y/N)\n > ").at(0);

        if (shouldSave == 'y' || shouldSave == 'Y')
        {
        }
    }
    else
    {
    }
}

void CLI::save()
{

}

void CLI::load()
{

}
