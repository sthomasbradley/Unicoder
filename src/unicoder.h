/***************************************************************************//**
 * \file unicoder.h
 * \brief  Unicoder definition header file
 *
 *         Linux/Windows 2020 COnsole VIDeo project (COVID-20)
 * \author  S.Thomas Bradley; email: sthomasbradley@gmail.com
 * \date    Nov 2021
 * \version 21.11
 *
 *   Macro definitions and inline functions used to display Unicpde in the
 *   Windows and Linux Terminal window.
 *
 ******************************************************************************/
/*   Unpublished work copyright (c) 2021 S. Thomas Bradley
 *   Software license: GNU GENERAL PUBLIC LICENSE, Version 3
 ******************************************************************************/

/*******************************************************************************
This is part of the Unicoder Linux/Windows 2020 Console Video project (COVID-20).
This is free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation,
either version 3 of the License, or (at your option) any later version.

It is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the GNU General Public License for more details.
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Tested with:                                              Unicode not working
//  _win32    __CYGWIN__  __LCC__  __linux__  Visual Studio      __DMC__
//    MinGW     Cygwin      lcc      Ubuntu     2017               dmc
//    MSYS                                      2019
//    MSYS2   __POCC__    __WATCOMC__
//    clang     Pelles C    Open Watcom
//
////////////////////////////////////////////////////////////////////////////////
#ifndef UNICODER_H_INCLUDED
#define UNICODER_H_INCLUDED

//#define EXTENDED_UNICODE 1  //To always use extended characters uncomment this.

#ifndef _UNICODE
    #define _UNICODE          // map to wide character functions
#endif

// Visual Studio may need these definitions to use macros without errors
// Must be defined before calling #includes.
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NON_CONFORMING_WCSTOK
// MinGW may need this definition to use __mingw_snwprintf()
#define __USE_MINGW_ANSI_STDIO 1

#ifdef __cplusplus
    #include <cstdarg>
    #include <cstdlib>
    #include <cctype>
    #include <cwchar>
    #include <iostream>
    #include <string>

    static size_t* __g_sz;       // for internal use
#else
    #include <ctype.h>
    #include <stdarg.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <wchar.h>
#endif // __cplusplus

////////////////////////////////////////////////////////////////////////////////
// Initialization
////////////////////////////////////////////////////////////////////////////////
//==============================================================================
// Windows 10 targets
//==============================================================================
#ifdef _WIN32
    #ifndef UNICODE
        #define UNICODE 1    // map windows.h to wide characters
    #endif
    #include <fcntl.h>
    #include <io.h>
    #include <windows.h>

    //--------------------------------------------------------------------------
    // Digital Mars C compiler (dmc)
    //--------------------------------------------------------------------------
    #ifdef __DMC__
        #include <disp.h>
        #include <locale.h>

        typedef int umode_t;
        /*----------------------------------------------------------------------
        | Digital Mars does not seem to support displaying Unicode characters
        | on the Terminal display. If you know how to do this please ]et me know.
        +---------------------------------------------------------------------*/
//		#define wprintf _cprintf             // Let preprocessor swap
        static inline umode_t udispOn(void){return 0;}
        #define scrnClr() disp_move(0,0);disp_eeop()
        #define formatOff() disp_setattr(DISP_NORMAL)
        #define udispOff(A) disp_setattr(A)
        #define utf8On() udispOn()

    //--------------------------------------------------------------------------
    // Little C compiler (lcc)
    //--------------------------------------------------------------------------
    #elif defined (__LCC__)
        #include <tcconio.h>
        #include <locale.h>

        typedef char* umode_t;

        static int __color = LIGHTGRAY;  // bad idea!

        wchar_t * endp;
        static inline umode_t udispOn(void)
        {
            umode_t pold = setlocale (LC_CTYPE, NULL);
            static umode_t psaved;
            psaved = (umode_t)malloc(sizeof(char)*(strlen(pold)+1));
            strcpy(psaved,pold);
            setlocale (LC_ALL, "");
            return psaved;
        }
        #define scrnClr() clrscr()
        #define formatOff() normvideo()
        #define udispOff(A) normvideo()
        #define utf8On() udispOn()

    //--------------------------------------------------------------------------
    // Minimal System 2 (MSYS2)
    //--------------------------------------------------------------------------
    #elif defined (__MSYS2__)
        #include <locale.h>

        typedef int umode_t;

        static inline umode_t udispOn(void)
        {
            DWORD dwMode = 0;
            GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &dwMode);
            dwMode |= 0x0004;
            SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), dwMode);
            return _setmode(_fileno(stdout),0x40000);
        }  // _O_U8TEXT

        #define scrnClr() system("clear")
        #define formatOff() wprintf(L"\x1b[m")
        #define udispOff(A) wprintf(L"")
        #define utf8On() udispOn()

    //--------------------------------------------------------------------------
    // Pelles C
    //--------------------------------------------------------------------------
    #elif defined (__POCC__)
        #define _CONIO_RETRO_COLORS
        #include <conio.h>
        #ifndef __STDC_VERSION__
            #define __STDC_VERSION__ 201112  // Claims to be c11 complient!
        #endif
        typedef int umode_t;

        static int __color = LIGHTGRAY;      // bad idea!

        #define wprintf _cwprintf            // Let preprocessor swap
        static inline umode_t udispOn(void) {return 0;} //Unicode is available
        #define scrnClr() _clrscr()
        #define formatOff() _textbackground(BLACK);_textcolor(LIGHTGRAY);__color = LIGHTGRAY
        #define udispOff(A) _cwprintf(L"")   // Can't disable Unicode
        #define utf8On() udispOn()

    //--------------------------------------------------------------------------
    // All other Windows targets (MINGW, MSYS, Clang, MSVC)
    //--------------------------------------------------------------------------
    #else // _WIN32, etc.
        typedef int umode_t;

        static inline umode_t udispOn(void)
        {
            DWORD dwMode = 0;
            GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &dwMode);
            dwMode |= 0x0004;
            SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), dwMode);
            return _setmode(_fileno(stdout),0x20000);
        }   // _O_U16TEXT

        #define scrnClr() system("cls")
        #define formatOff() wprintf(L"\x1b[m")
        #define udispOff(A) _setmode(_fileno(stdout),A)
        static inline umode_t utf8On(void)
        {
            DWORD dwMode = 0;
            GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &dwMode);
            dwMode |= 0x0004;
            SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), dwMode);
            return _setmode(_fileno(stdout),0x40000);
        }  // _O_U8TEXT
    #endif
#endif // _WINv32
//==============================================================================
// Open Watcom
//==============================================================================
#ifdef __WATCOMC__
	typedef int umode_t;

	static inline umode_t udispOn(void) {return 0;} //Unicode is available
	#define scrnClr() system("cls");
	#define formatOff() wprintf(L"\x1b[m")
	#define udispOff(A) wprintf(L"");               // Can't disable Unicode
	#define utf8On() udispOn()


#endif

//==============================================================================
// Cygwin platform
//==============================================================================
#ifdef __CYGWIN__
    #include <locale.h>

    typedef char* umode_t;

    static inline umode_t udispOn(void)
    {
        umode_t pold = setlocale (LC_CTYPE, NULL);
        static umode_t psaved;
        psaved = (umode_t)malloc(sizeof(char)*(strlen(pold)+1));
        strcpy(psaved,pold);
        setlocale (LC_ALL, "");
        return psaved;
    }

    #define scrnClr() system("clear")
    #define formatOff() wprintf(L"\x1b[0m")
    #define udispOff(A) setlocale(LC_CTYPE,A)
    #define utf8On() udispOn()
#endif // __CYGWIN__

//==============================================================================
// Linux platform
//==============================================================================
#ifdef __linux__
    #include <locale.h>

    typedef char* umode_t;

    static inline umode_t udispOn(void)
    {
        umode_t pold = setlocale (LC_CTYPE, NULL);
        static umode_t psaved;
        psaved = (umode_t)malloc(sizeof(char)*(strlen(pold)+1));
        strcpy(psaved,pold);
        setlocale(LC_CTYPE,"en_US.UTF-8");
        return psaved;
    }

    #define scrnClr() system("setterm -clear all")
    #define formatOff() system("setterm -default")
    #define udispOff(A) setlocale(LC_CTYPE,A)
    #define utf8On() udispOn()
#endif // __linux__

