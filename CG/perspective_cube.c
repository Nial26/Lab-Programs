#include <stdio.h>
#include <GL/glut.h>

int axis = 1;
float theta[] = {0, 0, 0};
float viewer[] = {0, 0, 5};

float vertices[] = {-1, -1, -1,
                    1, -1, -1,
                    1, 1, -1,
                    -1, 1, -1,
                    -1, -1, 1,
                    1, -1, 1,
                    1, 1, 1,
                    -1, 1, 1};

float colors[] = {0, 0, 0,
                  0, 0, 1,
                  0, 1, 0,
                  0, 1, 1,
                  1, 0, 0,
                  1, 0, 1,
                  1, 1, 0,
                  1, 1, 1};

GLubyte cubeIndices[] = {0, 3, 2, 1,
                        1, 2, 6, 5,
                        4, 5, 6, 7,
                        4, 7, 3, 0,
                        7, 6, 2, 3,
                        0, 1, 5, 4};


void display(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(viewer[0], viewer[1], viewer[2], 0, 0, 0, 0, 1, 0);
    
    glRotatef(theta[0], 1, 0, 0);
    glRotatef(theta[1], 0, 1, 0);
    glRotatef(theta[2], 0, 0, 1);
   
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);

    glFlush();
    glutSwapBuffers();
}


void reshape(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if ( w <= h){
        glFrustum(-2, 2, -2.0*h/w, 2.0*h/w, -10, 10);
    }
    else{
        glFrustum(-2.0*w/h, 2.0*w/h, -2, 2, -10, 10);
    }
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y){
    if (key == 'X') viewer[0] += 1;
    if (key == 'x') viewer[0] -= 1;
    if (key == 'Y') viewer[1] += 1;
    if (key == 'y') viewer[1] -= 1;
    if (key == 'Z') viewer[2] += 1;
    if (key == 'z') viewer[2] -= 1;
    glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y){
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
    if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 1;
    if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 2;
    
    theta[axis] += 5;
    if (theta[axis] >= 360){
        theta[axis] -= 360;
    }
    glutPostRedisplay();

}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Perspective Cube");

    glEnable(GL_DEPTH_TEST);
    
    glClearColor(1, 1, 1, 1);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);

    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}

