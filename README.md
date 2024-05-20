1. Introduction
This report covers the basic elements of an operating system written in C language, focusing on process management and memory allocation. The code defines several constants for system configuration and a structure for process representation.

2. Definitions and Structures
The first part of the code includes #define directives and a struct definition. These are crucial for setting system parameters and organizing process information.

2.1 Definitions
The #define directives are used to create constants that will be used throughout the program. This improves readability and maintainability by replacing magic numbers with meaningful names.
•	MAX_PROCESSES: The maximum number of processes that the operating system can handle concurrently.
•	MAX_RAM: The total RAM available in the system, specified in megabytes.
•	CPU_1 and CPU_2: The memory allocated to each CPU, indicating a simple dual-CPU system where each CPU has a dedicated portion of RAM.
•	HIGH_PRIORITY_QUEUE, MEDIUM_PRIORITY_QUEUE, and LOW_PRIORITY_QUEUE: Constants representing different priority levels for process scheduling.
•	RR_QUANTUM_MEDIUM and RR_QUANTUM_LOW: Time quanta for the Round Robin scheduling algorithm, used for medium and low priority processes respectively.

2.2 Process Structure
The struct Process defines the structure of a process, encapsulating all necessary attributes for process management.
•	process_number: A unique identifier for the process.
•	arrival_time: The time at which the process arrives in the system.
•	priority: The priority level of the process (e.g., high, medium, low).
•	burst_time: The total time required by the process to complete execution.
•	ram_required: The amount of RAM needed by the process.
•	cpu_rate: The rate at which the CPU processes the task, possibly indicating the CPU time allocated.

3. Input Parsing Function
This section of the code is responsible for reading process data from an input file and storing it into an array of Process structures. This function is crucial for initializing the process management system with the necessary data.
3.1 Function Definition
The parse_input_file function reads an input file containing process data and populates an array of Process structures. This function is essential for initializing the system with process information.
Parameters:
•	filename: A string representing the name of the input file containing process data.
•	processes[]: An array of Process structures where the parsed data will be stored.
Return Value:
•	The function returns the number of processes successfully parsed from the input file.
Steps:
1.	File Opening: The function attempts to open the specified input file in read mode. If the file cannot be opened, an error message is printed, and the function returns 0.
2.	Reading and Parsing: The function reads the file line by line using fgets. Each line is expected to contain process data in a comma-separated format. The strtok function is used to split each line into tokens based on commas. The atoi function converts these tokens to integers, which are then assigned to the corresponding fields of the Process structure.
3.	File Closing: After all lines have been read and parsed, the input file is closed.
4.	Return Number of Processes: The function returns the total number of processes parsed from the input file.
Conclusion
The parse_input_file function is a critical component of the operating system, enabling it to initialize its process management system with data read from an input file. This function reads and parses process data, stores it in an array of Process structures, and handles file operations efficiently.

4. Resource Check Function
This section of the code is responsible for checking if there are sufficient resources available for a given process. The function evaluates if the required RAM for a process can be allocated based on the process's priority.
4.1 Function Definition
The resource_check function determines if the system has enough resources to run a specific process. It assesses the RAM requirements and checks against the available memory for the assigned CPU.
Parameters:
•	process: A Process structure representing the process for which the resource check is being performed.
Return Value:
•	The function returns 1 if sufficient resources are available.
•	The function returns 0 if insufficient resources are available, and it prints an error message.
Steps:
1.	Determine CPU Allocation: The function assigns a CPU to the process based on its priority. If the process has a high priority (priority == 0), it is allocated to CPU_1. Otherwise, it is allocated to CPU_2.
2.	Resource Evaluation: The function compares the required RAM (ram_required) of the process with the available memory of the assigned CPU (CPU). If the required RAM is less than or equal to the available memory, the function returns 1, indicating that sufficient resources are available.
3.	Insufficient Resources Handling: If the required RAM exceeds the available memory, the function prints an error message specifying the process number and returns 0, indicating that insufficient resources are available.
4.2 Function Explanation
The resource_check function ensures that each process can only proceed if the necessary resources are available. This function helps in efficient resource management by preventing processes from starting when the required memory is not available, thus avoiding potential system crashes or performance issues.
Conclusion
The resource_check function is a critical component of the operating system's resource management system. By determining whether a process can be allocated the required memory based on its priority and the available CPU memory, the function helps maintain system stability and efficiency. The function's logic ensures that processes with insufficient resources are identified early, allowing for appropriate handling and scheduling.

