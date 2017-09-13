#include "App.h"
#include "RectStash.h"
#include <math.h>
#include <vector>
#include <algorithm>

//some places to put rectangles
std::vector<std::vector<Rect>> InsertSortVec;
std::vector<std::vector<Rect>> QSvec;
std::vector<std::vector<Rect>> BubbleVec;
std::vector<std::vector<Rect>> SelectionVec;
std::vector<Rect*> butVec;
Rect BigBoy(-1, 0, 2, 1, 0, 0, 0);

//some bools to handle what sorting algo we see
bool QSBool, InsertBool, BubbleBool, SelectionBool = false;

//initialize some vars to control the sorting
int toDraw = 0;
 
//vector to swap heights of rectangles
void swapH(std::vector<Rect>& vec, int x, int y)
{
	float xH, yH;

	xH = vec[x].h;
	yH = vec[y].h;

	vec[y].h = xH;
	vec[x].h = yH;

	return;
}

int partition(std::vector<Rect>& vec, int low, int high)
{
	//pivot selection/sorting mini algo
	Rect pivot = vec[ low ];
	int left = low;
	int right = high - 1;
	int j = low + 1;

	for (int i = low + 1; i < high; i++)
	{
		//the thing were comparing becomes green
		vec[j].setColor(0, 1, 0);

		//right becomes blue
		vec[right].setColor(1.0, 1.0, 0);

		//left becomes red
		vec[left].setColor(1, 0, 0);

		//save the new vector
		QSvec.push_back(vec);

		if( vec[j].compare(pivot) )
		{//put things less than the pivot on the left of the pivot
			swapH(vec, j, left);
			left++;
			vec[j].setColor(1, 1, 1);
			j++;
		}

		else
		{//put things bigger than the pivot to the right of the pivot
			swapH(vec, j, right);
			right--;
		}
		QSvec.push_back(vec);		
	}

	for (int i = low; i < vec.size(); i++)
	{
		vec[i].setColor(1, 1, 1);
	}

	QSvec.push_back(vec);

	return left;

}

void  bubbleSort() {
	int Row = 0;

	for (int i = 0; i < BubbleVec[0].size(); i++) {

		for (int j = 0; j < BubbleVec[0].size() - 1 - i; j++) {

			if (!BubbleVec[Row][j].compare(BubbleVec[Row][j + 1])) {

				BubbleVec.push_back(std::vector<Rect>());
				for (int k = 0; k < BubbleVec[0].size(); k++) {
					BubbleVec[Row + 1].push_back(BubbleVec[Row][k]);
				}
				Row++;

				std::swap(BubbleVec[Row][j].x, BubbleVec[Row][j + 1].x);
				std::swap(BubbleVec[Row][j], BubbleVec[Row][j + 1]);

				BubbleVec[Row][j].setColor(1, 0, 1);    //setColor
				BubbleVec[Row][j + 1].setColor(1, 0, 1);


				//   redraw();

			}
		}
	}

	for (int i = 0; i < BubbleVec[0].size(); i++) 
	{
		for (int j = 0; j < BubbleVec[0].size() - 1 - i; j++) {
			BubbleVec[Row][j].setColor(1, 1, 1);    //setColor
			BubbleVec[Row][j + 1].setColor(1, 1, 1);
		}
	}
}


void quicksort(std::vector<Rect>& vec, int low, int high)
{
	//sorting main branching algo
	int pivot = 0;
	if (low < high)
	{
		//find pivot
		pivot = partition(vec, low, high);

		//sort based on pivot
		quicksort(vec, low, pivot);
		quicksort(vec, pivot + 1, high);

	}
	return;
}

void insertionSort(std::vector<Rect> vec)
{
	int j;
	for (int i = 0; i < vec.size(); i++)
	{
		//set j to i
		//moves us towards the end of the vector
		j = i;
		while (j > 0 && vec[j].compare(vec[j - 1]))
		{
			//change the color of the swapping vectors
			vec[j].setColor(1, 0, 0);
			vec[j - 1].setColor(0, 1, 0);
			
			//store the to be swapped vecs 
			InsertSortVec.push_back(vec);

			//swap them
			swapH(vec, j, j - 1);

			//restore the vectors back to normal
			vec[j].setColor(1, 1, 1);
			vec[j - 1].setColor(1, 1, 1);

			//store the swapped vecs
			InsertSortVec.push_back(vec);

			

			//decrement so we can continue;
			j--;
		}
	}
}

