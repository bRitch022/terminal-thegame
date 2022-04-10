// Test File

#include <cli/cli.h>
#include <cli/clifilesession.h>

#include <string>
#include <iostream>

using namespace std;
using namespace cli;

int main(int argc, char **argv)
{
    string newstring = "Hello World";
    cout << newstring << endl;

    auto rootMenu = make_unique< Menu >("Hello World CLI");
    rootMenu -> Insert(
                        "hello",
                        [](std::ostream& out){ Cli::cout() << "Hello, everybody" << std::endl;},
                        "Print hello world" );

    Cli cli( std::move(rootMenu) );
    cli.ExitAction( [](auto& out){ out << "What a wonderful world. Goodbye\n"; });

    CliFileSession input(cli);
    input.Start();

    return 0;
}