#include <iostream>
#include <conio.h>
#include <windows.h>
#include "engin.h"

/**
 * ASCIIDraw - By DeetSteve00
 *
 * This is a small program to create ASCII art using a cursor and you keyboard
 * You can also add colors to your canvas if you feel creative
 * 
 * This small program is not fully finished, bugs are possible, everytihng is meant to be what it is,
 * there should and isn't any unexpected behaivour on this small program,
 * Given the same input, there will be the same output
**/

const int Width = 120, Height = 30; /* Every console program starts with default 120 x 30 screen */
int cursorX = (Width/2)-1, cursorY = Height/2;
Display display(0x07, "ASCIIDraw v0.2", true);
#define MAP(X) Map_ ## X
	UCHAR Map_Char[Width*Height];
	byte Map_Color[Width*Height];
FILE* file;

CHAR Input[100] = "XXX"; /* Three digit number 0 - 255 + terminating char */
CHAR CopiedChar = ' ';
int i, a, b;

int main(int argc, char const *argv[]) {
	if(argc < 2) for (i = 0; i < Width*Height; i++) {
		MAP(Char)[i] = ' ';
		MAP(Color)[i] = 0x0f;
	} else { /* Read target file */
		file = fopen(argv[1], "r");
		a = 0, b = 0;
		while (a < Width*Height) {
			MAP(Char)[a] = fgetc(file);
			MAP(Color)[b] = fgetc(file);
			a++, b++;
		}
		fclose(file);
	}
	
	while (true) {
		for (a = 0; a < Height; a++) for (b = 0; b < Width; b++) {
			display.srcDisplay[display.in(b, a)].Char.AsciiChar = MAP(Char)[a*Width+b];
			display.srcDisplay[display.in(b, a)].Attributes = MAP(Color)[a*Width+b];
		}

		display.srcDisplay[display.in(cursorX, cursorY)].Attributes = 0x1f;
		display.WriteOutput();

		if(_kbhit()) switch(_getch()) { /* Just about everything happens here */
			case 27: exit(0); break;

			case 'w': cursorY--; if(cursorY < 0) cursorY = Height - 1; break;
			case 'a': cursorX--; if(cursorX < 0) cursorX = Width - 1; break;
			case 's': cursorY++; if(cursorY >= Height) cursorY = 0; break;
			case 'd': cursorX++; if(cursorX >= Width) cursorX = 0; break;

			case 'q':  /* Input single char from single keystroke */
				display.srcDisplay[display.in(cursorX, cursorY)].Attributes = 0x4f;
				while(!_kbhit()) display.WriteOutput();
				MAP(Char)[cursorY*Width+cursorX] = _getch();
				break;
			case 'e': /* Input number of ASCII code */
				i = 0, a = 0; /* Initialize variables (i = index, a = input) */
				display.srcDisplay[display.in(cursorX, cursorY)].Attributes = 0x4f;
				display.WriteOutput();
				while(a != 13) if(_kbhit()) {
					a = _getch();
					Input[i] = a;
					i++;
				}
				MAP(Char)[cursorY*Width+cursorX] = (CHAR) atoi(Input); /* Convert string to integer */
				break;
			case 'c': /* Input the color code */
				i = 0, a = 0; /* Initialize variables (i = index, a = input) */
				display.srcDisplay[display.in(cursorX, cursorY)].Attributes = 0x4f;
				display.WriteOutput();
				while(a != 13) if(_kbhit()) {
					a = _getch();
					Input[i] = a;
					i++;
				}
				MAP(Color)[cursorY*Width+cursorX] = (CHAR) strtol(Input, NULL, 16); /* Convert Hex string to integer */
				break;

			case 'o': CopiedChar = MAP(Char)[cursorY*Width+cursorX]; break; /* Copy */
			case 'p': MAP(Char)[cursorY*Width+cursorX] = CopiedChar; break; /* Paste */

			case 'z': for(i = 0; i < Width*Height; i++) MAP(Color)[i] = 0xf0; break;
			case 'x': for(i = 0; i < Width*Height; i++) MAP(Color)[i] = 0x0f; break;

			case 'm': /* Save ascii art on "out.ASCIIArt" */
				file = fopen("out.aart", "w");
				a = 0;/*, b = 0;*/
				while (a < Width*Height) {
					fputc(MAP(Char)[a], file);
					fputc(MAP(Color)[a], file);
					a++;
				}
				fclose(file);
				break;

		}
	}
	return 0;
}
