#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <stdlib.h>

const int REPEATS = 3;
const int PERIOD = 1300;

const int LENGTH = 24;
char str[LENGTH];

const char CHAR_COLORS_AMOUNT = 16;
const char BACK_COLORS_AMOUNT = 8;

const int x1 = 10;
const int y1 = 10;
const int x2 = 70;
const int y2 = 20;

void outputGreetings()
{
	printf("Program will output your string with different colors.\n");
	printf("Enter string with length less than 24 characters.\n");
	printf("Excess characters will not be read.\n");
}

void readString()
{
	printf("Enter your string: ");
	scanf("%24s", str);
}

void goToNextLine()
{
	cprintf("\r\n");
}

void outputBackgroundColor(int code)
{
	switch(code)
	{
		case BLACK:
		cprintf("black");
		break;
		case BLUE:
		cprintf("blue");
		break;
		case GREEN:
		cprintf("green");
		break;
		case CYAN:
		cprintf("cyan");
		break;
		case RED:
		cprintf("red");
		break;
		case MAGENTA:
		cprintf("magenta");
		break;
		case BROWN:
		cprintf("brown");
		break;
		case LIGHTGRAY:
		cprintf("lightgray");
		break;
	}
}

void outputCurrentColors(int backColor, int charColor)
{
	cprintf("Back color:");
	outputBackgroundColor(backColor);
	cprintf(",char color:%d ", charColor);
}

void scroll()
{
	union REGS r;
	r.h.ah = 6;
	r.h.al = REPEATS;
	r.h.ch = y1-1;
	r.h.cl = x1-1;
	r.h.dh = y2-1;
	r.h.dl = x2-1;
	r.h.bh = 0x07;
	int86(0x10, &r, &r);
}

void main()
{
	clrscr();
	outputGreetings();
	readString();
	clrscr();
	window(x1,y1,x2,y2);
	for(int i = 0; i < BACK_COLORS_AMOUNT; i++)
	{
		for(int j = 0; j < CHAR_COLORS_AMOUNT; j++)
		{
			textbackground(i);
			textcolor(j);
			outputCurrentColors(i,j);
			cprintf(str);
			clreol();
			delay(PERIOD);
			scroll();
			goToNextLine();
		}
	}
	textbackground(BLACK);
	textcolor(WHITE);
	clreol();
	system("PAUSE");
}
