# Custom Shell Implementation

## Overview

This project implements a custom shell with various functionalities such as command execution, directory navigation, process management, and more. The shell supports a variety of commands, including user-defined commands and standard system commands.

## Specifications

### Specification 1: Display Requirement

The shell prompt displays the username, system name, and current directory path. The format is: <Username@SystemName:~>


### Specification 2: Input Requirements

- Supports `;` and `&` separated list of commands.
- Handles random spaces and tabs in input.
- Commands separated by `;` are executed sequentially.
- Commands followed by `&` are executed in the background, printing the process ID.

### Specification 3: `warp` Command

- Changes the current working directory and prints the new path.
- Supports `.` (current directory), `..` (parent directory), `~` (home directory), and `-` (previous directory) symbols.
- Executes multiple arguments sequentially.
- Example:
` <JohnDoe@SYS:~> warp test
/home/johndoe/test `

### Specification 4: `peek` Command

- Lists files and directories in lexicographic order.
- Supports `-a` (all files, including hidden) and `-l` (detailed information) flags.
- Color-codes output: green for executables, white for files, blue for directories.


### Specification 5: `pastevents` Command

- Stores the 15 most recent command statements.
- `pastevents purge` clears all stored events.
- `pastevents execute <index>` executes the command at the specified index.


### Specification 6: System Commands

- Executes standard system commands in foreground or background.
- Prints the process name and duration if a foreground process takes more than 2 seconds.


### Specification 7: `proclore` Command

- Prints process information such as PID, status, process group, virtual memory, and executable path.


### Specification 8: `seek` Command

- Searches for files or directories in the specified directory.
- Supports `-d` (directories only), `-f` (files only), and `-e` (print or change directory if only one match found) flags.


### Specification 9: I/O Redirection

- Supports `>`, `>>`, and `<` for output and input redirection.
- Displays error if input file not found.


### Specification 10: Pipes

- Supports piping between commands.


### Specification 11: Redirection with Pipes

- Supports combining I/O redirection and pipes.

  
### Specification 13: Signals

- `ping <pid> <signal_number>` sends signals to processes.
- Handles Ctrl-C, Ctrl-D, and Ctrl-Z for signal management.


### Specification 14: `fg` and `bg` Commands

- `fg <pid>` brings a background process to foreground.
- `bg <pid>` changes a stopped background process to running.

  
### Specification 15: `neonate` Command

- Prints the PID of the most recently created process every specified seconds until 'x' is pressed.


### Specification 16: `iMan` Command

- Fetches man pages from the internet using sockets.


## Assumptions and Limitations

- The shell does not handle background execution for user-defined commands (`warp`, `peek`, `pastevents`).
- File and directory names do not contain whitespace characters.
- Multiple inputs and outputs for I/O redirection are not handled.

## Compilation and Execution

Compile the shell program using the provided `Makefile`:

  


