#include "memory_event.h"
#include <string.h>
#include <stdio.h>

void parse_memory_event(char* event_str, size_t len, memory_event* event) {
    char delims[] = ":,";
    char* tok = strtok(event_str, delims);
    event->alloc = *strtok(NULL, delims);

    strtok(NULL, delims);
    char* address = strtok(NULL, delims);
    event->address = (void*)strtoull(address, NULL, 16);

    strtok(NULL, delims);
    
    char* timestamp = strtok(NULL, delims);
    sscanf(timestamp, "%ld.%ld", &event->timestamp.tv_sec, &event->timestamp.tv_nsec);

    char* size_tok = strtok(NULL, delims);

    if (size_tok != NULL)  {
        char* size = strtok(NULL, delims);
        event->size = strtoull(size, NULL, 10);
    }
}