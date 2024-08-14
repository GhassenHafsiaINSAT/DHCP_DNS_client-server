#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *name; 
    unsigned short mask; 
} tcp_flag; 


void tcp_flags(unsigned short flags){
    tcp_flag tcp[] = {
        {"NS", 0x0001},
        {"CWR", 0x0002},
        {"URG", 0x0004},
        {"ACK", 0x0008},
        {"PSH", 0x0010},
        {"RST", 0x0020},
        {"SYN", 0x0040},
        {"FIN", 0x0080}
    };
    for (int i=0; i<7; i++){
        if (tcp[i].mask & flags)
        {
            printf("%s, ",tcp[i].name); 
        }
    }
    if (flags & 0x0080){
        printf("%s \n", "FIN"); 
    }
}

int main(){
    tcp_flags(0x0083); 
    return 0;
}