void selectionSort(std::vector<Rect> vec)
{
	int i, j, min;
	// One by one move boundary of unsorted subarray
	for (i = 0; i < vec.size(); i++)
	{
		// Find the minimum element in unsorted array
		min = 5;
		vec[i].setColor(0, 1, 0);
		for (j = i + 1; j < vec.size(); j++)
		{
			vec[j].setColor(1, 0, 0);
			SelectionVec.push_back(vec);
			if (vec[j].compare(vec[min]))
			{
				vec[min].setColor(1, 1, 1);
				min = j;

			}
			vec[j].setColor(1, 1, 1);
			vec[min].setColor(1, 0, 0);
		}
		// Swap the found minimum element with the first element
		SelectionVec.push_back(vec);
		for (int nawp = 0; nawp < vec.size(); nawp++)
		{
			vec[i].setColor(1, 1, 1);
		}
		swapH(vec, i, min);

	}
}


App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h){
    // Initialize state variables
    mx = 0.0;
    my = 0.0;
	
	//Store buttons in a vec
	butVec.push_back(new Rect(-.6, -.25, .2, .1, 1, 0, 1));//QS 0
	butVec.push_back(new Rect(-.35, -.25, .2, .1, 0, 1, 0));//IS 1
	butVec.push_back(new Rect(.25, -.25, .2, .1, 1, 0, 0));//BS 2
	butVec.push_back(new Rect(.5, -.25, .2, .1, 1, 1, 1));//SS 3
	butVec.push_back(new Rect(.5, -.5, .2, .1, 1, 0, 1));//next 4
	butVec.push_back(new Rect(-.5, -.5, .2, .1, 1, 0, 1));//prev 5
	butVec.push_back(new Rect(-.75, -.5, .2, .1, 0, 1, 1));//tobegin 6
	butVec.push_back(new Rect(.75, -.5, .2, .1, 0, 1, 1));//toend 7
	butVec.push_back(new Rect(-.1, -.4, .2, .2, .5, 1, .5));//select 8
	
#if defined WIN32
	buttonN = loadTexture("..\\next.bmp");
	buttonP = loadTexture("..\\previous.bmp");
	buttonQ_sort = loadTexture("..\\QuickButton.bmp");
	buttonS_sort = loadTexture("..\\SelectionButton.bmp");
	buttonB_sort = loadTexture("..\\BubbleButton.bmp");
	buttonI_sort = loadTexture("..\\InsertionButton.bmp");
	buttonB = loadTexture("..\\beginning.bmp");
	buttonE = loadTexture("..\\end.bmp");
	buttonM = loadTexture("..\\menu.bmp");
	wall = loadTexture("..\\bluebackground.bmp");
#else
	buttonN = loadTexture("next.bmp");
	buttonP = loadTexture("previous.bmp");
	buttonQ_sort = loadTexture("QuickButton.bmp");
	buttonS_sort = loadTexture("SelectionButton.bmp");
	buttonB_sort = loadTexture("BubbleButton.bmp");
	buttonI_sort = loadTexture("InsertionButton.bmp");
	buttonB = loadTexture("beginning.bmp");
	buttonE = loadTexture("end.bmp");
	buttonM = loadTexture("menu.bmp");
	wall = loadTexture("bluebackground.bmp");
#endif

	//draw background
	background = new TexRect(-1, 1, 2, 2);
	//Create and draw the buttons
	buttonQuickSort = new TexRect(-.6, -.15, .2, .1, 128, 128, 128);
	buttonInsertionSort = new TexRect(-.35, -.15, .2, .1, 128, 128, 128);
	buttonBubbleSort = new TexRect(.25, -.15, .2, .1, 128, 128, 128);
	buttonSelectionSort = new TexRect(.5, -.15, .2, .1, 128, 128, 128);
	buttonNext = new TexRect(.5, -.4, .2, .1, 128, 128, 128);
	buttonPrevious = new TexRect(-.5, -.4, .2, .1, 128, 128, 128);
	buttonBeginning = new TexRect(-.75, -.4, .2, .1, 128, 128, 128);
	buttonEnd = new TexRect(.75, -.4, .2, .1, 128, 128, 128);
	buttonMenu = new TexRect(-.1, -.2, .2, .2, 128, 128, 128);
	background = new TexRect(-1, 1, 2, 2, 128, 128, 128);

	std::vector<Rect> tempVec;

	//create some new rectangles to be sorted
	for (float i = 0; i < 40; i++)
	{
		tempVec.push_back( Rect(-1 + (i*.05), 0, .05, rand() % 40 / (40.0), 1, 1, 1) );
	}
	
	//have the first iteration of all algorithms be the untouched vector
	InsertSortVec.push_back(tempVec);
	QSvec.push_back(tempVec);
	BubbleVec.push_back(tempVec);
	SelectionVec.push_back(tempVec);
	

	//insertion sort the vector
	insertionSort(tempVec);

	//bubblesort the vector
	bubbleSort();

	//selection sort the vector
	selectionSort(tempVec);

	//quicksort the vector
	quicksort(tempVec, 0, tempVec.size());
}


