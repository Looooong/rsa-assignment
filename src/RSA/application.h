#ifndef RSA_APPLICATION_H
#define RSA_APPLICATION_H

#include <iostream>
#include <string>

namespace RSA
{
class Application
{
public:
    Application(int argc, char **argv);

    int Execute();

private:
    int argc;
    char **argv;

    void CloseInputStream(std::istream *input);
    void CloseOutputStream(std::ostream *output);
    int Decrypt();
    int Encrypt();
    int Generate();
    std::istream *GetInputStream(std::string path);
    std::ostream *GetOutputStream(std::string path);
    int Help();
    int InvalidCommand();
    int InvalidCommand(std::string command);
};
} // namespace RSA

#endif // RSA_APPLICATION_H
