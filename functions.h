#pragma once
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
void interruptSignalController(int value);

void counterSignalController(int value);

void killSignalController(int value);

void forkSignalController(int value);

char convertSignal(int number);

void init(int children, int flag);
