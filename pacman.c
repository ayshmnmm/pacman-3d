#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#include "pacman.h"

// Function to draw pacman
void drawPacman(float ballX, float ballY, float ballZ, int mouthAaa, int direction) {
    // Draw the pacman manually as a spphere with a slice cut out
    glPushMatrix();

    // Draw the sphere
    glTranslatef(ballX, ballY, ballZ);

    float radius = 0.5f;
    int slices = 200;
    int stacks = 20;

    if (direction == 1) {
        glRotatef(90, 0.0f, 1.0f, 0.0f);
    } else if (direction == 2) {
        glRotatef(180, 0.0f, 1.0f, 0.0f);
    } else if (direction == 3) {
        glRotatef(270, 0.0f, 1.0f, 0.0f);
    }


    // Draw the sphere with shading from yellow in front to dark yellow in back
    for (int i = 0; i <= slices; i++) {
        float theta1 = i * 2 * 3.14 / slices;
        float theta2 = (i + 1) * 2 * 3.14 / slices;

        // Set the color - black for mouth
        if  (i> slices / 2 - mouthAaa && i < slices / 2 + mouthAaa) {
            glColor3f(0.0f, 0.0f, 0.0f);
        } else {
            glColor3f(1.0f, 1.0f, 0.0f);
        }

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= stacks; j++) {
            float phi = j * 3.14 / stacks;
            float x1 = radius * cos(theta2) * sin(phi);
            float y1 = radius * sin(theta2) * sin(phi);
            float z1 = radius * cos(phi);
            float x2 = radius * cos(theta1) * sin(phi);
            float y2 = radius * sin(theta1) * sin(phi);
            float z2 = radius * cos(phi);

            glVertex3f(x1, y1, z1);
            glVertex3f(x2, y2, z2);
        }
        glEnd();
    }


    // Draw eyes
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(-0.1f, 0.3f, 0.3f);
    glutSolidSphere(0.1f, 50, 50);

    glTranslatef(0.0f, 0.0f, -0.6f);
    glutSolidSphere(0.1f, 50, 50);

    glPopMatrix();


}