5. FCFS Sorting Function
The following code snippet represents a function FCFS_sort_processes that performs sorting based on the First-Come, First-Served (FCFS) scheduling algorithm. This algorithm sorts processes based on their arrival times in ascending order.
5.1 Function Definition
The FCFS_sort_processes function sorts an array of Process structures using the First-Come, First-Served (FCFS) scheduling algorithm.
Parameters:
•	processes[]: An array of Process structures to be sorted.
•	num_processes: The number of processes in the array.
Return Value:
•	The function does not return a value (void).
Steps:
1.	Variable Initialization: Initialize variables i, j, and key of type struct Process.
2.	Sorting Algorithm (FCFS):
o	Iterate over the processes starting from the second process (i = 1).
o	Assign the current process to key.
o	Initialize j to the index before i.
o	Compare the arrival times of key and the process at index j. If the arrival time of the process at index j is greater than the arrival time of key, move the process at index j one position to the right (processes[j + 1] = processes[j]).
o	Decrement j until the correct position for key is found.
o	Insert key into its correct position in the sorted array.
5.2 Function Explanation
The FCFS_sort_processes function implements the First-Come, First-Served (FCFS) scheduling algorithm for sorting processes based on their arrival times. This algorithm prioritizes processes based on their arrival order, ensuring that the process that arrives first gets executed first.
Conclusion
The FCFS_sort_processes function plays a crucial role in scheduling processes based on the FCFS algorithm. By arranging processes in ascending order of their arrival times, the function ensures fairness in process execution, where the earliest arriving process is given priority. This function is essential for maintaining system stability and optimizing resource utilization in an operating system environment.


6. CPU Assignment Function using FCFS Algorithm
The following code snippet represents a function assign_to_cpu1 that assigns processes to CPU-1 based on the First-Come, First-Served (FCFS) algorithm. This function checks the priority of the process and assigns it to CPU-1 if its priority is high.
6.1 Function Definition
The assign_to_cpu1 function assigns a process to CPU-1 based on its priority using the First-Come, First-Served (FCFS) algorithm.
Parameters:
•	process: A Process structure representing the process to be assigned.
•	output_file: A pointer to the output file where the assignment information will be written.
Return Value:
•	The function does not return a value (void).

Steps:
1.	Priority Check: Check if the priority of the process is high (priority value of 0).
2.	Assignment to CPU-1: If the priority is high, write a message to the output file indicating that the process is assigned to CPU-1.
6.2 Function Explanation
The assign_to_cpu1 function is responsible for assigning processes to CPU-1 based on their priority. In this case, only processes with a high priority (priority value of 0) are assigned to CPU-1. This function is part of the scheduling logic that ensures high-priority processes are executed on specific CPUs.
Conclusion
The assign_to_cpu1 function contributes to the CPU assignment process in the operating system. By implementing the FCFS algorithm and considering process priorities, this function helps in distributing processes efficiently across different CPUs, optimizing resource utilization and system performance.


7. Burst Time Sorting Function (Shortest Job First - SJF)
The following code snippet represents a function burst_sort_processes that sorts processes based on their burst times using the Shortest Job First (SJF) scheduling algorithm.
7.1 Function Definition
The burst_sort_processes function sorts an array of Process structures based on their burst times using the Shortest Job First (SJF) scheduling algorithm.
Parameters:
•	processes[]: An array of Process structures to be sorted based on burst times.
•	num_processes: The number of processes in the array.
Return Value:
•	The function does not return a value (void).
Steps:
1.	Nested Loop for Sorting:
o	Use two nested loops for comparison and swapping.
o	Outer loop (i): Iterate over each process in the array, except the last one.
o	Inner loop (j): Iterate over the remaining unsorted processes in the array.
2.	Comparison and Swapping:
o	Compare the burst times of adjacent processes (processes[j] and processes[j + 1]).
o	If the burst time of the current process (processes[j]) is greater than the burst time of the next process (processes[j + 1]), swap their positions in the array.
7.2 Function Explanation
The burst_sort_processes function implements the Shortest Job First (SJF) scheduling algorithm for sorting processes based on their burst times. This algorithm prioritizes processes with shorter burst times, ensuring that shorter tasks are executed before longer ones, thus optimizing overall system performance.
Conclusion
The burst_sort_processes function plays a crucial role in scheduling processes based on the Shortest Job First (SJF) algorithm. By sorting processes in ascending order of their burst times, the function ensures that shorter tasks are given priority, leading to reduced waiting times and improved system responsiveness. This function contributes to efficient resource utilization and enhanced overall system performance in an operating system environment.

