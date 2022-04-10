# LINUX CLI GAME 
This is a Linux-teaching game engine. This framework can be built onto to teach other command line interfaces like MSDOS, CmdPrompt, PowerShell

## Dependancies
* GNU g++ 9.4.0

## Building
* Clone this repo
* cd into the repo
* ```make -j4```
* The built binary is located in ./build/bin/

## Cleaning
* ```make clean```

## Credits
### Command Line Interface
> https://github.com/daniele77/cli  
> Twitter account @DPallastrelli


# Release Notes
### 01.00.0001
* 

# (Preliminary) Architectural Design
    --> Player
        --> Username
        --> Level
        --> Current XP
    --> Scene
        --> Scene Text
        --> ID
        --> Level
            --> ID
            --> Exit point -> Scene/Level ID
            --> Tasks
            --> Granted XP
            --> Level Text
            --> CLI
                --> Commands
                    [whoami] - Prints the current username
                    [pwd]    - Prints the current working directory
                    [ls]     - Lists the contents of the current working directory
                    [cd]     - Changes directory
                    [cat]    - Prints the contents of a file
                    [grep]   - Searches for a keyword in files and directories
                    [vi]     - Edit a text file
                    --> callname
                    --> options
                    --> help text
                --> Director(y/ies)
                    --> Name
                    --> Permissions
                    --> File(s)
                        --> Name
                        --> Permissions
                        --> Type 
                            [Text]
                                ---> Contents
                            [Binary]
                                ---> Effects if executed
