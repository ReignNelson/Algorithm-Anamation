//
//  TexRect.hpp
//  glutapp
//
//  Created by Angelo Kyrilov on 4/11/17.
//  Copyright © 2017 Angelo Kyrilov. All rights reserved.
//

#ifndef TexRect_hpp
#define TexRect_hpp

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

class TexRect {
    float x;
    float y;
    float w;
    float h;
	float r, g, b;
    
public:
	TexRect(float x = 0, float y = 0, float w = 0.5, float h = 0.5, float r = 128, float g = 128, float b = 128) {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
		this->r = r;
		this->g = g;
		this->b = b;
    }
    
    
    void draw(){
        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        
        glBegin(GL_QUADS);
		glColor3d(r, g, b);

        glTexCoord2f(0.0, 0.0);
        glVertex2f(x, y - h);
        
        glTexCoord2f(0.0, 1.0);
        glVertex2f(x, y);
        
        glTexCoord2f(1.0, 1.0);
        glVertex2f(x+w, y);
        
        glTexCoord2f(1.0, 0.0);
        glVertex2f(x+w, y - h);
        
        glEnd();
        
        glDisable(GL_TEXTURE_2D);
    }
};

#endif /* TexRect_hpp */
