#include <fstream>
#include <getopt.h>
#include <stdio.h>
#include "application.h"
#include "public_key.h"
#include "private_key.h"

namespace RSA
{
Application::Application(int argc, char **argv) : argc(argc), argv(argv)
{
}

int Application::Execute()
{
    if (argc < 2)
    {
        return Help();
    }

    optind = 2;
    std::string command = argv[1];

    if (command == "generate")
    {
        return Generate();
    }
    else if (command == "encrypt")
    {
        return Encrypt();
    }
    else if (command == "decrypt")
    {
        return Decrypt();
    }
    else if (command == "help")
    {
        return Help();
    }
    else
    {
        return InvalidCommand(command);
    }
}

void Application::CloseInputStream(std::istream *input)
{
    if (input != &std::cin)
        delete input;
}

void Application::CloseOutputStream(std::ostream *output)
{
    if (output != &std::cout)
        delete output;
}

int Application::Decrypt()
{
    int c, i;
    std::string input_file, output_file, private_key_path;
    option long_options[] = {
        {"input", required_argument, 0, 'i'},
        {"output", required_argument, 0, 'o'},
        {"private-key", required_argument, 0, 0}};

    while (true)
    {
        c = getopt_long(argc, argv, "i:o:", long_options, &i);

        if (c == -1)
            break;

        switch (c)
        {
        case 0:
            switch (i)
            {
            case 2:
                private_key_path = optarg;
                break;

            default:
                return InvalidCommand();
            }
            break;

        case 'i':
            input_file = optarg;
            break;

        case 'o':
            output_file = optarg;
            break;

        default:
            return InvalidCommand();
        }
    }

    if (private_key_path.length() == 0)
    {
        std::cout << "Missing option --private-key.\n";
        return 1;
    }

    PrivateKey key;
    key.Read(private_key_path);

    std::istream *input = GetInputStream(input_file);
    std::ostream *output = GetOutputStream(output_file);

    int length = NumBytes(key.n);
    char *cipertext = new char[length];
    char *plaintext = new char[length];

    input->read(cipertext, length);
    length = input->gcount();
    length = key.Decrypt((unsigned char *)plaintext, (unsigned char *)cipertext, length);
    output->write(plaintext, length);

    delete cipertext;
    delete plaintext;

    CloseInputStream(input);
    CloseOutputStream(output);
}

int Application::Encrypt()
{
    int c, i;
    std::string input_file, output_file, public_key_path;
    option long_options[] = {
        {"input", required_argument, 0, 'i'},
        {"output", required_argument, 0, 'o'},
        {"public-key", required_argument, 0, 0}};

    while (true)
    {
        c = getopt_long(argc, argv, "i:o:", long_options, &i);

        if (c == -1)
            break;

        switch (c)
        {
        case 0:
            switch (i)
            {
            case 2:
                public_key_path = optarg;
                break;

            default:
                return InvalidCommand();
            }
            break;

        case 'i':
            input_file = optarg;
            break;

        case 'o':
            output_file = optarg;
            break;

        default:
            return InvalidCommand();
        }
    }

    if (public_key_path.length() == 0)
    {
        std::cout << "Missing option --public-key.\n";
        return 1;
    }

    PublicKey key;
    key.Read(public_key_path);

    std::istream *input = GetInputStream(input_file);
    std::ostream *output = GetOutputStream(output_file);

    int length = NumBytes(key.n) - 1;
    char *cipertext = new char[length];
    char *plaintext = new char[length];

    input->read(plaintext, length);
    length = input->gcount();
    length = key.Encrypt((unsigned char *)cipertext, (unsigned char *)plaintext, length);
    output->write(cipertext, length);

    delete cipertext;
    delete plaintext;

    CloseInputStream(input);
    CloseOutputStream(output);
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

            default:
                return InvalidCommand();
            }
            break;

        case 's':
            size = std::atoi(optarg);
            break;

        default:
            return InvalidCommand();
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

std::istream *Application::GetInputStream(std::string path)
{
    if (path.length() == 0)
    {
        return &std::cin;
    }
    else
    {
        return new std::ifstream(path, std::ios::binary);
    }
}

std::ostream *Application::GetOutputStream(std::string path)
{
    if (path.length() == 0)
    {
        return &std::cout;
    }
    else
    {
        return new std::ofstream(path, std::ios::binary);
    }
}

int Application::Help()
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
            return InvalidCommand(command);
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

int Application::InvalidCommand()
{
    std::cout << "Invalid command. See 'rsa help'.\n";
    return 1;
}

int Application::InvalidCommand(std::string command)
{
    printf("Action '%s' is not a valid command. See 'rsa help'.\n", command.c_str());
    return 1;
}
} // namespace RSA
