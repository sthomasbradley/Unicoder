#include <stdio.h>                  // For C++ use #include <iostream> instead.
#include "unicoder.h"

int main()
{
    wcharOn();                     // Turn on wide character mode.
    wprintf(L"Unicode: f(x) = %lc%lc+ %lc%lc\n",U_alpha,U_squared,U_beta, U_cubed);

    return 0;
}
