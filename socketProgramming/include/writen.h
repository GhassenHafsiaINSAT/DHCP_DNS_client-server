#ifndef WRITEN_H
#define WRITEN_H

#include "common.h"

// write n bytes to a descriptor
ssize_t writen(int fd, const void *vptr, size_t n); 

#endif // WRITEN_H