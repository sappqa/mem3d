- memory event ingestion
    - read memory events into array of memory events
        - might not need to worry about having a map to get the size of deallocs, because I can just tie the vertex data to the ptr. all I need to know is if that ptr is freed, I just stop rendering that block.
    - capture min and max ptr address and get the difference. Use that to base the size of the world space



later:
- update readme with build/usage instructions
- add input args checking/parsing
- encapsulate graphics debugging logic