GLuint App::loadTexture(const char *filename) {
	GLuint texture_id;
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

	RgbImage theTexMap(filename);

	// Pixel alignment: each row is word aligned (aligned to a 4 byte boundary)
	//    Therefore, no need to call glPixelStore( GL_UNPACK_ALIGNMENT, ... );


	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);





	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(),
		GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData());

	return texture_id;

}

void App::draw() {

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Set background color to black
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    // Set up the transformations stack
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	
	//Draw the Rectangles
	if ( QSBool || InsertBool || BubbleBool || SelectionBool )
	{
		
		for (int i = 4; i < butVec.size(); i++)
		{
			//fetch the next rectangle to draw
			Rect* tempRect = butVec[i];
		}
		

		glBindTexture(GL_TEXTURE_2D, buttonN);
		buttonNext->draw();

		glBindTexture(GL_TEXTURE_2D, buttonP);
		buttonPrevious->draw();

		glBindTexture(GL_TEXTURE_2D, buttonM);
		buttonMenu->draw();

		glBindTexture(GL_TEXTURE_2D, buttonB);
		buttonBeginning->draw();

		glBindTexture(GL_TEXTURE_2D, buttonE);
		buttonEnd->draw();

		glDisable(GL_TEXTURE_2D);

		for (int i = 0; i < InsertSortVec[toDraw].size(); i++)
		{
			//fetch the next rectangle to draw
			Rect* tempRect = new Rect();
			if (QSBool)
			{
				tempRect = &QSvec[toDraw][i];
				
				glBindTexture(GL_TEXTURE_2D, buttonQ_sort);
				buttonQuickSort->draw();
				glDisable(GL_TEXTURE_2D);
				
			}
			else if (InsertBool)
			{
				tempRect = &InsertSortVec[toDraw][i];
				glBindTexture(GL_TEXTURE_2D, buttonI_sort);
				buttonInsertionSort->draw();
				glDisable(GL_TEXTURE_2D);
			}
			else if (BubbleBool)
			{
				tempRect = &BubbleVec[toDraw][i];
				glBindTexture(GL_TEXTURE_2D, buttonB_sort);
				buttonBubbleSort->draw();
				glDisable(GL_TEXTURE_2D);

			}
			else if (SelectionBool)
			{
				tempRect = &SelectionVec[toDraw][i];
				glBindTexture(GL_TEXTURE_2D, buttonS_sort);
				buttonSelectionSort->draw();
				glDisable(GL_TEXTURE_2D);
			}
			else
			{
				tempRect = &BigBoy;
			}

			//draw the rectangle
			(*tempRect).draw();


		}
	}
	
	else
	{	
		for (int i = 0; i < 4; i++)
		{
			//fetch the next rectangle to draw
			Rect* tempRect = butVec[i];
		}

		glBindTexture(GL_TEXTURE_2D, buttonQ_sort);
		buttonQuickSort->draw();

		glBindTexture(GL_TEXTURE_2D, buttonI_sort);
		buttonInsertionSort->draw();

		glBindTexture(GL_TEXTURE_2D, buttonB_sort);
		buttonBubbleSort->draw();

		glBindTexture(GL_TEXTURE_2D, buttonS_sort);
		buttonSelectionSort->draw();

		glDisable(GL_TEXTURE_2D);
	}
	glBindTexture(GL_TEXTURE_2D, wall);
	background->draw();
	glDisable(GL_TEXTURE_2D);
    // We have been drawing everything to the back buffer
    // Swap the buffers to see the result of what we drew
    glFlush();
    glutSwapBuffers();
}



