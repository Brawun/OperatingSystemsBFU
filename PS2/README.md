# My Simple Shell

SimpleShell is a simple, interactive shell program written in C++. It allows users to enter basic commands, which are then executed as separate processes. The shell provides basic functionality, such as command parsing and execution, through a continuous loop that reads user input, interprets the command, and displays results. This shell program is intentionally minimal, making it a starting point for learning shell basics and process management in C++.

## Features

- **Command Parsing**: User inputs are tokenized into commands and arguments, allowing a variety of commands with arguments.
- **Command Execution**: Each command runs in a child process, created using `fork()` and executed with `execvp()`.
- **Looping Prompt**: The shell continuously prompts users for commands until they signal EOF (e.g., `Ctrl+D`).
- **Basic Error Handling**: Provides feedback for failed executions or invalid commands.

## Program Structure

- **SimpleShell.h**: Defines the `SimpleShell` class, including methods for running the shell loop, parsing input, and executing commands.
- **SimpleShell.cpp**: Implements the `SimpleShell` class, containing the core functionality of the shell.
- **Makefile**: A Makefile for compiling, running, and cleaning up the program.

## File Descriptions

- `SimpleShell.h`: Header file containing the declarations of the shell methods and class structure.
- `SimpleShell.cpp`: Source file with the full implementation of the shell’s features, including command parsing and execution.
- `Makefile`: Used to compile, run, and clean the program with simple commands.

## How to Build and Run the Program

### Prerequisites

- **C++ Compiler**: Ensure you have a C++11-compatible compiler installed (e.g., `g++`).
- **Make**: Make should be installed to use the Makefile commands.

### Compilation and Execution

Open a terminal in the project directory and use the following commands:

```bash
make           # Compiles and runs the program
make compile   # Only compiles the program and creates an executable in bin/
make run       # Executes the compiled program
make clean     # Cleans up object files and the executable in bin/
```

### Using SimpleShell

1. Run the shell using `make` or `make run`.
2. When the prompt `SimpleShell % ` appears, type any standard command (e.g., `ls`, `pwd`, `echo Hello`).
3. Press **Enter** to execute the command.
4. To exit the shell, type **Ctrl+D** or terminate the process.

### Example Session

```shell
SimpleShell % ls
file1.cpp  file2.cpp  SimpleShell.cpp  bin

SimpleShell % echo "Hello, SimpleShell!"
Hello, SimpleShell!

SimpleShell % pwd
/home/user/Simpleshell

SimpleShell % invalidcommand
Execution failed: No such file or directory

SimpleShell % Ctrl+D
```

## Code Overview

- **Shell Loop** (`run()`): The main loop displays the prompt, reads user input, parses it, and executes the command.
- **Command Parsing** (`parse()`): Splits the input string by spaces to form a command and argument list.
- **Command Execution** (`execute()`): Uses `fork()` to create a new process and `execvp()` to run the command in the child process. If the command fails, an error message is displayed.

## Future Extensions

SimpleShell is designed as a minimalistic shell, ideal for adding more advanced features, such as:
- **Pipe Handling**: Allowing commands to be chained (e.g., `ls | grep file`).
- **Input/Output Redirection**: Enabling input and output redirection with `>`, `<`, and `>>`.
- **Signal Handling**: Implementing custom handling for signals (e.g., `Ctrl+C` to terminate commands).
- **Environment Variables**: Supporting access and modification of environment variables.

## Troubleshooting

- **"Execution failed" Error**: If a command cannot be found, ensure it’s installed and accessible in your system’s `PATH`.
- **Compilation Errors**: Ensure your environment supports C++11 or later and that `make` is installed.

## Author

Brandon Figueroa Ugalde - ID# 660282688
