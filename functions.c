#include "functions.h"

void interruptSignalController(int value) {
    printf("\n>> pid: %d, ctrl + C\n", getpid());
    exit(1);
}

void counterSignalController(int value) {
    printf("\n>> pid: %d, counter\n", getpid());
}

void killSignalController(int value) {
    printf("Soy el hijo con pid: %d y mi papá me quiere matar\n", getpid());
    exit(1);
}

void forkSignalController(int value) {
    printf("\n>> pid: %d, fork\n", getpid());
}

char convertSignal(int number) {
    if (number == 15) {
        return 'A';
    }
    else if (number == 16) {
        return 'B';
    }

    return 'C';
}

void init(int children, int mflag) {

    signal(SIGINT, &interruptSignalController);
    signal(SIGUSR1, &counterSignalController);
    signal(SIGUSR2, &forkSignalController);
    signal(SIGTERM, &killSignalController);

    int x = 0;
    int y = 0;
    int counter = 0;
    int fatherPid = getpid();
    int* pids = (int*)malloc(children * sizeof(int));

    for (int i = 0; i < children; i++) {
        pids[i] = fork();
        if (pids[i] == 0) {
            break;
        }
    }

    if (getpid() == fatherPid) {
        if (mflag) {
            printf("Mostrando la información por pantalla:\n");
            for (int i = 0; i < children; i++) {
                printf("Numero %d, pid: %d\n", i+1, pids[i]);
            }
        }

        char z;
        while(1) {
            write(1, ">> Ingresar núumero de hijo y señal a enviar (X - Y):\n", 56);
            write(1, ">> ", 4);
            scanf("%d - %d", &x, &y);
            printf(">> La señal %d será enviada al hijo %d de pid %d,\n", y, x, pids[x-1]);

            z = convertSignal(y);

            switch (z) {
                case 'A':
                    kill(pids[x-1], 15);
                    waitpid(pids[x-1], NULL, 0);
                    break;
                case 'B':
                    kill(pids[x-1], 16);
                    waitpid(pids[x-1], NULL, 0);
                    break;
                case 'C':
                    kill(pids[x-1], 17);
                    waitpid(pids[x-1], NULL, 0);
                    break;
            }

        }
    }
    else {
        while (1) {
            /* children will be waiting for a signal */
        }
    }

    free(pids);
}
