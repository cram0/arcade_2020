#include <iostream>
#include <dlfcn.h>
#include <stdlib.h>

int main(void)
{
    std::cout << "Hello CORE" << std::endl;

    void *bite = dlopen("libs/games/nibbler/arcade_nibbler.so", RTLD_LAZY);

    int (*print)(void);
    *(void **)(&print) = dlsym(bite, "main");

    (*print)();

    return (0);
}