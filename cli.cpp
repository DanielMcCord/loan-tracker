#include "cli.h"

using namespace std;

// If I was on clang-format 11, I'd probably use the BeforeLambdaBody rule.
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
            cout << (added ? "Item created." : "Failed to create item.") << endl;
            self->unsavedChanges = self->unsavedChanges || added;
        } // end of "create item"
    },
    {
        "create loan",
        [](CLI *self) // Interactively adds a loan to the database.
        {
            if (!self->db->itemsAvailable())
            {
                cout << "No items to lend - cannot create loan." << endl;
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
                        cout << "Item '" << itemName
                             << "' not found. Please choose one of the following:" << endl;

                        for (const auto &pair : self->db->items.records)
                        {
                            cout << "'" << pair.second.name << "'" << endl;
                        }
                    }
                }

                Loan toAdd(itemID, borrowerName);
                bool added = self->db->loans.add(toAdd);
                cout << (added ? "Loan created." : "Failed to create loan.") << endl;
                self->unsavedChanges = self->unsavedChanges || added;
            }
        } // end of "create loan"
    },
    {
        "list items",
        [](CLI *self) // Shows a list of all the items.
        {
            string delimStr;
            delimStr += Item().fieldDelimiter;
            string legend = "Item ID" + delimStr + "Name" + delimStr + "Description";
            cout << legend << endl;

            for (size_t i = 0; i < legend.size(); ++i)
            {
                cout << "-";
            }

            cout << endl;
            cout << self->db->items.toString() << endl;
        } // end of "list items"
    },
    {
        "list loans",
        [](CLI *self) // Shows a list of all the loans.
        {
            string delimStr;
            delimStr += Loan().fieldDelimiter;
            string legend =
                "Loan ID" + delimStr + "Item ID" + delimStr + "Borrower" + delimStr + "Created On";

            cout << legend << endl;

            for (size_t i = 0; i < legend.size(); ++i)
            {
                cout << "-";
            }

            cout << endl;
            cout << self->db->loans.toString() << endl;
        } // end of "list loans"
    },
    {
        "delete item",
        [](CLI *self) // Interactively deletes an item from the database.
        {
            /*
             * Checks if an item is involved in any loans, which would prevent its deletion.
             * This function is not needed outside this scope, which is why I made it a lambda.
             */
            auto inUse = [&](Item::key_t itemID) {
                size_t users = 0;

                for (const auto &loanRecord : self->db->loans.records)
                {
                    if (loanRecord.second.itemID == itemID)
                    {
                        ++users;
                    }
                }

                return users;
            };

            bool anyDeletableItems = false;

            for (const auto &pair : self->db->items.records)
            {
                if (!inUse(pair.first))
                {
                    anyDeletableItems = true;
                    break;
                }
            }

            if (!anyDeletableItems)
            {
                cout << "There are currently no items that can be deleted." << endl;
                return;
            }

            // Prompt user for item to delete.
            string nameofDeleteTarget = "";
            size_t itemID = 0;

            // Loop until user enters either a valid item, or nothing.
            do
            {
                cout << "Enter the name of the item to delete, or press enter without no input to "
                        "cancel."
                     << endl;

                nameofDeleteTarget = self->prompt(" > ");
                // Check that the item exists.
                Item target = self->db->items.findByName(nameofDeleteTarget);

                if (target.isEmpty())
                {
                    cout << "There is no item with that name to delete." << endl;
                    continue;
                }

                // Need the ID for later.
                itemID = target.primaryKey;

                size_t count = inUse(itemID);

                if (count > 0)
                {
                    cout << "Can't delete: would orphan " << count << " loan records." << endl;
                    continue;
                }

                // We can delete it.
                break;
            } while (nameofDeleteTarget != "");

            DBTable<Item>::size_type removed = (self->db->items.remove(itemID));

            // Tell the user what happened.
            switch (removed)
            {
            case 0:
                cout << "Failed to delete '" << nameofDeleteTarget << "' for an unknown reason."
                     << endl;

                break;
            case 1:
                cout << "Deletion completed successfuly." << endl;
                break;
            default:
                // If this happens, you were probably using a multimap with duplicate keys.
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
            istringstream input("");

            while (true)
            {
                istringstream input(self->prompt("Enter the ID of the loan to delete.\n > "));
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
            string legend = "Loan ID|Item ID|Borrower|Created On";
            cout << legend << endl << string(legend.size(), '-') << endl;
            cout << self->db->loans.records.at(toDelete).toString() << endl;
            cout << "Are you sure you wish to proceed? (y/N)" << endl;
            string confirmationAnswer = self->prompt(" > ");

            if (!confirmationAnswer.empty() &&
                (confirmationAnswer.at(0) == 'y' || confirmationAnswer.at(0) == 'Y'))
            {
                DBTable<Loan>::size_type removed(self->db->loans.remove(toDelete));
                cout << (removed > 0 ? "Loan deleted." : "Delete failed.") << endl;
                self->unsavedChanges = self->unsavedChanges || removed != 0;
            }
            else
            {
                cout << "Action cancelled." << endl;
            }
        } // end of "delete loan"
    },
    {
        "save",
        [](CLI *self) // Save changes to a file.
        {
            bool saved = false;
            self->onSave();
            self->unsavedChanges = self->unsavedChanges && !saved;
        } // end of "save"
    },
    {
        "exit",
        [](CLI *self) // Exit the application.
        {
            self->onExit();
            cout << "Exiting." << endl;
        } // end of "exit"
    },
    {
        "help",
        [](CLI *self) // Display help information.
        {
            self->commandHint();
            self->listValidCommands();
        } // end of "help"
    },
    {
        "edit item",
        [](CLI *self) // Change details of item
        {
            Item::key_t toEdit = 0;
            string input("");

            // Loop until user enters a valid item.
            while (true)
            {
                input = self->prompt("Enter name of item to edit.\n > ");

                if (input.empty())
                {
                    cout << "Name cannot be empty." << endl;
                }
                else
                {
                    Item temp = self->db->items.findByName(input);

                    if (temp.isEmpty())
                    {
                        cout << "Item not found." << endl;
                    }
                    else
                    {
                        toEdit = temp.primaryKey;
                        break;
                    }
                }
            }

            cout << "Enter a new name, or press enter to keep existing name." << endl;
            string newName = self->prompt(" > ");

            if (!newName.empty())
            {
                self->db->items.records.at(toEdit).name = newName;
                cout << "Name updated." << endl;
            }

            cout << "The current description is:" << endl
                 << self->db->items.records.at(toEdit).description << endl
                 << "Enter a new description, or press enter to keep the existing one." << endl;

            string newDescription = self->prompt(" > ");

            if (!newDescription.empty())
            {
                self->db->items.records.at(toEdit).description = newDescription;
                cout << "Description updated." << endl;
            }
        } // end of "edit item"
    } // end of lambda map
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

bool CLI::attemptCommand(const string &command)
{
    if (validCommands.count(command) == 1)
    {
        validCommands.at(command)(this);
        return true;
    }
    else
    {
        onInvalidCommand(command);
        return false;
    }
}

void CLI::onInvalidCommand(const string &command) const
{
    cout << "Unrecognized command '" << command << "'." << endl;
    listValidCommands();
}

void CLI::listValidCommands() const
{
    cout << "The following commands are available:" << endl;

    for (const auto &command : validCommands)
    {
        cout << command.first << endl;
    }
}

void CLI::commandHint()
{
    cout << "Run with `-f FILEPATH` to load data from a file." << endl;
}

string CLI::prompt(const string &message) const
{
    cout << message << flush;
    string userInput;
    getline(cin, userInput);
    return userInput;
}

void CLI::onExit(const filesystem::path defaultSavePath)
{
    onSave(defaultSavePath);
}

void CLI::onSave(const filesystem::path defaultSavePath)
{
    if (unsavedChanges)
    {
        unsigned char shouldSave = prompt("\nSave changes? (y/N)\n > ").at(0);

        if (shouldSave == 'y' || shouldSave == 'Y')
        {
            cout << "Where would you like to save the data? If you leave this blank, the file will "
                 << ((defaultSavePath == "") ? "not be saved."
                                             : "be saved to:\n" + defaultSavePath.string());

            filesystem::path inputPath = prompt("\n > ");
            // Use the default if nothing was entered.
            filesystem::path savePath = inputPath.empty() ? defaultSavePath : inputPath;

            if (!savePath.empty())
            {
                string encodedData = this->db->serialize();
                FileHandler::writeTextFile(encodedData, savePath);
                cout << "Data saved to " << savePath << endl;
            }
            else
            {
                cout << "Changes not saved." << endl;
            }
        }
    }
    else
    {
        cout << "No changes to save." << endl;
    }
}
