#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

// utils
#include "ghosts.h"
#include "intro.h"
#include "pacman.h"

int currentMenu = 0;
// Global variables for ball position and camera position
float ballX = 0.0f;
float ballY = 0.0f;
float ballZ = 1.0f;
float cameraX = -10.0f;
float cameraY = 8.0f;
float cameraZ = 11.0f;
int numGridlines = 50; // Number of gridlines to draw
float gridSize = 1.0f; // Size of each grid square
int mouthAaa = 0;      // Mouth open/close variable
int direction = 0;     // Direction of the pacman
int pelletBitmap[200][200];
int score = 0;
int lives = 3; // Number of lives Pac-Man has
float pelletY = 0.0f;
int numGhosts = 140; // Number of ghosts

Ghost ghosts[400]; // Array of ghosts
int decoy[400];    // Array to keep track of decoys

// Function to draw gridlines on the floor
void drawGridlines() {
  glColor3f(0.2f, 0.2f, 1.0f); // Set color to gray

  // Draw horizontal gridlines
  for (int i = -numGridlines; i <= numGridlines; i++) {
    glBegin(GL_LINES);
    glVertex3f(-numGridlines * gridSize, 0.0f, i * gridSize);
    glVertex3f(numGridlines * gridSize, 0.0f, i * gridSize);
    glEnd();
  }

  // Draw vertical gridlines
  for (int i = -numGridlines; i <= numGridlines; i++) {
    glBegin(GL_LINES);
    glVertex3f(i * gridSize, 0.0f, -numGridlines * gridSize);
    glVertex3f(i * gridSize, 0.0f, numGridlines * gridSize);
    glEnd();
  }
}

// Function to draw pellets randomly in grid
void drawPellets() {
  glColor3f(1.0f, 1.0f, 1.0f); // Set color to white

  for (int i = -numGridlines; i <= numGridlines; i++) {
    for (int j = -numGridlines; j <= numGridlines; j++) {
      if (pelletBitmap[i + numGridlines][j + numGridlines] == 1) {
        glPushMatrix();
        // glTranslatef(1.0f * i - 0.5f, pelletY, 1.0f * j - 0.5f);
        glTranslatef(1.0f * i, pelletY, 1.0f * j);
        glutSolidSphere(0.1f, 30, 30);
        glPopMatrix();
      }
    }
  }
}

void deployDecoys() {
  // randomly fill decoy array with 0s and 1s
  for (int i = 0; i < numGhosts; i++) {
    decoy[i] = rand() % 2;
  }
}

// Function to draw score and lives
void drawHUD() {
  // Draw score
  glColor3f(1.0f, 1.0f, 1.0f);
  glRasterPos3f(ballX - 0.5f, ballY + 1.1f, ballZ - 0.5f);
  char scoreText[50];
  sprintf(scoreText, "Score: %d", score);
  for (int i = 0; scoreText[i] != '\0'; i++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scoreText[i]);
  }

  // Draw lives
  /* glRasterPos3f(ballX - 0.5f, ballY + 0.8f, ballZ - 0.5f);
   char livesText[50];
   sprintf(livesText, "Lives: %d", lives);
   for (int i = 0; livesText[i] != '\0'; i++) {
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, livesText[i]);
   }*/

  // draw number of decoys
  glRasterPos3f(ballX - 0.5f, ballY + 0.8f, ballZ - 0.5f);
  char decoysText[50];
  int sum = 0;
  for (int i = 0; i < numGhosts; i++)
    sum += decoy[i];
  sprintf(decoysText, "Decoy percentage: %d %%", sum * 100 / numGhosts);
  for (int i = 0; decoysText[i] != '\0'; i++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, decoysText[i]);
  }
}

