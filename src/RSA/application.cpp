#include <getopt.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include "application.h"
#include "public_key.h"
#include "private_key.h"

namespace RSA
{
Application::Application(int argc, char **argv) : argc(argc), argv(argv)
{
}

int Application::execute()
{
    if (argc < 2)
    {
        return help();
    }

    optind = 2;
    std::string command = argv[1];

    if (command == "generate")
    {
        return Generate();
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

int Application::Generate()
{
    int c, i, size = 0;
    std::string private_key_path, public_key_path;
    option long_options[] = {
        {"private-key", required_argument, 0, 0},
        {"public-key", required_argument, 0, 0},
        {"size", required_argument, 0, 's'}};

    while (true)
    {
        c = getopt_long(argc, argv, "s:", long_options, &i);

        if (c == -1)
            break;

        switch (c)
        {
        case 0:
            switch (i)
            {
            case 0:
                private_key_path = optarg;
                break;

            case 1:
                public_key_path = optarg;
                break;

            case 2:
                size = std::atoi(optarg);
                break;
            }
            break;

        case 's':
            size = std::atoi(optarg);
            break;

        default:
            printf("Invalid command.");
            return 1;
        }
    }

    if (size <= 0)
    {
        std::cout << "Size must be greater than 0.\n";
        return 1;
    }

    if (private_key_path.length() == 0)
    {
        std::cout << "Missing option --private-key.\n";
        return 1;
    }

    if (public_key_path.length() == 0)
    {
        std::cout << "Missing option --public-key.\n";
        return 1;
    }

    std::cout << "Generating public-private key pairs with " << size << "-bits modulus...\n";

    PrivateKey private_key(size);
    PublicKey public_key = private_key.publicKey();

    std::cout << "Writing public key to \"" << public_key_path << "\"...\n";

    public_key.Write(public_key_path);

    std::cout << "Writing private key to \"" << private_key_path << "\"...\n";

    private_key.Write(private_key_path);

    std::cout << "Done.\n";
}

int Application::help()
{
    if (argc >= 3)
    {
        std::string command = argv[2];

        if (command == "generate")
        {
            printf(
                "Usage: rsa generate --size=<number> --public-key=<file> --private-key=<file>\n"
                "Options:\n"
                "\t-s, --size <number>     \tThe modulus bit-length\n"
                "\t    --public-key <file> \tWhere to store public key\n"
                "\t    --private-key <file>\tWhere to store private key\n");
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

int Application::invalidCommand(std::string command)
{
    printf("Action '%s' is not a valid command. See 'rsa help'.\n", command.c_str());
    return 1;
}

int Application::notImplemented()
{
    printf("Not implemented.\n");
}
} // namespace RSA
