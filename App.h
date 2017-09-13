#ifndef App_hpp
#define App_hpp

#include "GlutApp.h"
#include "RgbImage.h"
#include "TexRect.hpp"

class App: public GlutApp {
    // Maintain app state here
    float mx;
    float my;
public:
    // Constructor, to initialize state
    App(const char* label, int x, int y, int w, int h);
    
    // These are the events we want to handle
    void draw();
	void idle();
    void keyPress(unsigned char key);
    void mouseDown(float x, float y);
    void mouseDrag(float x, float y);

	GLuint loadTexture(const char* filename);

	//file name
	GLuint buttonN;
	GLuint buttonP;
	GLuint buttonM;
	GLuint buttonE;
	GLuint buttonB;
	GLuint buttonQ_sort;
	GLuint buttonI_sort;
	GLuint buttonS_sort;
	GLuint buttonB_sort;
	GLuint wall;


	TexRect* buttonNext;
	TexRect* buttonPrevious;
	TexRect* buttonBeginning;
	TexRect* buttonEnd;
	TexRect* buttonMenu;
	TexRect* buttonQuickSort;
	TexRect* buttonInsertionSort;
	TexRect* buttonSelectionSort;
	TexRect* buttonBubbleSort;
	TexRect* button;
	TexRect* background;

};

#endif
