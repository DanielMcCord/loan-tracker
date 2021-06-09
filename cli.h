#ifndef CLI_H
#define CLI_H

#include <iostream>
#include <string>
#include <vector>

class CLI
{
  public:
    CLI();
    CLI(const std::vector<std::string> &validCommands);
    void welcome() const;
    /**
     * @brief Displays a message when an invalid command is used.
     * @param command The command that was used.
     */
    void on_invalid_command(const std::string &command) const;
    void list_valid_commands() const;
    std::string prompt(const std::string &message = "") const;
    std::vector<std::string> validCommands;
};

#endif // CLI_H
