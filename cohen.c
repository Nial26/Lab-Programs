#include <stdio.h>
#include <GL/glut.h>

#define outcode int
#define bool int

#define true 1
#define false 0

outcode LEFT = 1, RIGHT = 2, BOTTOM = 4, TOP = 8;


float xmin = 10, ymin = 10, xmax = 100, ymax = 100;
float xvmin = 300, yvmin = 300, xvmax = 450, yvmax = 450;


outcode computeOutcode(float x, float y){
    outcode out = 0;
    if ( x < xmin) out |= LEFT;
    if ( x > xmax) out |= RIGHT;
    if ( y < ymin) out |= BOTTOM;
    if ( y > ymax) out |= TOP;
    return out;
}

void clipAndDraw(float x0, float y0, float x1, float y1){
    outcode outcode0, outcode1, outcodeout;
    bool done = false, accept = false;
    float x, y;

    outcode0 = computeOutcode(x0, y0);
    outcode1 = computeOutcode(x1, y1);

    while (!done){
        if (!(outcode0 | outcode1)){ // Both Points are inside the center frame
            done = true;
            accept = true;
        }
        else if (outcode0 & outcode1){ //Both points are outside and the line through them doesn't pass through the center frame
            done = true;
        }
        else{
            outcodeout = outcode0 ? outcode0 : outcode1 ;

            if (outcodeout & TOP){
                x = x0 + (ymax -y0)/(y1 - y0)*(x1 - x0);
                y = ymax;
            }
            if (outcodeout & BOTTOM){
                x = x0 + (ymin -y0)/(y1 - y0)*(x1 - x0);
                y = ymin;
            }
            if (outcodeout & RIGHT){
                y = y0 + (xmax - x0)/(x1 - x0)*(y1 -y0);
                x = xmax;
            }
            if (outcodeout & LEFT){
                y = y0 + (xmax - x0)/(x1 - x0)*(y1 - y0);
                x = xmin;
            }
            if (outcodeout == outcode0){
                x0 = x;
                y0 = y;
                outcode0 = computeOutcode(x0, y0);
            }
            else{
                x1 = x;
                y1 = y;
                outcode1 = computeOutcode(x1, y1);
            }
        }
    }
    if (accept){
        glColor3f(0, 1, 0);
        glBegin(GL_LINE_LOOP);
            glVertex2f(xvmin, yvmin);
            glVertex2f(xvmax, yvmin);
            glVertex2f(xvmax, yvmax);
            glVertex2f(xvmin, yvmax);
        glEnd();
        
        float sx, sy; 
        float vx0, vx1, vy0, vy1;

        sx = (xvmax - xvmin)/(xmax - xmin);
        sy = (yvmax - yvmin)/(ymax - ymin);
        
        vx0 = xvmin + (x0 - xmin)*sx; //add to xvmin the scaled distance between original point and original box min
        vy0 = yvmin + (y0 - ymin)*sy;
        vx1 = xvmin + (x1 - xmin)*sx;
        vy1 = yvmin + (y1 - ymin)*sy;

        glColor3f(0, 0, 0);
        glBegin(GL_LINES);
            glVertex2f(vx0, vy0);
            glVertex2f(vx1, vy1);
        glEnd();
    }

}


void display(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(xmin, ymin);
        glVertex2f(xmax, ymin);
        glVertex2f(xmax, ymax);
        glVertex2f(xmin, ymax);
    glEnd();

    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
        
        glVertex2f(20, 0);
        glVertex2f(125, 130);

        glVertex2f(12, 5);
        glVertex2f(130, 124);

    glEnd();
    
    clipAndDraw(20, 0, 125, 130);
    clipAndDraw(12, 5, 130, 124);

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
    glutCreateWindow("Cohen Sutherland Line Clipping");

    init();
    
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
