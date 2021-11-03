#include <stdio.h>                   // For C++ use #include <iostream> instead.
#include "unicoder.h"

int main()
{
    #define SPADE 0x2660

    wcharOn();
    wprintf(L"Don't worry, be happy! \u263A\n");
    wprintf(L"An Ace of %lc\n",SPADE);

    return 0;
}
