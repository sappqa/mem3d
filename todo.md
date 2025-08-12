- memory event ingestion
    - create memory event struct
    - read memory events into array of memory events
        - might not need to worry about having a map to get the size of deallocs, because I can just tie the vertex data to the ptr. all I need to know is if that ptr is freed, I just stop rendering that block.  



later:
- update readme with build/usage instructions
- add input args checking/parsing
- encapsulate graphics debugging logic