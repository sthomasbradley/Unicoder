#include <stdio.h>                   // For C++ use #include <iostream> instead.
#include "unicoder.h"

int main()
{
    wcharOn();
    wprintf(L"Don't worry, be happy! %lc\n",U_lthappy); // Table 4.6
    wprintf(L"An Ace of %lc\n",U_spades);               // Table 4.7

    return 0;
}
