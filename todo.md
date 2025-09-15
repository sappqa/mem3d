- render blocks with size
- camera init distance needs to scale with grid size
- zoom ammount needs to scale with grid size
- add 3d axis
- debug grid drawing issues with different grid_size.
- debug first allocation and animation start delay
- maybe add keyboard controls/animation controls - start stop, reset scrub. needs to interface nicely with the live render list...


note:
- might not need to worry about having a map to get the size of deallocs, because I can just tie the vertex data to the ptr. all I need to know is if that ptr is freed, I just stop rendering that block.

later:
- update readme with build/usage instructions
- add input args checking/parsing
- encapsulate graphics debugging logic
- ui controls