#include <conio.h>
#include <dos.h>

#define UP 0x06
#define DOWN 0x07
#define CLEAR 0x00
class SuperWindow
{
private:
	int x1, x2, y1, y2;
	void scroll(int dir, char l_row, char l_col, char r_row, char r_col, char attr)
	{
		union REGS regs;
		if (dir)
		{
			//scroll by direction
			regs.h.al = 0x01;
			regs.h.ah = dir;
		}
		else //clear window
		{
			regs.h.al = 0x00;
			regs.h.ah = 0x06;
		}

		regs.h.ch = l_row;
		regs.h.cl = l_col;
		regs.h.dh = r_row;
		regs.h.dl = r_col;
		regs.h.bh = attr;
		int86(0x10, &regs, &regs);
	}

public:
	SuperWindow(int x1, int x2, int y1, int y2)
	{
		this->x1 = x1;
		this->x2 = x2;
		this->y1 = y1;
		this->y2 = y2;

		clrscr();
		window(x1, y1, x2, y2);
		DrawBorder(0x10);
	}
	void DrawBorder(char colorAttr)
	{
		char borderSize = 1;
		//draw border --> blue foreground black text
		scroll(CLEAR, y1 - borderSize - 1, x1 - borderSize - 1, y2, x2, colorAttr);
		//draw window black foreground white text
		scroll(CLEAR, y1 - 1, x1 - 1, y2 - 1, x2 - 1, 0x07);
	}
	void ScrollUp()
	{
		scroll(UP, y1 - 1, x1 - 1, y2 - 1, x2 - 1, 0x07);
	}
	void ScrollDown()
	{
		scroll(DOWN, y1 - 1, x1 - 1, y2 - 1, x2 - 1, 0x07);
	}
	void Clear()
	{
		textbackground(0);
		scroll(CLEAR, 0, 0, 24, 79, 0x07);
	}
};

int main()
{
	int x1 = 25, x2 = 55, y1 = 5, y2 = 15;
	float delayTime = 0.6f;
	int sCount = 1;

	SuperWindow w(x1, x2, y1, y2);

	int colorsCount = 16;
	for (int i = 0; i < colorsCount; i++)
	{
		for (int j = 0; j < colorsCount; j++)
		{
			textcolor(j);
			textbackground(i);

			char* eng[16] = { "Black","Blue","Green","Cyan", "Red", "Magenta","Brown","Lightgray","Darkgray","Lightblue","Lightgreen","Lightcyan","Lightred","Lightmagenta","Yellow","White" };
			for (int k = 0; k < sCount; k++)
			{
				w.ScrollDown();
				gotoxy(1, 1);
				cprintf("%s %s", eng[j], eng[i]);
			}
			delay(delayTime * 1000);
		}
	}
	getch();
	w.Clear();
	return 1;
}