void initPacman() {
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

// Function to handle game over
void checkGameOver() {
  if (lives <= 0) {
    printf("Game Over! Your score: %d\n", score);
    currentMenu = 0;
    score = 0;
    lives = 3;
    ballX = 0.0f;
    ballY = 0.0f;
    ballZ = 1.0f;
    cameraX = -10.0f;
    cameraY = 8.0f;
    cameraZ = 11.0f;
    deployDecoys();
    initPacman();
  }
}

// Modify the drawScene function to include the gridlines, ghosts, and HUD
void drawScene() {
  // Clear the color and depth buffers
  if (currentMenu == 0) {
    // clear the screen
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    initOpenGL();
    display();
  } else {
    initPacman();
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // Set background color to blue
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Reset transformations
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Set the camera position and look at the ball from front
    gluLookAt(cameraX, cameraY, cameraZ, ballX, ballY, ballZ, 0.0f, 1.0f, 0.0f);
    // Draw the gridlines
    drawGridlines();
    // Draw the pellets
    drawPellets();
    // Draw the ghosts
    drawGhosts(ghosts, numGhosts);
    // Draw the HUD (score and lives)
    drawHUD();
    // Draw the pacman with eyes and mouth
    drawPacman(ballX, ballY, ballZ, mouthAaa, direction);

    // Swap buffers
    glutSwapBuffers();
  }
}

// Function to handle keyboard input
void handleKeypress(unsigned char key, int x, int y) {
  // Move the ball based on keyboard input
  if (currentMenu == 0) {
    keyboardFun(key, x, y);
  } else {
    if (key == 'w') {
      ballZ -= 0.2f;
      cameraZ -= 0.2f;
      direction = 3;
    } else if (key == 's') {
      ballZ += 0.2f;
      cameraZ += 0.2f;
      direction = 1;
    } else if (key == 'a') {
      ballX -= 0.2f;
      cameraX -= 0.2f;
      direction = 0;
    } else if (key == 'd') {
      ballX += 0.2f;
      cameraX += 0.2f;
      direction = 2;
    } else if (key == 'q') {
      ballY -= 0.1f;
      cameraY -= 0.1f;
    } else if (key == 'e') {
      ballY += 0.1f;
      cameraY += 0.1f;
    }
  }

  // print updated position od pacman
  printf("Pac-Man position updated: (%f, %f, %f)\n", ballX, ballY, ballZ);
  int sum = 0;
  for (int i = 0; i < numGhosts; i++)
    sum += decoy[i];
  printf("Number of decoys: %d\n", sum);

  // Redisplay the scene
  glutPostRedisplay();
}

// Function to handle window resizing
void handleResize(int w, int h) {
  // Set the viewport to the entire window
  glViewport(0, 0, w, h);

  // Set the perspective projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

// Function to open and close Pac-Man's mouth and move him
void mouthOpenClose() {
  // Open and close the mouth
  if (mouthAaa < 24) {
    mouthAaa++;
  } else {
    mouthAaa = 0;
  }

  // move pacman
  if (direction == 0) {
    ballX -= 0.05f;
    cameraX -= 0.05f;
  } else if (direction == 1) {
    ballZ += 0.05f;
    cameraZ += 0.05f;
  } else if (direction == 2) {
    ballX += 0.05f;
    cameraX += 0.05f;
  } else {
    ballZ -= 0.05f;
    cameraZ -= 0.05f;
  }

  // ease in out pelletY
  // if (pelletY < 0.1f) {
  //   pelletY += 0.05f;
  // } else if (pelletY > 1.8f) {
  //   pelletY -= 0.05f;
  // }

  // if pacman is on a pellet, eat it
  if (pelletBitmap[(int)ballX + numGridlines][(int)ballZ + numGridlines] == 1) {
    pelletBitmap[(int)ballX + numGridlines][(int)ballZ + numGridlines] = 0;
    score++;
    for (int i = 0; i < numGhosts; i++) {
      if (decoy[i] == 1) {
        decoy[i] = 0;
        break;
      }
    }
  }

  // Move ghosts
  moveGhosts(ghosts, numGhosts, ballX, ballZ, numGridlines, &lives,
             checkGameOver, decoy);

  // Redisplay the scene
  glutPostRedisplay();
}

void actualMenu(GLint selectedOption) {
  switch (selectedOption) {
  case 1:
    // glLoadIdentity();
    currentMenu = 1;
    score = 0;
    lives = 3;
    ballX = 0.0f;
    ballY = 0.0f;
    ballZ = 1.0f;
    cameraX = -10.0f;
    cameraY = 8.0f;
    cameraZ = 11.0f;
    deployDecoys();
    break;
  case 2:
    exit(0);
    break;
  }
  glutPostRedisplay();
}

int main(int argc, char **argv) {
  // Initialize GLUT and create a window
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  // glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(1000, 1000);
  glutCreateWindow("Pac-Man Game");
  glutTimerFunc(25, update, 0);
  // initOpenGL();

  // Enable depth testing for 3D rendering
  // glEnable(GL_DEPTH_TEST);
  //

  // Initialize ghosts
  initGhosts(ghosts, numGhosts, numGridlines);

  // init random pellet bitmap
  for (int i = 0; i < 200; i++) {
    for (int j = 0; j < 200; j++) {
      if (rand() % 10 == 0) {
        pelletBitmap[i][j] = 1;
      } else {
        pelletBitmap[i][j] = 0;
      }
    }
  }

  // print initial position of pacman
  printf("Initial Pac-Man position: (%f, %f, %f)\n", ballX, ballY, ballZ);

  // Set up callback functions
  glutDisplayFunc(drawScene);
  glutKeyboardFunc(handleKeypress);
  glutReshapeFunc(handleResize);
  glutIdleFunc(mouthOpenClose);

  glutCreateMenu(actualMenu);
  glutAddMenuEntry("START", 1);
  glutAddMenuEntry("EXIT", 2);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  // Enter the main loop
  glutMainLoop();

  return 0;
}
