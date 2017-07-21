#include <stdio.h>
#include <GL/glut.h>

float xmin = 10, ymin = 10, xmax = 100, ymax = 120;
float xvmin = 300, yvmin = 300, xvmax = 400, yvmax = 450;

int clipTest(float p, float q, float *t1, float *t2){
    float t = q/p;
    if (p < 0){
        if (t > *t1)
            *t1 = t;
        if (t > *t2)
            return 0;
    }
    if (p > 0){
        if (t < *t2)
            *t2 = t;
        if (t < *t1)
            return 0;
    }
    if (p == 0){
        if ( q < 0)
            return 0;
    }
    return 1;
}

void clipAndDraw(float x0, float y0, float x1, float y1){
    float dx = x1 - x0, dy = y1 - y0, tc = 0, t1 = 1;
    if (clipTest(-dx, x0-xmin, &tc, &t1) && 
        clipTest(dx, xmax -x0, &tc, &t1) &&
        clipTest(-dy, y0 -ymin, &tc, &t1) &&
        clipTest(dy, ymax - y0, &tc, &t1)){
        
        if (t1 < 1){
            x1 = x0 + t1 * dx;
            y1 = y0 + t1 * dy;
        }
        if (tc > 0){
            x0 = x0 + tc * dx;
            y0 = y0 + tc * dy;
        }
        
        float vx0, vy0, vx1, vy1;
        float sx, sy;

        sx = (xvmax - xvmin)/(xmax - xmin);
        sy = (yvmax - yvmin)/(ymax - ymin);

        vx0 = xvmin + (x0 - xmin)*sx;
        vy0 = yvmin + (y0 - ymin)*sy;
        vx1 = xvmin + (x1 - xmin)*sx;
        vy1 = yvmin + (y1 - ymin)*sy;

        glColor3f(0, 1, 0);
        glBegin(GL_LINE_LOOP);
            glVertex2f(xvmin, yvmin);
            glVertex2f(xvmax, yvmin);
            glVertex2f(xvmax, yvmax);
            glVertex2f(xvmin, yvmax);
        glEnd();

        glColor3f(0, 0, 0);
        glBegin(GL_LINES);
            glVertex2f(vx0, vy0);
            glVertex2f(vx1, vy1);
        glEnd();
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(xmin, ymin);
        glVertex2f(xmax, ymin);
        glVertex2f(xmax, ymax);
        glVertex2f(xmin, ymax);
    glEnd();

    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
        glVertex2f(4, 3);
        glVertex2f(124, 89);

        glVertex2f(12, 43);
        glVertex2f(143, 141);
    glEnd();

    clipAndDraw(4, 3, 124, 89);
    clipAndDraw(12, 43, 143, 141);

    glFlush();
}
        

void init(){
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Liang Barsky Clipping Algorithm");

    init();
    
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
