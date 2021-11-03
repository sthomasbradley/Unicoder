#include <stdio.h>             // For C++ use #include <iostream> instead.
#define EXTENDED_UNICODE
#include "unicoder.h"

int main()
{
    wcharOn();
    wprintf(L"Checkmate! %lc %lc\n",U_whking,U_blkqueen);

    return 0;
}
