//IMPLEMENTACAO SANITY
#include "types.h"
#include "user.h"
int main(int argc, char *argv[])
{
    if (argc != 2){
        printf(1, "Sanity expects one parameter [n]\n");
        exit();
 	}

    int n=atoi(argv[1]);
    //loop creating 3n processes
    int pid;
    int proc_type;
    //Running processes
    for (int i=0; i<3*n;i++)
    {
        pid=fork();
        if(pid==0) //if its the child
            {
                proc_type=getpid()%3;
                switch (proc_type)
                {
                case 0: //CPU-BOUND
                    for (int a = 0; a < 100; a++)
                        {for (int b = 0; b<1000000; b++){}}
                    
                    break;
                case 1: //S-CPU
                    for (int a = 0; a < 20; a++){
                            for (int b = 0; b<1000000; b++){}
                            yield();
                        }
                    break;  
                case 2: //IO-BOUND
                    for (int a = 0; a < 100; a++)
                        {sleep(1);}
                    break;
                default:
                    break;
                }
                exit(); //exiting children processes
            }
    }

    //Info for each process
    int retime,cpu_retime=0,s_retime=0,io_retime=0;
	int rutime,cpu_rutime=0,s_rutime=0, io_rutime=0;
	int stime, cpu_stime=0, s_stime=0, io_stime=0;
    for (int i=0; i<3*n;i++){
        pid=wait2(&retime, &rutime, &stime);
        proc_type=pid%3;
        switch (proc_type)
        {
            case 0: //CPU-BOUND
                printf(1, "CPU-Bound, pid: %d, ready time: %d, running time: %d, sleeping time: %d\n", pid, retime, rutime, stime);
                cpu_retime+=retime;
                cpu_rutime+=rutime;
                cpu_stime+=stime;

                break;
            case 1: //S-CPU
                printf(1, "CPU-S Bound, pid: %d, ready time: %d, running time: %d, sleeping time: %d\n", pid, retime, rutime, stime);
                s_retime+=retime;
                s_rutime+=rutime;
                s_stime+=stime;
                break;  
            case 2: //IO-BOUND
                printf(1, "IO-Bound, pid: %d, ready time: %d, running time: %d, sleeping time: %d\n", pid, retime, rutime, stime);
                io_retime+=retime;
                io_rutime+=rutime;
                io_stime+=stime;
                break;
            default:
                break;
        }
    }
    //Average Info
	printf(1, "\n\nCPU bound:\nAverage ready time: %d\nAverage running time: %d\nAverage sleeping time: %d\nAverage turnaround time: %d\n\n\n", cpu_retime/n, cpu_rutime/n, cpu_stime/n, (cpu_retime+cpu_rutime+cpu_stime)/n);
	printf(1, "CPU-S bound:\nAverage ready time: %d\nAverage running time: %d\nAverage sleeping time: %d\nAverage turnaround time: %d\n\n\n", s_retime/n, s_rutime/n, s_stime/n,(s_retime+s_rutime+s_stime)/n);
	printf(1, "I/O bound:\nAverage ready time: %d\nAverage running time: %d\nAverage sleeping time: %d\nAverage turnaround time: %d\n\n\n", io_retime/n, io_rutime/n, io_stime/n,(io_retime+io_rutime+io_stime)/n);
	exit();

}