////////////////////////////////////////////////////////////////////////////////
// Display mode stuff
////////////////////////////////////////////////////////////////////////////////
//==============================================================================
// Windows/Cygwin fonts
//==============================================================================
#if defined (_WIN32) || defined (__CYGWIN__) || defined (__WATCOMC__)
    //--------------------------------------------------------------------------
    // Digital Mars C compiler (dmc)
    //--------------------------------------------------------------------------
    #ifdef __DMC__
        #define underlineOn() wprintf(L"")   // Doesn't work!
        #define underlineOff() wprintf(L"")
        #define reverseTextOn() disp_setattr(DISP_REVERSEVIDEO)
        #define reverseTextOff() disp_setattr(DISP_NORMAL)
        #define boldOn() disp_setattr(disp_getattr()|DISP_INTENSITY)
        #define boldOff() disp_setattr(disp_getattr()&0xF7)

        #define blackfontOn() disp_setattr((disp_getattr()&0xF8)|0x00)
        #define redfontOn() disp_setattr((disp_getattr()&0xF8)|0x04)
        #define greenfontOn() disp_setattr((disp_getattr()&0xF8)|0x02)
        #define yellowfontOn() disp_setattr((disp_getattr()&0xF8)|0x06)
        #define bluefontOn() disp_setattr((disp_getattr()&0xF8)|0x01)
        #define magentafontOn() disp_setattr((disp_getattr()&0xF8)|0x05)
        #define cyanfontOn() disp_setattr((disp_getattr()&0xF8)|0x03)
        #define whitefontOn() disp_setattr((disp_getattr()&0xF8)|0x07)
        #define blackbBkgdOn() disp_setattr((disp_getattr()&0x0F)|0x00)
        #define redbkgdOn() disp_setattr((disp_getattr()&0x0F)|0x40)
        #define greenbkgdOn() disp_setattr((disp_getattr()&0x0F)|0x20)
        #define yellowbkgdOn() disp_setattr((disp_getattr()&0x0F)|0x60)
        #define bluebkgdOn() disp_setattr((disp_getattr()&0x0F)|0x10)
        #define magentabkgdOn() disp_setattr((disp_getattr()&0x0F)|0x50)
        #define cyanbkgdOn() disp_setattr((disp_getattr()&0x0F)|0x30)
        #define whitebkgdOn() disp_setattr((disp_getattr()&0x0F)|0x70)

    //--------------------------------------------------------------------------
    // Little C compiler (lcc)
    //--------------------------------------------------------------------------
    #elif defined __LCC__
        #define underlineOn() wprintf(L"")  // Doesn't work!
        #define underlineOff() wprintf(L"")
        #define reverseTextOn() textbackground(__color);textcolor(__color^0X07)
        #define reverseTextOff() textbackground(BLACK);textcolor(LIGHTGRAY)
        #define boldOn() highvideo()
        #define boldOff() lowvideo()

        #define blackfontOn() textcolor(BLACK);__color = BLACK
        #define redfontOn() textcolor(RED);__color = RED
        #define greenfontOn() textcolor(GREEN);__color = GREEN
        #define yellowfontOn() textcolor(BROWN);__color = BROWN
        #define bluefontOn() textcolor(BLUE);__color = BLUE
        #define magentafontOn() textcolor(MAGENTA);__color = MAGENTA
        #define cyanfontOn() textcolor(CYAN);__color = CYAN
        #define whitefontOn() textcolor(LIGHTGRAY);__color = LIGHTGRAY
        #define blackbBkgdOn() textbackground(BLACK)
        #define redbkgdOn() textbackground(RED)
        #define greenbkgdOn() textbackground(GREEN)
        #define yellowbkgdOn() textbackground(BROWN)
        #define bluebkgdOn() textbackground(BLUE)
        #define magentabkgdOn() textbackground(MAGENTA)
        #define cyanbkgdOn() textbackground(CYAN)
        #define whitebkgdOn() textbackground(LIGHTGRAY)

    //--------------------------------------------------------------------------
    // Pelles C
    //--------------------------------------------------------------------------
     #elif defined __POCC__
        #define underlineOn() _cwprintf(L"")  // Doesn't work!
        #define underlineOff()  _cwprintf(L"")
        #define reverseTextOn() _textbackground(__color);_textcolor(__color^0X07)
        #define reverseTextOff() _textbackground(BLACK);_textcolor(LIGHTGRAY)
        #define boldOn() _textcolor(__color | 0x08)
        #define boldOff() _textcolor(__color)

        #define blackfontOn() _textcolor(BLACK);__color = BLACK
        #define redfontOn() _textcolor(RED);__color = RED
        #define greenfontOn() _textcolor(GREEN);__color = GREEN
        #define yellowfontOn() _textcolor(BROWN);__color = BROWN
        #define bluefontOn() _textcolor(BLUE);__color = BLUE
        #define magentafontOn() _textcolor(MAGENTA);__color = MAGENTA
        #define cyanfontOn() _textcolor(CYAN);__color = CYAN
        #define whitefontOn() _textcolor(LIGHTGRAY);__color = LIGHTGRAY
        #define blackbBkgdOn() _textbackground(BLACK);
        #define redbkgdOn() _textbackground(RED);
        #define greenbkgdOn() _textbackground(GREEN);
        #define yellowbkgdOn() _textbackground(BROWN);
        #define bluebkgdOn() _textbackground(BLUE);
        #define magentabkgdOn() _textbackground(MAGENTA)
        #define cyanbkgdOn() _textbackground(CYAN)
        #define whitebkgdOn() _textbackground(LIGHTGRAY)

    //--------------------------------------------------------------------------
    // All other Windows and Cygwin
    //--------------------------------------------------------------------------
    #else
        #define underlineOn() wprintf(L"\x1b[4m")
        #define underlineOff() wprintf(L"\x1b[24m")
        #define reverseTextOn() wprintf(L"\x1b[7m")
        #define reverseTextOff() wprintf(L"\x1b[27m")
        #define boldOn() wprintf(L"\x1b[1m")
        #define boldOff() wprintf(L"\x1b[22m")

        #define blackfontOn() wprintf(L"\x1b[30m")
        #define redfontOn() wprintf(L"\x1b[31m")
        #define greenfontOn() wprintf(L"\x1b[32m")
        #define yellowfontOn() wprintf(L"\x1b[33m")
        #define bluefontOn() wprintf(L"\x1b[34m")
        #define magentafontOn() wprintf(L"\x1b[35m")
        #define cyanfontOn() wprintf(L"\x1b[36m")
        #define whitefontOn() wprintf(L"\x1b[37m")
        #define blackbBkgdOn() wprintf(L"\x1b[40m")
        #define redbkgdOn() wprintf(L"\x1b[41m")
        #define greenbkgdOn() wprintf(L"\x1b[42m")
        #define yellowbkgdOn() wprintf(L"\x1b[43m")
        #define bluebkgdOn() wprintf(L"\x1b[44m")
        #define magentabkgdOn() wprintf(L"\x1b[45m")
        #define cyanbkgdOn() wprintf(L"\x1b[46m")
        #define whitebkgdOn() wprintf(L"\x1b[47m")
    #endif
#endif

//==============================================================================
// Linux fonts
//==============================================================================
#ifdef __linux__
//    #define inverseScrnOn() system("setterm -inversescreen on")
//    #define inverseScrnOff() system("setterm -inversescreen off")

    #define underlineOn() system("setterm -underline on")
    #define underlineOff() system("setterm -underline off")
    #define reverseTextOn() system("setterm -reverse on")
    #define reverseTextOff() system("setterm -reverse off")
    #define boldOn() system("setterm -bold on")
    #define boldOff() system("setterm -bold off")

    #define blackfontOn() system("setterm -foreground black")
    #define redfontOn() system("setterm -foreground red")
    #define greenfontOn() system("setterm -foreground green")
    #define yellowfontOn() system("setterm -foreground yellow")
    #define bluefontOn() system("setterm -foreground blue")
    #define magentafontOn() system("setterm -foreground magenta")
    #define cyanfontOn() system("setterm -foreground cyan")
    #define whitefontOn() system("setterm -foreground white")
    #define blackbBkgdOn() system("setterm -background black")
    #define redbkgdOn() system("setterm -background red")
    #define greenbkgdOn() system("setterm -background green")
    #define yellowbkgdOn() system("setterm -background yellow")
    #define bluebkgdOn() system("setterm -background blue")
    #define magentabkgdOn() system("setterm -background magenta")
    #define cyanbkgdOn() system("setterm -background cyan")
    #define whitebkgdOn() system("setterm -background white")

#endif // __linux__

////////////////////////////////////////////////////////////////////////////////
// Inline functions
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
// Drawing
//------------------------------------------------------------------------------
#ifdef __DMC__
    static inline void thinlineDraw(int cnt)
    {
        for (int i=0; i<cnt; i++)
            wprintf(L"%lc",'_');
        return;
    }
#elif defined (__WATCOMC__)
    static inline void thinlineDraw(int cnt)
    {
        int i;
        for (i=0; i<cnt; i++)
        {
            wprintf(L"%lc",0x2500);
        }
        return;
    }

#else
    static inline void thinlineDraw(int cnt)
    {
        for (int i=0; i<cnt; i++)
            wprintf(L"%lc",0x2500);
        return;
    }
#endif
static inline void thinlineDrawLn(int cnt)
    {thinlineDraw(cnt);wprintf(L"\n");return;}

#ifdef __LCC__
    static inline void boldlineDraw(int cnt)
    {
        for (int i=0; i<cnt; i++)
        {
            wprintf(L"%lc",0x25AC);
        }
        return;
    }
#elif defined (__DMC__)
    static inline void boldlineDraw(int cnt)
    {
        boldOn();
        for (int i=0; i<cnt; i++)
            wprintf(L"%lc",'_');
        boldOff();
        return;
    }
#elif defined __WATCOMC__
    static inline void boldlineDraw(int cnt)
    {
        int i;
        for (i=0; i<cnt; i++)
        {
            wprintf(L"%lc",0x25AC);
        }
        return;
    }
#else
    static inline void boldlineDraw(int cnt)
    {
        for (int i=0; i<cnt; i++)
            wprintf(L"%lc",0x2501);
        return;
    }
#endif
static inline void boldlineDrawLn(int cnt)
    {boldlineDraw(cnt);wprintf(L"\n");return;}

#ifdef __WATCOMC__
    static inline void dashlineDraw(int cnt)
    {
        int i;
        for (i=0; i<cnt; i++)
        {
            wprintf(L"%lc",'-');
        }
        return;
    }
#else
    static inline void dashlineDraw(int cnt)
    {
        for (int i=0; i<cnt; i++)
            wprintf(L"%lc",'-');
        return;
    }
#endif
static inline void dashlineDrawLn(int cnt)
    {dashlineDraw(cnt);wprintf(L"\n");return;}

#ifdef __DMC__
    static inline void dbllineDraw(int cnt)
    {
        for (int i=0; i<cnt; i++)
            wprintf(L"%lc",'=');
        return;
    }
#elif defined __WATCOMC__
    static inline void dbllineDraw(int cnt)
    {
        int i;
        for (i=0; i<cnt; i++)
        {
            wprintf(L"%lc",0x2550);
        }
        return;
    }
#else
    static inline void dbllineDraw(int cnt)
    {
        for (int i=0; i<cnt; i++)
            wprintf(L"%lc",0x2550);
        return;
    }
#endif
static inline void dbllineDrawLn(int cnt)
    {dbllineDraw(cnt);wprintf(L"\n");return;}

#ifdef __WATCOMC__
    static inline void __rowPDraw(const long arr[][2])
    {
        int i,k;
        for(i=1; i<((int)arr[0][1]+1); i++)
        {
            for (k=0; k<arr[i][1]; k++)
            {
                wprintf(L"%lc",(wchar_t)arr[i][0]);
            }
        }
        return;
    }
#else
    static inline void __rowPDraw(const long arr[][2])
    {
        for(int i=1; i<((int)arr[0][1]+1); i++)
            for (int k=0; k<arr[i][1]; k++)
                wprintf(L"%lc",(wchar_t)arr[i][0]);
        return;
    }
#endif

#ifdef __WATCOMC__
    static inline void __rowCDraw(const long arr[][2])
    {
        int k,i = 0;
        do {
            for (k=0; k<arr[i][1]; k++)
            {
                wprintf(L"%lc",(wchar_t)arr[i][0]);
            }
        } while (arr[++i][0]!=0);
        return;
    }
#else
    static inline void __rowCDraw(const long arr[][2])
    {
        int i = 0;
        do {
            for (int k=0; k<arr[i][1]; k++)
                wprintf(L"%lc",(wchar_t)arr[i][0]);
        } while (arr[++i][0]!=0);
        return;
    }
#endif

static inline void rowDraw(const long arr[][2])
{
    if (arr[0][0] == 0)
        __rowPDraw(arr);
    else
        __rowCDraw(arr);
    return;
}
static inline void rowDrawLn(const long arr[][2])
    {rowDraw(arr);wprintf(L"\n");return;}

////////////////////////////////////////////////////////////////////////////////
// wide character functions
////////////////////////////////////////////////////////////////////////////////
//==============================================================================
// Everyones platforms
//==============================================================================
#define UNICODER_VERSION L"20.06"
#define to_wchar_t(A) &A[0]
//------------------------------------------------------------------------------
// string.h-like
//------------------------------------------------------------------------------
#define wstrcmp(A,B) wcscmp(A,B)
#define wstrncmp(A,B,C) wcsncmp(A,B,C)
#define wstrchr(A,B) wcschr(A,B)
#define wstrrchr(A,B) wcsrchr(A,B)
#define wstrspn(A,B) wcsspn(A,B)
#define wstrcspn(A,B) wcscspn(A,B)
#define wstrpbrk(A,B) wcspbrk(A,B)
#define wstrwstr(A,B) wcsstr(A,B)
#define wstrlen(A) wcslen(A)

