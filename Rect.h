#include "Vec.h"
#include "math.h"
#include <iostream>


class  Rect
{
public:
	//floats, in order:
	//x,y are upper left coordinates of the rectangle
	//h,w are height and width of the rectangle
	//r,g,b are the RGB colors of the rectangle
	//leftwall,rightwall,cieling,floor are for testing if a point is contained in the rectangle
	float x, y, h, w, r, g, b, leftwall, rightwall, cieling, floor;
	//clicky and counter are for flipping the color of the rectangles
	int clicky, counter = 1;

	//bool for telling if the rect has been sorted this pass yet
	bool sorted;

	Rect()
	{
		x = 0;
		y = 0;
		w = 0;
		h = 0;
		r = 0;
		g = 0;
		b = 0;
	}

	//copy constructor

	Rect(float Ix, float Iy, float Iw, float Ih, float Ir, float Ig, float Ib)
	{
		x = Ix;
		y = Iy;
		w = Iw;
		h = Ih;
		r = Ir;
		g = Ig;
		b = Ig;
		leftwall = x;
		rightwall = x + w;
		cieling = y + h;
		floor = y;
	}
	void draw()
	{
		//begin drawing
		glBegin(GL_QUADS);

		//color of the rectangle
		glColor3d(r,g,b);

		//vertices of the rectangle
		glVertex2f(x, y);
		glVertex2f(x + w, y);
		glVertex2f(x + w, y + h);
		glVertex2f(x, y + h);

		//stop drawing
		glEnd();
	}
	void setColor(float Ir = 1, float Ig = 1, float Ib = 1)
	{
		r = Ir;
		g = Ig;
		b = Ib;
	}
	bool compare(Rect walrus)
	{
		return this->h < walrus.h;
	}
	bool contains(Vec peter)
	{
		return peter.x >= leftwall && peter.x <= rightwall && peter.y <= cieling && peter.y >= floor;
	}


	~Rect()
	{
		//ok i dont need this but it was maded so ima just leave it
	}

private:

};

