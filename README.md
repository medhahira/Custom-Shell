# Custom-Shell
Creating a Basic Unix/Linux Shell using Processes and Threads

~This assignment was done as a part of the Operating Systems Course (CSE231) at IIITD.

Created a shell using standard C libraries. Including Linux system calls such as fork(),exec() family system calls and wait() family of system calls.
Designed a simple shell that can handle three, internal commands – ‘cd’, ‘echo’ and ‘pwd’. These commands would be handled directly by the shell. Furtherm the shell can also handle five external commands – ‘ls’, ‘cat’, ‘date’, ‘rm’ and ‘mkdir’. 
For the external commands, I wrote individual programs to handle these. The shell typically creates a new process, using the fork() system ‘call and within each process I have used the execl() family system call to run the individual program. The parent program also waits for the child program to terminate using the wait() family of system calls.
I have alse achieved the above functionality of the shell using pthread create() (instead of fork()) and system() (instead of execl() family of functions).
The thread based execution would be performed if the command is followed by the characters, “&t”.