// Visual Studio or not
#ifdef _MSC_VER
    #if defined (__clang__)
        #define wstrcat(A,B) wcscat_s(A,sizeof(A)/sizeof(wchar_t),B)
        #define wstrncat(A,B,C) wcsncat_s(A,sizeof(A)/sizeof(wchar_t),B,C)
        #define wstrcpy(A,B) wcscpy_s(A,sizeof(A)/sizeof(wchar_t),B)
        #define wstrncpy(A,B,C) wcsncpy_s(A,sizeof(A)/sizeof(wchar_t),B,C)
        #define wstrtok(A,B,C) wcstok(A,B)
    #elif defined (__POCC__)
        #define wstrcat(A,B) wcscat(A,B)
        #define wstrncat(A,B,C) wcsncat(A,B,C)
        #define wstrcpy(A,B) wcscpy(A,B)
        #define wstrncpy(A,B,C) wcscpy(A,L"");wcsncat(A,B,C)
        #define wstrtok(A,B,C) wcstok(A,B,C)
    #else  // Avoids Visual Studio security errors
        #define wstrcat(A,B) wcscat_s(A,B)
        #define wstrncat(A,B,C) wcsncat_s(A,B,C)
        #define wstrcpy(A,B) wcscpy_s(A,sizeof(A)/sizeof(wchar_t),B)
        #define wstrncpy(A,B,C) wcsncpy_s(A,B,C)
        #define wstrtok(A,B,C) wcstok(A,B,C)
    #endif
#else
    #define wstrcat(A,B) wcscat(A,B)
    #define wstrncat(A,B,C) wcsncat(A,B,C)
    #define wstrcpy(A,B) wcscpy(A,B)
    #define wstrncpy(A,B,C) wcscpy(A,L"");wcsncat(A,B,C)
    #if defined (__MINGW32__) || defined (__MINGW64__) || defined (__LCC__)
        #define wstrtok(A,B,C) wcstok(A,B)
    #else
        #define wstrtok(A,B,C) wcstok(A,B,C)
    #endif  // __MINGW
#endif  // _MSC_VER

#if defined (__CYGWIN__) || defined (__linux__)
    #define strtowstr(A,B,C) mbstowcs(A,B,strlen(B));A[strlen(B)]=L'\0'
#elif defined (__LCC__) || defined (__DMC__) || defined (__WATCOMC__)
    #define strtowstr(A,B,C) mbstowcs(A,B,strlen(B));A[strlen(B)]=L'\0'
#else
    #define strtowstr(A,B,C) mbstowcs_s(C,A,strlen(B)+1,B,strlen(B))
#endif // __CYGWIN__

//------------------------------------------------------------------------------
// LCC doesn't define these functions so we had to create them.
//------------------------------------------------------------------------------
#ifdef __LCC__
    static inline wchar_t *wmemcpy(wchar_t *dest, const wchar_t *src, size_t cnt)
    {
        size_t i=0;
        while (i<cnt)
            dest[i] = src[i++];
        return dest;
    }
    static inline wchar_t *wmemmove(wchar_t *dest, const wchar_t *src, size_t cnt)
    {
        wchar_t temp[wcslen(src)+1];
        size_t i=0;
        wmemcpy(temp,src,wcslen(src));
        while (i<cnt)
            dest[i] = temp[i++];
        dest[i] = L'\0';
        return dest;
    }
    static inline wchar_t *wmemset(wchar_t *dest, wchar_t c, size_t cnt)
    {
        size_t i=0;
        while(i<cnt)
            dest[i++] = c;
        return dest;
    }
    static inline int wmemcmp(const wchar_t *ptr1, const wchar_t *ptr2, size_t cnt)
    {
        int bool = 0;
        int i = 0;
        while ((bool == 0)&&(i < cnt))
        {
           bool = wstrcmp(&ptr1[i],&ptr2[i]);
           i++;
        }
        return bool;
    }
#endif
//------------------------------------------------------------------------------
// Define the wide character function to_wstring().
//------------------------------------------------------------------------------
#ifndef __cplusplus
    #if (__STDC_VERSION__ >= 201112L) // Check C11 compliance
         #define umodetype(x) _Generic((x), \
            int: 0, \
            char *: 1)

        #define _wformat(x) _Generic((x), \
            char: L"%hhu", \
            signed char: L"%hhd", \
            unsigned char: L"%hhu", \
            signed short: L"%hd", \
            unsigned short: L"%hu", \
            signed int: L"%d", \
            unsigned int: L"%u", \
            long int: L"%ld", \
            unsigned long int: L"%lu", \
            long long int: L"%lld", \
            unsigned long long int: L"%llu", \
            float: L"%f", \
            double: L"%17.15f", \
            long double: L"%20.19Lf", \
            char *: "%s", \
            void *: "%p")

        #if defined (__MINGW32__) || defined (__MINGW64__)
            #define to_wstring(y,x) __mingw_snwprintf(y,sizeof(y)/sizeof(wchar_t),_wformat(x),x)
        #elif defined (__CYGWIN__) || defined (__linux__)
            #define to_wstring(y,x) swprintf(y,sizeof(y)/sizeof(wchar_t),_wformat(x),x)
        #elif defined(__POCC__)
            #define to_wstring(y,x) _snwprintf(y,sizeof(y)/sizeof(wchar_t),_wformat(x),x)
        #else
            #define to_wstring(y,x) _snwprintf(y,sizeof(y)/sizeof(wchar_t),_wformat(x),x)
        #endif  // c11 compiler
    #elif defined (__LCC__) || defined (__DMC__) || defined (__WATCOMC__)
        #define umodetype(x) -1
        #define to_wstring(y,x) wcscpy(y,L"N/A")      // not c11 compliant
    #else
        #define to_wstring(y,x) snwprintf(y,4,L"N/A") // not c11 compliant
    #endif  // End of C11 std

#else   // deal with C++
    #define umodetype(x) -1
    #define to_wstring(y,x) strtowstr(y,to_wchar_t(std::to_string(x)),__g_sz)
#endif  // !__cplusplus

//------------------------------------------------------------------------------
// stdlib.h-like
//------------------------------------------------------------------------------
#if defined (__CYGWIN__) || defined (__DMC__) || defined (__linux__)
    #define watof(A) wcstod(A,NULL)
    #define watoi(A) (int)wcstol(A,NULL,10)
    #define watol(A) wcstol(A,NULL,10)
#elif defined __LCC__
    #define watof(A) wcstod(A,&endp)
    #define watoi(A) (int)wcstol(A,NULL,10)
    #define watol(A) wcstol(A,NULL,10)
#else
    #define watof(A) _wtof(A)
    #define watoi(A) _wtoi(A)
    #define watol(A) _wtol(A)
#endif
#if defined (__CYGWIN__) || defined (__LCC__) || defined (__POCC__) || defined (__linux__)
    static inline wchar_t *itowstr(int n,wchar_t *str, int base)
    {swprintf(str,6,L"%d",n);return str;}
    static inline wchar_t *ltowstr(long n,wchar_t *str, int base)
    {swprintf(str,12,L"%ld",n);return str;}
    static inline wchar_t *ultowstr(unsigned long n,wchar_t *str, int base)
    {swprintf(str,12,L"%lu",n);return str;}
    static inline wchar_t *lltowstr(long long n,wchar_t *str, int base)
    {swprintf(str,20,L"%lld",n);return str;}
    static inline wchar_t *ulltowstr(unsigned long n,wchar_t *str, int base)
    {swprintf(str,20,L"%llu",n);return str;}
#else
    #define itowstr(A,B,C) _itow(A,B,C)
    #define ltowstr(A,B,C) _ltow(A,B,C)
    #define ultowstr(A,B,C) _ultow(A,B,C)

    #ifdef __DMC__
        #define lltowstr(A,B,C) wcscpy(B,L"N/A")
        #define ulltowstr(A,B,C) wcscpy(B,L"N/A")
    #else
        #define lltowstr(A,B,C) _i64tow(A,B,C)
        #define ulltowstr(A,B,C) _ui64tow(A,B,C)
    #endif

#endif // __CYGWIN__

#ifdef __LCC__
    #define wstrtof(A,B) wcstod(A,B)
    static inline long long wstrtoll(const wchar_t *str,wchar_t **endp, int base)
    {
        return -1;
    }
    static inline long long wstrtoull(const wchar_t *str,wchar_t **endp, int base)
    {
        return -1;
    }
#else
    #ifdef __DMC__
	    #define wstrtof(A,B) wcstod(A,B)
	#else
        #define wstrtof(A,B) wcstof(A,B)
	#endif
    #define wstrtoll(A,B,C) wcstoll(A,B,C)
    #define wstrtoull(A,B,C) wcstoull(A,B,C)
#endif
#define wstrtod(A,B) wcstod(A,B)
#define wstrtold(A,B) wcsstrtold(A,B)
#define wstrtol(A,B,C) wcstol(A,B,C)

