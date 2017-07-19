#include <stdio.h>
#include <GL/glut.h>

#define dx 10
#define dy 10

#define nx 10
#define ny 20

void init(){
    glClearColor(1, 1, 1, 1);
    glColor3f(1, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    int i , j;
    for (i = 10; i < nx*dx + 10; i+= dx){
        for (j = 10; j < ny*dy + 10; j+= dy){
            glBegin(GL_LINE_LOOP);
            glVertex2f(i, j);
            glVertex2f(i+dx, j);
            glVertex2f(i+dx, j+dy);
            glVertex2f(i, j+dy);
            glEnd();
        }}

    glFlush();
}


int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Mesh");

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}

