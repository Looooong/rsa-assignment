#include <getopt.h>
#include <stdio.h>
#include <string>
#include "application.h"

namespace RSA
{
Application::Application(int argc, char **argv) : argc(argc), argv(argv)
{
}

int Application::execute()
{
    if (argc < 2) {
        return help();
    }

    std::string command = argv[1];

    if (command == "generate")
    {
        return notImplemented();
    }
    else if (command == "encrypt")
    {
        return notImplemented();
    }
    else if (command == "decrypt")
    {
        return notImplemented();
    }
    else if (command == "help")
    {
        return help();
    }
    else
    {
        return invalidCommand(command);
    }
}

int Application::invalidCommand(std::string command)
{
    printf("Action '%s' is not a valid command. See 'rsa help'.\n", command.c_str());
    return 1;
}

int Application::help()
{
    if (argc >= 3)
    {
        std::string command = argv[2];

        if (command == "generate")
        {
            printf(
                "Usage: rsa generate --public-key=<file> --private-key=<file>\n"
                "Options:\n"
                "\t--public-key <file> \tWhere to store public key\n"
                "\t--private-key <file>\tWhere to store private key\n");
        }
        else if (command == "encrypt")
        {
            printf(
                "Usage: rsa encrypt --public-key=<file> [--input=<file>] [--output=<file>]\n"
                "Options:\n"
                "\t    --public-key <file>\tPath to public key\n"
                "\t-i, --input <file>     \tEncrypt data in this file.\n"
                "\t                       \tIf not specified, read from standard input.\n"
                "\t-o, --output <file>    \tWhere to store encrypted data.\n"
                "\t                       \tIf not specified, write to standard output.\n");
        }
        else if (command == "decrypt")
        {
            printf(
                "Usage: rsa decrypt --private-key=<file> [--input=<file>] [--output=<file>]\n"
                "Options:\n"
                "\t    --private-key=<file>\tPath to private key\n"
                "\t-i, --input=<file>      \tDecrypt data in this file.\n"
                "\t                        \tIf not specified, read from standard input.\n"
                "\t-o, --output=<file>     \tWhere to store decrypted data.\n"
                "\t                        \tIf not specified, write to standard output.\n");
        }
        else
        {
            return invalidCommand(command);
        }
    }
    else
    {
        printf(
            "Usage: rsa <command> [<args>]\n"
            "Available commands:\n"
            "\tgenerate\tGenerate RSA key pairs\n"
            "\tencrypt \tEncrypt data given a public key\n"
            "\tdecrypt \tDecrypt data given a private key\n"
            "\thelp    \tYou are looking at it\n"
            "See 'rsa help <command>' to read about a specific subcommand.\n");
    }
}

int Application::notImplemented()
{
    printf("Not implemented.\n");
}
} // namespace RSA
