#ifdef _WIN32

#include <windows.h>

#endif
#ifdef _WIN32
// Some old MinGW/CYGWIN distributions don't define this:
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
#endif

static HANDLE hConsole;
static DWORD outModeInit;

void setupConsole(void) {
    DWORD outMode = 0;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hConsole == INVALID_HANDLE_VALUE) {
        exit(GetLastError());
    }

    if (!GetConsoleMode(hConsole, &outMode)) {
        exit(GetLastError());
    }

    outModeInit = outMode;

    // Enable ANSI escape codes
    outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

    if (!SetConsoleMode(hConsole, outMode)) {
        exit(GetLastError());
    }
}

void restoreConsole(void) {

    // Reset console mode
    if (!SetConsoleMode(hConsole, outModeInit)) {
        exit(GetLastError());
    }
}

#else
void setupConsole(void) {}

void restoreConsole(void) {
        // Reset colors
        printf("\x1b[0m");
    }
#endif