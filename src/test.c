//#define __MSYS2__
#include "unicoder.h"
#include <math.h>

void getIDs(void);
void colorchk(void);
void warnings(int);

int errornum = 0;

int main(void)
{

    char ch,chstr[40];
    const long MyArray[4][2] = { {0,3},{U_hearts,3},{U_spades,5},{U_diamonds,3} };
    const long MyCArray[][2] = { {U_alpha,3},{U_beta,3},{U_gamma,5},{U_delta,3},{0,0} };
    const wchar_t delimiters[] = L" .,;:!-";
    double dbl;
    float flt;
    int intg,i;
    long lint;
    long double ldbl;
    long long int llint;
    signed char schar;
    signed short sshrt;
    size_t size;
    unsigned char uchar;
    unsigned long ulint;
    unsigned long long ullint;
    unsigned short ushrt;
    umode_t attr;
    wchar_t  * pc,str[80] = L"Science";
    wchar_t numstr1[40],numstr2[40],numstr3[40],numstr4[40],numstr5[40];
    wchar_t str1[] = L"computer";
    wchar_t str2[] = L"Science";
    wchar_t wstr[80], * endp;
    wchar_t tokstr[] = L"words separated by spaces -- and, punctuation!";
    wchar_t* token;


    attr = udispOn();
    wprintf(L"(scrnClr) screen didn't clear\n");
    scrnClr();
    wprintf(L"***************************\n");
    wprintf(L"** Unicoder test program **\n");
    wprintf(L"***************************\n");
#ifdef __STDC_VERSION__
    wprintf(L"STDC_VERSION %ld\n", __STDC_VERSION__);
#else
    wprintf(L"STDC_VERSION not defined\n");
#endif
#ifdef __cplusplus
    wprintf(L"C++ defined\n");
#else
    wprintf(L"C++ not defined\n");
#endif

    getIDs();
    wprintf(L"umode = 0x%x   type:", attr);
    i = umodetype(attr);
    wprintf(L"%ls\n\n", i ? (i-1 ?  L"unknown" : L"char *") : L"int");

    wprintf(L"(udispOn)  alpha: \u03B1");
    wprintf(L"   alpha: %lc", 0x03B1);
    wprintf(L"   alpha: %lc\n", U_alpha);

    udispOff(attr);
    wprintf(L"(udispOff) alpha: %lc\n", U_alpha);

    udispOn();
    wprintf(L"(udispOn)  alpha: %lc\n", U_alpha);
    warnings(0);
    wprintf(L"\n");

    colorchk();
    underlineOn();
    wprintf(L"(underlineOn)");
    underlineOff();
    wprintf(L"     (underlineOff)\n");
    bluefontOn();
    underlineOn();
    boldOn();
    wprintf(L"blue bold underlined");
    formatOff();
    wprintf(L"    (formatOff)\n");
    warnings(1);

    reverseTextOn();
    wprintf(L"\n(reversetextOn)");
    reverseTextOff();
    wprintf(L"   (reversetextOff)\n");
    warnings(2);

    wprintf(L"(thinlineDrawLn)  ");
    thinlineDrawLn(20);
    wprintf(L"(boldlineDrawLn)  ");
    boldlineDrawLn(20);
    wprintf(L"(dashlineDrawLn)  ");
    dashlineDrawLn(20);
    wprintf(L"(dbllineDrawLn)   ");
    dbllineDrawLn(20);
    wprintf(L"without & with Ln ");
    dashlineDraw(5);
    dbllineDraw(10);
    dashlineDrawLn(5);

    wprintf(L"(rowDrawLn P)     ");
    rowDrawLn(MyArray);
    wprintf(L"(rowDrawLn C)     ");
    rowDraw(MyCArray);

    wprintf(L"\n-----------------------------------------\n");
    wprintf(L" wstrtok(str,delimiter,&pc) str= %ls\n",tokstr);
    token = wstrtok(tokstr, delimiters,&pc);
    while (token) {
            wprintf(L"    %ls\n", token);
            token = wstrtok(NULL, delimiters,&pc);
    }
    wprintf(L"str1:%ls  str2:%ls     ",str1,str2);
    i = wstrcmp(str1, str2);
    wprintf(L"wstrcmp(str1.str2)    %ls\n",i?L"not equal":L"equal");
    wprintf(L"str2:%ls   str1:%ls    ",str2,str1);
    i = wstrcmp(str2, str1);
    wprintf(L"wstrcmp(str2,str1)    %ls\n",i?L"not equal":L"equal");
    wprintf(L"str: %ls   str2:%ls     ",str,str2);
    i = wstrcmp(str, str2);
    wprintf(L"wstrcmp(str,str2)     %ls\n",i?L"not equal":L"equal");

    wstrcpy(str,str1);
    wstrcat(str,str2);
    wprintf(L"str1:%ls  str2:%ls     wstrcpy(str,str1)   &  wstrcat(str,str2)    str: %ls\n",str1,str2, str);

    wstrncpy(str,str1, 4);
    wstrncat(str,str2, 3);
    wprintf(L"str1:%ls  str2:%ls     ",str1,str2);
    wprintf(L"wstrncpy(str,str1,4) & wstrncat(str,str2,3) str: %ls\n", str);
    i = wstrncmp(str, str1, 4);
    wprintf(L"str:%ls    str1:%ls    wstrncmp(str,str1,4)  %ls\n",str, str1,i?L"not equal":L"equal");
    i = wstrncmp(str, str1, 5);
    wprintf(L"str:%ls    str1:%ls    wstrncmp(str,str1,5)  %ls\n",str, str1,i?L"not equal":L"equal");
    i = wstrncmp(str1, str, 5);
    wprintf(L"str1:%ls  str:%ls      wstrncmp(str1,str,5)  %ls\n",str1, str,i?L"not equal":L"equal");

    pc = wstrchr(str, L'c');
    wprintf(L"str:%ls                     wstrchr(str,L'c')     c found at %d\n",str, pc - str + 1);

    pc = wstrrchr(str, L'c');
    wprintf(L"str:%ls                     wstrrchr(str.L'c')    last c found at %d\n",str, pc - str + 1);

    size = wstrspn(str, str1);
    wprintf(L"str:%ls    str1:%ls    wstrspn(str,str11)    length of prrfix match%3d\n",str,str1, size);

    size = wstrcspn(str,L"S");
    wprintf(L"str:%ls    \"S\"              wstrcspn(str,L\"S\")    Number of char before \"S\" %d\n",str, size);

    wstrcpy(str,L"aeiouAEIOU");
    pc = wstrpbrk(str1,str);
    while(pc != NULL)
    {
        wprintf(L"str1:%ls  str:%ls   wstrpbrk(str1,str)    %ls\n",str1,str,pc);
        pc = wstrpbrk(pc+1,str);
    }

    wstrcpy(str,L"put");
    pc = wstrwstr(str1,str);
    wprintf(L"str1:%ls  str:%ls          wstrwstr(str1,str)    %ls\n",str1,str,pc);

    i = wstrlen(str1);
        wprintf(L"str1:%ls                   wstrlen(str1)        %2d\n",str1,i);

    strcpy(chstr,"8-bit string");
    strtowstr(str,chstr,&size);
    wprintf(L"                                strtowstr(str,chstr)  %ls\n",str);
    wprintf(L"-----------------------------------------\n");
    wstrcpy(str, L"GREETINGS");
    wprintf(L"str:%ls  str1:%ls    ", str, str1);
    wmemcpy(str, str1, 4);
    str[wstrlen(str)] = '\0';
    wprintf(L"wmemcpy(str,str1,4)   str: %ls\n", str);
    wstrcpy(str, L"A very useful function.");
    wprintf(L"str[80]:%ls", str);
    wmemmove(str + 7, str + 2, 21);
    str[27] = '\0';
    wprintf(L" memmove(str+7,str+2,21) str: %ls\n", str);

    wstrcpy(str,str2);
    wprintf(L"str[80]: %ls str2: %ls ",str,str2);
    i = wmemcmp(str,str2,7);
        wprintf(L" wmemcmp(str,str2,7)   %ls\n",i?L"not equal":L"equal");
    wprintf(L"str[80]: %ls str2: %ls ",str,str2);
    i = wmemcmp(str,str2,20);
        wprintf(L" wmemcmp(str,str2,20)  %ls\n",i?L"not equal":L"equal");
    pc = wmemchr(str, L'c',size);
        wprintf(L"str:%ls                     wmemchr(str,L'c',size)c found at %d\n",str, pc - str + 1);
    wstrcpy(str,L"A very useful function.");
    wprintf(L"str[80]:%ls",str);
    pc = wmemset(str,L'-',7);
    wprintf(L" wmemset(str,L'-',7)   pc: %ls\n",pc);
    wprintf(L"-----------------------------------------\n");

    dbl = watof(L"1.234567890123456");
    #ifdef __LCC__
	   printf("dbl = watof(L\"1.234567890123456\")                     dbl: %16.15f\n",dbl);
    #else
    	wprintf(L"dbl = watof(L\"1.234567890123456\")                     dbl: %16.15f\n",dbl);
    #endif

	i = watoi(L"123456");
	wprintf(L"i   = watoi(L\"123456\")                                  i: %d\n",i);
	lint = watol(L"-2147483647");
	wprintf(L"sl  = watol(L\"-2147483647\")                            sl: %ld\n\n",lint);

    wstrcpy(numstr1,L"3.141593");
//	flt = wstrtof(numstr1, &endp);
	wstrcpy(numstr2,L"3.141592653589793");
	dbl = wstrtod(numstr2, &endp);
    wstrcpy(str,L"-2147483647");
	lint = wstrtol(str,&endp,10);
    wstrcpy(numstr3,L"-9223372036854775807");
	llint = wstrtoll(numstr3,&endp,10);
    wstrcpy(numstr4,L"4294967295");
	ulint = wstrtoul(numstr4,&endp,10);
    wstrcpy(numstr5,L"1844674407370955168");
	ullint = wstrtoull(numstr5,&endp,10);
    #ifdef __LCC__
        printf("str: \"%ls\"           flt = wstrtof(str,&endp)    flt: %9.7f\n",numstr1, flt);
        printf("str: \"%ls\"  dbl = wstrtod(str,&endp)    dbl: %16.15f\n",numstr2, dbl);
	    printf("str: \"%ls\"         sl = wstrtol(str,&endp,10)  sl: %ld\n",str, lint);
        printf("str: \"%ls\"ll = wstrtoll(str,&endp,10) ll: %lld\n",numstr3, llint);
    	printf("str: \"%ls\"          ul = wstrtoul(str,&endp,10) ul: %u\n",numstr4,ulint);
    	printf("str: \"%ls\"ull = wstrtoull(str,&endp,10)ull:%lld\n",numstr5,ullint);

    #else
        wprintf(L"str: \"%ls\"           flt = wstrtof(str,&endp)    flt: %9.7f\n",numstr1, flt);
        wprintf(L"str: \"%ls\"  dbl = wstrtod(str,&endp)    dbl: %16.15f\n",numstr2, dbl);
	    wprintf(L"str: \"%ls\"         sl = wstrtol(str,&endp,10)  sl: %ld\n",str, lint);
        wprintf(L"str: \"%ls\"ll = wstrtoll(str,&endp,10) ll: %lld\n",numstr3, llint);
    	wprintf(L"str: \"%ls\"          ul = wstrtoul(str,&endp,10) ul: %u\n",numstr4,ulint);
     	wprintf(L"str: \"%ls\"ull = wstrtoull(str,&endp,10)ull:%lld\n",numstr5,ullint);
    #endif

	pc = itowstr(12345,str,10);
	wprintf(L"                           pc = itowstr(12345,str,10) str: \"%ls\"            pc: \"%ls\"\n",str,pc);
	pc = ltowstr(-1234567890,str,10);
	wprintf(L"                    pc = ltowstr(-1234567890,str,10)  str: \"%ls\"      pc: \"%ls\"\n",str,pc);
	pc = ultowstr(1234567890,str,10);
	wprintf(L"                    pc = ultowstr(1234567890,str,10)  str: \"%ls\"       pc: \"%ls\"\n",str,pc);
//	pc = lltowstr(-123456789012345,str,10);
	wprintf(L"              pc = lltowstr(-123456789012345,str,10)  str: \"%ls\" pc: \"%ls\"\n",str,pc);
//	pc = ulltowstr(123456789012345,str,10);
	wprintf(L"              pc = ulltowstr(123456789012345,str,10)  str: \"%ls\"  pc: \"%ls\"\n",str,pc);

    wprintf(L"-----------------------------------------\n");
    wprintf(L"to_wstring(str,x)\n");
    ch = '\xFF';
    to_wstring(wstr, ch);
    wprintf(L"char           %ls         ", wstr);
    schar = -127;
    to_wstring(wstr, schar);
    wprintf(L"signed char    %ls        ", wstr);
    uchar = 255;
    to_wstring(wstr, uchar);
    wprintf(L"unsiged char   %ls\n", wstr);
    intg = -32767;
    to_wstring(wstr, intg);
    wprintf(L"int          \"%ls\"      ", wstr);
    sshrt = -32767;
    to_wstring(wstr, sshrt);
    wprintf(L"signed short  \"%ls\"     ", wstr);
    ushrt = 65535;
    to_wstring(wstr, ushrt);
    wprintf(L"unsiged short \"%ls\"\n", wstr);
    lint = -2147483647;
    to_wstring(wstr, lint);
    wprintf(L"signed long      \"%ls\"         ", wstr);
    ulint = 4294967295;
    to_wstring(wstr, ulint);
    wprintf(L"unsigned long      \"%ls\"\n", wstr);
    llint = 9223372036854775807LL;
    to_wstring(wstr, llint);
    wprintf(L"signed long long \"%ls\" ", wstr);
    ullint = 1844674407370955168;
    to_wstring(wstr, ullint);
    wprintf(L"unsigned long long \"%ls\"\n", wstr);

    flt = 3.141593f;
    to_wstring(wstr, flt);
    wprintf(L"float \"%ls\" ", wstr);
    dbl = 4 * atan(1);
    to_wstring(wstr, dbl);
    wprintf(L"double \"%ls\" ", wstr);
    ldbl = 3.1415926535897932384626L;
    to_wstring(wstr, ldbl);
    wprintf(L"long double \"%ls\"\n", wstr);
    wprintf(L"-----------------------------------------\n");
#if 0
#endif
    wprintf(L"\n(test)  alpha %lc\n", U_alpha);
    wprintf(L"\n(test)  alpha %lc\n", U_alpha);
    wprintf(L"Hi\n");
    wprintf(L"\nWARNINGS: %d\n", errornum);

#ifdef __WATCOMC__
    getchar();
#endif
    return 0;
}
void getIDs(void)
{
    wprintf(L"Compiler IDs: ");
#ifdef __CYGWIN__
    wprintf(L"CYGWIN ");
#endif
#ifdef __DMC__
    wprintf(L"DMC ");
#endif
#ifdef __LCC__
    wprintf(L"LCC ");
#endif
#ifdef __clang__
    wprintf(L"clang ");
#endif
#ifdef __linux__
    wprintf(L"Linux ");
#endif
#ifdef __MINGW32__
    wprintf(L"MINGW32 ");
#endif
#ifdef __MINGW64__
    wprintf(L"MINGW64 ");
#endif
#ifdef _MSC_VER
    wprintf(L"MSC_VER ");
#endif
#ifdef __MSYS2__
    wprintf(L"MSYS ");
#endif
#ifdef _MSYS_
    wprintf(L"MSYS ");
#endif
#ifdef __POCC__
    wprintf(L"Pelles_C ");
#endif
#ifdef __WATCOMC__
    wprintf(L"Open Watcom ");
#endif
#ifdef _WIN32
    wprintf(L"WIN32 ");
#endif

    wprintf(L"\n");
    return;
}