void App::idle() 
{}

void App::mouseDown(float x, float y){
    // Update app state
    mx = x;
    my = y;

	Vec newVec(mx, my);

		
		//if the "QS" rectangle contains the point
		Rect* tempRect = butVec[0];
		if ((*tempRect).contains(newVec))
		{
			QSBool = true;
			SelectionBool = false;
			InsertBool = false;
			BubbleBool = false;
		}
		
		//if the "Insertion" rectangle contains the point
		tempRect = butVec[1];
		if ((*tempRect).contains(newVec))
		{
			InsertBool = true;
			SelectionBool = false;
			BubbleBool = false;
			QSBool = false;
		}

		//if the "Bubble" rectangle contains the point
		tempRect = butVec[2];
		if ((*tempRect).contains(newVec))
		{
			BubbleBool = true;
			SelectionBool = false;
			InsertBool = false;
			QSBool = false;
		}

		//if the "Selection" rectangle contains the point
		tempRect = butVec[3];
		if ((*tempRect).contains(newVec))
		{
			SelectionBool = true;
			InsertBool = false;
			BubbleBool = false;
			QSBool = false; 
		}

		// if the "next" rectangle contains the point
		tempRect = butVec[4];
		if ( (*tempRect).contains(newVec) )
		{
			if (QSBool)
			{
				if (toDraw < QSvec.size() - 1 )
				{
					toDraw++;
				}
			}
			else if (InsertBool)
			{
				if (toDraw < InsertSortVec.size() - 1)
				{
					toDraw++;
				}
			}
			else if (BubbleBool)
			{
				if (toDraw < BubbleVec.size() - 1)
				{
					toDraw++;
				}
			}
			else if (SelectionBool)
			{
				if (toDraw < SelectionVec.size() - 1)
				{
					toDraw++;
				}
			}
		}

		
		//if the "prev" rectangle contains the point
		tempRect = butVec[5];
		if ((*tempRect).contains(newVec))
		{
			if (toDraw != 0)
			{
				toDraw--;
			}
		}
		//if the "toBegin" rectangle contains the point
		tempRect = butVec[6];
		if ((*tempRect).contains(newVec))
		{
			toDraw = 0;
		}

		//if the "ToEnd" rectangle contains the point
		tempRect = butVec[7];
		if ((*tempRect).contains(newVec))
		{
			if (QSBool)
			{
				if (toDraw < QSvec.size() - 1)
				{
					toDraw = QSvec.size() - 1;
				}
			}
			else if (InsertBool)
			{
				if (toDraw < InsertSortVec.size() - 1)
				{
					toDraw = InsertSortVec.size() - 1;
				}
			}
			else if (BubbleBool)
			{
				if (toDraw < BubbleVec.size() - 1)
				{
					toDraw = BubbleVec.size() - 1;
				}
			}
			else if (SelectionBool)
			{
				if (toDraw < SelectionVec.size() - 1)
				{
					toDraw = SelectionVec.size() - 1;
				}
			}
		}

		//if the "Select Sort Screen" rectangle contains the point
		tempRect = butVec[8];
		if ( (*tempRect).contains(newVec) )
		{
			SelectionBool = false;
			InsertBool = false;
			BubbleBool = false;
			QSBool = false;
			toDraw = 0;
		}
		
    // Redraw the scene
    redraw();
}

void App::mouseDrag(float x, float y){
    // Update app state
    mx = x;
    my = y;
    
    // Redraw the scene
    redraw();
}

void App::keyPress(unsigned char key) {
    if (key == 27){
        // Exit the app when Esc key is pressed
		delete this;
        exit(0);
    }
}
