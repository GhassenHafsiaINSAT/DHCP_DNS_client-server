#include "common.h"

// Read a text line from a descriptor, one byte at a time.

ssize_t readline (int fd, void *vptr, size_t maxlen); 