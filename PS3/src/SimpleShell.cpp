#include "SimpleShell.h"
#include <fcntl.h>

using namespace std;

/**
 * @brief Executes a command using fork and execv.
 * 
 * This function spawns a child process that replaces its image with the command
 * specified by the user. The parent process waits for the child process to finish.
 * 
 * @param argv A vector containing the command and its arguments to be executed.
 */
void SimpleShell::execute(const vector<string>& argv)
{
    int status;
    pid_t child;
    vector<const char*> args;
    string inputFile;
    string outputFile;
    bool redirectInput = false;
    bool redirectOutput = false;

    // Parse arguments to check for redirection
    for (size_t i = 0; i < argv.size(); ++i) {
        if (argv[i] == "<") {
            if (i + 1 < argv.size()) {
                inputFile = argv[i + 1];
                redirectInput = true;
                ++i;
            } else {
                cerr << "Error: No input file specified after '<'" << endl;
                return;
            }
        } else if (argv[i] == ">") {
            if (i + 1 < argv.size()) {
                outputFile = argv[i + 1];
                redirectOutput = true;
                ++i;
            } else {
                cerr << "Error: No output file specified after '>'" << endl;
                return;
            }
        } else {
            args.push_back(argv[i].c_str());
        }
    }
    args.push_back(nullptr);

    // Spawning a child process
    child = fork();

    // Parent process portion
    if (child > 0) {
        // Parent process waits for the child to finish
        waitpid(child, &status, 0);
    }
    // Child process portion
    else if (child == 0) {
        // Handle input redirection
        if (redirectInput) {
            int fd = open(inputFile.c_str(), O_RDONLY);
            if (fd == -1) {
                perror("Error opening input file");
                _exit(1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }

        // Handle output redirection
        if (redirectOutput) {
            int fd = open(outputFile.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1) {
                perror("Error opening output file");
                _exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }

        // Execute the command specified by the user
        if (execvp(args[0], const_cast<char* const*>(args.data())) == -1) {
            perror("Execution failed");
            _exit(1);
        }
    }
    else {
        // Handle fork failure
        perror("fork failed");
        exit(1);
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
        vector<string> tokens;

        // Print the prompt
        cout << "SimpleShell % ";

        // Get input from the keyboard
        if (!getline(cin, line)) {
            break; // Exit the shell if input fails (e.g., EOF)
        }

        // Parse the input into tokens
        parse(line, tokens, " ");

        if (tokens.empty()) {
            continue; // Skip empty input
        }

        // Execute the user command
        execute(tokens);
    }
}

int main()
{
    SimpleShell shell;
    shell.run(); // Start the shell loop
    return 0;
}
