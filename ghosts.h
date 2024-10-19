#ifndef GHOSTS_H
#define GHOSTS_H

// Structure for Ghosts
typedef struct {
  float x, y, z;
  int direction;
} Ghost;

void initGhosts(Ghost ghosts[], int numGhosts, int numGridlines);
void drawGhosts(Ghost ghosts[], int numGhosts);
void moveGhosts(Ghost ghosts[], int numGhosts, float ballX, float ballZ,
                int numGridlines, int *lives, void (*checkGameOver)(),
                int decoy[]);

#endif // GHOSTS_H
