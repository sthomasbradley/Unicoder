#include <stdio.h>                   // For C++ use #include <iostream> instead.
#include "unicoder.h"

int main()
{
    wchar_t oldmode;

    oldmode = wcharOn();

    boldOn();
    wprintf(L"This text is bright (bold)\n");
    formatOff();
    wprintf(L"This text has returned to default\r\n");
    underlineOn();
    wprintf(L"Underlined text\n");
    underlineOff();
    redfontOn();
    wprintf(L"Font is RED\n");
    greenfontOn();
    wprintf(L"%lc, %lc, %lc\n",U_alpha, U_beta,U_gamma);
    bluebkgdOn();
    wprintf(L"Hard to read this\n");
    formatOff();
    wprintf(L"Return to default\n");
    wcharOff(oldmode);
    return 0;
}
