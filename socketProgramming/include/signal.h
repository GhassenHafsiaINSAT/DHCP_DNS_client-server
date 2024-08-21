#include "common.h"

typedef void Sigfunc(int);

Sigfunc* signal(int signo, Sigfunc *func); 