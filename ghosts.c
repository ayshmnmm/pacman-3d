#include "ghosts.h"
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

void initGhosts(Ghost ghosts[], int numGhosts, int numGridlines) {
  for (int i = 0; i < numGhosts; i++) {
    ghosts[i].x = rand() % (2 * numGridlines) - numGridlines;
    ghosts[i].y = 0.0f;
    ghosts[i].z = rand() % (2 * numGridlines) - numGridlines;
    ghosts[i].direction = rand() % 4;
    printf("Ghost %d initialized at (%f, %f, %f)\n", i, ghosts[i].x,
           ghosts[i].y, ghosts[i].z);
  }
}

void drawGhosts(Ghost ghosts[], int numGhosts) {
  glColor3f(1.0f, 0.0f, 0.0f); // Setting  color to red

  for (int i = 0; i < numGhosts; i++) {
    glPushMatrix();
    glTranslatef(ghosts[i].x, ghosts[i].y, ghosts[i].z);
    glutSolidSphere(0.5f, 30, 30);
    glPopMatrix();
    // printf("Drawing ghost %d at (%f, %f, %f)\n", i, ghosts[i].x, ghosts[i].y,
    // ghosts[i].z);
  }
}

void moveGhosts(Ghost ghosts[], int numGhosts, float ballX, float ballZ,
                int numGridlines, int *lives, void (*checkGameOver)(),
                int decoy[]) {
  for (int i = 0; i < numGhosts; i++) {
    if (ghosts[i].direction == 0) {
      ghosts[i].x -= 0.25f;
    } else if (ghosts[i].direction == 1) {
      ghosts[i].z += 0.25f;
    } else if (ghosts[i].direction == 2) {
      ghosts[i].x += 0.25f;
    } else {
      ghosts[i].z -= 0.25f;
    }

    // Change direction randomly
    if (rand() % 10 == 0) {
      ghosts[i].direction = rand() % 4;
    }

    // Checking for collision with Pac-Man
    if (abs(ghosts[i].x - ballX) < 0.5f && abs(ghosts[i].z - ballZ) < 0.5f) {
      (*lives)--;
      if (!decoy[i]) {
        checkGameOver();
      }
      ballX = 0.0f;
      ballZ = 1.0f; // Reset Pac-Man position

      // Ensure ghosts stay within bounds
      if (ghosts[i].x < -numGridlines || ghosts[i].x > numGridlines) {
        ghosts[i].direction =
            (ghosts[i].direction + 2) % 4; // Reverse direction
      }
      if (ghosts[i].z < -numGridlines || ghosts[i].z > numGridlines) {
        ghosts[i].direction =
            (ghosts[i].direction + 2) % 4; // Reverse direction
      }
    }
  }
}
