#ifndef RSA_APPLICATION_H
#define RSA_APPLICATION_H

#include <string>

namespace RSA
{
class Application
{
public:
    Application(int argc, char **argv);

    int execute();

private:
    int argc;
    char **argv;

    int invalidCommand(std::string command);
    int help();
    int notImplemented();
};
} // namespace RSA

#endif // RSA_APPLICATION_H
