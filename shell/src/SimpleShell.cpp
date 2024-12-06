#include "SimpleShell.h"
#include <fcntl.h>

using namespace std;

/**
 * @brief Executes a command or pipeline using fork and execvp.
 * 
 * This function handles both single commands and pipelines of commands connected with '|'.
 * Each command in a pipeline runs in a separate child process, and pipes are used to
 * redirect the output of one command to the input of the next.
 * 
 * @param commands A vector of vectors, where each inner vector contains a command and its arguments.
 */
void SimpleShell::execute(const vector<vector<string>>& commands)
{
    int numCommands = commands.size();
    int pipefds[2 * (numCommands - 1)];
    pid_t pids[numCommands];

    // Create necessary pipes
    for (int i = 0; i < numCommands - 1; ++i) {
        if (pipe(pipefds + i * 2) == -1) {
            perror("pipe failed");
            exit(1);
        }
    }

    // Iterate over each command to execute it
    for (int i = 0; i < numCommands; ++i) {
        pids[i] = fork();

        if (pids[i] == -1) {
            perror("fork failed");
            exit(1);
        } else if (pids[i] == 0) { // Child process
            // Redirect input from previous pipe, if applicable
            if (i > 0) {
                dup2(pipefds[(i - 1) * 2], STDIN_FILENO);
            }

            // Redirect output to next pipe, if applicable
            if (i < numCommands - 1) {
                dup2(pipefds[i * 2 + 1], STDOUT_FILENO);
            }

            // Close all pipe file descriptors in the child process
            for (int j = 0; j < 2 * (numCommands - 1); ++j) {
                close(pipefds[j]);
            }

            // Prepare arguments for execvp
            vector<const char*> args;
            for (const auto& arg : commands[i]) {
                args.push_back(arg.c_str());
            }
            args.push_back(nullptr);

            // Execute the command
            if (execvp(args[0], const_cast<char* const*>(args.data())) == -1) {
                perror("Execution failed");
                _exit(1);
            }
        }
    }

    // Close all pipe file descriptors in the parent process
    for (int i = 0; i < 2 * (numCommands - 1); ++i) {
        close(pipefds[i]);
    }

    // Wait for all child processes to complete
    for (int i = 0; i < numCommands; ++i) {
        int status;
        waitpid(pids[i], &status, 0);
    }
}

/**
 * @brief Parses a line of input into tokens based on a delimiter.
 * 
 * This function takes a string and splits it into tokens, storing each token
 * into a vector. The delimiter is used to identify where the string should be split.
 * 
 * @param line The input string to be tokenized.
 * @param tokens A reference to a vector that will hold the parsed tokens.
 * @param delimiter The delimiter used to split the input string.
 */
void SimpleShell::parse(const string& line, vector<string>& tokens, const string& delimiter)
{
    size_t start = 0;
    size_t end = 0;

    while ((end = line.find(delimiter, start)) != string::npos) {
        if (end != start) { // Ignore empty tokens
            tokens.push_back(line.substr(start, end - start));
        }
        start = end + delimiter.length();
    }

    if (start < line.length()) { // Add the last token
        tokens.push_back(line.substr(start));
    }
}

/**
 * @brief Starts the shell loop.
 * 
 * This method runs the shell's main loop, taking user input, parsing it, and executing commands.
 */
void SimpleShell::run()
{
    while (true) {
        string line;

        // Print the prompt
        cout << "SimpleShell % ";

        // Get input from the keyboard
        if (!getline(cin, line)) {
            break; // Exit the shell if input fails (e.g., EOF)
        }

        // Split the input into individual commands (if pipe '|' is present)
        vector<string> commandStrings;
        parse(line, commandStrings, "|");

        // Split each command into its arguments
        vector<vector<string>> commands;
        for (const auto& commandString : commandStrings) {
            vector<string> tokens;
            parse(commandString, tokens, " ");
            if (!tokens.empty()) {
                commands.push_back(tokens);
            }
        }

        if (commands.empty()) {
            continue; // Skip empty input
        }

        // Execute the commands, handling piping if necessary
        execute(commands);
    }
}

int main()
{
    SimpleShell shell;
    shell.run(); // Start the shell loop
    return 0;
}
