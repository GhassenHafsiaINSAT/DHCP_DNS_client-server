#ifndef READN_H
#define READN_H

#include "common.h"

// reads n bytes from a descriptor 
ssize_t readn(int fields, void *buff, size_t nbytes); 

#endif // READN_H