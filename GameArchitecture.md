Game (main)
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
