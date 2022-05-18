# gameStart.sh

echo "gameStart.sh: Game Started"
# Initialize the registry here

# Call the main game file here
# /usr/game/gamefiles/Terminal /usr/game/gamefiles/Registry.ini /usr/game/gamefiles/levels TODO (BAR): uncomment this line

# DEBUGGING
#
#
/usr/game/gamefiles/Terminal.dbg /usr/game/gamefiles/Registry.ini /usr/game/gamefiles/levels

if [[ $? != 0 ]]; then
    gdb -q -ex=r --args /usr/game/gamefiles/Terminal.dbg /usr/game/gamefiles/Registry.ini /usr/game/gamefiles/levels 
fi
#
#
# END DEBUGGING