#define wstrtoul(A,B,C) wcstoul(A,B,C)
//
////////////////////////////////////////////////////////////////////////////////
// Unicode default character set
////////////////////////////////////////////////////////////////////////////////
//
#define U_NSarrowbar    0x21A8
//------------------------------------------------------------------------------
// Greek
//------------------------------------------------------------------------------
// lower case greek
#define U_alpha         0x03B1
#define U_beta          0x03B2
#define U_gamma         0x03B3
#define U_delta         0x03B4
#define U_epsilon       0x03B5
#define U_theta         0x03B8
#define U_iota          0x03B9
#define U_rho           0X03C1
#define U_upsilon       0x03C5
#define U_phi           0x03C6
#define U_chi           0x03C7
#define U_psi           0x03C8
//
#define U_varbeta       0x03D0
#define U_vargamma      0x0263
#define U_varepsilon    0x03F5
#define U_vartheta      0x03D1
#define U_varsigma      0x03DB
#define U_varupsilon    0x03D2
#define U_varphi        0x03D5
#define U_varkoppa      0x03DF
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Superscript lower case greek
#define U_supalpha      0x1D45
#define U_supbeta       0x1D5D
#define U_supgamma      0x1D5E
#define U_supdelta      0x1D5F
#define U_supepsilon    0x1D4B
#define U_suptheta      0x1DBF
#define U_supiota       0x1DA5
#define U_supupsilon    0x1DB9
#define U_supphi        0x1DB2
#define U_supchi        0x1D61
#define U_suppsi        0x1D60
#define U_varsuptheta   0x1DB1
//
#define U_varsupphi     0x1DB2
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Subscript lower case Greek
#define U_subbeta       0x1D66
#define U_subgamma      0x1D67
#define U_subrho        0x1D68
#define U_subchi        0x1D6A
#define U_subpsi        0x1D69
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Upper case Greek
#define U_Alpha         0x0391
#define U_Beta          0x0392
#define U_Gamma         0x0393
#define U_Delta         0x0394
#define U_Epsilon       0x0395
#define U_Theta         0x0398
#define U_Iota          0x0399
#define U_Rho           0X03A1
#define U_Upsilon       0x03A5
#define U_Phi           0x03A6
#define U_Chi           0x03A7
#define U_Psi           0x03A8
//
#define U_VarOmega      0x0460
#define U_VarSigma      0x03DA
#define U_VarUpsilon    0x03D2
#define U_varGamma      0x0194
#define U_VarKoppa      0x03DE
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// More lower case greek
#define U_zeta          0x03B6
#define U_eta           0x03B7
#define U_kappa         0x03BA
#define U_lambda        0x03BB
#define U_mu            0x03BC
#define U_nu            0x03BD
#define U_xi            0x03BE
#define U_omicron       0x03BF
#define U_pi            0x03C0
#define U_sigma         0x03C3
#define U_tau           0x03C4
#define U_omega         0x03C9
#define U_kai           0x03D7
#define U_koppa         0x03D9
#define U_digamma       0x03DD
#define U_sampi         0x03E1
#define U_heta          0x0371
//
#define U_finalsigma    0x03C2
#define U_baromega      0x03D6
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// More upper case greek
#define U_Zeta          0x0396
#define U_Eta           0x0397
#define U_Kappa         0x039A
#define U_Lambda        0x039B
#define U_Mu            0x039C
#define U_Nu            0x039D
#define U_Xi            0x039E
#define U_Omicron       0x039F
#define U_Pi            0x03A0
#define U_Sigma         0x03A3
#define U_Tau           0x03A4
#define U_Omega         0x03A9
#define U_Kai           0x03CF
#define U_Koppa         0x03D8
#define U_Digamma       0x03DC
#define U_Sampi         0x03E0
#define U_Heta          0x0370
#define U_tildeomega    0x1FF6
//------------------------------------------------------------------------------
// Modified Greek
//------------------------------------------------------------------------------
#define U_theta2nd      0x04EB
#define U_iota2nd       0x03CA
#define U_upsilon2nd    0x03CB
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_baralpha      0x1FB1
#define U_barupsilon    0x1FE1
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_alphatilde    0x1FB6
#define U_iotatilde     0x1FD6
#define U_upsilontilde  0x1FE6
#define U_omegatilde    0x1FF6
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_Theta2nd      0x04EA
#define U_Iota2nd       0x03AA
#define U_Upsilon2nd    0x03AB
//
//------------------------------------------------------------------------------
// Mathematical symbols
//------------------------------------------------------------------------------
#define U_minussign     0x2212
#define U_pm            0x00B1
#define U_equiv         0x2261
#define U_neq           0x2260
#define U_approx        0x2248
#define U_crossprod     0x00D7
#define U_times         0x00D7
#define U_div           0x00F7
#define U_less          0x2039
#define U_greater       0x203A
#define U_prime         0x2032
#define U_transpose     0x0372
#define U_estimate      0x212E
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_supminus      0x207B
#define U_supplus       0x207A
#define U_supequal      0x207C
#define U_supintgl      0x1DB4
#define U_dotprod       0x2219
#define U_cdot          0x00B7
#define U_divslash      0x2215
#define U_leq           0x2264
#define U_geq           0x2265
#define U_diprime       0x2033
#define U_rightangle    0x221F
#define U_eulersnum     0x212E
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_subminus      0x208B
#define U_subplus       0x208A
#define U_subequal      0x208C
#define U_squared       U_sup2
#define U_cubed         U_sup3
#define U_ordinal       0x00AA
#define U_ll            0x00AB
#define U_gg            0x00BB
#define U_triprime      0x2034
#define U_imaginary     0x0269
#define U_masordin      0x00BA
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_partial       0x2202
#define U_sum           0x2211
#define U_prod          0x220F
#define U_intgl         0x222B
#define U_sqrt          0x221A
#define U_increment     0x2206
#define U_lnell         0x2113
#define U_esh           0x0285
#define U_neg           0x00AC
#define U_belongsto     0x03F5
#define U_intgltop      0x2320
#define U_lpartop       0x256D
#define U_rpartop       0x256E
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_infty         0x221E
#define U_emptyset      0x00D8
#define U_exists        0x2C7B
#define U_dagger        0x2020
#define U_dbldagr       0x2021
#define U_ldots         0x2026
#define U_cap           0x2229
#define U_forall        0x2C6F
#define U_circldot      0x0298
#define U_revneg        0x2310
#define U_contains      0x03F6
#define U_intglbtm      0x2321
#define U_lparbtm       0x2570
#define U_rparbtm       0x256F
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Combining
#define U_comboseconds  0x030E
#define U_combo1stderiv 0x0307
#define U_combo2ndderiv 0x0308
#define U_combohat      0x0302
#define U_combotilde    0x0303
#define U_combobar      0x0305
#define U_comboxabove   0x033D
#define U_comboxbelow   0x0353
#define U_combounderline 0x035F
#define U_combolowinfty 0x035A
#define U_combolowplus  0x031F
#define U_combolowminus 0x0320
#define U_combolowaster 0x0359
//
//------------------------------------------------------------------------------
// Numbers
//------------------------------------------------------------------------------
// Superscript numbers
#define U_sup0          0x2070
#define U_sup1          0x00B9
#define U_sup2          0x00B2
#define U_sup3          0x00B3
#define U_sup4          0x2074
#define U_sup5          0x2075
#define U_sup6          0x2076
#define U_sup7          0x2077
#define U_sup8          0x2078
#define U_sup9          0x2079
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Subscript numbers
#define U_sub0          0x2080
#define U_sub1          0x2081
#define U_sub2          0x2082
#define U_sub3          0x2083
#define U_sub4          0x2084
#define U_sub5          0x2085
#define U_sub6          0x2086
#define U_sub7          0x2087
#define U_sub8          0x2088
#define U_sub9          0x2089
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Lite circled
#define U_ltcircle0     0x24EA
#define U_ltcircle1     0x2460
#define U_ltcircle2     0x2461
#define U_ltcircle3     0x2462
#define U_ltcircle4     0x2463
#define U_ltcircle5     0x2464
#define U_ltcircle6     0x2465
#define U_ltcircle7     0x2466
#define U_ltcircle8     0x2467
#define U_ltcircle9     0x2468
#define U_ltcircle10    0x2469
#define U_ltcircle11    0x246A
#define U_ltcircle12    0x246B
#define U_ltcircle13    0x246C
#define U_ltcircle14    0x246D
#define U_ltcircle15    0x246E
#define U_ltcircle16    0x246F
#define U_ltcircle17    0x2470
#define U_ltcircle18    0x2471
#define U_ltcircle19    0x2472
#define U_ltcircle20    0x2473
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Dark circled
#define U_dkcircle0     0x24FF
#define U_dkcircle1     0x2776
#define U_dkcircle2     0x2777
#define U_dkcircle3     0x2778
#define U_dkcircle4     0x2779
#define U_dkcircle5     0x277A
#define U_dkcircle6     0x277B
#define U_dkcircle7     0x277C
#define U_dkcircle8     0x277D
#define U_dkcircle9     0x277E
#define U_dkcircle10    0x277F
#define U_dkcircle11    0x24EB
#define U_dkcircle12    0x24EC
#define U_dkcircle13    0x24ED
#define U_dkcircle14    0x24EE
#define U_dkcircle15    0x24EF
#define U_dkcircle16    0x24F0
#define U_dkcircle17    0x24F1
#define U_dkcircle18    0x24F2
#define U_dkcircle19    0x24F3
#define U_dkcircle20    0x24F4
//
//------------------------------------------------------------------------------
// Fractions
//------------------------------------------------------------------------------
#define U_oneeighth     0x215B     // 1/8
#define U_onesixth      0x2159     // 1/6
#define U_onefifth      0x2155     // 1/5
#define U_onefourth     0x00BC     // 1/4
#define U_onethird      0x2153     // 1/3
#define U_onehalf       0x00BD     // 1/2
#define U_twofifths     0x2156     // 2/5
#define U_twothirds     0x2154     // 2/3
#define U_threeeighths  0x215C     // 3/8
#define U_threefifths   0x2157     // 3/5
#define U_threequarter  0x00BE     // 3/4
#define U_fourfifths    0x2158     // 4/5
#define U_fiveeighths   0x215D     // 5/8
#define U_fivesixths    0x215A     // 5/6
#define U_seveneighths  0x215E     // 7/8
//
//------------------------------------------------------------------------------
// Symbols
//------------------------------------------------------------------------------
// Units
#define U_Angstrom      0x00C5
#define U_Degree        0x00B0
#define U_Micro         0x00B5
#define U_Mhos          0x01B1
#define U_Ohms          0x2126
#define U_Wavelen       0x019B
#define U_RedPlanck     0x0127
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Symbols
#define U_careof        0x2105
#define U_copyright     0x00A9
#define U_numero        0x2116
#define U_permile       0x2030
#define U_registered    0x00AE
#define U_soundrecd     0x2117
#define U_trademark     0x2122
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Arrows
#define U_Warrow        0x2190
#define U_Earrow        0x2192
#define U_Narrow        0x2191
#define U_Sarrow        0x2193
#define U_WEarrow       0x2194
#define U_NSarrow       0x2195
#define U_uphead        0x02C4
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_subleftarw    0x02FF
#define U_combsubrgtarw 0x0362
#define U_supNarrow     0xA71B
#define U_supSarrow     0xA71C
#define U_combosublrarw 0x034D
#define U_NSarrowandbar 0x21A8
#define U_downhead      0x02C5
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_lefthead      0x02C2
#define U_rgthead       0x02C3
#define U_subuphead     0x02F0
#define U_subdownhead   0x02EF
#define U_sublefthead   0x02F1
#define U_subrgthead    0x02F2
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Glyphs
#define U_lthappy       0x263A
#define U_dkhappy       0x263B
#define U_dkstar        0x2736
#define U_female        0x2640
#define U_male          0x2642
#define U_sunshine      0x263C
#define U_house         0x2302
//
//------------------------------------------------------------------------------
// Geometric shapes
//------------------------------------------------------------------------------
// Black Objects
#define U_blacksqr      0x25A0
#define U_blackcircle   0x25CF
#define U_blacksqrlow   0x2584
#define U_blackblock    0x2588
#define U_blktriangle   0x25B2
#define U_blkdwnarw     0x25BC
#define U_blkrgtarw     0x25BA
#define U_blklftarw     0x25C4
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_blacksqrsm    0x25AA
#define U_inversecircle 0x25D9
#define U_blacksqrhigh  0x2580
#define U_darkblock     0x2593
#define U_blktrianglesm 0x25B4
#define U_blkdwnarwsm   0x25BE
#define U_blkrgtarwsm   0x25B8
#define U_blklftarwsm   0x25C2
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// White Objects
#define U_box           0x25A1
#define U_circle        0x25CB
#define U_swirl         0x058D
#define U_mediumblock   0x2592
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_boxsm         0x25AB
#define U_litecircle    0x25CC
#define U_lozenge       0x25CA
#define U_liteblock     0x2591
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Cards
#define U_spades        0X2660
#define U_clubs         0x2663
#define U_diamonds      0x2666
#define U_hearts        0x2665
// Music
#define U_8thnote       0x266A
#define U_beamed8th     0x266B
#define U_sharp         0x266F
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_blackrect     0x25AC
//
//------------------------------------------------------------------------------
// Characters
//------------------------------------------------------------------------------
// Typographic
#define U_section       0x00A7
#define U_paragraph     0x00B6
#define U_tie           0x0361
#define U_bullet        0x2022
#define U_litebullet    0x25E6
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Dots
#define U_lowdot        0x2024
#define U_highdot       0x0387
#define U_2vtdots       0xA789
#define U_4vtdots       0x205E
#define U_diaeresis     0x00A8
#define U_ellipsis      0x2026
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Punctuation
#define U_leftquot      0x201C
#define U_rgtquot       0x201D
#define U_lowquot       0x201E
#define U_reversed      0x201F
#define U_caron         0x02C7
#define U_cedilla       0x00B8
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_leftsnglquot  0x2018
#define U_rgtsnglquot   0x2019
#define U_lowsnglquot   0x201A
#define U_revsnglquot   0x201B
#define U_acute         0x00B4
#define U_obliquehyphen 0x2E17
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_supopen       0x207D
#define U_supclose      0x207E
#define U_suptilde      0x02DC
#define U_supinvtexclm  0xA71E
#define U_invertexclm   0x00A1
#define U_invertquestn  0x00BF
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_subopen       0x208D
#define U_subclose      0x208E
#define U_subtilde      0x02F7
#define U_supexclm      0xA71D
#define U_dblexclm      0x203C
#define U_exclmsm       0xA71F
//
//------------------------------------------------------------------------------
// Modified Latin
//------------------------------------------------------------------------------
#define U_a1st          0x0227
#define U_b1st          0x1E03
#define U_c1st          0x010B
#define U_d1st          0x1E0B
#define U_e1st          0x0117
#define U_f1st          0x1E1F
#define U_g1st          0x0121
#define U_h1st          0x1E23
#define U_i1st          0x0456
#define U_j1st          0x0458
#define U_m1st          0x1E41
#define U_n1st          0x1E45
#define U_o1st          0x022F
#define U_p1st          0x1E57
#define U_r1st          0x1E59
#define U_s1st          0x1E61
#define U_t1st          0x1E6B
#define U_w1st          0x1E87
#define U_x1st          0x1E8B
#define U_y1st          0x1E8F
#define U_z1st          0x017C
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_a2nd          0x00E4
#define U_e2nd          0x00EB
#define U_h2nd          0x1E27
#define U_i2nd          0x00EF
#define U_o2nd          0x00F6
#define U_t2nd          0x1E97
#define U_u2nd          0x00FC
#define U_w2nd          0x1E85
#define U_x2nd          0x1E8D
#define U_y2nd          0x00FF
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_ahat          0x00E2
#define U_chat          0x0109
#define U_ehat          0x00EA
#define U_ghat          0x011D
#define U_hhat          0x0125
#define U_ihat          0x00EE
#define U_jhat          0x0135
#define U_ohat          0x00F4
#define U_shat          0x015D
#define U_uhat          0x00FB
#define U_what          0x0175
#define U_yhat          0x0177
#define U_zhat          0x1E91
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_abar          0x0101
#define U_ebar          0x0113
#define U_gbar          0x1E21
#define U_ibar          0x012B
#define U_obar          0x014D
#define U_ubar          0x016B
#define U_ybar          0x0233
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_atilde        0x00E3
#define U_etilde        0x1EBD
#define U_itilde        0x0129
#define U_ntilde        0x00F1
#define U_otilde        0x00F5
#define U_utilde        0x0169
#define U_vtilde        0x1E7D
#define U_ytilde        0x1EF9
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_A1ST          0x0226
#define U_B1ST          0x1E02
#define U_C1ST          0x010A
#define U_D1ST          0x1E0A
#define U_E1ST          0x0116
#define U_F1ST          0x1E1E
#define U_G1ST          0x0120
#define U_H1ST          0x1E22
#define U_I1ST          0x0130
#define U_M1ST          0x1E40
#define U_N1ST          0x1E44
#define U_O1ST          0x022E
#define U_P1ST          0x1E56
#define U_R1ST          0x1E58
#define U_S1ST          0x1E60
#define U_T1ST          0x1E6A
#define U_W1ST          0x1E86
#define U_X1ST          0x1E8A
#define U_Y1ST          0x1E8E
#define U_Z1ST          0x017B
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_A2ND          0x00C4
#define U_E2ND          0x00CB
#define U_H2ND          0x1E26
#define U_I2ND          0x00CF
#define U_O2ND          0x00D6
#define U_U2ND          0x00DC
#define U_W2ND          0x1E84
#define U_X2ND          0x1E8C
#define U_Y2ND          0x0178
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_Ahat          0x00C2
#define U_Chat          0x0108
#define U_Ehat          0x00CA
#define U_Ghat          0x011C
#define U_Hhat          0x0124
#define U_Ihat          0x00CE
#define U_Jhat          0x0134
#define U_Ohat          0x00D4
#define U_Shat          0x015C
#define U_Uhat          0x00DB
#define U_What          0x0174
#define U_Yhat          0x0176
#define U_Zhat          0x1E90
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_Abar          0x0100
#define U_Ebar          0x0112
#define U_Gbar          0x1E20
#define U_Ibar          0x012A
#define U_Obar          0x014C
#define U_Ubar          0x016A
#define U_Ybar          0x0232
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_Atilde        0x00C3
#define U_Etilde        0x1EBC
#define U_Itilde        0x0128
#define U_Ntilde        0x00D1
#define U_Otilde        0x00D5
#define U_Utilde        0x0168
#define U_Vtilde        0x1E7C
#define U_Ytilde        0x1Ef8
//
//------------------------------------------------------------------------------
// Latin Modifiers Lower case
//------------------------------------------------------------------------------
// Superscript lower case Latin
#define U_supa          0x1D43
#define U_supb          0x1D47
#define U_supc          0x1D9C
#define U_supd          0x1D48
#define U_supe          0x1D49
#define U_supf          0x1DA0
#define U_supg          0x1D4D
#define U_suph          0x02B0
#define U_supi          0x1DA4
#define U_supj          0x02B2
#define U_supk          0x1D4F
#define U_supl          0x02E1
#define U_supm          0x1D50
#define U_supn          0x207F
#define U_supo          0x1D52
#define U_supp          0x1D56
#define U_supr          0x02B3
#define U_sups          0x02E2
#define U_supt          0x1D57
#define U_supu          0x1D58
#define U_supv          0x1D5B
#define U_supw          0x02B7
#define U_supx          0x02E3
#define U_supy          0x02B8
#define U_supz          0x1DBB
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Subscript lower case latin
#define U_suba          0x2090
#define U_sube          0x2091
#define U_subi          0x1D62
#define U_subj          0x2C7C
#define U_subo          0x2092
#define U_subr          0x1D63
#define U_subu          0x1D64
#define U_subv          0x1D65
#define U_subx          0x2093

