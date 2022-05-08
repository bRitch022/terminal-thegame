# Terminal
This is a Linux-teaching game engine. This framework can be built onto to teach other command line interfaces like MSDOS, CmdPrompt, PowerShell

## Dependancies
* GNU g++ 9.4.0

## Building
* Clone this repo
* cd into build/
* ```make -j4```
* The built binary is located in ./build/bin/

## Cleaning
* ```make clean```

## Launching game
* cd into game/
* `docker build -t gameenv . && docker run -it gameenv bash`

## Credits
