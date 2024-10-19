#ifndef INTRO_H
#define INTRO_H
#include <GL/glut.h>

void drawPacman2D(float x, float y, float radius, float mouthOpen, int dir);
void drawText(const char *text, int x, int y);
void drawButton(const char *label, int x, int y, int width, int height);
void display();
void update(int value);
void initOpenGL();
void keyboardFun(GLubyte key, GLint x, GLint y);
void menu(GLint selectedOption);

#endif