void colorchk(void)
{
    bluefontOn(); wprintf(L"blue    ");
    boldOn(); wprintf(L"BLUE\n");

    redfontOn(); wprintf(L"RED     ");
    boldOff(); wprintf(L"red\n");

    greenfontOn(); wprintf(L"green   ");
    boldOn(); wprintf(L"GREEN\n");

    yellowfontOn(); wprintf(L"YELLOW  ");
    boldOff(); wprintf(L"yellow\n");

    magentafontOn(); wprintf(L"magenta ");
    boldOn(); wprintf(L"MAGENTA\n");

    cyanfontOn(); wprintf(L"CYAN    ");
    boldOff(); wprintf(L"cyan\n");

    whitefontOn(); wprintf(L"white   ");
    boldOn(); wprintf(L"WHITE\n\n");

    boldOff();
    return;
}

void warnings(int errnum)
{
#ifdef __DMC__
    if (errnum == 0) {
        wprintf(L"** WARNING - Unicode display does not work! **\n");
        errornum++;
    }
    if (errnum == 1) {
        wprintf(L"** WARNING - Underline does not work! **\n");
        errornum++;
    }
#endif
#ifdef __LCC__
    if (errnum == 0) {
        wprintf(L"** WARNING - udispOff() does not work!! **\n");
        errornum++;
    }
    if (errnum == 1) {
        wprintf(L"** WARNING - Underline does not work! **\n");
        errornum++;
    }
#endif
#ifdef __POCC__
    if (errnum == 1) {
        wprintf(L"** WARNING - Underline does not work! **\n");
        errornum++;
    }
#endif
#ifdef __WATCOMC__
    if (errnum == 10) {
        wprintf(L"** WARNING! **\n");
        errornum++;
    }
#endif

    return;
}