8. CPU Assignment Function using Specific Scheduling Algorithms
The following code snippet represents a function assign_to_cpu2 that assigns processes to CPU-2 based on specific scheduling algorithms. In this case, processes with priority values 1, 2, or 3 are assigned to CPU-2.
8.1 Function Definition
The assign_to_cpu2 function assigns a process to CPU-2 based on specific scheduling algorithms and priority values.
Parameters:
•	process: A Process structure representing the process to be assigned.
•	output_file: A pointer to the output file where the assignment information will be written.
Return Value:
•	The function does not return a value (void).

Steps:
1.	Priority Check: Check if the priority of the process is 1, 2, or 3.
     2.  Assignment to CPU-2: If the priority matches the specified values, write            a message to the output file indicating that the process is assigned to CPU-2.
8.2 Function Explanation
The assign_to_cpu2 function is designed to handle specific scheduling requirements where processes with priority values 1, 2, or 3 are assigned to CPU-2. This function allows for custom scheduling strategies based on process priorities.
Conclusion
The assign_to_cpu2 function provides flexibility in CPU assignment by allowing processes with specific priority values to be directed to CPU-2. By implementing specific scheduling algorithms, this function supports customized resource allocation strategies in the operating system, contributing to optimized performance and resource utilization.


9. Round Robin Scheduling Function
The round_robin function performs Round Robin scheduling on a queue of processes. It executes each process for a defined quantum time and then queues them again if they are not completed.
Parameters:
•	queue[]: An array of Process structures representing the process queue.
•	count: The number of processes in the queue.
•	output_file: A pointer to the output file where scheduling information will be written.
•	quantum_time: The time quantum for Round Robin scheduling.
Return Value:
•	The function returns the new count of processes after scheduling.
Steps:
1.	Initialization:
o	Create an array RR of Process structures for the Round Robin queue.
o	Initialize arrays done[] and remaining_time[] to keep track of completed processes and their remaining burst times respectively.
2.	Looping through Processes:
o	Iterate over each process in the queue.
o	Adjust the time_elapsed based on process arrival times to handle scheduling properly.
3.	Assigning Processes to CPU-2:
o	Call the assign_to_cpu2 function to assign the current process to CPU-2.
4.	Handling Quantum Time:
o	If the remaining time for the current process is greater than the quantum time:
	Update time_elapsed and reduce remaining_time by the quantum time.
	Re-queue the process if it's not completed and print a message to the output file.
	Increment the process count to handle re-queued processes.
o	If the remaining time is less than or equal to the quantum time:
	Update time_elapsed, set remaining time to 0, and print a completion message to the output file.
5.	Updating Queue and Return:
o	Update the main queue with the Round Robin queue after processing.
o	Return the new count of processes after Round Robin scheduling.

Conclusion
The round_robin function implements the Round Robin scheduling algorithm for processing a queue of processes. It handles time quantums, CPU assignments, process completion, and re-queuing based on remaining burst times, ensuring fair and efficient process execution in an operating system environment.

10. Main Function Overview
The main function orchestrates the entire process scheduling and resource allocation logic. It reads input from a file, sorts processes, performs resource checks, assigns processes to CPUs based on their priority, and executes scheduling algorithms like First-Come, First-Served (FCFS), Shortest Job First (SJF), and Round Robin (RR).
Key Steps:
1.	Argument Check:
o	Checks if the correct number of command-line arguments is provided.
o	If not, prints usage instructions and exits with an error code.
2.	File Reading and Parsing:
o	Reads process information from the input file using parse_input_file function.
o	Handles errors if parsing fails.
3.	Output File Initialization:
o	Opens an output file for writing scheduling and execution information.
o	Handles errors if file creation fails.
4.	Process Queue Initialization:
o	Initializes separate queues (que0, que1, que2, que3) for processes based on their priorities.
o	Initializes counters (count0, count1, count2, count3) for each queue.
5.	Sorting and Resource Check:
o	Sorts processes using FCFS scheduling algorithm (FCFS_sort_processes).
o	Performs resource check for each process using resource_check function.
o	Queues processes to respective CPU queues based on their priorities and prints queueing information to the output file.
6.	CPU Assignment and Execution:
o	Assigns processes from que0 to CPU-1 using assign_to_cpu1 function.
o	Executes SJF scheduling for que1 using burst_sort_processes function.
o	Executes Round Robin scheduling for que2 and que3 using round_robin function with specific quantum times (RR_QUANTUM_MEDIUM and RR_QUANTUM_LOW).
7.	Output and Printing:
o	Prints the contents of each CPU queue to the console for visualization.
8.	File Closing and Program Exit:
o	Closes the output file.
o	Returns 0 to indicate successful execution.
Conclusion
The main function serves as the central controller for the scheduling and execution of processes in the operating system simulation. It ensures proper organization, resource allocation, scheduling algorithm execution, and output generation, contributing to a simulated environment that reflects real-world operating system behavior.














