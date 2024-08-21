#include "../include/signal.h"

Sigfunc *signal(int signo, Sigfunc *func)
{
    struct sigaction act, oact; // act: new action, oact: the old action

    act.sa_handler = func;

    /*The signal handler won't prevent other signals from being delivered while it's running.*/
    sigemptyset(&act.sa_mask);
    /* no additional signals will be blocked 
        while our handler is working*/
    act.sa_flags = 0;

    if (signo == SIGALRM) {
#ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT; // SunOS 4.x
#endif
    } else {
#ifdef SA_RESTART
        act.sa_flags |= SA_RESTART; // SVR4, 4.4BSD
#endif
    }

    if (sigaction(signo, &act, &oact) < 0)
        return (SIG_ERR);
    
    return (oact.sa_handler);
}