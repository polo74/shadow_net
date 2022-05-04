#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>

#include <err.h>
#include <time.h>

#include <sys/wait.h>

#define min 10
#define max 175
#define step 10

#define MIN_Z 10
#define MAX_Z 175
#define STEP_Z 10

int main(int argc, char** argv){

	if (argc != 2) {
        err(EXIT_FAILURE, "incorrect arguments");
    }

    char* path = argv[1];

    for (int k = MIN_Z; k < MAX_Z; k += STEP_Z) {
        for (int i = min; i < max; i += step) {

            time_t begin;
            time_t end;

            begin = time(NULL);
            if (begin < 0) {
                err(EXIT_FAILURE, "time error");
            }

            int pid = fork();

            if (pid < 0) {
                err(EXIT_FAILURE, "Fork error");
            }

            if (pid == 0) {
                char argxy[16];
                char argz[16];
                sprintf(argxy, "%d", i);
                sprintf(argz, "%d", k);
                char *args[5] = {
                        path,
                        argxy,
                        argxy,
                        argz,
                        NULL
                };

                if (execvp(path, args) < 0) {
                    err(EXIT_FAILURE, "oops...");
                }
            }

            if (pid > 0) {
                waitpid(pid, NULL, 0);
                end = time(NULL);
                if (end < 0) {
                    err(EXIT_FAILURE, "time error");
                }

                double diff = difftime(end, begin);

                printf("%d\t%d\t%d\t%f\n", i, i, k, diff);
            }
        }
    }

	return 0;
}
