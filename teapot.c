#include <stdio.h>
#include <GL/glut.h>

void wall(float thickness){
    glPushMatrix();
    glTranslated(0.5, 0.5*thickness, 0.5);
    glScaled(1, thickness, 1);
    glutSolidCube(1);
    glPopMatrix();
}

void tableleg(float thickness, float length){
    glPushMatrix();
    glTranslated(0, length/2, 0);
    glScaled(thickness, length, thickness);
    glutSolidCube(1);
    glPopMatrix();
}

void table(float topw, float topt, float legt, float legl){
    
    glPushMatrix();
    glTranslated(0, legl, 0);
    glScaled(topw, topt, topw);
    glutSolidCube(1);
    glPopMatrix();

    float dist = topw/2 - legt/2;

    glPushMatrix();
    
    glTranslated(dist, 0, dist);
    tableleg(legt, legl);

    glTranslated(0, 0, -2*dist);
    tableleg(legt, legl);

    glTranslated(-2*dist, 0, 2*dist);
    tableleg(legt, legl);

    glTranslated(0, 0, -2*dist);
    tableleg(legt, legl);

    glPopMatrix();
}


void display(){
    float mat_ambient[] = {0.7, 0.7, 0.7, 1},
          mat_diffuse[] = {0.5, 0.5, 0.5, 1},
          mat_specular[] = {1, 1, 1, 1},
          mat_shininess[] = {50};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    float light_pos[] = {2, 6, 3, 1}, light_diffuse[] = {0.7, 0.7, 0.7, 1};
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-64/48.0, 64/48.0, -1, 1, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(2, 1, 2, 0, 0, 0, 0, 1, 0);

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

//------------Teapot----------------------
    glPushMatrix();
    glTranslated(0.6, 0.3, 0.5);
    glRotated(30, 0, 1, 0);
    glutSolidTeapot(0.08);
    glPopMatrix();

//--------------Wall------------------------
    glPushMatrix();
    glRotated(90, 0, 0, 1);
    wall(0.01);
    glPopMatrix();

    wall(0.01);

    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    wall(0.01);
    glPopMatrix();

//-------------Table-------------------------
    
    glPushMatrix();
    glTranslated(0.4, 0, 0.4);
    table(0.6, 0.02, 0.02, 0.2);
    glPopMatrix();
    
    glFlush();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Teapot");
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glShadeModel(GL_SMOOTH);

    glClearColor(1, 1, 1, 1);
    glViewport(0, 0, 640, 480);

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
