#include <dos.h>
#include <conio.h>
#include <stdio.h>



#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_RIGHT 77
#define KEY_LEFT 75
#define KEY_ESC 27

#define KEY_UPRIGHT 73
#define KEY_UPLEFT 71
#define KEY_DOWNRIGHT 81
#define KEY_DOWNLEFT 79


void SetCursorVisibility(int value)
{
	//use 01h function of int 10h
	asm mov ah, 0x01
		if (value > 0)
			asm mov cx, 0x0607
		else
			asm mov cx, 0x2607

			asm int 0x10
}
char GetINT21Key()
{
	//use 07h function int 21h
	union REGS regs;
	regs.h.ah = 0x07;
	int86(0x21, &regs, &regs);
	return regs.h.al;
}

class Window
{
	int x1, x2, y1, y2;

	//functions to clamp cursor within the window
	void clampY(int& y)
	{
		if (y > y2 - y1 + 1)
			y = y2 - y1 + 1;
		if (y < 1)
			y = 1;
	}
	void clampX(int& x)
	{
		if (x > x2 - x1 + 1)
			x = x2 - x1 + 1;
		if (x < 1)
			x = 1;
	}

	void ClearWindow(char l_row, char l_col, char r_row, char r_col, char attr)
	{
		union REGS regs;

		regs.h.al = 0x00;
		regs.h.ah = 0x06;
		regs.h.ch = l_row - 1;
		regs.h.cl = l_col - 1;
		regs.h.dh = r_row - 1;
		regs.h.dl = r_col - 1;
		regs.h.bh = attr;

		int86(0x10, &regs, &regs);
	}


public:
	Window(int x1, int y1, int x2, int y2)
	{
		this->x1 = x1;
		this->x2 = x2;
		this->y1 = y1;
		this->y2 = y2;

		clrscr();
		window(x1, y1, x2, y2);

		//draw border --> blue foreground black text
		DrawBorder(0x10);
		SetCursorVisibility(0);
		InputCycle();
	}
	void DrawBorder(char colorAttr)
	{
		char borderSize = 1;
		ClearWindow(y1 - borderSize, x1 - borderSize, y2 + borderSize, x2 + borderSize, colorAttr);

		//draw window black foreground white text
		ClearWindow(y1, x1, y2, x2, 0x07);
	}
	void Dispose()
	{
		ClearWindow(0, 0, 255, 255, 0x07);
	}
	void InputCycle()
	{
		int cursorX = 0, cursorY = 0, exitFlag = 0;
		while (exitFlag == 0)
		{
			//cpp realization
			//char input = getch();

			// int21 realization
			char input = GetINT21Key();

			switch (input)
			{
			case KEY_ESC: exitFlag = 1; break;
			case KEY_UP: cursorY--; break;
			case KEY_DOWN: cursorY++; break;
			case KEY_RIGHT: cursorX++; break;
			case KEY_LEFT: cursorX--; break;
			case KEY_UPRIGHT: cursorY--; cursorX++; break;
			case KEY_DOWNRIGHT: cursorY++; cursorX++; break;
			case KEY_UPLEFT: cursorY--; cursorX--; break;
			case KEY_DOWNLEFT: cursorY++; cursorX--; break;
			}

			clampX(cursorX);
			clampY(cursorY);

			clrscr();
			gotoxy(cursorX, cursorY);

			cputs("+");
		}
		Dispose();
	}
};

int main()
{
	clrscr();

	int x1 = 25, x2 = 55, y1 = 5, y2 = 15;
	Window mainWindow(x1, y1, x2, y2);
	return 1;
}