# Custom Shell

This repository contains the code for a basic Unix/Linux shell developed as a part of the Operating Systems Course (CSE231) at IIITD. The shell is implemented using processes and threads, utilizing standard C libraries and Linux system calls.

## Assignment Overview

The objective of this assignment was to create a custom shell capable of handling internal and external commands. The shell utilizes various Linux system calls, such as `fork()`, `exec()` family of system calls, and `wait()` family of system calls.

### Internal Commands

The shell can handle three internal commands directly:

- `cd`: Change the current working directory.
- `echo`: Display the given message.
- `pwd`: Print the current working directory.

### External Commands

The shell can handle five external commands by executing separate programs for each:

- `ls`: List files and directories in the current directory.
- `cat`: Concatenate and display the contents of files.
- `date`: Print the current date and time.
- `rm`: Remove files or directories.
- `mkdir`: Create directories.

## Shell Implementation

The shell creates a new process using the `fork()` system call. Within each process, the appropriate command is executed using the `execl()` family of system calls. The parent program waits for the child program to terminate using the `wait()` family of system calls.

Additionally, the functionality of the shell can also be achieved using threads by utilizing the `pthread_create()` function instead of `fork()`, and the `system()` function instead of the `execl()` family of functions. Thread-based execution is performed when the command is followed by the characters "&t".

## Usage

To use the custom shell:

1. Clone this repository to your local machine.
2. Compile the shell program using a C compiler.
3. Run the compiled program to start the shell.
4. Enter commands in the shell and observe the output.

## Acknowledgements

I would like to acknowledge the instructors and staff of the Operating Systems Course (CSE231) at IIITD for their guidance and support during the development of this shell. Additionally, I acknowledge the open-source community for their valuable contributions to the field of shell scripting and system programming.
