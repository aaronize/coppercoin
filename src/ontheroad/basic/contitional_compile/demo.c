#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    // printf("argc: %d, argv: %s\n", argc, argv[0]);
    if (argc != 2) {
        printf("[ERR] Missing input parameter. Usage: %s <port>\n", argv[0]);
        // exit(1);
    }

    #if _WIN32
        printf("Windows platform\n");
    #elif _linux_
        printf("Linux platform\n");
    #else
        printf("Not windows platform\n");
    #endif

    return 0;
}