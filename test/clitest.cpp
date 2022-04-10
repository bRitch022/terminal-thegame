/**
 * @file clitest.cpp
 * @brief Contains version control information for releases
 * @copyright 
 * Copyright 2022, Ridgetech, LLC.. This software and its contents are 
 * Ridgetech confidental and proprietary. It cannot be used, disclosed 
 * or distributed without Ridgetech's prior written permission. Modification 
 * of this software is only allowed at the direction of Ridgetech.
 * All allowed modifications must be provided back to Ridgetech.
 * 
 */

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