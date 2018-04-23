# Simple Forking and Multi-Threading

Processes uses forks to create threads that pipe into each other. <br />
Processes's purpose is to mimic the command "ps -A | grep <arg> | wc -l". <br />
<br />
Shell uses the exec and join command to launch multiple threads and wait for them to finish executing. <br />
Shell's purpose is to mimic a UNIX shell. <br />
 <br />
Languages: C++ for processes, Java for Shell. <br />
Written classes: process, Shell. <br />
Uses operating system simulator provided by the course. <br />
Outputs available.