#define U_dli           0x0131
#define U_dlj           0x0237
//
//------------------------------------------------------------------------------
// Latin Modifiers Upper case
//------------------------------------------------------------------------------
// Superscript
#define U_supA          0x1D2C
#define U_supB          0x1D2E
#define U_supD          0x1D30
#define U_supE          0x1D31
#define U_supG          0x1D33
#define U_supH          0x1D34
#define U_supI          0x1D35
#define U_supJ          0x1D36
#define U_supK          0x1D37
#define U_supL          0x1D38
#define U_supM          0x1D39
#define U_supN          0x1D3A
#define U_supO          0x1D3C
#define U_supP          0x1D3E
#define U_supR          0x1D3F
#define U_supT          0x1D40
#define U_supU          0x1D41
#define U_supV          0x2C7D
#define U_supW          0x1D42
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_varsupI       0x1DA6
#define U_varsupL       0x1DAB
#define U_varsupN       0x1DB0
#define U_varsupU       0x1DB8
//
//------------------------------------------------------------------------------
// Combining Latin Lower case
//------------------------------------------------------------------------------
#define combosupa       0x0363
#define combosupc       0x0368
#define combosupd       0x0369
#define combosupe       0x0364
#define combosuph       0x036A
#define combosupi       0x0365
#define combosupm       0x036B
#define combosupo       0x0366
#define combosupr       0x036C
#define combosupt       0x036D
#define combosupu       0x0367
#define combosupv       0x036E
#define combosupx       v0x036F
//
//------------------------------------------------------------------------------
// Latin small capital
//------------------------------------------------------------------------------
#define U_smallcapA     0x1D00
#define U_smallcapB     0x0299
#define U_smallcapC     0x1D04
#define U_smallcapD     0x1D05
#define U_smallcapE     0x1D07

#define U_smallcapG     0x0262
#define U_smallcapH     0x029C
#define U_smallcapI     0x026A
#define U_smallcapJ     0x1D0A
#define U_smallcapK     0x1D0B
#define U_smallcapL     0x029F
#define U_smallcapM     0x1D0D
#define U_smallcapN     0x0274
#define U_smallcapO     0x1D0F
#define U_smallcapP     0x1D18

#define U_smallcapR     0x0280

#define U_smallcapT     0x1D1B
#define U_smallcapU     0x1D1C
#define U_smallcapV     0x1D20
#define U_smallcapW     0x1D21

