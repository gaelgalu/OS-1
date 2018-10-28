#include "functions.h"

void interruptSignalController(int value) {
    printf("ctrl + C\n");
    exit(1);
}

void counterSignalController(int value) {
    printf(">> pid: %d, y he recibido esta llamada ? veces.\n", getpid());
}

void killSignalController(int value) {
    printf("Soy el hijo con pid: %d y mi papá me quiere matar\n", getpid());
    exit(1);
}

void forkSignalController(int value) {
    fork();
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


    int x = 0;
    int y = 0;
    int fatherPid = getpid();
    int* pids = (int*)malloc(children * sizeof(int));

    signal(SIGINT, interruptSignalController);
    signal(SIGUSR1, counterSignalController);
    signal(SIGUSR2, forkSignalController);
    signal(SIGTERM, killSignalController);

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
            printf(">> Ingresar núumero de hijo y señal a enviar (X - Y):\n");
            printf(">> ");
            scanf("%d - %d", &x, &y);
            printf(">> La señal %d será enviada al hijo %d de pid %d,\n", y, x, pids[x-1]);

            z = convertSignal(y);

            switch (z) {
                case 'A':
                    kill(pids[x-1], SIGTERM);
                    sleep(1);
                    break;
                case 'B':
                    kill(pids[x-1], SIGUSR1);
                    sleep(1);
                    break;
                case 'C':
                    kill(pids[x-1], SIGUSR2);
                    sleep(1);
                    break;
            }
        }
    }
    else {
        while (1) {
            /* children will be waiting for a signal until the father dies*/
        }
    }

    free(pids);
}
