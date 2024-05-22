
#include <stdio.h>
  #include <stdlib.h>
    #include <string.h>

      #define MAX_PROCESSES 100
      #define MAX_RAM 2048 // Maximum RAM size in MB
      #define CPU_1 512 // Memory allocated  CPU-1
      #define CPU_2 1536 // Memory allocated  CPU-2
      #define HIGH_PRIORITY_QUEUE 1
      #define MEDIUM_PRIORITY_QUEUE 2
      #define LOW_PRIORITY_QUEUE 3
      #define RR_QUANTUM_MEDIUM 8 // Quantum time for medium priority Round Robin
      #define RR_QUANTUM_LOW 16   // Quantum time for low priority Round Robin

      struct Process {
        int process_number;
        int arrival_time;
        int priority;
        int burst_time;
        int ram_required;
        int cpu_rate;
      };

      // Function to read input file and parse process data
      int parse_input_file(char *filename, struct Process processes[]) {
        FILE *file = fopen(filename, "r");
        if (file == NULL) {
          printf("Error: Unable to open input file.\n");
          return 0;
        }

        int num_processes = 0;
        char line[100];
        while (fgets(line, sizeof(line), file) != NULL) {
          // Parse process data from each line
          char *token;
          token = strtok(line, ",");
          processes[num_processes].process_number = atoi(&token[1]);
          token = strtok(NULL, ",");
          processes[num_processes].arrival_time = atoi(token);
          token = strtok(NULL, ",");
          processes[num_processes].priority = atoi(token);
          token = strtok(NULL, ",");
          processes[num_processes].burst_time = atoi(token);
          token = strtok(NULL, ",");
          processes[num_processes].ram_required = atoi(token);
          token = strtok(NULL, ",");
          processes[num_processes].cpu_rate = atoi(token);
          num_processes++;
        }

        fclose(file);
        return num_processes;
      }

      // Function to perform resource check
      int resource_check(struct Process process) {
        int CPU = (process.priority == 0) ? CPU_1 : CPU_2;
        if (process.ram_required <= CPU) {
          return 1; // Sufficient resources available
        } else {
          printf("Insufficient resources available for process %d.\n", process.process_number);
          return 0; // Insufficient resources available
        }
      }

      void FCFS_sort_processes(struct Process processes[], int num_processes) {
      int i, j;
      struct Process key;

      for (i = 1; i < num_processes; i++) {
        key = processes[i];
        j = i - 1;

        while (j >= 0 && processes[j].arrival_time > key.arrival_time) {
            processes[j + 1] = processes[j];
            j = j - 1;
        }
        processes[j + 1] = key;
        }
      }
 
      // Function to assign processes to CPU-1 using FCFS algorithm
      void assign_to_cpu1(struct Process process, FILE *output_file) {
        if (process.priority == 0) {
          fprintf(output_file, "Process %d is assigned to CPU-1.\n", process.process_number);
        }
      }

      // Function to sort processes based on burst time (SJF)
      void burst_sort_processes(struct Process processes[], int num_processes) {
        for (int i = 0; i < num_processes - 1; i++) {
          for (int j = 0; j < num_processes - i - 1; j++) {
            if (processes[j].burst_time+processes[j].arrival_time > processes[j + 1].burst_time+processes[j + 1].arrival_time) {
              struct Process temp = processes[j];
              processes[j] = processes[j + 1];
              processes[j + 1] = temp;
            }
          }
        }
      }

      // Function to assign processes to CPU-2 using specific scheduling algorithms
      void assign_to_cpu2(struct Process process, FILE *output_file) {
        if (process.priority == 1 || process.priority == 2 || process.priority == 3) {
            fprintf(output_file, "Process %d is assigned to CPU-2.\n", process.process_number);
         }
      }

      // Function to perform Round Robin scheduling
      int round_robin(struct Process queue[], int count, FILE* output_file, int quantum_time) {
        struct Process RR[MAX_PROCESSES];

        int done[MAX_PROCESSES] = {0};
        int quantum = quantum_time;
        int remaining_time[MAX_PROCESSES];

        for (int i = 0; i < count; i++) {
          remaining_time[i] = queue[i].burst_time;
        }

        int total_arrival = 0;
        int time_elapsed = 0;
        int newcount = 0;

          for (int i = 0; i < count; i++) {

               if ( i != 0 && time_elapsed < queue[i].arrival_time && queue[i].arrival_time != queue[i-1].arrival_time)
               {
                time_elapsed += queue[i].arrival_time - queue[i-1].arrival_time;
               }else if (i == 0)
               {
                time_elapsed += queue[i].arrival_time;
               }
               

              assign_to_cpu2(queue[i], output_file);

              if (remaining_time[i] > quantum) {


                time_elapsed += quantum;
                remaining_time[i] -= quantum;


                for (int a = 0; a < count; a++)
                {

                    if (queue[a].arrival_time > time_elapsed)
                    {
                        
                        for (int x = count - 1; x > 0; x--)
                        {
                            if (queue[a].process_number == queue[x+1].process_number)
                            {
                                queue[x+1] = queue[i];
                                remaining_time[x+1] = remaining_time[i];
                                queue[x+1].burst_time=remaining_time[x+1];
                                x=0;
                                a=count;
                            }else{
                            queue[x+1] = queue[x];
                            remaining_time[x+1] = remaining_time[x];
                            }
                            

                        }
                        
                    }
                  
                }
                count++;

                fprintf(output_file, "Process %d run until the defined quantum time and is queued again because the process is not completed\n", queue[i].process_number);
              } else {

                time_elapsed += remaining_time[i];
                remaining_time[i] = 0;
                fprintf(output_file, "Process %d is completed and terminated.\n", queue[i].process_number);
              }

              
              RR[newcount] = queue[i];
              newcount++;
            
          }


        for (int i = 0; i < newcount; i++) {
          queue[i] = RR[i];
        }
        return newcount;
      }


      int main(int argc, char *argv[]) {
        if (argc != 2) {
          printf("Usage: %s <input_file>\n", argv[0]);
            return 1;
          }

          struct Process processes[MAX_PROCESSES];
          int num_processes = parse_input_file(argv[1], processes);
          if (num_processes == 0) {
            printf("Error: Failed to parse input file.\n");
            return 1;
          }

          FILE *output_file = fopen("output.txt", "w");
          if (output_file == NULL) {
            printf("Error: Unable to create output file.\n");
            return 1;
          }

          struct Process que0[MAX_PROCESSES];
          struct Process que1[MAX_PROCESSES];
          struct Process que2[MAX_PROCESSES];
          struct Process que3[MAX_PROCESSES];
          int count0 = 0, count1 = 0, count2 = 0, count3 = 0;

          FCFS_sort_processes(processes, num_processes);

          for (int i = 0; i < num_processes; i++) {
            if (!resource_check(processes[i])) {
              printf("Resource check failed for process %d\n", processes[i].process_number);
            } else {
              if (processes[i].priority == 0) {
                que0[count0++] = processes[i];
                fprintf(output_file, "Process %d is queued to be assigned to CPU-1.\n", processes[i].process_number);
              } else if (processes[i].priority == 1) {
                que1[count1++] = processes[i];
                fprintf(output_file, "Process %d is queued to be assigned to CPU-2.\n", processes[i].process_number);
              } else if (processes[i].priority == 2) {
                que2[count2++] = processes[i];
                fprintf(output_file, "Process %d is queued to be assigned to CPU-2.\n", processes[i].process_number);
              } else if (processes[i].priority == 3) {
                que3[count3++] = processes[i];
                fprintf(output_file, "Process %d is queued to be assigned to CPU-2.\n", processes[i].process_number);
              }
            }
          }

          for (int i = 0; i < count0; i++) {
            assign_to_cpu1(que0[i], output_file);
            fprintf(output_file, "Process %d is completed and terminated.\n", que0[i].process_number);
          }

          burst_sort_processes(que1, count1);

          for (int i = 0; i < count1; i++) {
            assign_to_cpu2(que1[i], output_file);
            fprintf(output_file, "Process %d is completed and terminated.\n", que1[i].process_number);
          }

          count2 = round_robin(que2, count2, output_file, RR_QUANTUM_MEDIUM);
          count3 = round_robin(que3, count3, output_file, RR_QUANTUM_LOW);

          printf("CPU-1 queue (priority-0) (FCFS) -> ");
          for (int i = 0; i < count0; i++) {
            printf("P%d ", que0[i].process_number);
          }
          printf("\n");

          printf("CPU-2 queue (priority-1) (SJF) -> ");
          for (int i = 0; i < count1; i++) {
            printf("P%d ", que1[i].process_number);
          }
          printf("\n");

          printf("CPU-2 queue (priority-2) (RR-q8) -> ");
          for (int i = 0; i < count2; i++) {
            printf("P%d ", que2[i].process_number);
          }
          printf("\n");

          printf("CPU-2 queue (priority-3) (RR-q16) -> ");
          for (int i = 0; i < count3; i++) {
            printf("P%d ", que3[i].process_number);
          }
          printf("\n");

          fclose(output_file);
          return 0;
        }
