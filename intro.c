#include <GL/glut.h>
#include <math.h>
#include <string.h>

#define PI 3.14159265
float mouthAngle = 45.0;
int mouthOpening = 1;
float pacmanX = -900.0;
float pacmanY = -900.0;
int direc = 0.0; // 0: right, 1: up, 2: left, 3: down
int moving = 0.0;

void drawPacman2D(float x, float y, float radius, float mouthOpen, int dir) {
  glBegin(GL_TRIANGLE_FAN);
  switch (dir) {
  case 0:
    glColor3f(255, 255, 0);
    break;
  case 1:
    glColor3f(255, 0, 255);
    break;
  case 2:
    glColor3f(0, 255, 0);
    break;
  case 3:
    glColor3f(0, 0, 255);
    break;
  }
  glVertex2f(x, y);

  float startAngle, endAngle;
  switch (dir) {
  case 0: // right
    startAngle = mouthOpen;
    endAngle = 360 - mouthOpen;
    break;
  case 1: // up
    startAngle = 90 + mouthOpen;
    endAngle = 450 - mouthOpen;
    break;
  case 2: // left
    startAngle = 180 + mouthOpen;
    endAngle = 540 - mouthOpen;
    break;
  case 3: // down
    startAngle = 270 + mouthOpen;
    endAngle = 630 - mouthOpen;
    break;
  }

  for (float angle = startAngle; angle <= endAngle; angle += 1.0) {
    float rad = angle * PI / 180.0;
    glVertex2f(x + cos(rad) * radius, y + sin(rad) * radius);
  }
  glEnd();
}

void drawText(const char *text, int x, int y) {
  glRasterPos2i(x, y);
  // Draw the text
  for (int i = 0; i < strlen(text); ++i) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
  }
}

void drawButton(const char *label, int x, int y, int width, int height) {
  glColor3f(0.7, 0.7, 0.7);
  glBegin(GL_QUADS);
  glVertex2i(x, y);
  glVertex2i(x + width, y);
  glVertex2i(x + width, y + height);
  glVertex2i(x, y + height);
  glEnd();

  glColor3f(0.0, 0.0, 0.0);
  drawText(label, x + 10, y + 10);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(1.1, 0.0, 1.1);
  drawText("CAMBRIDGE INSTITUTE OF TECHNOLOGY BANGALORE", -700.0, 700);
  glColor3f(1.1, 1.0, 0.0);
  drawText("WELCOME TO CG PROJECT", -400.0, 500);
  drawText("PACMAN GAMING", -300.0, 410);

  glColor3f(0.0, 1.0, 0.0);
  drawText("___________________________________________", -1000.0, 400);

  glColor3f(0.0, 1.0, 1.0);
  drawText("BY:", -300.0, 200.0);
  drawText("B.Harish kumar", -200.0, 100);
  drawText("Anuradha M", -200.0, -0.0);
  drawText("Ayushman Muduli", -200.0, -100);
  drawText("Mohammed Abyan", -200.0, -200);

  glColor3f(0.0, 0.0, 1.0);
  drawText("Guided by", 200.0, -400);

  glColor3f(1.0, 1.0, 1.0);
  drawText("Priyadharshini", 300.0, -500);
  drawText("Assistant.Prof CSE department", 300.0, -600);

  glColor3f(1.0, 0.0, 0.0);
  drawText("To move pacamn press r(right),l(left),up(u),down(d) ", -60.0, -800);

  drawPacman2D(pacmanX, pacmanY, 100.0, mouthAngle, direc);

  glutSwapBuffers();
}

void update(int value) {
  if (mouthOpening) {
    mouthAngle -= 1.0;
    if (mouthAngle <= 0) {
      mouthOpening = 0;
    }
  } else {
    mouthAngle += 1.0;
    if (mouthAngle >= 45.0) {
      mouthOpening = 1;
    }
  }

  if (moving) {
    float speed = 10.0;

    switch (direc) {

    case 0: // Move right
      pacmanX += speed;
      if (pacmanX >= 900) { // Right edge
        pacmanX = 900;
      }
      break;
    case 1: // Move up
      pacmanY += speed;
      if (pacmanY >= 900) { // Top edge
        pacmanY = 900;
      }
      break;
    case 2: // Move left
      pacmanX -= speed;
      if (pacmanX <= -900) { // Left edge
        pacmanX = -900;
      }
      break;
    case 3: // Move down
      pacmanY -= speed;
      if (pacmanY <= -900) { // Bottom edge
        pacmanY = -900;
      }
      break;
    }
  }

  glutPostRedisplay();
  glutTimerFunc(25, update, 0);
}

void initOpenGL() {
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-1000, 1000, -1000, 1000);
}
void keyboardFun(GLubyte key, GLint x, GLint y) {
  switch (key) {
  case 'u':

    direc = 1;
    break;
  case 'l':
    direc = 2;
    break;
  case 'd':
    direc = 3;
    break;
  case 'r':
    moving = 1.1;
    direc = 0;
    break;
  }
  glFlush();
}

void menu(GLint selectedOption) {
  switch (selectedOption) {
  case 1:
    moving = 1;
    break;
  case 2:
    exit(0);
    break;
  }
  glutPostRedisplay();
}
// int main(int argc, char **argv) {
//     glutInit(&argc, argv);
//     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//     glutInitWindowSize(1000, 1000);
//     glutCreateWindow("Pacman");
//      glutTimerFunc(25, update, 0);
//     initOpenGL();
//     glutDisplayFunc(display);
//     glutKeyboardFunc(keyboardFun);
//     glutCreateMenu(menu);
// 		glutAddMenuEntry("START",1);
// 		glutAddMenuEntry("EXIT",2);
// 	glutAttachMenu(GLUT_RIGHT_BUTTON);
//     glutMainLoop();
//     return 0;
// }
