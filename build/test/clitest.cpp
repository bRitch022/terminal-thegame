/** Test environment for various features that are being added */

#include <cli/cli.h>
#include <cli/clifilesession.h>

#include <string>
#include <iostream>
#include <fstream>

#include <nlohmann/json.hpp>

using namespace std;
using namespace cli;
using namespace nlohmann;

string find_filepath(string filename)
{
    char cmd[128];
    char inbuf[128];
    string result;

    sprintf(cmd, "find ../../../ -name %s -exec readlink -f {} \\; | awk '{ print $1 }' | tr -d '\n'", filename.c_str());

    FILE* pipe = popen(cmd, "r");

    if(pipe)
    {
        while(!feof(pipe))
        {
            if(fgets(inbuf, 128, pipe) != NULL)
                result += inbuf;
        }
    }

    pclose(pipe);
    return result;
}

// std::function<void()> PrintHello()
// {
//     cout << "Hello World Test Function" << endl;
// }

static void foo(std::ostream& out, string x) { out << x << std::endl; }

int main(int argc, char **argv)
{
    // Create the CLI menu
    ifstream commands_file(find_filepath("commands.json"));
    if(commands_file.is_open())
    {
        json json;
        commands_file >> json;

        string newstring = "Welcome to the CLI bitch!";
        cout << newstring << endl;

        auto rootMenu = make_unique< Menu >(" CLI ");
        if(json.is_array())
        {
            for(size_t i = 0; i < json.size(); i++)
            {
                string command = json[i].contains("cmd") ? json[i]["cmd"] : "oops";
                string action = json[i].contains("info") ? json[i]["info"] : "oops";
                string info = json[i].contains("info") ? json[i]["info"] : "oops";

                // rootMenu -> Insert(command, foo((std::ostream&)Cli::cout, action), info );
                // This is a template for now, need to create the lambda functions that each cmd will be associated with
                rootMenu -> Insert(command, 
                [action](std::ostream& out)
                { 
                    Cli::cout() << action << std::endl;
                }
                , info);
            }
        }
        
        Cli cli( std::move(rootMenu) );
        cli.ExitAction( [](auto& out){ out << "Quitting already?\n"; });

        CliFileSession input(cli);
        input.Start();
    }

    return 0;
}
