#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

/**
 * @brief A simple wrapper for text file I/O.
 */
class FileHandler
{
  public:
    /**
     * @brief Reads text from a file.
     * @return A string containing the text.
     */
    static std::string readTextFile(const std::filesystem::path &source);

    /**
     * @brief Writes a string to a text file. Overwrites the whole file by default.
     * @param content What to write to the file.
     * @param destination What file to write to.
     * @param clobber Whether to destroy existing content in the file. If false, appends.
     */
    static void writeTextFile(
        const std::string &content, const std::filesystem::path &destination, bool clobber = true);
};

#endif // FILEHANDLER_H
