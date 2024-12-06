Test Report: My Simple Shell
===========================

**System Under Test**: SimpleShell - a basic interactive shell written in C++ that provides command parsing, command execution, input/output redirection, and pipe handling.

## Test Environment

- **OS**: Linux Mint 21.3
- **C++ Compiler**: g++ 9.3.0
- **Hardware**: x86_64 architecture, 8GB RAM

## Test Plan
The test plan was divided into the following sections to verify the functionality and robustness of SimpleShell:

1. **Basic Command Execution**
2. **Input/Output Redirection**
3. **Pipe Handling**
4. **Error Handling**
5. **Exit Condition**

### Test Cases and Results

#### 1. Basic Command Execution

- **Test Case 1**: Run `ls` command.
  - **Expected Result**: List of files in the current directory.
  - **Actual Result**: Success. Files were listed as expected.
  - **Status**: Pass

- **Test Case 2**: Run `echo Hello, SimpleShell!`.
  - **Expected Result**: Output displays "Hello, SimpleShell!"
  - **Actual Result**: Success. The output was correct.
  - **Status**: Pass

- **Test Case 3**: Run `pwd` command.
  - **Expected Result**: Path of the current directory is displayed.
  - **Actual Result**: Success. Path was displayed correctly.
  - **Status**: Pass

#### 2. Input/Output Redirection

- **Test Case 4**: Run `cat < input.txt` where `input.txt` contains sample text.
  - **Expected Result**: Contents of `input.txt` displayed on the screen.
  - **Actual Result**: Success. File contents were displayed.
  - **Status**: Pass

- **Test Case 5**: Run `echo Test > output.txt`.
  - **Expected Result**: A file `output.txt` is created containing the text "Test".
  - **Actual Result**: Success. File was created with correct content.
  - **Status**: Pass

#### 3. Pipe Handling

- **Test Case 6**: Run `cat input.txt | grep pattern` where `input.txt` contains multiple lines and "pattern" is a valid substring in the file.
  - **Expected Result**: Lines containing "pattern" are displayed.
  - **Actual Result**: Success. Correct lines were displayed.
  - **Status**: Pass

- **Test Case 7**: Run `ls | wc -l` to count the number of files in the directory.
  - **Expected Result**: A number indicating the count of files.
  - **Actual Result**: Success. Correct count displayed.
  - **Status**: Pass

#### 4. Error Handling

- **Test Case 8**: Run `invalidcommand`.
  - **Expected Result**: Error message displayed stating "Execution failed: No such file or directory".
  - **Actual Result**: Success. Error message displayed as expected.
  - **Status**: Pass

- **Test Case 9**: Run `cat < non_existent.txt`.
  - **Expected Result**: Error message displayed for missing file.
  - **Actual Result**: Success. Proper error message displayed.
  - **Status**: Pass

#### 5. Exit Condition

- **Test Case 10**: Press `Ctrl+D` at the prompt.
  - **Expected Result**: Shell exits gracefully.
  - **Actual Result**: Success. Shell terminated as expected.
  - **Status**: Pass

### Summary of Results

- **Total Test Cases**: 10
- **Passed**: 10
- **Failed**: 0

## Issues Encountered
- **None**

## Recommendations
- **Signal Handling**: Adding support for signal handling such as handling `Ctrl+C` to terminate the current running command without exiting the shell.
- **Command History**: Adding a command history feature to recall previously run commands.

## Conclusion
All the functionality specified in the README.md was tested, and all test cases passed successfully. SimpleShell performed as expected for both normal operations and error conditions.