#define U_smallcapX     U_crossprod
#define U_smallcapY     0x028F
#define U_smallcapZ     0x1D22
//
//------------------------------------------------------------------------------
// Line Segments
//------------------------------------------------------------------------------
#define U_vtdash        0x2577
#define U_vtb           0x2575
#define U_vtsolid       0x2502
#define U_vtdashs       0x254E
#define U_vte           0x2506
#define U_vtf           0x250A
#define U_vtg           0x257D
#define U_vth           0x257F
#define U_vti           0x2579
#define U_vtj           0x257B
#define U_vtbold        0x2503
#define U_vtl           0x254F
#define U_vtm           0x2507
#define U_vtn           0x250B
#define U_vtdbl         0x2551
#define U_fwd           0x2571
#define U_bwd           0x2572
#define U_cross         0x2573
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_hzdash        0x2574
#define U_hzb           0x2576
#define U_hzsolid       0x2500
#define U_hzdashs       0x254C
#define U_hze           0x2504
#define U_hzdots        0x2508
#define U_hzg           0x257C
#define U_hzh           0x257E
#define U_hzi           0x2578
#define U_hzj           0x257A
#define U_hzbold        0x2501
#define U_hzl           0x254D
#define U_hzm           0x2505
#define U_hzn           0x2509
#define U_hzdbl         0x2550
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_tla           0x250c
#define U_mla           0x251C
#define U_bla           0x2514
#define U_tlb           0x250d
#define U_mlb           0x251D
#define U_blb           0x2515
#define U_tlc           0x250E
#define U_mlc           0x2520
#define U_blc           0x2516
#define U_tld           0x250f
#define U_mld           0x2523
#define U_bld           0x2517
#define U_tle           0x2552
#define U_mle           0x255E
#define U_ble           0x2558
#define U_tlf           0x2553
#define U_mlf           0x255F
#define U_blf           0x2559
#define U_tldbl         0x2554
#define U_mldbl         0x2560
#define U_bldbl         0x255A
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_tma           0x252C
#define U_mma           0x253C
#define U_bma           0x2534
#define U_tmb           0x252F
#define U_mmb           0x253F
#define U_bmb           0x2537
#define U_tmc           0x2530
#define U_mmc           0x2542
#define U_bmc           0x2538
#define U_tmd           0x2533
#define U_mmd           0x254B
#define U_bmd           0x253B
#define U_tme           0x2564
#define U_mme           0x256A
#define U_bme           0x2567
#define U_tmf           0x2565
#define U_mmf           0x256B
#define U_bmf           0x2568
#define U_tmdbl         0x2566
#define U_mmdbl         0x256C
#define U_bmdbl         0x2569
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_tra           0x2510
#define U_mra           0x2524
#define U_bra           0x2518
#define U_trb           0x2511
#define U_mrb           0x2525
#define U_brb           0x2519
#define U_trc           0x2512
#define U_mrc           0x2528
#define U_brc           0x251A
#define U_trd           0x2513
#define U_mrd           0x252B
#define U_brd           0x251B
#define U_tre           0x2555
#define U_mre           0x2561
#define U_bre           0x255B
#define U_trf           0x2556
#define U_mrf           0x2562
#define U_brf           0x255C
#define U_trdbl         0x2557
#define U_mrdbl         0x2563
#define U_brdbl         0x255D
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_tmh           0x252E
#define U_tmi           0x2532
#define U_bmh           0x2536
#define U_bmi           0x253A
#define U_mlh           0x251F
#define U_mli           0x2522
#define U_mlj           0x251E
#define U_mlk           0x2521
#define U_mmh           0x253E
#define U_mmi           0x2546
#define U_mmj           0x2544
#define U_mmk           0x254A
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_mml           0x2541
#define U_mmm           0x2548
#define U_mmn           0x2547
#define U_mmo           0x2540
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_tmj           0x252D
#define U_tmk           0X2531
#define U_bmj           0x2535
#define U_bmk           0x2539
#define U_mrh           0x2527
#define U_mri           0x252A
#define U_mrj           0x2526
#define U_mrk           0x2529
#define U_mmp           0x253D
#define U_mmq           0x2545
#define U_mmr           0x2543
#define U_mms           0x2549
//
//------------------------------------------------------------------------------
// Currency
//------------------------------------------------------------------------------
#define U_austral       0x20B3
#define U_baht          0x0E3F
#define U_bitcoin       0x20BF
#define U_cent          0x00A2
#define U_currency      0x00A4
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_dong          0x20AB
#define U_drachma       0x20AF
#define U_euro          0x20AC
#define U_franc         0x20A3
#define U_guarani       0x20B2
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_hryvnia       0x20B4
#define U_indiarupee    0x20B9
#define U_kip           0x20AD
#define U_lira          0x20A4
#define U_livre         0x20B6
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_mill          0x20A5
#define U_naria         0x20A6
#define U_peseta        0x20A7
#define U_peso          0x20B1
#define U_pfennig       0x20B0
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_pound         0x00A3
#define U_ruble         0x20BD
#define U_rupee         0x20A8
#define U_shekel        0x20AA
#define U_spesmilo      0x20B7
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_tenge         0x20B8
#define U_tugrik        0x20AE
#define U_turkeylira    0x20BA
#define U_won           0x20A9
#define U_yen           0x00A5
//
//
////////////////////////////////////////////////////////////////////////////////
// Extended Unicode character set
////////////////////////////////////////////////////////////////////////////////
#ifdef EXTENDED_UNICODE
#undef U_Angstrom
#undef U_belongsto
#undef U_contains
#undef U_emptyset
#undef U_exists
#undef U_forall
#undef U_Planck
//
//------------------------------------------------------------------------------
// Modified Greek & Latin
//------------------------------------------------------------------------------
#define U_barAlpha      0x1FB9
#define U_barIoto       0x1FD9
#define U_barUpsilon    0x1FE9

#define U_bariota       0x1FD1
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_alphabar      0x2376
#define U_epsilonbar    0x2377
#define U_iotabar       0x2378
#define U_omegabar      0x2379
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_bbar          0x0180
#define U_dbar          0x0111
//
//------------------------------------------------------------------------------
// Relational Operators
//------------------------------------------------------------------------------
#define U_lessorequal   0x2266
#define U_eqorless      0x22DC
#define U_lessoreqival  0x2272
#define U_lessornoteqival    0x22E6
#define U_lessorgreater 0x2276
#define U_lesseqgreater 0x22DA
#define U_precedes      0x227A
#define U_precedesoreq  0x227C
#define U_eqorprecedes  0x22DE
#define U_preceedsorequiv    0x227E
//
#define U_minustilde    0x2242
#define U_approaches    0x2250
#define U_approximageof 0x2252
#define U_definition    0x2254
#define U_almosteq      0x224A
#define U_ringinequal   0x2256
#define U_estimates     0x2259
#define U_starequals    0x225B
#define U_geoequivalent 0x224E
#define U_equalrobydef  0x225D
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_notlessthan   0x226E
#define U_notlessoreq   0x2270
#define U_notlessorequiv     0x2274
#define U_lessbutnoteq  0x2268
#define U_notlessorgreater   0x2278
#define U_notprecedes   0x2280
#define U_notprecedesoreq    0x22E0
#define U_preceedsnorequiv   0x22E8
//
#define U_greatereqless 0x22DB
//
#define U_asymptoticeq  0x2243
#define U_geoequalto    0x2251
#define U_imageofapprox 0x2253
#define U_equalcolon    0x2255
#define U_tripletilde   0x224B
#define U_ringequalto   0x2257
#define U_equiangularto 0x225A
#define U_deltaequalto  0x225C
#define U_difference    0x224F
#define U_measuredby    0x225E
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_greaterdiaersis 0x2369
#define U_greateroreq   0x2267
#define U_eqorgreater   0x22DD
#define U_greateroreqiv 0x2273
#define U_greaterornoteqiv   0x22E7
#define U_greaterorless 0x2277
#define U_succeeds      0x227B
#define U_succeedsoreq  0x227D
#define U_eqorsucceeds  0x22DF
#define U_succeedsorequiv    0x227F
//
#define U_reversetildeeq     0x22CD
#define U_equivalent    0x224D
#define U_approxequal   0x2245
#define U_allequalto    0x224C
#define U_strictlyequiv 0x2263
#define U_correspondsto 0x2258
#define U_questionedeq  0x225F
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_notgreater    0x226F
#define U_notgreateroreq     0x2271
#define U_notgreatoreqiv     0x2275
#define U_greaterbutneq 0x2269
#define U_notgreaterorless   0x2279
#define U_notsucceed    0x2281
#define U_notsucceedsoreq    0x22E1
#define U_succeedsnorequiv   0x22E9
//
#define U_notasymptoteq 0x2244
#define U_notapprox     0x2249
#define U_notequivalent 0x226D
#define U_approxnoteq   0x2246
#define U_notapproxoreq 0x2247
#define U_notequiv      0x2262
//
//------------------------------------------------------------------------------
// Games & Music
//------------------------------------------------------------------------------
// Chess
#define U_whking        0x2654
#define U_whqueen       0x2655
#define U_whrook        0x2656
#define U_whbishop      0x2657
#define U_whknight      0x2658
#define U_whpawn        0x2659
#define U_whshogi       0x2616
//
#define U_blkking       0x265A
#define U_blkqueen      0x265B
#define U_blkrook       0x265C
#define U_blkbishop     0x265D
#define U_blkknight     0x265E
#define U_blkpawn       0x265F
#define U_blkshogi      0x2617

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Cards
#define U_ltspades      0x2664
#define U_ltclubs       0x2667
#define U_ltdiamonds    0x2662
#define U_lthearts      0x2661
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Dice
#define U_ace           0x2680
#define U_deuce         0x2681
#define U_trey          0x2682
#define U_cater         0x2683
#define U_cinque        0x2684
#define U_sice          0x2685
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Music
#define U_quarternote   0x2669
#define U_beamed16th    0x266C
#define U_flat          0x266D
#define U_natural       0x266E
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Glyphs
#define U_hotsprings    0x2668
#define U_shamrock      0x2618
#define U_electrical    0x2301
#define U_helm          0x2388
#define U_hotcoffee     0x2615
#define U_blkphone      0x260E
#define U_whitephone    0x260F
#define U_blkcloud      0x2601
#define U_umbrella      0x2602
#define U_rainumbrella  0x2614
#define U_snowman       0x2603
//
//------------------------------------------------------------------------------
// Characters
//------------------------------------------------------------------------------
// Typographical
#define U_revparagraph  0x204B
#define U_trianglecolon 0x02D0
//
#define U_midellipsis   0x22EF
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Punctuation
#define U_supquestion   0x02C0
#define U_dblquestion   0x2047
#define U_questionexclm 0x2048
#define U_exclmquestion 0x2049
#define U_semicolonbar  0x236E
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_revprime      0x2035
#define U_revdiprime    0x2036
#define U_revtriprime   0x2037
#define lftquill        0x2045
#define rgtquill        0x2046
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Superscript
#define U_supmhos       0x1DB7
#define U_continuous    0x2381
#define U_discontinue   0x2382
#define U_emphasis      0x2383
//
//------------------------------------------------------------------------------
// Latin Modifiers Lower case
//------------------------------------------------------------------------------
#define U_subh          0x2095
#define U_subk          0x2096
#define U_subl          0x2097
#define U_subm          0x2098
#define U_subn          0x2099
#define U_subp          0x209A
#define U_subs          0x209B
#define U_subt          0x209C
//
#define U_varg          0x1DA2
//
//------------------------------------------------------------------------------
// Mathematical symbols
//------------------------------------------------------------------------------
#define U_cbrt          0x221B
#define U_4thrt         0x221C
//
#define U_mp            0x2213
#define U_ratio         0x2236
#define U_excess        0x2239
#define U_tildeop       0x223C
#define U_homothetic    0x223B
//
#define U_lftceiling    0x2308
#define U_lftfloor      0x230A

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_dblintgl      0x222C
#define U_tripleintgl   0x222D
#define U_proportion    0x2237
#define U_geoproportion 0x223A
#define U_dotminus      0x2238
#define U_reversetilde  0x223D
#define U_tildediaersis 0x2368
#define U_lftbrackettop 0x23A1
#define U_lftbracketext 0x23A2
#define U_lftbracketbtm 0x23A3

#define U_lftparenttop  0x239B
#define U_lftparentext  0x239C
#define U_lftparentbtm  0x239D
#define U_lftcurlytop   0x23A7
#define U_lftcurlyext   0x23AA
#define U_lftcurlymid   0x23A8
#define U_lftcurlybtm   0x23A9
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_complement    0x2201
#define U_verum         0x22A4
#define U_dotop         0x22C5
#define U_starop        0x22C6
#define U_multiplication 0x2715
//
#define U_rgtceiling    0x2309
#define U_rgtfloor      0x230B
#define U_rgtparenttop  0x239E
#define U_rgtparentext  0x239F
#define U_rgtparentbtm  0x23A0
#define U_rgtcurlytop   0x23AB
#define U_rgtcurlyext   0x23AE
#define U_rgtcurlymid   0x23AC
#define U_rgtcurlybtm   0x23AD

