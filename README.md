# Simple Shell
A basic UNIX command line interpreter that replicates the functionality of the original Unix shell.

## Features
* Display a prompt and wait for user input
* Execute commands and handle errors
* Support for command-line arguments and handling the PATH
* Built-in commands like `exit` and `env`

## Why These Technologies?
### C Language
Chosen for its low-level capabilities and direct interaction with system calls, making it ideal for developing operating system-level programs like a shell.

### UNIX System Calls
Used to manage processes, handle files, and interact with the environment, ensuring the shell operates efficiently and in line with Unix standards.

### GCC Compiler
Ensures the shell is compiled with strict standards, maintaining code quality and compatibility with Unix-based systems.

## Challenges
### Memory Management
Avoiding memory leaks was critical, requiring careful allocation and deallocation of resources.

### Process Handling
Implementing correct behavior for process creation and management using `fork`, `execve`, and `wait` was challenging but essential for shell functionality.

### Error Handling
Ensuring that the shell gracefully handles errors, such as command not found or invalid syntax, required meticulous attention to detail.

## Learning Objectives
By the end of this project, I will be able to:

1. Explain the origins and key figures in Unix history, such as Ken Thompson and the development of the UNIX shell and the C programming language.
2. Understand how a shell works, including concepts like process IDs (pid/ppid) and the use of system calls.
3. Manipulate the environment of the current process and understand the distinction between functions and system calls.
4. Create and manage processes using C, and implement core shell features like command execution using the `execve` system call.

## Requirements
### Editors
* vi
* vim
* emacs

### Compilation
`gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh`

### Style
* Betty style compliance
* No memory leaks
* A maximum of 5 functions per file
