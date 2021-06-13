#ifndef CLI_H
#define CLI_H

#include "filehandler.h"
#include "loanschema.h"
#include <filesystem>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

class CLI
{
  public:
    CLI(LoanSchema *db = nullptr);

    void welcome() const;
    /**
     * @brief Displays a message when an invalid command is used.
     * @param command The command that was used.
     */

    bool attempt_command(const std::string &command);
    void on_invalid_command(const std::string &command) const;
    void list_valid_commands() const;
    void commandHint();
    std::string prompt(const std::string &message = "") const;
    void onExit(const std::filesystem::path defaultSavePath = std::filesystem::path());
    LoanSchema *db;
    bool unsavedChanges;

  private:
    /**
     * A table of all the commands the user may issue.
     */
    static const std::map<std::string, std::function<void(CLI *)>> validCommands;
};

#endif // CLI_H