#define U_turnednot     0x2319
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_asterisk      0x2217
#define U_boldasterisk  0x2731
#define U_openasterisk  0x2732
#define U_spikeasterisk 0x2733
#define U_blkspikeaster 0x2734
#define U_falsum        0x22A5
#define U_nabla         0x2207
#define U_nottilde      0x2241
#define U_stardiaeresis 0x2363
#define U_zilde         0x236C
#define U_stiletilde    0x236D
//
#define U_rgtbrackettop 0x23A4
#define U_rgtbracketext 0x23A5
#define U_rgtbracketbtm 0x23A6
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_parallel      0x01C1
#define U_perp          0x22A5
#define U_angle         0x2220
#define U_arc           0x2312
#define U_segment       0x2313
#define U_sector        0x2314
#define U_rectangle     0x2337
#define U_quad          0x2395
#define U_triangle      0x25B3
#define U_smtriangle    0x25B5
#define U_parallelogram 0x25B1
//
#define U_oneover       0x215F
//
//------------------------------------------------------------------------------
// Arrows
//------------------------------------------------------------------------------
// arrow heads
#define U_blkdwnarrhead 0x02D1
// West
#define U_Warrowopen    0x21FD
#define U_Warrowslash   0x219A
#define U_Warrowstroke  0x21F7
#define U_Warrowdistroke 0x21FA
#define U_Warrowtobar   0x21E4
#define U_Warrowwavy    0x219C
#define U_WbyWarrows    0x21C7
#define U_Warrowbarb    0x21BC
#define U_Warrowharpon  0x21BD
#define U_Wdblarrow     0x21D0
#define U_Wdblarrowslash 0x21CD
// North
#define U_Narrowbar     0x21A5
#define U_NbyNarrows    0x21C8
#define U_Ndblarrow     0x21D1
#define U_Nwhitearrow   0x21E7
#define U_Nwhitepedbar  0x21EC
#define U_Nwhitepedline 0x21ED
#define U_Nwhitediarrow 0x21EE
#define U_Nwhitediarwped 0x21EF
// Northeast
#define U_NEarrow       0x2197
#define U_NEdblarrow    0x21D7
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// West/East
#define U_WEarrowopen   0x21FF
#define U_WEarrowslash  0x21AE
#define U_WEarrowstroke 0x21F9
#define U_WEarrowdistroke 0x21FC
#define U_WbyEarrowstobar 0x21B9
#define U_WEwavyarrow   0x21AD
#define U_WbyEarrows    0x21C6
#define U_EbyWarrows    0x21C4
#define U_WbyEarrowsbarb 0x21CB
#define U_EbyWarrowsbarb 0x21CC
#define U_WEdblarrow    0x21D4
#define U_WEdblarrowslash 0x21CE
// North/South
#define U_NbySarrows    0x21C5
#define U_SbyNarrows    0x21F5
#define U_NSdblarrow    0x21D5
#define U_NSwhitearrow  0x21F3
// Northwest
#define U_NWarrow       0x2196
#define U_NWdblarrow    0x21D6
#define U_NWarrowcorner 0x21F1
#define U_NWarrowedge   0x21B8
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// East
#define U_Earrowopen    0x21FE
#define U_Earrowslash   0x219B
#define U_Earrowstroke  0x21F8
#define U_Earrowdistroke 0x21FB
#define U_Earrowtobar   0x21E5
#define U_Earrowwavy    0x219D
#define U_EbyEarrows    0x21C9
#define U_Etriarrows    0x21F6
#define U_Earrowbarb    0x21C0
#define U_Earrowharpon  0x21C1
#define U_Edblarrow     0x21D2
#define U_Edblarrowslash 0x21CF
// South
#define U_Sarrowbar     0x21A7
#define U_SbySarrows    0x21CA
#define U_Sdblarrow     0x21D3
#define U_Swhitearrow   0x21E9
// Southeast
#define U_SEarrow       0x2198
#define U_SEdblarrow    0x21D8
#define U_SEarrowcorner 0x21F2
#define U_SEelbowarrow  0x2607
#define U_thunderstorm  0x2608
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// West
#define U_Warrowtail    0x21A2
#define U_Warrowdash    0x21E0
#define U_Warrowloop    0x21AB
#define U_Warrowhook    0x21A9
#define U_Wdiarrow      0x219E
#define U_Warrowbar     0x21A4
#define U_Warrowwaves   0x21DC
#define U_Warrowturn    0x21B5
#define U_Warrowleft    0x21B2
#define U_Warrowbent    0x21B0
#define U_Wwhitearrow   0x21E6
#define U_Wtriarrow     0x21DA
// North
#define U_Narrowhook    0x21BA
#define U_Narrowloop    0x21BB
#define U_Narrowdash    0x21E1
#define U_Narrowbarb    0x21BE
#define U_Narrowharpon  0x21BF
#define U_Ndiarrow      0x219F
#define U_Narrowbars    0x21DE
#define U_Nwhitearrowbar 0x21EA
#define U_Nwhitearrowped 0x21EB
// Southwest
#define U_SWarrow       0x2199
#define U_SWdblarrow    0x21D9
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//East
#define U_Earrowtail    0x21A3
#define U_Earrowdash    0x21E2
#define U_Earrowloop    0x21AC
#define U_Earrowhook    0x21AA
#define U_Ediarrow      0x21A0
#define U_Earrowbar     0x21A6
#define U_Earrowwaves   0x21DD
#define U_Earrowcircle  0x21F4
#define U_Earrowright   0x21B3
#define U_Earrowbent    0x21B1
#define U_Ewhitearrow   0x21E8
#define U_Etriarrow     0x21DB
#define U_Ewhitearrowped 0x21F0
// South
#define U_Sarrowhook    0x21B6
#define U_Sarrowloop    0x21B7
#define  U_Sarrowdash   0x21E3
#define U_Sarrowbarb    0x21C2
#define U_Sarrowharpon  0x21C3
#define U_Sdiarrow      0x21A1
#define U_Sarrowbars    0x21DF
#define U_Sarrowbent    0x21B4
#define U_Sarrowzigzag  0x21AF
// Arrowheads
#define U_uparrowhead   0x2303
#define U_projective    0x2305
#define U_perspective   0x2306
#define U_downarrowhead 0x2304
#define U_insertion     0x2380
//
//------------------------------------------------------------------------------
// Sets
//------------------------------------------------------------------------------
#define U_intersect     0x2229
#define U_supersetof    0x2283
#define U_superset      0x2287
#define U_squareoriginal     0x2290
#define U_sqroriginaloreq    0x2292
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_notsuperset   0x2285
#define U_notsupersetoreq    0x2289
#define U_supersetnoteq 0x228B
#define U_notsquareoriginal  0x22E3
#define U_sqroriginalnoteq   0x22E5
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_union         0x222A
#define U_subsetof      0x2282
#define U_subset        0x2286
#define U_squareimageof 0x228F
#define U_sqrimqgeoreq  0x2291
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_notsubsetof   0x2284
#define U_notsubsetoreq 0x2288
#define U_subsetnoteq   0x228A
#define U_notsquareimageof   0x22E2
#define U_squareimagenoteq   0x22E4

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_emptyset      0x2205
#define U_belongsto     0x2208
#define U_notbelong     0x2209
#define U_contains      0x220B
#define U_notcontain    0x220C
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_complex       0x2102
#define U_naturalnum    0x2115
#define U_rationalnum   0x211A
#define U_realnum       0x211D
#define U_integernum    0x2124
#define U_dblstruckH    0x210D
#define U_dblstruckP    0x2119
#define Ucountersink    0x2335
//
//------------------------------------------------------------------------------
// Symbols
//------------------------------------------------------------------------------
#define U_logicalor     0x2228
#define U_exists        0x2203
#define U_proportional  0x221D
#define U_therefore     0x2234
#define U_xor           0x2295
#define U_forall        0x2200
#define U_implies       0x21D2
// zodiac
#define U_aries         0x2648
#define U_taurus        0x2649
#define U_gemini        0x264A
#define U_cancer        0x264B
#define U_leo           0x264C
#define U_virgo         0x264D
#define U_libre         0x264E
#define U_scorpius      0x264F
#define U_sagittarius   0x2650
#define U_capricorn     0x2651
#define U_aquarius      0x2652
#define U_pisces        0x2653
#define U_ascendnode    0x260A
#define U_descendnode   0x260B
#define U_conjunction   0x260C
#define U_comet         0x2604

