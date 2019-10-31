#include "application.h"

int main(int argc, char **argv)
{
    return new RSA::Application(argc, argv)->execute();
}
