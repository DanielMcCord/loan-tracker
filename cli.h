#ifndef CLI_H
#define CLI_H

#include <functional>
#include <iostream>
#include <map>
#include <string>

class CLI
{
  public:
    CLI();
    CLI(const std::map<std::string, std::function<void()>> &validCommands);
    void welcome() const;
    /**
     * @brief Displays a message when an invalid command is used.
     * @param command The command that was used.
     */
    bool attempt_command(const std::string &command);
    void on_invalid_command(const std::string &command) const;
    void list_valid_commands() const;
    std::string prompt(const std::string &message = "") const;

  private:
    /**
     * A table of all the commands the user may issue.
     */
    std::map<std::string, std::function<void()>> validCommands;
};

#endif // CLI_H
