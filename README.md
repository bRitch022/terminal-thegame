# Terminal
This is a Linux-teaching game engine. This framework can be built onto to teach other command line interfaces like MSDOS, CmdPrompt, PowerShell

## Dependancies
* GNU g++ 9.4.0

## Building
* Clone this repo
* cd into build/
* ```make all -j4```
* The built binaries are located in ./build/bin/ and ./game/bin/

## Cleaning
* ```make clean```

## Launching game
* cd into game/
* `docker build -t gameenv . && docker run -it gameenv bash`

## Debugging
* Within the gameenv container:
* `gdb /usr/game/gamefiles/Terminal.dbg`
* You will see: 
```
GNU gdb (Debian 10.1-1.7) 10.1.90.20210103-git
Copyright (C) 2021 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from /usr/game/gamefiles/Terminal...
(No debugging symbols found in /usr/game/gamefiles/Terminal)
(gdb) 
```
* Launch the gdb`r /usr/game/gamefiles/Registry.ini /usr/game/gamefiles/levels`
* View https://gabriellesc.github.io/teaching/resources/GDB-cheat-sheet.pdf for a list of commands

## Credits
