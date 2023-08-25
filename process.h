#ifndef __PROCESS_H
#define __PROCESS_H



void execute_process( int num_args, char **args, int background_flag, int *proc_no , pid_t *background_processes);
void check_background_processes(int *proc_no , pid_t *background_processes ) ;

#endif