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
    int proc_type,a,b;
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
        pid =wait2(&retime, &rutime, &stime);
        proc_type=getpid()%3;
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
int main(int argc, char *argv[])
{
	if (argc != 2){
				printf(1, "Sanity expects one parameter [n]\n");
				exit();
 	}
	int i;
	int n=atoi(argv[1]);
	int j = 0;
	int k;
	int retime;
	int rutime;
	int stime;
	int sums[3][3];

	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			sums[i][j] = 0;

	int pid;
	for (i = 0; i < n; i++) {
		j = i % 3;
		pid = fork();
		if (pid == 0) {//child
			j = (getpid() - 4) % 3; // ensures independence from the first son's pid when gathering the results in the second part of the program
			switch(j) {
				case 0: //CPU‐bound process (CPU):
						for (double z = 0; z < 10000.0; z+= 0.1){
				         double x =  x + 3.14 * 89.64;   // useless calculations to consume CPU time
					}
					break;
				case 1: //short tasks based CPU‐bound process (S‐CPU):
					for (k = 0; k < 100; k++){
						for (j = 0; j < 1000000; j++){}
						yield();
					}
					break;
				case 2:// simulate I/O bound process (IO)
					for(k = 0; k < 100; k++){
						sleep(1);
					}
					break;
			}
			exit(); // children exit here
		}
		continue; // father continues to spawn the next child
	}
	for (i = 0; i < n; i++) {
		pid = wait2(&retime, &rutime, &stime);
		int res = (pid - 4) % 3; // correlates to j in the dispatching loop
		switch(res) {
			case 0: // CPU bound processes
				printf(1, "CPU-bound, pid: %d, ready: %d, running: %d, sleeping: %d, turnaround: %d\n", pid, retime, rutime, stime, retime + rutime + stime);
				sums[0][0] += retime;
				sums[0][1] += rutime;
				sums[0][2] += stime;
				break;
			case 1: // CPU bound processes, short tasks
				printf(1, "CPU-S bound, pid: %d, ready: %d, running: %d, sleeping: %d, turnaround: %d\n", pid, retime, rutime, stime, retime + rutime + stime);
				sums[1][0] += retime;
				sums[1][1] += rutime;
				sums[1][2] += stime;
				break;
			case 2: // simulating I/O bound processes
				printf(1, "I/O bound, pid: %d, ready: %d, running: %d, sleeping: %d, turnaround: %d\n", pid, retime, rutime, stime, retime + rutime + stime);
				sums[2][0] += retime;
				sums[2][1] += rutime;
				sums[2][2] += stime;
				break;
		}
	}
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			sums[i][j] /= n;
	printf(1, "\n\nCPU bound:\nAverage ready time: %d\nAverage running time: %d\nAverage sleeping time: %d\nAverage turnaround time: %d\n\n\n", sums[0][0], sums[0][1], sums[0][2], sums[0][0] + sums[0][1] + sums[0][2]);
	printf(1, "CPU-S bound:\nAverage ready time: %d\nAverage running time: %d\nAverage sleeping time: %d\nAverage turnaround time: %d\n\n\n", sums[1][0], sums[1][1], sums[1][2], sums[1][0] + sums[1][1] + sums[1][2]);
	printf(1, "I/O bound:\nAverage ready time: %d\nAverage running time: %d\nAverage sleeping time: %d\nAverage turnaround time: %d\n\n\n", sums[2][0], sums[2][1], sums[2][2], sums[2][0] + sums[2][1] + sums[2][2]);
	exit();
}