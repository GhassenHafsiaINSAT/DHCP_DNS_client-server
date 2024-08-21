#include "common.h"


/* signal handler to handle the `SIGHLD` signal, this signal is sent to 
parent process whenever one of its child processe terminates or stops */
void sig_chld(int signo);