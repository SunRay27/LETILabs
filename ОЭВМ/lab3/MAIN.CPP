#include <iostream.h>
#include <graphics.h>
#include <math.h>
#include <stdlib.h>
#include <conio.h>

#define pi 3.1415

class Plotter
{
private:
	class Point
	{
	public:
		float x, y;
		Point()
		{
			x = 0;
			y = 0;
		}
		Point(float xp, float yp)
		{
			x = xp;
			y = yp;
		}
	};

	float round(float x)
	{
		int val = (int)(x * 100 + 0.5f);
		return ((float)val / 100);
	}

	int gDriver, gMode;

	//main window pixel margin
	int marginX, marginY, marginSmallX, marginSmallY;
	int sizeX, sizeY;

	float xMax, yMax, xMin, yMin;
	float v, h, v1, h1, kv, kh;
	Point* realPoints;
	Point* plotPoints;

	int nOfPoints;


	void buildScale()
	{
		h1 = (xMax + xMin) / 2;
		v1 = (yMax + yMin) / 2;

		h = (sizeX / 2) / (xMax - h1);
		v = (sizeY / 2) / (yMax - v1);

		kh = (sizeX) / 2 - h1 * h;
		if (kh < 0)
			kh = 0;
		else if (kh > sizeX)
			kh = sizeX;

		kv = (sizeY) / 2 + v1 * v;
		if (kv < 0)
			kv = 0;
		else if (kv > sizeY)
			kv = sizeY;
	}
	void buildRealPoints()
	{
		float step = 0.1f;
		xMin = 3*pi/2;
		xMax = 18*pi;

		yMax = -HUGE_VAL;
		yMin = HUGE_VAL;

		nOfPoints = (int)floor(((xMax - xMin) / step)) + 10;

		realPoints = new Point[nOfPoints];

		int c = 0;
		for (float x = xMin; x < xMax; x += step)
		{
			float y = cos(x / 2) * cos(x / 2) + sqrt(x);

			Point point(x, y);
			realPoints[c] = point;

			yMax = point.y > yMax ? point.y : yMax;
			yMin = point.y < yMin ? point.y : yMin;

			c++;
		}
		nOfPoints = c;
	}
	void buildPlotPoints()
	{
		buildScale();

		plotPoints = new Point[nOfPoints];

		for (int i = 0; i < nOfPoints; i++)
		{
			float x = (realPoints[i].x - h1) * h + sizeX / 2;
			float y = (-realPoints[i].y + v1) * v + sizeY / 2;

			Point p(x, y);
			plotPoints[i] = p;
		}
	}

	void drawPlot()
	{
		setcolor(WHITE);
		for (int i = 1; i < nOfPoints; i++)
			line(plotPoints[i - 1].x, plotPoints[i - 1].y, plotPoints[i].x, plotPoints[i].y);
	}
	void drawPlotText()
	{
		setviewport(0, 0, 0, 0, 0);
		settextstyle(0, HORIZ_DIR, 1);
		outtextxy(5, 5, "SuperGrapher2000 DOS Edition, func = cos^2(x/2)+sqrt(x)");

		//setviewport(0,0,0,0,0);
		setlinestyle(CENTER_LINE, 0, 1);

		rectangle(
			marginX - marginSmallX,
			sizeY + marginY + marginSmallY,

			sizeX + marginSmallX + marginX,
			getmaxy() - 5);

		setviewport(
			marginX - marginSmallX,
			sizeY + marginY + marginSmallY,

			sizeX + marginSmallX + marginX,
			getmaxy() - 5, 0);

		setcolor(YELLOW);
		char* ymax = new char[10];
		char* ymin = new char[10];
		char* xmin = new char[10];
		char* xmax = new char[10];

		ymin = gcvt(round(yMin), 10, ymin);
		ymax = gcvt(round(yMax), 10, ymax);
		xmin = gcvt(round(xMin), 10, xmin);
		xmax = gcvt(round(xMax), 10, xmax);


		//draw yMin, yMax
		//5 - hor offset, -10 - vertical offset
		outtextxy(5, 5, "Max y: ");
		outtextxy(7 * 8 + 5, 5, ymax);
		outtextxy(5, 16, "Min y: ");
		outtextxy(7 * 8 + 5, 16, ymin);

		outtextxy(5, 26, "Max x: ");
		outtextxy(7 * 8 + 5, 26, xmax);
		outtextxy(5, 36, "Min x: ");
		outtextxy(7 * 8 + 5, 36, xmin);

		settextstyle(0, HORIZ_DIR, 1);
		setcolor(RED);
		outtextxy(5, 66, "THANKS FOR USING SUPERGRAPHER2000 DOS EDITION!!!");
		outtextxy(5, 76, "DONATE ME PLZ I WANT TO KILL MYSELF");


	}
	void drawPlotOrds()
	{
		//int ordMargin = 10;
		setlinestyle(SOLID_LINE, 0, THICK_WIDTH);

		setcolor(12);

		//verical
		line((int)kh, sizeY + marginSmallY, (int)kh, -marginSmallY);
		//horizontal
		line(-marginSmallX, (int)kv, sizeX + marginSmallX, (int)kv);

		setcolor(WHITE);
		char* ymax = new char[10];
		char* ymin = new char[10];
		char* xmin = new char[10];
		char* xmax = new char[10];

		ymin = gcvt(round(yMin), 10, ymin);
		ymax = gcvt(round(yMax), 10, ymax);
		xmin = gcvt(round(xMin), 10, xmin);
		xmax = gcvt(round(xMax), 10, xmax);


		//draw yMin, yMax
		//5 - hor offset, -10 - vertical offset
		outtextxy((int)kh + 5, -10, ymax);
		outtextxy((int)kh + 5, sizeY + 2, ymin);

		//draw xMin, xMax
		outtextxy(-8 * 5, (int)kv + 5, xmin);
		outtextxy(sizeX + 5, (int)kv + 5, xmax);
	}


public:
	Plotter()
	{
		marginX = 76;
		marginY = 50;
		marginSmallX = 50;
		marginSmallY = 24;
	}
	int InitGraphics()
	{
		int gresult;

		// Detect the graphics driver and mode
		detectgraph(&gMode, &gDriver);

		// initialize the graphics mode with initgraph
		initgraph(&gMode, &gDriver, "C:\\BGI");
		gresult = graphresult();

		if (gresult != grOk)
		{
			cout << grapherrormsg(gresult);
			return -1;
		}

		sizeX = getmaxx() - marginX * 2 - 1;
		sizeY = getmaxy() - marginY * 2 - 1 - getmaxy() / 4;

		setviewport(marginX, marginY, getmaxx() - marginX, getmaxy() - marginY, 0);


		// set the background color
		setbkcolor(BLACK);
		// set the foreground color
		setcolor(WHITE);
		// draw a white color border with rectangle
		rectangle(0, 0, sizeX, sizeY);
		rectangle(-marginSmallX, -marginSmallY, sizeX + marginSmallX, sizeY + marginSmallY);
	}
	void Draw()
	{
		buildRealPoints();
		buildPlotPoints();
		drawPlotOrds();
		drawPlot();
		drawPlotText();
	}
	void Dispose()
	{
		delete[] realPoints, plotPoints;
		closegraph();
		clrscr();
	}
};

int main()
{
	Plotter plot;

	if (!plot.InitGraphics())
		return 0;

	plot.Draw();
	getch();
	plot.Dispose();

	return 1;
}

