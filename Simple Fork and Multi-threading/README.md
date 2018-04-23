# Simple Forking and Multi-Threading

Processes uses forks to create threads that pipe into each other.
Processes's purpose is to mimic the command "ps -A | grep <arg> | wc -l".

Shell uses the exec and join command to launch multiple threads and wait for them to finish executing.
Shell's purpose is to mimic a UNIX shell.

Languages: C++ for processes, Java for Shell
Written classes: process, Shell.
Uses operating system simulator provided by the course.
Outputs available.