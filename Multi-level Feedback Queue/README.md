# Multi-level Feedback Queue
Creates a multi-level feedback queue scheduler with 3 queues. <br />
Attempts to complete processes within a certain time frame. <br />
If processes are not finished, they are moved into lower priority queues with a longer time frame. <br />
At the lowest queue, unfinished processes are rotated to the end of the queue. <br />
Within each time slice, higher priority queue is checked for any available processes. <br />
Current process is paused and higher priority queue is executed. <br />
 <br />
Languages: Java. <br />
Written classes: Scheduler. <br />
Uses operating system simulator provided by the course. <br />
Outputs available.