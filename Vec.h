

class Vec {



public:



	static Vec null;

	float x, y;

	Vec()
	{
		x = 0;
		y = 0;
	}

	Vec(float Ix, float Iy)
	{
		x = Ix;
		y = Iy;
	}

	void print()
	{
		//std::cout << "(" << x << ", " << y << ")" << std::endl;
	}

	void add(Vec IVector)
	{
		x += IVector.x;
		y += IVector.y;
	}

};
//Vec Vec::null(0, 0);
