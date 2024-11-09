#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/wait.h>

/**
 * @file SimpleShell.h
 * @brief Header file for the SimpleShell class.
 *
 * This header file defines the SimpleShell class, which implements a basic shell
 * that accepts commands from the user, parses them, and executes them in a new process.
 * The class supports command parsing and execution, using standard Unix functions.
 */

/**
 * @class SimpleShell
 * @brief A simple shell class that handles basic shell operations such as parsing and executing commands.
 *
 * The SimpleShell class provides a command-line interface for executing basic commands.
 * It continuously prompts the user for commands, parses the input, and executes
 * the specified command using child processes. The shell runs in an infinite loop
 * until the user signals to end the input (e.g., via EOF).
 */
class SimpleShell {
public:
    /**
     * @brief Starts the main shell loop.
     *
     * This method runs the main loop of the shell, where it continually prompts the user for input,
     * parses the input command, and attempts to execute it. The shell loop exits if the user
     * signals an end-of-file (EOF) condition.
     */
    void run();

private:
    /**
     * @brief Executes a command in a child process using fork and execvp.
     *
     * This function spawns a child process that replaces its process image with the command
     * specified by the user. The parent process waits for the child process to complete execution.
     *
     * @param argv A vector containing the command and its arguments to be executed.
     */
    void execute(const std::vector<std::string>& argv);

    /**
     * @brief Parses a line of input into tokens based on a specified delimiter.
     *
     * This function takes a string input (typically a line of user input) and splits it into tokens.
     * The tokens are stored in a vector for easy access by other functions. The delimiter (default is whitespace)
     * is used to split the input into command and arguments.
     *
     * @param line The input string to be tokenized.
     * @param tokens A reference to a vector that will store the parsed tokens.
     * @param delimiter The delimiter used to split the input string (default is whitespace).
     */
    void parse(const std::string& line, std::vector<std::string>& tokens, const std::string& delimiter = " ");
};

#endif // SIMPLE_SHELL_H
