#ifndef ENGIN_H
#define ENGIN_H

/**
 * "engin.h"
 * DeetSteve00 - deetsteve00@gmail.com
 * Windows ASCII screen buffer wrapper
 * 
 * This comment was written on 2022-09-28
 */

#include <windows.h>

class Display {
    public:
        short wWidth;
        short wHeight;
        HANDLE hConsole;
        SMALL_RECT rectWindow;
        CHAR_INFO *srcDisplay;

        Display(byte defCol, CONST CHAR title[], bool LockSize) {
            hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
            SetConsoleActiveScreenBuffer(hConsole);
            GetConsoleSize();
            srcDisplay = new CHAR_INFO[wWidth * wHeight];
            wWidth--; wHeight--;
            rectWindow = {0, 0, wWidth, wHeight};
            wWidth++; wHeight++;

            for(int i = 0; i < wWidth*wHeight; i++) {
                srcDisplay[i].Char.AsciiChar = ' ';
                srcDisplay[i].Attributes = defCol;
            }

            SetConsoleTitleA(title);
            if(LockSize) BlockWindowSize();
        }

        VOID WriteOutput(VOID) { WriteConsoleOutputA(hConsole, srcDisplay, {wWidth, wHeight}, {0, 0}, &rectWindow); }
        long int in(short X, short Y) { return (Y * wWidth + X); }

    private:
        VOID GetConsoleSize(VOID) {
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
            wWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            wHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        }
        VOID BlockWindowSize(VOID) {
            HWND consoleWindow = GetConsoleWindow();
            SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
        }
};

#endif