// astronomy
#define U_sun           0x2609
#define U_1stquarter    0x263D
#define U_lastquarter   0x263E
#define U_mercury       0x263F
#define U_venus         0x2640
#define U_earth         0x2641
#define U_mars          0x2642
#define U_jupiter       0x2643
#define U_saturn        0x2644
#define U_uranus        0x2645
#define U_neptune       0x2646
#define U_pluto         0x2647
#define U_whstar        0x2606
#define U_blkstar       0x2605
#define U_blksunshine   0x2600
#define U_opposition    0x260D
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_logicaland    0x2227
#define U_notexists     0x2204
#define U_not           U_suptilde
#define U_materialediv  0x21D4
#define U_because       0x2235
// keyboard
#define U_macintosh     0x2318
#define U_option        0x2325
#define U_erase         0x2326
#define U_delete        0x2327
#define U_keyboard      0x2328
#define U_backspace     0x2329
#define U_return        0x23CE
#define U_eject         0x23CF
//Plastics
#define U_plastic1      0x2673
#define U_plastic2      0x2674
#define U_plastic3      0x2675
#define U_plastic4      0x2676
#define U_plastic5      0x2677
#define U_plastic6      0x2678
#define U_plastic7      0x2679
#define U_plastic       0x267A
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// recycle
#define U_recylce       0x2672
#define U_invrecycle    0x267B
#define U_recyclepaper  0x267C
#define U_partialrecycle 0x267D
// Tacks
#define U_righttack     0x22A2
#define U_lefttack      0x22A3
#define U_downtack      0x22A4
#define U_uptack        0x22A5
// Signs
#define U_poison        0x2620
#define U_paper         0x267E
#define U_handycap      0x267F
#define U_radioactive   0x2622
#define U_atomic        0x269B
#define U_biohazard     0x2623
#define U_caution       0x2621
#define U_medical       0x2624
#define U_aesculapius   0x2695
#define U_hermes        0x269A
//
#define U_gear          0x2699
#define U_fleurdelis    0x269C
#define U_coffin        0x26B0
#define U_urn           0x26B1
#define U_warning       0x26A0
#define U_highvoltage   0x26A1
#define U_scissors1     0x2701
#define U_scissors2     0x2702
#define U_scissors3     0x2703
#define U_scissors4     0x2704
//
#define U_peace         0x262E
#define U_yinyang       0x262F
#define U_phone         0x2706
#define U_tapedrive     0x2707
#define U_ankh          0x2625
#define U_orthodox      0x2626
#define U_chirho        0x2627
#define U_lorraine      0x2628
#define U_jerusalem     0x2629
#define U_westsyrian    0x2670
#define U_latincross    0x271D
#define U_outlinecross  0x271E
#define U_outlinecross2 0x271F
#define U_maltese       0x2720
#define U_starofdavid   0x2721
#define U_4ptteardrop   0x2722
#define U_6ptteardrop   0x273B
#define U_openteardrop  0x273C
#define U_boldflorette  0x273D
#define U_florette      0x273E
#define U_blkflorette   0x273F
#define U_whflorette    0x2740
#define U_8petalled     0x2741
#define U_balloondrop   0x2723
#define U_boldballoon   0x2724
#define U_clubsdrop     0x2725
#define U_eastsyrian    0x2671
#define U_greekcross    0x2719
#define U_boldgreekcross 0x271A
#define U_centrecross   0x271B
#define U_boldcentre    0x271C
#define U_starcrescent  0x262A
#define U_hammersickle  0x262D
#define U_hammerpick    0x2692
#define U_anchor        0x2693
#define U_scales        0x2696
#define U_alembic       0x2697
#define U_flower        0x2698
#define U_crossedswords 0x2694
#define U_ltflag        0x2690
#define U_dkflag        0x2691
#define U_sadface       0x2639
#define U_airplane      0x2708
#define U_envelope      0x2709
#define U_victory       0x270C
#define U_writing       0x270D
#define U_pencil1       0x270E
#define U_pencil2       0x270F
#define U_pencil3       0x2710
#define U_whnib         0x2711
#define U_blknib        0x2712
//
#define U_blk6ptstar    0x2736
#define U_blk8ptstar    0x2737
#define U_bold8ptstar   0x2738
#define U_blk12ptstar   0x2739
#define U_blk16ptstar   0x273A
#define U_blk4pointstar 0x2726
#define U_wh4pointstar  0x2727
#define U_stresswhstar  0x2729
#define U_openblkstar   0x272B
#define U_blkcenterstar 0x272C
#define U_outlinestar   0x272D
#define U_stardot       0x272E
#define U_5ptpinwheel  0x272F
#define U_shadowstar    0x2730
#define U_8ptpinwheel   0x2735
//
#define U_blkpointlft   0x261A
#define U_blkpointrgt   0x261B
#define U_whpointlft    0x261C
#define U_whpointrgt    0x261E
#define U_whpointup     0x261D
#define U_whpointdwn    0x261F
//
#define U_checkmark     0x2713
#define U_boldcheckmark 0x2714
#define U_boldx         0x2716
#define U_ballotx       0x2717
#define U_boldballotx   0x2718
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_Planck        0x210E
#define U_RedPlanck     0x210F
#define U_Kelvin        0x212A
#define U_Angstrom      0x212B
#define U_perthousand   0x2031
//
#define U_cruzeiro      0x20A2
#define U_saltire       0x2613
#define U_revheart      0x2619
//
#define U_sqrlozenge    0x2311
#define U_recorder      0x2315
#define U_openbox       0x237D
#define U_openedbox     0x2423
//
//------------------------------------------------------------------------------
// Geometric Shapes
//------------------------------------------------------------------------------
// Quadralaterials
#define U_quadless      0x2343
#define U_quaddown      0x234C
#define U_quadleftarrw  0x2347
#define U_quaduparrw    0x2350
#define U_quadcolon     0x2360
#define U_quaddivide    0x2339
#define U_quadquestion  0x2370
//
#define U_quadequal     0x2338
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_quadgreater   0x2344
#define U_quadup        0x2353
#define U_quadrgtarrw   0x2348
#define U_quaddownarrw  0x2357
#define U_quadslash     0x2341
#define U_quadbackslash 0x2342
#define U_quadcircle    0x233C
#define U_quadjot       0x233B
#define U_quadnotequal  0x236F
//
#define U_quaddel       0x2354
#define U_quadtriangle  0x234D
#define U_quaddiamond   0x233A
#define U_quadquote     0x235E
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Circles
#define U_circleplus    0x2295
#define U_circleminus   0x2296
#define U_circletimes   0x2297
#define U_circledot     0x2299
#define U_circleslash   0x2298
//
#define U_circlebar     0x235C
#define U_circlergtdot  0x2686
#define U_circletwodot  0x2687
#define U_blkcircledot  0x2688
#define U_blkcircledots 0x2689
#define U_circlering    0x229A
#define U_circleequal   0x229C
#define U_circleaster   0x229B
#define U_circledash    0x229D
#define U_lftblkcircle  0x25D0
#define U_rgtblkcircle  0x25D1
#define U_circledel     0x238A
//
#define U_deltabar      0x2359
#define U_diamondbar    0x235A
#define U_quotebar      0x2358
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//Boxes
#define U_boxplus       0x229E
#define U_boxminus      0x229F
#define U_boxtimes      0x22A0
#define U_boxdot        0x22A1
// Circles
#define U_circlenwarrw  0x238B
#define U_circlestile   0x233D
#define U_circlejot     0x233E
#define U_circlestar    0x235F
#define U_blkcircledstar 0x272A
#define U_circlenotch   0x2389
#define U_btmblkcircle  0x25D2
#define U_topblkcircle  0x25D3
//
#define U_delstile      0x2352
#define U_deltastile    0x234B
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_topleft       0x231C
#define U_btmleft       0x231E
#define U_topright      0x231D
#define U_btmright      0x231F
// Circles
#define U_circlebackslash    0x2349
#define U_circlediaersis 0x2365
#define U_jotdiaersis   0x2364
#define U_jotbar        0x235B
#define U_blkcircle     0x25CF
#define U_whblkcircle   0x25C9
#define U_cirlcebars    0x25CD
//
#define U_deltilde      0x236B
//------------------------------------------------------------------------------
// Polygons Shapes
//------------------------------------------------------------------------------
#define U_blkbargraph1   0x2581
#define U_blkbargraph2   0x2582
#define U_blkbargraph3   0x2583
#define U_blkbargraph4   0x2584
#define U_blkbargraph5   0x2585
#define U_blkbargraph6   0x2586
#define U_blkbargraph7   0x2587
#define U_blkbargraph8   0x2588
#define U_blkbargraph9   0x2594
#define U_blkparallel    0x25B0
#define U_rectangleA1    0x2599
#define U_rectangleA2    0x259C
#define U_rectangleA3    0x259F
#define U_rectangleA4    0x259B
//
#define U_blkbar1        0x2589
#define U_blkbar2        0x258A
#define U_blkbar3        0x258B
#define U_blkbar4        0x258C
#define U_blkbar5        0x258D
#define U_blkbar6        0x258E
#define U_blkbar7        0x258F
#define U_blkbar8        0x2590
#define U_blkbar9        0x2595
#define U_blkbar10       0x25AE
#define U_rectangleB1    0x259D
#define U_rectangleB2    0x2596
#define U_rectangleB3    0x2598
#define U_rectangleB4    0x2597
//
#define U_roundedwhbox   0x25A2
#define U_boxsquare      0x25A3
#define U_boxhfill       0x25A4
#define U_boxlftdiag     0x25A7
//
#define U_rectanglesm    0x25AD
#define U_whbar10        0x25AF
#define U_mtballotbox    0x2610
#define U_chkballotbox   0x2611
#define U_xedballotbox   0x2612
//
#define U_rectangleB12   0x259E
#define U_rectangleB34   0x259A
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_boxvfill       0x25A5
#define U_boxrgtdiag     0x25A8
// Triangles
#define U_blkrgttriangle 0x25B6
#define U_blklfttriangle 0x25C0
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define U_boxcage        0x25A6
#define U_boxdiag        0x25A9
#define U_blkrgttriangle 0x25C1
//
#define U_whrgttriangle  0x25B7
#define U_whrgtarwsm     0x25B9
#define U_whrgtarw       0x25BB
#define U_whdwnarw       0x25BD
#define U_whdwnarwsm     0x25BF
#define U_whlftarwsm     0x25C3
#define U_whlftarw       0x25C5
#define U_blkdiamond     0x25C6
#define U_whdiamond      0x25C7
#define U_whblkdiamond   0x25C8
#define U_toprgtblkcircle 0x25D4
#define U_lfthalfcircle  0x25D6
#define U_rgthalfcircle  0x25D6
#define U_inversebullet  0x25D8
#define U_tophalfcircle  0x25DA
#define U_btmhalfcircle  0x25DB
#define U_toplftquarter  0x25DC
#define U_toprgtquarter  0x25DD
#define U_btmrgtquarter  0x25DE
#define U_btmlftquarter  0x25DF
#define U_toparc         0x25E0
#define U_btmarc         0x25E1
#define U_blklowerrgt    0x25E2
#define U_blklowerlft    0x25E3
#define U_blkupperlft    0x25E4
#define U_blkupperrgt    0x25E5
#define U_lfthalfbox     0x25E7
#define U_rgthalfbox     0x25E8
#define U_sqrupperlft    0x25E9
#define U_sqrlowergt     0x25EA
#define U_whbisectbox    0x25EB
#define U_whtriangledot  0x25EC
#define U_lfthalftri     0x25ED
#define U_rgthalftri     0x25EE
#define U_whcircle       0x25EF
#define U_whupperlftbx   0x25F0
#define U_whlowerlftbx   0x25F1
#define U_whlowerrgtbx   0x25F2
#define U_whupperrgtbx   0x25F3
#define U_toplftwhcircle 0x25F4
#define U_btmlftwhcircle 0x25F5
#define U_btmrgtwhcircle 0x25F6
#define U_toprgtwhcircle 0x25F7
#define U_whupperlft     0x25F8
#define U_whupperrgt     0x25F9
#define U_whlowerlft     0x25FA
#define U_whlowerrgt     0x25FF
#define U_whitebox       0x25FB
#define U_blackbox       0x25FC
#define U_smwhbox        0x25FD
#define U_smblkbox       0x25FE
//
#define U_exclaimheart   0x2763
#define U_boldblkheart   0x2764
#define U_rotatedheart   0x2765
#define U_floralheart    0x2766
#define U_rotatefloral   0x2767
#define U_lftmedmpar     0x2768
#define U_rgtmedmpar     0x2769
#define U_lftboldpar     0x276A
#define U_rgtboldpar     0x276B
#define U_lftmedmangle   0x276C
#define U_rgtmedmangle   0x276D
#define U_lftboldangle   0x2770
#define U_rgtboldangle   0x2771
#define U_lfttortoise    0x2772
#define U_rgttortoise    0x2773
#define U_lftboldbrckt   0x2774
#define U_rgtboldbrckt   0x2775
#define U_SEbold         0x2798
#define U_SWbold         0x279A
#define U_NEbowarrow     0x27B6
#define U_circlearrow    0x27B2

#define U_Eopenarrow     0x27BE
#define U_lftbagdelimit  0x27C5
#define U_rgtbagdelimit  0x27C6
#define U_divideddiam    0x27E0
#define U_lftanglebrkt   0x27E8
#define U_rgtanglebrkt   0x27E9
//
#define U_blkdiamond     0x29EB
#define U_doubleplus     0x29FA
#define U_tripleplus     0x29FB
//
#define U_crossproduct   0x2A2F
//
#define U_tophalfbox     0x2B12
#define U_btmhalfbox     0x2B13
#define U_sqrupperrgt    0x2B14
#define U_sqrlowerlft    0x2B15
#define U_lfthalfdiam    0x2B16
#define U_rgthalfdiam    0x2B17
#define U_tophalfdiam    0x2B18
#define U_btmhalfdiam    0x2B19
#define U_dottedbox      0x2B1A

#endif // EXTENDED_UNICODE

#endif // UNICODER_H_INCLUDED
